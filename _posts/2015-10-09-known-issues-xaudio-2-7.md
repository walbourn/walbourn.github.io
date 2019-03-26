---
layout: post
title: Known Issues - XAudio 2.7
date: 2015-10-09 11:08
author: Chuck Walbourn
comments: true
categories: [audio, dxsdk]
---
The XAudio2 library in the <a href="https://walbourn.github.io/where-is-the-directx-sdk-2015-edition/">legacy DirectX SDK</a> makes use of COM creation and reference counting for lifetime management, and a recent investigation has found a problem in this implementation. In short: in some situations the XAudio DLL itself is unloaded before the XAudio2 objects are completely destroyed, thus leading to an access violation. This normally happens on exit, although the exact details of when it might be evident depends on exactly which version of Windows you are using and the overall process layout for your application.
<!--more-->

<em>This issue does not affect XAudio 2.8 (Windows 8 SDK), XAudio 2.9 (Windows 10 SDK), XAudio2 on Xbox 360, or XAudio2 on Xbox One.</em>

An application level workaround is very easy to implement, and is already implemented in <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectX Tool Kit for Audio</a> and in the XAudio2 DirectX SDK refreshed samples on <a href="https://github.com/walbourn/directx-sdk-samples">GitHub</a>.

Before your first XAudio object creation, you should create an explicit reference to the DLL and hold on to it.

```cpp
#if ( _WIN32_WINNT < 0x0602 /*_WIN32_WINNT_WIN8*/)
HMODULE g_XAudioDLL = nullptr;
#endif
```

```cpp
#if ( _WIN32_WINNT < 0x0602 /*_WIN32_WINNT_WIN8*/)
#ifdef _DEBUG
g_XAudioDLL = LoadLibraryExW( L"XAudioD2_7.DLL", nullptr, 0x00000800 /* LOAD_LIBRARY_SEARCH_SYSTEM32 */ );
#else
g_XAudioDLL = LoadLibraryExW( L"XAudio2_7.DLL", nullptr, 0x00000800 /* LOAD_LIBRARY_SEARCH_SYSTEM32 */ );
#endif
if ( !mXAudioDLL )
    // error
#endif
```

```cpp
DWORD creationFlags = 0;
#if (_WIN32_WINNT < 0x0602 /*_WIN32_WINNT_WIN8*/) && defined(_DEBUG)
creationFlags |= XAUDIO2_DEBUG_ENGINE;
#endif
IXAudio2* pXAudio2 = nullptr;
HRESULT hr = XAudio2Create( &pXAudio2, creationFlags, XAUDIO2_DEFAULT_PROCESSOR );
if ( FAILED(hr) )
```

From here on, you work with XAudio2 as normal, delete objects, etc. Later after you do all cleanup and are fully done with working with XAudio2, you release the "extra" DLL reference:

```cpp
if (pXAudio2)
    pXAudio2->Release();

#if ( _WIN32_WINNT < 0x0602 /*_WIN32_WINNT_WIN8*/)
if (g_XAudioDLL)
{
    FreeLibrary(g_XAudioDLL);
    g_XAudioDLL = nullptr;
}
#endif
```

This ensures that the DLL is not unloaded while XAudio2 objects are active.

<strong>Note:</strong> The use of <code>LoadLibraryEx</code> above with the <code>LOAD_LIBRARY_SEARCH_SYSTEM32</code> flag is a <a href="https://docs.microsoft.com/en-us/security-updates/SecurityAdvisories/2010/2269637">security best practice</a>.  For a Windows 7 system, this requires the <a href="https://support.microsoft.com/en-us/help/2533623/microsoft-security-advisory-insecure-library-loading-could-allow-remot">KB 2533623</a> update to be installed.

<strong>See also:</strong> <a href="https://walbourn.github.io/xaudio2-and-windows-8/">XAudio2 and Windows 8</a>, <a href="https://walbourn.github.io/learning-xaudio2/">Learning XAudio2</a>, <a href="https://walbourn.github.io/windows-10-sdk-rtm/">Windows 10 SDK RTM</a>
