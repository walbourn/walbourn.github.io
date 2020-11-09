---
layout: post
title: Care and Feeding of Modern Swap Chains (part 2)
date: 2020-11-08 22:22
author: Chuck Walbourn
comments: true
categories: [direct3d]
---

In [part 1](https://walbourn.github.io/care-and-feeding-of-modern-swapchains/), I covered the split between "blt-style" and "flip-style" swap effects, and in particular the handling of gamma-correct rendering. In this post, I'll be addressing implementation of Multi-Sample Anti-Aliasing (MSAA).
<!--more-->

# Multi-Sample Anti-Aliasing (MSAA)

If you look at a classic DirectX 10 or DirectX 11 tutorial on MSAA, the instructions are to modify the creation of the swap chain. I  also followed this simple pattern in my [DirectX Tool Kit for DX11](https://github.com/microsoft/DirectXTK/wiki/Line-drawing-and-anti-aliasing) tutorial on the topic:

* Set the backbuffer for multiple samples:

```cpp
DXGI_SWAP_CHAIN_DESC1 csDesc = {};
csDesc.Width = backBufferWidth;
csDesc.Height = backBufferHeight;
csDesc.Format = backBufferFormat;
csDesc.SampleDesc.Count = 4; // <-- 4x MSAA
csDesc.SampleDesc.Quality = 0;
csDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
csDesc.BufferCount = backBufferCount;
scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
```

* Set the depth/stencil buffer for multiple samples:

```cpp
D3D11_TEXTURE2D_DESC dsvDesc = {};
dsvDesc.Width = backBufferWidth;
dsvDesc.Height = backBufferHeight;
dsvDesc.MipLevels = 1;
dsvDesc.ArraySize = 1;
dsvDesc.Format = depthBufferFormat;
dsvDesc.SampleDesc.Count = 4; // <-- 4x MSAA
dsvDesc.SampleDesc.Quality = 0;
dsvDesc.Usage = D3D11_BIND_DEPTH_STENCIL;
```

* Make sure you are using ``D3D11_RTV_DIMENSION_TEXTURE2DMS`` for the render target view, and ``D3D11_DSV_DIMENSION_TEXTURE2DMS`` for the depth/stencil view--or just use the default description of ``nullptr``.

* In your raster state, make sure you have ``D3D11_RASTERIZER_DESC.MultisampleEnable`` set to ``TRUE``.

## Out with the old

If you change the line above to use 'flip-style' instead of the old 'blt-style':

```cpp
scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
```

Then the creation of the swapchain will fail with HRESULT ``DXGI_ERROR_INVALID_CALL`` (0x887a0001).

If you have [DXGI debugging](https://walbourn.github.io/dxgi-debug-device/) enabled, you'll get this "wall of text" debug output:

```
DXGI ERROR: IDXGIFactory::CreateSwapChain: Flip model swapchains
(DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL and
DXGI_SWAP_EFFECT_FLIP_DISCARD) do not support
multisampling.
DXGI_SWAP_CHAIN_DESC{ SwapChainType = ..._HWND,
BufferDesc = DXGI_MODE_DESC1{Width = 800, Height = 600,
RefreshRate = DXGI_RATIONAL{ Numerator = 0, Denominator = 0 },
Format = B8G8R8A8_UNORM, ScanlineOrdering =
..._UNSPECIFIED,
Scaling = ..._UNSPECIFIED, Stereo = FALSE },
SampleDesc = DXGI_SAMPLE_DESC{ Count = 4, Quality = 0 },
BufferUsage = 0x20, BufferCount = 2,
OutputWindow = 0x00410976, Scaling = ..._STRETCH, Windowed = TRUE,
SwapEffect = ..._FLIP_DISCARD, AlphaMode = ..._UNSPECIFIED, Flags = 0x0 }
[ MISCELLANEOUS ERROR #102: ]
```

The reason it failed is that while this set up is extremely simple for toy samples, it's **not** how any real rendering pipeline or game uses MSAA.

## In with the new

With the older setup, the swapchain is doing an implicit "resolve" from the multiple samples to a single sample as part of present. This step is hidden from the developer, and in almost all cases there's a lot more to this process before the final image is presented.

Typically a game will render scene to a number of render targets, possibly using MSAA for some of them, then combine all the images directly. After that is a few passes of 'post-process' to do more to the image like blurs, blooms, glow, tone-mapping for HDR, color-toning, compositing of user-interface (UI or HUD), etc. That means the resolve happens *well before* the present.

For new "flip-style" swapchains, you *never* set ``SampleDesc.Count`` to anything but 1. If you want to do MSAA, your create your own MSAA render targets and use those.

This is also in-keeping with the DirectX 12 "no runtime magic" design. See the[DirectX Tool Kit for DX12](https://github.com/microsoft/DirectXTK12/wiki/Line-drawing-and-anti-aliasing) tutorial.

# Sample code

For a detailed C++ implementation handling this behavior including interactions with gamma-correct rendering, see:

* DirectX 11 [Win32](https://github.com/microsoft/Xbox-ATG-Samples/tree/master/PCSamples/IntroGraphics/SimpleMSAA_PC) and/or [UWP](https://github.com/microsoft/Xbox-ATG-Samples/tree/master/UWPSamples/IntroGraphics/SimpleMSAA_UWP)
* DirectX 12 [Win32](https://github.com/microsoft/Xbox-ATG-Samples/tree/master/PCSamples/IntroGraphics/SimpleMSAA_PC12) and/or [UWP](https://github.com/microsoft/Xbox-ATG-Samples/tree/master/UWPSamples/IntroGraphics/SimpleMSAA_UWP12)

# Known issue

When using MSAA + sRGB color space resources, there are some bugs in older versions of Windows 10's runtime validation layer. If you attempt "resolve" directly from an ``DXGI_FORMAT_*_SRGB`` MSAA resource to a non-sRGB resource, the function returns a failure. This limitation is fixed in Windows 10 Creators Update (Version 1703, build 15063) for DirectX 12, and the same bug for DirectX 11 is fixed in Windows 10 Fall Creators Update (Version 1709, build 16299) / Windows Server 2016 (Version 1709).

> Versions older than 1709 are out of the [support lifecycle](https://docs.microsoft.com/en-us/lifecycle/faq/windows), so this shouldn't be an issue in practice.

<b>See also:</b> <a href="https://walbourn.github.io/anatomy-of-direct3d-12-create-device/">Anatomy of Direct3D 12 Create Device</a>, <a href="https://walbourn.github.io/anatomy-of-direct3d-11-create-device/">Anatomy of Direct3D 11 Create Device</a>, <a href="https://walbourn.github.io/hdr-lighting-and-displays/">HDR Lighting and Displays</a>
