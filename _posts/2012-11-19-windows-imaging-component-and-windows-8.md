---
layout: msdnpost
title: Windows Imaging Component and Windows 8
date: 2012-11-19 15:07
author: Chuck Walbourn
comments: true
categories: [win7, win8, xbox]
---
There are a number of new features and some bugs fixed in the <a href="https://docs.microsoft.com/en-us/previous-versions//hh994467(v=vs.85)">Windows Imaging Component for Windows 8</a>. With the installation of <a href="https://walbourn.github.io/directx-11-1-and-windows-7-update/">KB 2670838</a> this new version of WIC is also available on Windows 7 Service Pack 1.
<!--more-->

The <a href="https://walbourn.github.io/visual-studio-2012-and-windows-8-0-sdk-rtm-are-now-available/">Windows 8.0 SDK</a> contains the latest version of the headers needed to build with the new version of WIC. The behavior of <code>wincodec.h</code> changes depending your build-settings. If you build with ``_WIN32_WINNT`` set to 0x602 or later, then <code>WINCODEC_SDK_VERSION</code>, <code>CLSID_WICImagingFactory</code>, and <code>CLSID_WICPngDecoder</code> are set to use "WIC2" by default. Otherwise, it uses the old "WIC1" version. This means Windows Store apps and Win32 desktop applications built for Windows 8 only are already using the new version of WIC. No muss. No fuss. Win32 desktop applications built for older versions of Windows continue to use "WIC1" and the old behaviors are maintained.

If, however, you want to use "WIC2" when it is available but successfully fall back to "WIC1" on Windows Vista or Windows 7 without the KB 2670838 update, then things get a little tricky. The ``_WIN7_PLATFORM_UPDATE`` define 'opts-in' to the Windows 8 header behavior without requiring you set your ``_WIN32_WINNT`` define in a way that doesn't support older versions of Windows. You will want to <em>avoid</em> using <code>WINCODEC_SDK_VERSION</code>, <code>CLSID_WICImagingFactory</code>, and <code>CLSID_WICPngDecoder</code> and instead use the explicit 'version' ones. You also need to be careful when using the four new WIC pixel format GUIDs (<code>GUID_WICPixelFormat32bppRGB, GUID_WICPixelFormat64bppRGB, GUID_WICPixelFormat96bppRGBFloat</code>, and <code>GUID_WICPixelFormat64bppPRGBAHalf</code>) as they are not valid for use with "WIC1" APIs.</p>
<p>For example, here is how you should be creating the WIC factory for Win32 desktop applications that support older versions of Windows:

```cpp
#define _WIN7_PLATFORM_UPDATE
#include <wincodec.h>

// CoInitializeEx needs called at some point before this

IWICImagingFactory* wicFactory = nullptr;
HRESULT hr = CoCreateInstance(
    CLSID_WICImagingFactory2,
    nullptr,
    CLSCTX_INPROC_SERVER,
    __uuidof(IWICImagingFactory2),
    reinterpret_cast<LPVOID*>( &wicFactory ) );
if ( SUCCEEDED(hr) )
{
    // WIC2 is available on Windows 8 and Windows 7 SP1 with KB 2670838 installed
    // Note you only need to QI IWICImagingFactory2 if you need to call CreateImageEncoder
}
else
{
    hr = CoCreateInstance(
        CLSID_WICImagingFactory1,
        nullptr,
        CLSCTX_INPROC_SERVER,
        __uuidof(IWICImagingFactory),
        reinterpret_cast<LPVOID*>( &wicFactory ) );
}
```

This results in the application using the new "WIC2" behaviors when available, but falls back to the older versions of WIC when it's not available.

<a href="https://github.com/Microsoft/DirectXTK">DirectXTK</a> and <a href="https://github.com/Microsoft/DirectXTex">DirectXTex</a> were both recently updated to support "WIC2" when it is available. This includes use of new WIC pixel formats ( <code>GUID_WICPixelFormat96bppRGBFloat</code> is the most useful since it matches <code>DXGI_FORMAT_R32G32B32_FLOAT</code> ), opts into the new Windows BMP <code>BITMAPV5HEADER</code> support (which encodes 32-bit with alpha channels for <code>GUID_WICPixelFormat32bppBGRA</code> and reads such BMP files as well), and can make use of the fix to the TIFF decoder for 96bpp floating-point images (which load as <code>GUID_WICPixelFormat96bppRGBFloat</code>).

<strong>Windows phone:</strong> Note that the Windows phone 8.0 platform does not support the WIC API, but Windows phone 8.1 does include it.

<strong>Xbox One:</strong> The Xbox One platform includes "WIC2". The HD Photo / JPEG XR codec is not currently supported for Xbox One XDK development.

<strong>VS 2012 Update 1: </strong>When building with the "<a href="https://walbourn.github.io/visual-studio-2012-update-1/">v110_xp</a>" Platform Toolset, the WIC2 header content is not available so avoid the use of ``_WIN7_PLATFORM_UPDATE`` for these configurations.

<strong>Windows 8.1</strong>: There are a few additional changes to WIC with Windows 8.1 including support for a limited ``DDS`` codec. See <a href="https://docs.microsoft.com/en-us/windows/desktop/wic/what-s-new-in-wic-for-windows-8-1">Microsoft Docs</a>.
