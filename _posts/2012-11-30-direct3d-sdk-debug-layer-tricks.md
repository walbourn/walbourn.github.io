---
layout: msdnpost
title: Direct3D SDK Debug Layer Tricks
date: 2012-11-30 12:25
author: Chuck Walbourn
comments: true
categories: [direct3d, win10, win8]
---
When programming graphics applications, one of the more frustrating aspects of development is that you can end up writing thousands of lines of code and when you run it, all you get is a blank screen. Or maybe a blue screen. Or a crash. But often, not actually a useful image. Errors in state setting, transformation math, and other coding problems can mean your application is completely valid just not useful. Other kinds of coding problems are due to misuse or abuse of the Direct3D API itself. In those cases, enabling the 'debug' device can quickly help identify the problems.
<!--more-->

With Direct3D 9 and older versions of the API, there was a "Developer Runtime" installed by the (now legacy) DirectX SDK and the <em>DirectX Control Panel</em> was used to switch the debug support on an off. This worked reasonably well in a world where only the running application was using Direct3D, but starting with Windows Vista this 'global' option was no longer feasible since the OS itself was using Direct3D. Even on the older systems, people would install the DirectX SDK, enable the debugging, and then forget about and find all their games would go really slowly.

Staring with Direct3D 10.0, a new mechanism was created for the "Developer Runtime" via a <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/overviews-direct3d-11-devices-layers">API layering mechanism</a> and is implemented in the <code>D3D10SDKLAYERS.DLL</code>. Developers could opt in their specific application to the debug validation either by creating the device with <code>D3Dxx_CREATE_DEVICE_DEBUG</code>, or by adding the executable to a list in the <em>DirectX Control Panel</em>. This layering mechanism is also used as a way to improve performance, with the non-debug version of the API doing fairly minimal parameter validation leaving the really detailed diagnostics and validation to the debug layer and only doing it when a developer was wanting the additional debug checking done.

This same system is still in place for Direct3D 11.0 (<code>D3D11SDKLAYERS.DLL</code>) and 11.1 (<code>D3D11_1SDKLAYERS.DLL</code>). It is <em>highly recommended</em> that developers make use of the debug layer to validate their Direct3D 11.x-based applications, paying particular attention to CORRUPTION and ERROR level messages. These are often indicators of severe problems lurking in your code, and could help avoid support issues once your application is deployed. The WARNING and INFO level messages can also be very useful. That said, sometimes there are warnings that are not as useful. Just like with compiler warnings, learning to ignore them as 'noise' can result in missing more actionable messages. Therefore, you should consider having your application suppress 'known' messages and the like whenever the debug device is active.

A common error comes from making use of the <a href="https://walbourn.github.io/object-naming/">Object Naming</a> feature to improve the debugging of you resources with the debug device, VS 2012 graphics debugging, and the legacy <em>PIX for Windows</em> tool.

```
D3D11 WARNING: ID3D11Texture2D::SetPrivateData: Existing private data of same name with different size found!<br /> [ STATE_SETTING WARNING #55: SETPRIVATEDATA_CHANGINGPARAMS]
```

This could be an important message in some cases, but likely not for cases where you are using <code>WKPDID_D3DDebugObjectName</code>. There may be other warnings your code generates which are also harmless. This can be solved with some code just after you create your device. This code should probably be excluded from your 'production' build for final release, but for testing you may want it in Release builds in cases where the tester turns on debugging manually (such as via the <em>DirectX Control Panel</em>) which is why I'm not showing it in an ``#ifdef _DEBUG`` block. Also, for debug builds it is useful for the application to trigger a break-point for the severe cases of CORRUPTION and ERRORs, which is the code I'm showing as ``#ifdef _DEBUG`` here. Finally, remember that on 'end-user' systems and standard OS installs, the debug layer creation fails without the appropriate SDK Layers DLL.

For Win32 desktop applications, this code looks like:

```cpp
#ifdef _DEBUG
deviceCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

...
...deviceCreationFlags is passed to D3D11CreateDevice as 'Flags' which is the fourth parameter
...

ID3D11Debug *d3dDebug = nullptr;
if (SUCCEEDED(d3dDevice->QueryInterface(__uuidof(ID3D11Debug), (void**)&d3dDebug)))
{
    ID3D11InfoQueue *d3dInfoQueue = nullptr;
    if (SUCCEEDED(d3dDebug->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&d3dInfoQueue)))
    {
#ifdef _DEBUG
        d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
        d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif

        D3D11_MESSAGE_ID hide[] =
        {
        D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
        // Add more message IDs here as needed
        };

        D3D11_INFO_QUEUE_FILTER filter = {};
        filter.DenyList.NumIDs = _countof(hide);
        filter.DenyList.pIDList = hide;
        d3dInfoQueue->AddStorageFilterEntries(&filter);
        d3dInfoQueue->Release();
    }
    d3dDebug->Release();
}
```

For Windows Store and Windows phone 8 applications, this code looks like:

