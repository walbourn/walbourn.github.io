---
layout: post
title: Anatomy of Direct3D 11 Create Device
date: 2014-02-05 12:21
author: walbourn
comments: true
categories: [direct3d, Uncategorized]
---
In answering some questions today, I remembered a topic I had been meaning to post about for some time: the seemingly simple act of creating a Direct3D 11 device. At it's core, it's pretty simple, but there's more to it than it first appears.

The standard code for creating a Direct3D 11 device starts out pretty simple using <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff476082.aspx">D3D11CreateDevice</a>:
<pre><code>DWORD createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

ComPtr&lt;ID3D11Device&gt; device;
ComPtr&lt;ID3D11DeviceContext&gt; context;
D3D_FEATURE_LEVEL fl;
HRESULT hr = D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_HARDWARE,
    nullptr, createDeviceFlags, nullptr,
    0, D3D11_SDK_VERSION, &amp;device, &amp;fl, &amp;context );
</code></pre>
This assumes you want the default hardware device and it handles requesting the debug device in debug builds of the application (see <a href="http://blogs.msdn.com/b/chuckw/archive/2012/11/30/direct3d-sdk-debug-layer-tricks.aspx">Direct3D SDK Debug Layer Tricks</a> for more). This will create a device at the highest available <a href="http://blogs.msdn.com/b/chuckw/archive/2012/06/20/direct3d-feature-levels.aspx">feature level</a> on most systems, but it has a subtle side-effect: you will never get a Feature Level 11.1 device. This is for better backwards compatibility and is easy to rectify, but for a Win32 desktop application (which can run on older versions of Windows) it's a little tricky.

This following code is the robust way to get all possible feature levels while handling DirectX 11.0 systems:
<pre><code>D3D_FEATURE_LEVEL lvl[] = {
    D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
    D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
    D3D_FEATURE_LEVEL_9_3, D3D_FEATURE_LEVEL_9_2, D3D_FEATURE_LEVEL_9_1 };

DWORD createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

ComPtr&lt;ID3D11Device&gt; device;
ComPtr&lt;ID3D11DeviceContext&gt; context;
D3D_FEATURE_LEVEL fl;
HRESULT hr = D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
    createDeviceFlags, lvl, _countof(lvl),
    D3D11_SDK_VERSION, &amp;device, &amp;fl, &amp;context );
if ( hr == E_INVALIDARG )
{
    hr = D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        createDeviceFlags, &amp;lvl[1], _countof(lvl)-1,
        D3D11_SDK_VERSION, &amp;device, &amp;fl, &amp;context );
}
</code></pre>
The <code>E_INVALIDARG</code> case is the one that trips up people, and it handles the case where the platform only supports DirectX 11.0 (Windows Vista, Windows 7 RTM, or Windows 7 SP1 without KB 2670838 installed). Note you can get a similar kind of failure if you are trying to create a resource with one of the 16-bit per pixel DXGI 1.2 formats (i.e. 5/5/5/1, 565, 4/44/4) on a system with DirectX 11.0 installed.

