---
layout: post
title: XINPUT and XAudio2
date: 2012-05-02 17:08
author: Chuck Walbourn
comments: true
categories: [audio, input, win8]
---
In an earlier [post](https://walbourn.github.io/xinput-and-windows-8-consumer-preview), I covered how to use XInput with the release of the Windows 8 Consumer Preview. In this post, I'll discuss how to make use of headset audio for the Xbox 360 Common Controller.
<!--more-->

<strong>Update:</strong> This advice also applies to the [Windows 8 Release Preview](https://walbourn.github.io/windows-8-release-preview-and-gdfs) / RTM and [Visual Studio 2012 RC](https://walbourn.github.io/visual-studio-2012-release-candidate) / RTM.

XInput 1.4 and XAudio2.8 in the Windows 8 Consumer Preview are designed to integrate well together. The code for creating an XAudio2 device for the headset on a Xbox 360 Common Controller is fairly simple as both are designed to return and consume WinRT style device identifiers:

```cpp
#if (_WIN32_WINNT >= 0x0602 /*_WIN32_WINNT_WIN8*/)
WCHAR renderID[256] = {};
WCHAR captureID[256] = {};
UINT renderCount = 256;
UINT captureCount = 256;

XInputGetAudioDeviceIds( 0, renderID, &renderCount, captureID, &;captureCount );

IXAudio2* pXAudio2 = nullptr;
if ( *renderID != 0 && SUCCEEDED( XAudio2Create( &pXAudio2, 0 ) ) )
{
  IXAudio2MasteringVoice* pMasteringVoice = nullptr;
  if ( SUCCEEDED( pXAudio2->CreateMasteringVoice( &pMasteringVoice, 0, 0, 0, renderID ) ) )
  {
#else
```

The older XInput 1.3 was designed to work with DirectSound and returns DirectSound device GUIDs.

```cpp
GUID render = {};
GUID capture = {};
XInputGetDSoundAudioDeviceGuids( 0, &render, &capture );
```
Using XInput 1.3 with XAudio 2.7 together is a little more work:

```cpp
WCHAR renderID[256] = {};
DSoundtoMMEndpoint( render, renderID, 256, false );

WCHAR captureID[256] = {};
DSoundtoMMEndpoint( capture, captureID, 256, true );

IXAudio2* pXAudio2 = nullptr;
if ( SUCCEEDED( XAudio2Create( &pXAudio2, 0 ) ) )
{
  UINT count = 0;
  pXAudio2->GetDeviceCount( &count );
  UINT index = 0;
  for( ; index < count; ++index )
  {
    XAUDIO2_DEVICE_DETAILS details;
    pXAudio2->GetDeviceDetails( index, &details );

    if ( ::_wcsnicmp( details.DeviceID, renderID, 256 ) == 0 )
      break;
  }

  if ( index < count )
  {
    IXAudio2MasteringVoice* pMasteringVoice = nullptr;
    if ( SUCCEEDED( pXAudio2->CreateMasteringVoice( &pMasteringVoice, 0, 0, 0, index ) ) )
    {
```

This code assumes you are only supporting Windows Vista or later which supports WASAPI. If you still need to support Windows XP, you need to add an additional comparison in the search loop over XAudio2 device details values in the code above. On Windows XP, the deviceID from XAudio2 is a DirectSound GUID, while on Windows Vista and later it is a WASAPI Audio Endpoint Device Identifier.

```cpp
#if (_WIN32_WINNT < _WIN32_WINNT_VISTA)
WCHAR szDSGUID[40] = {};
swprintf_s( szDSGUID, L"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}\n",
  render.Data1, render.Data2, render.Data3,
  render.Data4[0], render.Data4[1], render.Data4[2], render.Data4[3],
  render.Data4[4], render.Data4[5], render.Data4[6], render.Data4[7] );
#endif

...

#if (_WIN32_WINNT < _WIN32_WINNT_VISTA)
if ( ::_wcsnicmp( details.DeviceID, szDSGUID, 40 ) == 0 )
  break;
#endif
```

The key work here takes place in <code>DSoundtoMMEndpoint</code> using WASAPI APIs and properties.

> Note that this function assumes you already iniitalized COM via <code>CoInitializeEx</code>.

```cpp
bool DSoundtoMMEndpoint(const GUID& guid, WCHAR* id, size_t maxsize, bool capture)
{
    if (memcmp(&guid, &GUID_NULL, sizeof(GUID)) == 0)
        return false;

    IMMDeviceEnumerator* pEnumerator = nullptr;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    if (SUCCEEDED(hr))
    {
        IMMDeviceCollection* pCollection = nullptr;
        hr = pEnumerator->EnumAudioEndpoints((capture) ? eCapture : eRender, DEVICE_STATE_ACTIVE, &pCollection);

        if (SUCCEEDED(hr))
        {
            WCHAR szDSGUID[40] = {};
            swprintf_s(szDSGUID, L"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}\n",
                guid.Data1, guid.Data2, guid.Data3,
                guid.Data4[0], .Data4[1], guid.Data4[2], guid.Data4[3],
                guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

            UINT count = 0;
            pCollection->GetCount(& count);

            UINT index = 0;
            for (; index < count; ++index)
            {
                IMMDevice* pDevice = nullptr;
                hr = pCollection->Item(index, &pDevice);
                if (SUCCEEDED(hr))
                {
                    IPropertyStore* pProps = nullptr;
                    hr = pDevice->OpenPropertyStore(STGM_READ, &pProps);
                    if (SUCCEEDED(hr))
                    {
                        PROPVARIANT varName;
                        PropVariantInit(&varName);
                        hr = pProps->GetValue(PKEY_AudioEndpoint_GUID, &varName);
                        if (SUCCEEDED(hr) && ::_wcsnicmp(szDSGUID, varName.pwszVal, 38) == 0)
                        {
                            LPWSTR pStrId = nullptr;
                            hr = pDevice->GetId(&pStrId);
                            if (SUCCEEDED(hr))
                            {
                                wcscpy_s(id, maxsize, pStrId);
                                CoTaskMemFree(pStrId);
                                break;
                            }
                        }

                        PropVariantClear(& varName);
                        pProps->Release();
                    }

                    pDevice->Release();
                }
            }

            if (index <= count)
                hr = E_FAIL;

            pCollection->Release();
        }

        pEnumerator->Release();
    }

    return SUCCEEDED(hr);
}
```

The legacy XInput 9.1.0 doesn't support headset audio, so if you make use of audio features for XInput devices you'll have to use either the Windows 8 in box XInput 1.4 or the legacy DirectX SDK XInput 1.3 release.

In a future post I'll cover how to make use of the capture device given that XAudio2 doesn't support audio capture. We'll make use of the new <a href="https://docs.microsoft.com/en-us/uwp/api/Windows.Media.Capture">MediaCapture</a> API on Windows 8, and the venerable <code>waveIn</code> otherwise.