```cpp
...
#ifdef _DEBUG
deviceCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
...
...deviceCreationFlags is passed to D3D11CreateDevice as 'Flags' which is the fourth parameter
...

ComPtr<ID3D11Debug> d3dDebug;
if (SUCCEEDED(d3dDevice.As(&d3dDebug)))
{
    ComPtr<ID3D11InfoQueue> d3dInfoQueue;
    if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
    {
#ifdef _DEBUG
        d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
        d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
        D3D11_MESSAGE_ID hide[] =
        {
            D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
            // Add more message IDs here as needed
        };

        D3D11_INFO_QUEUE_FILTER filter = {};
        filter.DenyList.NumIDs = _countof(hide);
        filter.DenyList.pIDList = hide;
        d3dInfoQueue->AddStorageFilterEntries(&filter);
    }
}
```

In these cases I throw away the reference to the debug objects <a href="https://docs.microsoft.com/en-us/windows/desktop/api/d3d11sdklayers/nn-d3d11sdklayers-id3d11debug">ID3D11Debug</a> and <a href="https://docs.microsoft.com/en-us/windows/desktop/api/d3d11sdklayers/nn-d3d11sdklayers-id3d11infoqueue">ID3D11InfoQueue</a>, but there are some nifty features you might consider using so it can be useful to hold on them instead. For example, calling this just after releasing all your Direct3D objects just before releasing the ID3D11Device should report that all objects reference counts are 0--although the 'internal' reference counts might still be > 0 since a few objects are alive as long as the device is alive for internal defaults. It can also help to call <code>ClearState </code>and then <code>Flush </code>on the immediate context just before doing the report to ensure nothing is being kept alive by being bound to the render pipeline or because of <em>lazy destruction</em>. This information is output to the Debug Window in VS (or something like <a href="https://docs.microsoft.com/en-us/sysinternals/downloads/debugview">DebugView</a>)

```cpp
d3dDebug->ReportLiveDeviceObjects( D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL );
```

<strong>DirectX 11.1</strong>: DirectX 11.1 adds a <a href="https://walbourn.github.io/dxgi-debug-device/">DXGI debug interface</a> as well.

<strong>Windows phone: </strong>You cannot enable Direct3D debugging with hybrid Silverlight / Direct3D apps.

<strong>Update: </strong>This of course assumes you want to turn off these particular messages 'globally' for your application. You can also suppress them around only a specific part of your code via <a href="https://docs.microsoft.com/en-us/windows/desktop/api/d3d11sdklayers/nf-d3d11sdklayers-id3d11infoqueue-pushstoragefilter">PushStorageFilter</a> / <a href="https://docs.microsoft.com/en-us/windows/desktop/api/d3d11sdklayers/nf-d3d11sdklayers-id3d11infoqueue-popstoragefilter">PopStorageFilter</a>

<strong>Developer Runtime:</strong> For details on obtaining the proper "Developer Runtime" for your OS, see <a href="https://walbourn.github.io/directx-11-1-and-windows-7-update/">DirectX 11.1 and Windows 7</a>, <a href="https://walbourn.github.io/visual-studio-2012-and-windows-8-0-sdk-rtm-are-now-available/">Visual Studio 2012 and Windows 8.0 SDK</a>, <a href="https://walbourn.github.io/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available/">Visual Studio 2013 and Windows 8.1 SDK</a>, <a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a>, and <a href="https://walbourn.github.io/where-is-the-directx-sdk-2013-edition/">Where is the DirectX SDK (2013 Edition)?</a>. Remember that this includes installing the "reference" device as well as <a href="https://docs.microsoft.com/en-us/windows/desktop/Direct2D/direct2ddebuglayer-overview">Direct2D</a> debugging facilities.

<table border="1">
<tbody>
<tr>
<td><strong>Operating System</strong></td>
<td><strong>Developer Runtime</strong></td>
</tr>
<tr>
<td>Windows Vista<br />Windows 7 RTM</td>
<td>
<p>VS 2012 Remote Debugging Tools<br /> legacy DirectX SDK for Direct3D</p>
<p><em>Direct2D debugging for these version of the OS can also be done with <a href="https://docs.microsoft.com/en-us/windows/desktop/Direct2D/direct2ddebuglayer-overview#installing-the-direct2d-debug-layer">manual installation</a>.</em></p>
</td>
</tr>
<tr>
<td>Windows 7 SP1<br /> Windows 8</td>
<td>
<p>VS 2012<br />VS 2012 Remote Debugging Tools<br /> Windows 8 SDK</p>
</td>
</tr>
<tr>
<td>Windows 7 SP1<br /> Windows 8<br />Windows 8.1</td>
<td>
<p>VS 2013<br />VS 2013 Remote Debugging Tools<br /> Windows 8.1 SDK</p>
</td>
</tr>
<tr>
<td>Windows 10</td>
<td>
<p>Enable the Windows optional feature "Graphics Tools". Read <a href="https://devblogs.microsoft.com/cppblog/visual-studio-2015-and-graphics-tools-for-windows-10/">this post</a> for details.</p>
</td>
</tr>
</tbody>
</table>

<p><strong>Related: </strong><a href="https://walbourn.github.io/anatomy-of-direct3d-11-create-device/">Anatomy of Direct3D 11 Create Device</a>
