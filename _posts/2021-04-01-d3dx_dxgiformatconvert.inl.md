---
layout: post
title: D3DX_DXGIFormatConvert.inl - Back from the dead
date: 2021-04-01 23:22
author: Chuck Walbourn
comments: true
categories: [dxsdk]
---

In the DirectX SDK (June 2010) release, there was this release note:

> The new D3DX_DXGIFormatConvert.inl inline header includes light-weight conversion functions for use in Compute Shaders or Pixel Shaders on D3D11 Hardware that can be useful when applications need to simultaneously read and write to textures, such as in-place editing scenarios.

A number of developers found it useful, including [Tom Forsyth](https://tomforsyth1000.github.io/blog.wiki.html). Unfortunately, the header more or less disappeared after that. This [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/direct3dhlsl/dx-graphics-hlsl-unpacking-packing-dxgi-format) page mentions the header, but hasn't mentioned *where* to find it in over a decade...
<!--more-->

When I created the [Microsoft.DXSDK.D3DX](https://www.nuget.org/packages/Microsoft.DXSDK.D3DX) NuGet, I included the ``D3DX_DXGIFormatConvert.inl`` header. See [this blog post](https://walbourn.github.io/legacy-d3dx-on-nuget/) for more on the package.

In order to support potential contributions or bug-reports for this header, I set up a little [GitHub](https://github.com/walbourn/dxgiformatconvert) project to host this header and some related test code. You can obtain it from there as well.

This file can be built in both C++ and HLSL. For C++, the original June 2010 version relied on XNAMath which was part of the legacy DirectX SDK. The 9.29.952.3 and 9.29.952.7 versions of the NuGet package includes this original version.

I've recently updated both the header and the NuGet package to make use of DirectXMath instead when building with C++, which is part of the Windows 8.x SDK and Windows 10 SDK. This is included in ``Microsoft.DXSDK.D3DX`` version 9.29.952.8 or later. You can also obtain DirectXMath from [GitHub](https://github.com/microsoft/DirectXMath).
