---
layout: post
title: Anatomy of Direct3D 12 Create Device
date: 2016-08-16 23:39
author: Chuck Walbourn
comments: true
categories: [direct3d, win10]
---
Based on some questions I've been getting lately, it seems like now's a good time to revisit my classic post <a href="https://walbourn.github.io/anatomy-of-direct3d-11-create-device/">Anatomy of Direct3D 11 Create Device</a> updated for Direct3D 12!
<!--more-->

The first thing to note is that while you can pass a <code>nullptr</code> for the 'default' device with Direct3D 12 to <a href="https://docs.microsoft.com/en-us/windows/desktop/api/d3d12/nf-d3d12-d3d12createdevice">D3D12CreateDevice</a>, that's probably not the best solution. At this point, every driver on Windows 7 or later supports Direct3D 11, so you can pretty safely assume the default device is going to support Direct3D 11 at some <a href="https://walbourn.github.io/direct3d-feature-levels/">Direct3D hardware feature level</a>. While a lot of existing (as well as new) GPUs support Direct3D 12, this doesn't apply to all GPUs. Specifically, a new WDDM 2 driver is required to support Direct3D 12, and there are no devices below Direct3D Feature Level 11.0 that are expected to get such updated drivers.

Another difference is that the debug device is not enabled through a creation flag like it is in Direct3D 11. Therefore, our first step is to enable debugging if available (the debug device is only present if the Graphics Tools Windows 10 <a href="https://devblogs.microsoft.com/cppblog/visual-studio-2015-and-graphics-tools-for-windows-10/">optional feature</a> is enabled). I'm making use of <code>Microsoft::WRL::ComPtr</code> which is recommended for both Direct3D 11 and Direct3D 12 (see this <a href="https://github.com/Microsoft/DirectXTK/wiki/ComPtr">page</a> for more information on this useful smart-pointer for COM programming).

```cpp
#if defined(_DEBUG)
    // Enable the debug layer.
    {
        ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
        {
            debugController->EnableDebugLayer();
        }
    }
#endif
```

Next, we create a DXGI factory--if you are using DirectX 12 you can also assume DXGI 1.4:

```cpp
ComPtr<IDXGIFactory4> dxgiFactory;
HRESULT hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
if (FAILED(hr))
    // Error!
```

Then we scan DXGI adapters looking for one that supports Direct3D 12:

```cpp
ComPtr<IDXGIAdapter1> adapter;
for (UINT adapterIndex = 0;
     DXGI_ERROR_NOT_FOUND !=
         dxgiFactory->EnumAdapters1(adapterIndex, &adapter);
     ++adapterIndex)
{
    DXGI_ADAPTER_DESC1 desc;
    hr = adapter->GetDesc1(&desc);
    if (FAILED(hr))
        continue;

    if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
    {
        // Don't select the Basic Render Driver adapter.
        continue;
    }

    // Check to see if the adapter supports Direct3D 12,
    // but don't create the actual device yet.
    if (SUCCEEDED(
        D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0,
            _uuidof(ID3D12Device), nullptr)))
    {
        break;
    }
}
```