<strong>Update:</strong> The same thing happens if you include <code>D3D_FEATURE_LEVEL_12_0</code> and/or <code>D3D_FEATURE_LEVEL_12_1</code> in your array when run on versions of Windows prior to Windows 10. In this case, you'd end up with two <code>E_INVALIDARG</code> cases to handle if you wanted to go all the way back to DirectX 11.0 Runtime and still cover all possible feature levels. That said, the 12.x Direct3D hardware feature levels are basically just the 11.1 Direct3D hardware feature level with some additional optional features you could choose to detect individually instead.
<h1>Direct3D 11.1</h1>
Once you have the Direct3D device and context you can proceed, but if you want to use some of the newer features of Direct3D 11.1 you'll need another step:
<pre><code>ComPtr&lt;ID3D11Device1&gt; device1;
ComPtr&lt;ID3D11DeviceContext1&gt; context1;
if ( SUCCEEDED(device.As(&amp;device1) )
{
    (void)context.As(&amp;context1);
}
</code></pre>
This code requires you include <code>&lt;d3d11_1.h&gt;</code> and have the <a href="http://blogs.msdn.com/b/chuckw/archive/2012/08/15/visual-studio-2012-and-windows-8-0-sdk-rtm-are-now-available.aspx">Windows 8.0 SDK</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/10/18/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available.aspx">Windows 8.1 SDK</a>, or the <a href="https://blogs.msdn.microsoft.com/chuckw/2015/07/30/windows-10-sdk-rtm/">Windows 10 SDK</a>. You will get a valid <code>device1</code> and <code>context1</code> pointer on Windows 10,Windows 8.1, Windows 8.0, and Windows 7 SP1 with <a href="http://blogs.msdn.com/b/chuckw/archive/2013/02/26/directx-11-1-and-windows-7-update.aspx">KB 2670838</a> installed.

<strong>Note: </strong>For modern games, DirectX 11.1 or later is a reasonable requirement. Games should already require Windows 7 Service Pack 1 as Windows 7 RTM is out of support and isn't supported by VS 2015/2017 in any case. If you fail to obtain a 11.1 device in this case or get a <code>E_INVALIDARG</code> above, a fatal error telling the user they need to install KB 2670838 or upgrade to a newer OS is a reasonable course of action.
<h1>Direct3D 11.2</h1>
If you want to use Direct3D 11.2 features, you do basically the same thing:
<pre><code>ComPtr&lt;ID3D11Device2&gt; device2;
ComPtr&lt;ID3D11DeviceContext2&gt; context2;
if ( SUCCEEDED(device.As(&amp;device2) )
{
    (void)context.As(&amp;context2);
}
</code></pre>
This code requires you include <code>&lt;d3d11_2.h&gt;</code> and have the <a href="http://blogs.msdn.com/b/chuckw/archive/2013/10/18/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available.aspx">Windows 8.1 SDK</a> or the <a href="https://blogs.msdn.microsoft.com/chuckw/2015/07/30/windows-10-sdk-rtm/">Windows 10 SDK</a>. You will get a valid <code>device2</code> and <code>context2</code> pointer on Windows 8.1 or Windows 10.

<strong>Update:</strong> You could do the same with Direct3D 11.3 which would only return a valid pointer on Windows 10. Direct3D 11.4 requires Windows 10 (November 2015 or later). You need to include <code>&lt;d3d11_3.h&gt;</code> or <code>&lt;d3d11_4.h&gt;</code> and have the <a href="http://blogs.msdn.com/b/chuckw/archive/2015/11/30/windows-10-sdk-november-2015.aspx">Windows 10 SDK</a>.
<h1>DXGI</h1>
The primary reason to get a DXGI interface is to enumerate adapters and inputs, but you also use them to create swap chains. There's a trick to making sure you get it robustly if you have passed <code>nullptr</code> to <code>D3D11CreateDevice</code> for the <code>pAdapter</code> pointer as we have above. Mixing different DXGI factory versions can cause problems, so ideally we want to use whatever the system used internally. You can do this with a little COM sequence that is perhaps familiar to Windows Store app and Xbox One developers:
<pre><code>ComPtr&lt;IDXGIFactory1&gt; dxgiFactory;
{
    ComPtr&lt;IDXGIDevice&gt; dxgiDevice;
    if (SUCCEEDED(device.As(&amp;dxgiDevice)))
    {
        ComPtr&lt;IDXGIAdapter&gt; adapter;
        if (SUCCEEDED(dxgiDevice-&gt;GetAdapter(&amp;adapter)))
        {
            hr = adapter-&gt;GetParent(IID_PPV_ARGS(&amp;dxgiFactory));
            if ( SUCCEEDED(hr) )
            {
                ...
            }
        }
    }
}</code></pre>
If you want to specify a particular adapter for the device creation, you need a DXGI factory. For DirectX 11 systems generally, you use <code>CreateDXGIFactory1</code> (<code>CreateDXGIFactory</code> was for Direct3D 10 systems). You can make use of <code>CreateDXGIFactory2</code> on Windows 8.1 or Windows 10 systems to specify DXGI debugging, but generally you use <code>CreateDXGIFactory1</code> and then would <code>QueryInterface</code> other versions as needed.
<h1>Swap Chains</h1>
For Win32 classic desktop apps on DirectX 11.0 systems, you must use the <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/bb174537.aspx">IDXGIFactory1::CreateSwapChain</a> function. On DirectX 11.1 or later systems you can use <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/hh404557.aspx">IDXGIFactory2::CreateSwapChainForHwnd</a>.

For Universal Windows Platform (UWP) apps you use <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/hh404559.aspx">CreateSwapChainForCoreWindow</a> or <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/hh404558.aspx">CreateSwapChainForComposition</a>. You must also make use of <code>DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL</code> or <code>DXGI_SWAP_EFFECT_FLIP_DISCARD</code> for the <code>DXGI_SWAP_CHAIN_DESC1.SwapEffect</code> because the older swap effects are not supported for UWP.

For Universal Windows Platform (UWP) apps, you should also consider using <code>DXGI_SCALING_ASPECT_RATIO_STRETCH</code> for the <code>DXGI_SWAP_CHAIN_DESC1.Scaling</code>, but for Win32 classic desktop swap chains you need to stick with <code>DXGI_SCALING_NONE</code> or <code>DXGI_SCALING_STRETCH</code> on DirectX 11.1 systems.

One more consideration: For gamma-correct rendering to standard 8-bit per channel UNORM formats, you’ll want to create the Render Target using an sRGB format. The new flip modes required for UWP apps, however, do not allow you to create a swap chain back buffer using an sRGB format. In this case, you create one using the non-sRGB format (i.e. <code>DXGI_SWAP_CHAIN_DESC1.Format = DXGI_FORMAT_B8G8R8A8_UNORM</code>) and use sRGB for the Render Target View (i.e. <code>D3D12_RENDER_TARGET_VIEW_DESC.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB</code>).

<strong>Update:</strong> You also need to use the <code>FLIP_*</code> swap effects if you want to make use of <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/mt742104.aspx">variable refresh displays</a> or <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/mt742103.aspx">HDR10</a> output. See <a href="https://github.com/walbourn/directx-vs-templates/blob/master/d3d11game_win32_dr/DeviceResources.cpp">DeviceResources</a> for more details.
<h1>Microsoft Basic Render Driver</h1>
In the original code, we use <code>D3D_DRIVER_TYPE_HARDWARE</code>. If you had wanted to use the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/gg615082.aspx">WARP</a> software device, you would have used <code>D3D_DRIVER_TYPE_WARP</code>. WARP is exceptionally useful as a much faster 'ref' for testing and can be used quite successfully as a software fallback for many kinds of applications, but it is still a software renderer. As such, most games don't expect to be running under WARP.

With Windows 8.x and Windows 10, however, there is new situation to be aware of (see <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/23/desktop-games-on-windows-8-consumer-preview.aspx">Desktop Games on Windows 8.x</a>). In older versions of Windows, if a suitable video driver was not available it would fallback to a legacy VGA driver. Direct3D device creation with this driver would fail, which poses a problem for a desktop which requires it. Therefore, with Windows 8.x it defaults to the "Microsoft Basic Render Driver" instead. This is an extremely simple video output driver combined with WARP. This is a reasonable setup for servers, and the technology is very useful in making remote desktop work well.

For games, the most likely situation for this to come up is related to the fact that Direct3D9 era hardware is considered <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh848038.aspx">legacy</a> for Windows 8.x. Users can obtain older Windows Vista WDDM 1.0 or Windows 7 WDDM 1.1 drivers for their DirectX9 era video cards, but the expectation is that most x86/x64 systems will have a DirectX 10+ capable video card. Users who upgrade their systems with a DX9 video card could be running the "Microsoft Basic Render Driver" and not realize they are missing a needed driver or that their video card is too old to be supported at all (i.e. it only has an XPDM driver available which are not supported by Windows 8.x)

One way to mitigate this scenario is for a game to detect if <em>Microsoft Basic Render</em> driver is active and warn the user. This is easy to do since the "Microsoft Basic Render Driver" has a <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3ddxgi/d3d10-graphics-programming-guide-dxgi#new-info-about-enumerating-adapters-for-windows-8">well-known VendorID/DeviceID</a> combination:
<pre><code>ComPtr&lt;IDXGIDevice&gt; dxgiDevice;
if (SUCCEEDED(device.As(&amp;dxgiDevice)))
{
    ComPtr&lt;IDXGIAdapter&gt; adapter;
    if (SUCCEEDED(dxgiDevice-&gt;GetAdapter(&amp;adapter)))
    {
        DXGI_ADAPTER_DESC desc;
        if (SUCCEEDED(adapter-&gt;GetDesc(&amp;desc)))
        {
            if ( (desc.VendorId == 0x1414) &amp;&amp; (desc.DeviceId == 0x8c) )
            {
                // WARNING: Microsoft Basic Render Driver is active.
                // Performance of this application may be unsatisfactory.
                // Please ensure that your video card is Direct3D10/11 capable
                // and has the appropriate driver installed.
            }
        }
    }
}
</code></pre>
<strong>Note</strong>: If you are still supporting a Direct3D 9 game, you can detect this the same way:
<pre><code>IDirect3D9* d3ddevice = Direct3DCreate9(D3D_SDK_VERSION);
if ( d3ddevice )
{
    D3DADAPTER_IDENTIFIER9 adapterIdentifier;
    if (SUCCEEDED(d3ddevice-&gt;GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &amp;adapterIdentifier)))
    {
        if ( (adapterIdentifier.VendorId == 0x1414) &amp;&amp; (adapterIdentifier.DeviceId == 0x8c) )
        {
            // WARNING: Microsoft Basic Render Driver is active.
            // Performance of this application may be unsatisfactory.
            // Please ensure that your video card is Direct3D9 capable
            // and has the appropriate driver installed.
        }
    }
}
</code></pre>
<strong>Update:</strong> I've updated this blog post to make use of <code>Microsoft::WRL::ComPtr</code>. See this <a href="https://github.com/Microsoft/DirectXTK/wiki/ComPtr">page</a> for more information about this helpful smart-pointer for COM programming. Also updated with UWP information for Windows 10.

<strong>Related:</strong> <a href="https://blogs.msdn.microsoft.com/chuckw/2015/12/17/direct3d-game-visual-studio-templates-redux/">Direct3D Game Visual Studio templates (Redux)</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2016/08/16/anatomy-of-direct3d-12-create-device/">Anatomy of Direct3D 12 Create Device</a>
