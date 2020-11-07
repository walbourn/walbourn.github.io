---
layout: post
title: The Care and Feeding of Modern Swap Chains
date: 2020-11-06 17:31
author: Chuck Walbourn
comments: true
categories: [direct3d]
---
The original idea for *Microsoft DirectX Graphics Infrastructure* ([DXGI](https://docs.microsoft.com/en-us/windows/win32/direct3ddxgi/dx-graphics-dxgi)) was to factor out creating swapchains and enumerating monitor resolutions from the evolution of Direct3D, and that DXGI would be basically the same for a long time. Alas, in practice that's not remotely true, and DXGI has changed with every update of Direct3D and/or Windows. As a result, the "right" way to use DXGI has changed as well. The basic recommendations on [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/direct3darticles/dxgi-best-practices) are still a good place to start, but there are a number of important areas that need more explanation.
<!--more-->

# Old vs. new flip modes
The original "swap effects" were ``DXGI_SWAP_EFFECT_DISCARD`` and ``DXGI_SWAP_EFFECT_SEQUENTIAL``. The choice here is between "game-style" rendering where you create an entirely new image every frame, and "presentation-style" rendering where you just draw updates over the existing image. These were both designed for the needs of classic Win32 windows, and was a less complex support matrix than the four+ different swap effects of Direct3D 9. These are collectively referred to a "blt-style".

Over the life of Direct3D 10 and Direct3D 11, and in particular adding support for the "CoreWindow" model used by "Metro style apps"--a.k.a. "Tailored apps" a.k.a. "Windows Store apps" that eventually morphed into "Universal Windows Platform (UWP) apps"--, the ``DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL`` swap effect was introduced for Windows 8/DXGI 1.2. This allows the data to be fed to the Desktop Windows Compositor more efficiently.

For Windows 10/DXGI 1.4, ``DXGI_SWAP_EFFECT_FLIP_DISCARD`` was added as well. DirectX 12 devices were made to only support the new  ``DXGI_SWAP_EFFECT_FLIP_*`` models, with the intention of having games & applications 'modernize' their DXGI usage for classic Win32 applications.

A number of improvements have been made to swap chain performance, and for 'back compat' reasons these changes are heavily focused on the newer "flip-style" modes. At this point, it's recommended that DirectX 11 apps prefer to use the 'flip-modes' as discussed on the [DirectX Developer Blog](https://devblogs.microsoft.com/directx/dxgi-flip-model/), and DirectX 12 apps must use them.

> For implementation details, especially handling older versions of Windows, see the [DX11 DeviceResources](https://github.com/walbourn/directx-vs-templates/blob/master/d3d11game_win32_dr/DeviceResources.cpp).

> For anyone who has looked at [D3D12 on Windows 7](https://microsoft.github.io/DirectX-Specs/d3d/D3D12onWin7.html), there's a lot of weirdness and limitations around handling the swapchain present since Windows 7 doesn't support the newer flip modes.

See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_swap_effect)

# Scaling modes

Another swap chain feature introduced with DirectX 11.1/Window 8/DXGI 1.2 was controlling how to handle the case where the "swapchain buffer" was not the same dimension as the target output window. ``DXGI_SCALING_STRETCH`` was the original behavior of doing a StretchBlt, with ``DXGI_SCALING_NODE`` being an option to have the image just drawn in the middle with a background color (only supported for ``DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL``).

A more interesting ``DXGI_SCALING_ASPECT_RATIO_STRETCH`` mode was added for Windows Phone 8 and Windows 10/DXGI 1.4, which automatically supports "letter-boxing". It's an awesomely useful mode for dealing with scaling backbuffer size for performance (most on that later), but alas is only implemented for "CoreWindow" and "DirectComposition"-enabled Windows, not classic Win32 windows.

See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/api/dxgi1_2/ne-dxgi1_2-dxgi_scaling)

# Gamma-correct rendering

This bring us to the first major behavioral difference between "old blt-style" and "new flip-style": the handling of sRGB colorspace formats for render targets. As for why it matters, I'm not going to explain it in detail here. There are a number of good references below, but in short when you read a pixel from your typical r8g8b8a8 texture, you need to *remove* the gamma curve, do all your lighting math, then *apply* the gamma curve as you write the pixel into your render target for everything to be "not too dark" and "not too bright".

There are two ways to express this behavior.

1. The **first** is to use ``DXGI_FORMAT_*_SRGB`` when you create the resource:

```cpp
// Create texture
D3D11_TEXTURE2D_DESC desc = {};
...
desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
hr = device->CreateTexture2D(&desc, nullptr, &tex);
```

When you create a ShaderResourceView or a RenderTargetView, you just default to using the same format as the resource:

```cpp
D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
srvDesc.Format = desc.Format;
hr = device->CreateShaderResourceView(tex, &srvDesc, &srv);
// -or-
hr = device->CreateShaderResourceView(tex, nullptr, &srv);
```

```cpp
D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
...
rtvDesc.Format = desc.Format;
hr = device->CreateRenderTargetView(tex, &rtvDesc, &rtv);
// -or-
hr = device->CreateRenderTargetView(tex, nullptr, &rtv);
```

2. The **second** way you can express the same thing is to use the non-sRGB format for the resource, but to create the view using the matching ``DXGI_FORMAT_*_SRGB`` format:

```cpp
// Create texture
D3D11_TEXTURE2D_DESC desc = {};
...
desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
hr = device->CreateTexture2D(&desc, nullptr, &tex);
```

When you create a ShaderResourceView or a RenderTargetView, you indicate it's to use the sRGB degamma/gamma behavior:

```cpp
D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
hr = device->CreateShaderResourceView(tex, &srvDesc, &srv);
```

```cpp
D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
...
rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
hr = device->CreateRenderTargetView(tex, &rtvDesc, &rtv);
```

Both approaches work, and the hardware does the exact same thing in both cases. The difference is that logically the resource is "just a bag of bits", where the sRGB gamma/de-gamma behavior is really an aspect of "interpreting the bits", i.e. part of the view.

> All the same logic applies for DirectX 12 using ``D3D12_RESOURCE_DESC``,  ``CreateCommittedResource``, ``CreateShaderResourceView``, and ``CreateRenderTargetView``.

## Backbuffers
So what does this have to do with a swap chain? If you are using the "blt-style" swap-effect, you can use **either** approach when setting up a gamma-correct 8-bit-per-channel render target.

1. Using the ``DXGI_FORMAT_*_SRGB`` format for the backbuffer:

```cpp
DXGI_SWAP_CHAIN_DESC1 scDesc = {};
scDesc.Width = backBufferWidth;
scDesc.Height = backBufferHeight;
scDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
scDesc.SampleDesc.Count = 1;
scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
scDesc.BufferCount = backBufferCount;
scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsDesc = {};
fsSwapChainDesc.Windowed = TRUE;

hr = dxgiFactory->CreateSwapChainForHwnd(device, hwnd, &scDesc,
    &fsDesc, nullptr, &swapchain);
if (FAILED(hr)) // error

hr = swapchain->GetBuffer(0, &backBuffer);
if (FAILED(hr)) // error

hr = device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
if (FAILED(hr)) // error
```

2. Use the non-sRGB format for the backbuffer, but the matching ``DXGI_FORMAT_*_SRGB`` for the view:

```cpp
DXGI_SWAP_CHAIN_DESC1 scDesc = {};
scDesc.Width = backBufferWidth;
scDesc.Height = backBufferHeight;
scDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
scDesc.SampleDesc.Count = 1;
scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
scDesc.BufferCount = backBufferCount;
scDesc.SwapEffect = ...;

DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsDesc = {};
fsSwapChainDesc.Windowed = TRUE;

hr = dxgiFactory->CreateSwapChainForHwnd(device, hwnd, &scDesc,
    &fsDesc, nullptr, &swapchain);
if (FAILED(hr)) // error

hr = swapchain->GetBuffer(0, &backBuffer);
if (FAILED(hr)) // error

D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
hr = device->CreateRenderTargetView(backBuffer, &rtvDesc, &rtv);
if (FAILED(hr)) // error
```

For the recommended for DirectX 11--required for DirectX 12 & UWP--"flip-style" swap effects, you can only use the _second_ definition. If you try to use the first one, you get the HRESULT ``DXGI_ERROR_INVALID_CALL`` (0x887a0001).

If you have [DXGI debugging](https://walbourn.github.io/dxgi-debug-device/) enabled, you'll get this "wall of text" debug output:

```
DXGI ERROR: IDXGIFactory::CreateSwapChain: Flip model swapchains
(DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL and DXGI_SWAP_EFFECT_FLIP_DISCARD)
only support the following Formats: (DXGI_FORMAT_R16G16B16A16_FLOAT,
DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM,
DXGI_FORMAT_R10G10B10A2_UNORM), assuming the underlying Device
does as well.
DXGI_SWAP_CHAIN_DESC{ SwapChainType = ..._HWND,
BufferDesc = DXGI_MODE_DESC1{Width = 800, Height = 600,
RefreshRate = DXGI_RATIONAL{ Numerator = 0, Denominator = 0 },
Format = B8G8R8A8_UNORM_SRGB, ScanlineOrdering = ..._UNSPECIFIED,
Scaling = ..._UNSPECIFIED, Stereo = FALSE },
SampleDesc = DXGI_SAMPLE_DESC{ Count = 1, Quality = 0 },
BufferUsage = 0x20, BufferCount = 2,
OutputWindow = 0x002B03F6, Scaling = ..._STRETCH, Windowed = TRUE,
SwapEffect = ..._FLIP_DISCARD, AlphaMode = ..._UNSPECIFIED,
Flags = 0x0 }
[ MISCELLANEOUS ERROR #101: ]
```

*I'll be adding more parts to this blog series soon to cover MSAA and Fullscreen...*

# Sample code

For a detailed C++ implementation handling this behavior, see:

* DeviceResources for DirectX 11 [Win32](https://github.com/walbourn/directx-vs-templates/blob/master/d3d11game_win32_dr/DeviceResources.cpp) and/or [UWP](https://github.com/walbourn/directx-vs-templates/tree/master/d3d11game_uwp_dr)
* DeviceResources for DirectX 12 [Win32](https://github.com/walbourn/directx-vs-templates/blob/master/d3d12game_win32_dr/DeviceResources.cpp) and/or [UWP](https://github.com/walbourn/directx-vs-templates/tree/master/d3d12game_uwp_dr)

# References
[Gamma correction](http://en.wikipedia.org/wiki/Gamma_correction)

[Linear-Space Lighting (i.e. Gamma)](http://filmicworlds.com/blog/linear-space-lighting-i-e-gamma/)

[Chapter 24. The Importance of Being Linear](https://developer.nvidia.com/gpugems/gpugems3/part-iv-image-effects/chapter-24-importance-being-linear), GPU Gems 3

[Gamma-correct rendering](https://blog.molecular-matters.com/2011/11/21/gamma-correct-rendering/)   

<b>See also:</b> <a href="https://walbourn.github.io/anatomy-of-direct3d-12-create-device/">Anatomy of Direct3D 12 Create Device</a>, <a href="https://walbourn.github.io/anatomy-of-direct3d-11-create-device/">Anatomy of Direct3D 11 Create Device</a>, <a href="https://walbourn.github.io/hdr-lighting-and-displays/">HDR Lighting and Displays</a>
