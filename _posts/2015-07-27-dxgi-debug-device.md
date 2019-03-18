---
layout: post
title: DXGI Debug  Device
date: 2015-07-27 14:49
author: Chuck Walbourn
comments: true
categories: [direct3d, win10, win8]
---
In my original post on using the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/overviews-direct3d-11-devices-layers">debug layer</a>, I mentioned several tricks for getting helpful behavior out of the Direct3D SDK debug layer for your applications. This best practice is demonstrated in my <a href="https://walbourn.github.io/direct3d-win32-game-visual-studio-template/">Visual C++ Game templates</a> as follows:
<!--more-->

```cpp
#ifndef NDEBUG
Microsoft::ComPtr<ID3D11Debug> d3dDebug;
hr = m_d3dDevice.As(&d3dDebug);
if (SUCCEEDED(hr))
{
    ComPtr<ID3D11InfoQueue> d3dInfoQueue;
    hr = d3dDebug.As(&d3dInfoQueue);
    if (SUCCEEDED(hr))
    {
#ifdef _DEBUG
        d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
        d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
 #endif
        D3D11_MESSAGE_ID hide [] =
        {
            D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
            // TODO: Add more message IDs here as needed
        };
        D3D11_INFO_QUEUE_FILTER filter = {};
        filter.DenyList.NumIDs = _countof(hide);
        filter.DenyList.pIDList = hide;
        d3dInfoQueue->AddStorageFilterEntries(&filter);
    }
}
#endif
```

This snippet ensures that a common but harmless warning message is suppressed in non-Production builds, and enables 'break on' functionality in Debug builds if there are any serious corruption or error messages.

With the <strong>Direct3D 11.1 Runtime </strong>or later, you can also use a DXGI debug interface to track down additional leaks that are not known to your Direct3D 11 device. How this new interface is exposed, however, is a bit confusing.

For traditional Windows desktop apps, you are expected to use <span style="text-decoration: underline">explicit linking</span>. Since the DXGI debug layer is not present on end-user machines, this pattern encourages being able to handle the case of it not being present on the system. The confusing part is that the function you need, <code>DXGIGetDebugInterface</code> is not defined in any header and is not present in any import library.

```cpp
#include <dxgidebug.h>
#if defined(_DEBUG)
     Microsoft::WRL::ComPtr<IDXGIInfoQueue> dxgiInfoQueue;
  
     typedef HRESULT (WINAPI * LPDXGIGETDEBUGINTERFACE)(REFIID, void ** );
  
     HMODULE dxgidebug = LoadLibraryEx( L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32 );
     if ( dxgidebug )
     {
         auto dxgiGetDebugInterface = reinterpret_cast<LPDXGIGETDEBUGINTERFACE>(
             reinterpret_cast<void*>( GetProcAddress( dxgidebug, "DXGIGetDebugInterface" ) ) );
  
         if ( SUCCEEDED( dxgiGetDebugInterface( IID_PPV_ARGS( dxgiInfoQueue.GetAddressOf() ) ) ) )
         {
             dxgiInfoQueue->SetBreakOnSeverity( DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true );
             dxgiInfoQueue->SetBreakOnSeverity( DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true );
         }
     }
#endif
```

One issue with this pattern is that you can't use it for Windows Store or universal Windows apps since <code>LoadPackagedLibrary</code> cannot load a system DLL as a security measure. In the <strong>DirectX 11.2 Runtime</strong> (Windows 8.1 and Windows 10), there is now a <code>DXGIGetDebugInterface1</code> defined in the <code>dxgi1_3.h</code> header and in the <code>dxgi.lib</code> import library. This implicit linking works fine for Windows Store apps and UWP, but for desktop apps you should stick with the explicit method particularly if you need Windows 7 support as this function is not present in the 11.1 or 11.0 runtime.

```cpp
#if defined(_DEBUG)
Microsoft::WRL::ComPtr<IDXGIInfoQueue> dxgiInfoQueue;
if ( SUCCEEDED( DXGIGetDebugInterface1( 0, IID_PPV_ARGS( dxgiInfoQueue.GetAddressOf() ) ) ) )
{
       dxgiInfoQueue->SetBreakOnSeverity( DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true );
       dxgiInfoQueue->SetBreakOnSeverity( DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true );
}
#endif
```

As with the Direct3D debug layer, there is a method for reporting live DXGI objects as well for tracking down resource leaks. You obtain a <code>IDXGIDevice</code> instance the same was as you do a <code>IDXGIInfoQueue</code> interface above, and then call <a href="https://docs.microsoft.com/en-us/windows/desktop/api/dxgidebug/nf-dxgidebug-idxgidebug-reportliveobjects">ReportLiveObjects</a>.

<strong>DXGUID:</strong> One other issue of note is that the various DXGI debug control GUIDs (i.e. <code>DXGI_DEBUG_ALL</code>) are missing from <code>DXGUID.LIB</code>. You have to define it yourself using <code>INITGUID</code>. This is fixed for the Windows 10 SDK.

<strong>DirectX 12:</strong> Since DirectX 12 is only supported on Windows 10, you should use the DXGI debug interface obtained from <code>CreateDXGIFactory2</code> using <code>DXGI_CREATE_FACTORY_DEBUG</code> as the flag.

```cpp
DWORD debugFactoryFlags = 0;

#if defined(_DEBUG)
    // Enable the debug layer (requires the Graphics Tools "optional feature").
    //
    // NOTE: Enabling the debug layer after device creation will invalidate the active device.
    {
        ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(debugController.GetAddressOf()))))
        {
            debugController->EnableDebugLayer();
        }
        else
        {
            OutputDebugStringA("WARNING: Direct3D Debug Device is not available\n");
        }

        ComPtr<IDXGIInfoQueue> dxgiInfoQueue;
        if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(dxgiInfoQueue.GetAddressOf()))))
        {
            dxgiFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;

            dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR, true);
            dxgiInfoQueue->SetBreakOnSeverity(DXGI_DEBUG_ALL, DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION, true);
        }
    }
#endif

    ThrowIfFailed(
        CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(m_dxgiFactory.ReleaseAndGetAddressOf()))
        );
```

<strong>Related:</strong> <a href="https://walbourn.github.io/direct3d-sdk-debug-layer-tricks/">Direct3D SDK Debug Layer Tricks</a>, <a href="https://walbourn.github.io/directx-11-1-and-windows-7-update/">DirectX 11.1 and Windows 7 Update</a>