<strong>Note:</strong> We are excluding the <em>Microsoft Basic Render</em> adapter here (aka <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/gg615082.aspx">WARP</a>+VGA driver) since games typically don't play well using WARP, but keep in mind that WARP12 is not present on standard Windows 10 systems; it's only installed as part of the Graphics Tools optional feature.

If there's no Direct3D 12-capable hardware, then for development builds it is useful to fallback to the WARP software device for Direct3D 12. Here is another difference compared to Direct3D 11: WARP12 is a specific adapter you obtain from the DXGI factory (<code>IDXGIFactory4</code> or later):

```cpp
#if !defined(NDEBUG)
    if (!adapter)
    {
        if (FAILED(dxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&adapter))))
        {
            adapter.Reset();
        }
     }
#endif
```

If at this point, we still don't have a valid adapter, then either a fatal error should be displayed, -or- if the application supports it, you should fall back to using Direct3D 11 (in which case, you should use a <code>IDXGIFactory1</code> initially and then use <code>QueryInterface</code> to obtain <code>IDXGIFactory4</code> as needed).

Otherwise, it's time to create the device. Here's another Direct3D 11 difference: Instead of providing an input array of every possible Direct3D feature level your application supports, you simply provide the minimum feature level you can use. Because as I noted above there's no expected drivers for anything below Feature Level 11.0, that's the minimum I'm using in this code and you'll find the same in the Visual Studio DirectX 12 templates.

```cpp
ComPtr<ID3D12Device> device;
hr = D3D12CreateDevice(adapter.Get(),
    D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
if (FAILED(hr))
    // Error!
```

Great, so we have a device, but how do you know if you managed to get a higher feature level than your minimum? Here we use <a href="https://docs.microsoft.com/en-us/windows/desktop/api/d3d12/nf-d3d12-id3d12device-checkfeaturesupport">CheckFeatureSupport</a> to find that out:

```cpp
static const D3D_FEATURE_LEVEL s_featureLevels[] =
{
    D3D_FEATURE_LEVEL_12_1,
    D3D_FEATURE_LEVEL_12_0,
    D3D_FEATURE_LEVEL_11_1,
    D3D_FEATURE_LEVEL_11_0,
};

D3D12_FEATURE_DATA_FEATURE_LEVELS featLevels =
{
    _countof(s_featureLevels), s_featureLevels, D3D_FEATURE_LEVEL_11_0
};

D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
hr = device->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS,
     &featLevels, sizeof(featLevels));
if (SUCCEEDED(hr))
{
    featureLevel = featLevels.MaxSupportedFeatureLevel;
}
```

<h1>Swap Chain</h1>

At this point, you are ready to create the swap chain. For Win32 classic desktop apps you use <a href="https://docs.microsoft.com/en-us/windows/desktop/api/dxgi1_2/nf-dxgi1_2-idxgifactory2-createswapchainforhwnd">CreateSwapChainForHwnd</a>, and for Universal Windows Platform (UWP) apps you use <a href="https://docs.microsoft.com/en-us/windows/desktop/api/dxgi1_2/nf-dxgi1_2-idxgifactory2-createswapchainforcorewindow">CreateSwapChainForCoreWindow</a> or <a href="https://docs.microsoft.com/en-us/windows/desktop/api/dxgi1_2/nf-dxgi1_2-idxgifactory2-createswapchainforcomposition">CreateSwapChainForComposition</a>, all of which require <code>IDXGIFactory2</code> or later.

The key thing to note about swap chain creation is that you must use either <code>DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL</code> or <code>DXGI_SWAP_EFFECT_FLIP_DISCARD</code> for the <code>DXGI_SWAP_CHAIN_DESC1.SwapEffect</code> because the older swap effects are not supported for Direct3D 12.

For Universal Windows Platform (UWP) apps, you should also consider using <code>DXGI_SCALING_ASPECT_RATIO_STRETCH</code> for the <code>DXGI_SWAP_CHAIN_DESC1.Scaling</code>, but for Win32 classic desktop swap chains you need to stick with <code>DXGI_SCALING_NONE</code> or <code>DXGI_SCALING_STRETCH</code>.

One more consideration: For gamma-correct rendering to standard 8-bit per channel UNORM formats, you'll want to create the Render Target using an sRGB format. The new flip modes, however, do not allow you to create a swap chain back buffer using an sRGB format. In this case, you create one using the non-sRGB format (i.e. <code>DXGI_SWAP_CHAIN_DESC1.Format = DXGI_FORMAT_B8G8R8A8_UNORM</code>) and use sRGB for the Render Target View (i.e. <code>D3D12_RENDER_TARGET_VIEW_DESC.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB</code>).

<strong>Note:</strong> With Direct3D 12, you cannot use the <code>device.As(&dxgiDevice)</code> sequence to obtain the DXGI factory from the Direct3D 12 device for cases where you use <code>nullptr</code> to create the <code>D3D12CreateDevice</code> instance. You must always explicitly create the DXGI factory using <code>CreateDXGIFactory1</code> or <code>CreateDXGIFactory2</code>.

<b>Update:</b> If you want to make use of <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/mt742104.aspx">variable refresh displays</a> or <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/mt742103.aspx">HDR10</a> output see <a href="https://github.com/walbourn/directx-vs-templates/blob/master/d3d12game_win32_dr/DeviceResources.cpp">DeviceResources</a>.

<h1>Windows SDK</h1>

To build an application using Direct3D 12 APIs, you must make use of the Windows 10 SDK. The latest version is the <a href="https://walbourn.github.io/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK (14393)</a>. With Visual Studio 2015, you install it via a <a href="https://devblogs.microsoft.com/cppblog/developing-for-windows-10-with-visual-c-2015/">custom install option</a> and for Win32 classic desktop projects you'll need to explicitly change the project property to use it rather than the default Windows 8.1 SDK (Spring 2015).

<strong>Update: </strong>With Visual Studio 2017, you can use the <a href="https://walbourn.github.io/windows-10-creators-update-sdk/">Windows 10 Creators Update SDK (15063)</a> or <a href="https://walbourn.github.io/windows-10-fall-creators-update-sdk/">Windows 10 Fall Creators Update SDK (16299)</a>. VS 2015 is not supported by these newer SDKs.

<h1>Direct3D 12.1</h1>

With the <a href="https://walbourn.github.io/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update (14393)</a>, newer drivers and devices can support some additional features for Direct3D 12. You can obtain the 12.1 interface from your 12.0 device by using <code>QueryInterface</code> or <code>ComPtr::As</code>--this will fail on older versions of Windows 10.

```cpp
ComPtr<ID3D12Device1> device1;
if (SUCCEEDED(device.As(&device1)))
{
    // Direct3D 12.1 Runtime is available
}
```

<b>Note:</b> There is also a <code>ID3D12Device2</code> for the <a href="https://walbourn.github.io/windows-10-creators-update-sdk/">Windows 10 Creators Update (15063)</a>, a <code>ID3D12Device3</code> for the <a href="https://walbourn.github.io/windows-10-fall-creators-update-sdk/">Windows 10 Fall Creators Update (16299)</a> as well.

<h1>Win32 desktop application notes</h1>

If your application supports Windows 8.1 or earlier, then you need to make use of explicit rather than implicit linking to the Direct3D 12 functions since they are not available before Windows 10. Implicit linking to <code>dxgi.lib</code> (and <code>d3d11.lib</code> if needed) is not a problem unless you are trying to support Windows XP as well. You'll need to make sure the code above uses DXGI 1.1 for the initial detection to support Windows 7 systems.

```cpp
HMODULE dx12 = LoadLibraryEx(L"d3d12.dll",
    nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
if (!dx12)
    // Fallback to using Direct3D 11

auto pD3D12CreateDevice = reinterpret_cast<PFN_D3D12_CREATE_DEVICE>(
    GetProcAddress(dx12, "D3D12CreateDevice"));
if (!pD3D12CreateDevice)
    // Fallback to using Direct3D 11

...

#if defined(_DEBUG)
    // Enable the debug layer.
    auto pD3D12GetDebugInterface =
        reinterpret_cast<PFN_D3D12_GET_DEBUG_INTERFACE>(
        GetProcAddress(dx12, "D3D12GetDebugInterface"));
    if (pD3D12GetDebugInterface)
    {
        ComPtr<ID3D12Debug> debugController;
        if (SUCCEEDED(pD3D12GetDebugInterface(
            IID_PPV_ARGS(&debugController))))
        {
            debugController->EnableDebugLayer();
        }
    }
#endif

...
// Change both cases where we use D3D12CreateDevice above to
// pD3D12CreateDevice. If you fail to find an adapter, use
// Direct3D 11 instead
```

<h1>Universal Windows Platform (UWP) notes</h1>

Because the minimum OS version is enforced for the platform, you can count on <code>IDXGIFactory4</code> always being available.

<strong>Related:</strong> <a href="https://walbourn.github.io/direct3d-game-visual-studio-templates-redux/">Direct3D Game Visual Studio templates (Redux)</a>, <a href="https://walbourn.github.io/directx-tool-kit-for-directx-12/">DirectX Tool Kit for DirectX 12,</a> <a href="https://walbourn.github.io/getting-started-with-direct3d-12/">Getting Started with Direct3D 12</a>
