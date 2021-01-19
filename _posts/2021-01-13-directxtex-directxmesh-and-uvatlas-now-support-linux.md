---
layout: post
title: DirectXTex, DirectXMesh and UVAtlas now support Linux
date: 2021-01-13 01:33
author: Chuck Walbourn
comments: true
categories: [github]
---

At BUILD 2020 last year, Microsoft gave an update on [Windows Subsystem for Linux](https://devblogs.microsoft.com/commandline/the-windows-subsystem-for-linux-build-2020-summary/), along with an announcement about [DirectX coming to WSL](https://devblogs.microsoft.com/directx/directx-heart-linux/). As part of that effort, there are now DirectX 12 headers available under the MIT license on [GitHub](https://github.com/microsoft/DirectX-Headers) including support for building on Linux. Over the winter break, I took a little time to dig into [WSL](https://docs.microsoft.com/en-us/windows/wsl/install-win10), the C++ [vcpkg](https://github.com/Microsoft/vcpkg) package manager, and--since I got a Surface Pro X for Christmas--I could even try out WSL for both x64 and ARM64.
<!--more-->

The January 2021 releases of [DirectXTex](https://github.com/microsoft/DirectXTex/releases), [DirectXMesh](https://github.com/microsoft/DirectXMesh/releases), and [UVAtlas](https://github.com/microsoft/UVAtlas/releases) support building for Linux. The bulk of these three libraries don't actually make use of DirectX, so those portions should work on the Linux platform generally. That said, I make use of C++17 for non-Win32 platforms, so you need GCC 9 or later to build the code. This includes DDS, HDR, and TGA reader/writers, BC software codecs, mesh vertex cache optimization, isochart, etc.

The support for DirectX 11 is not built for Linux. The DirectX12 support will be available for x64 on WSL but will require linking to WSL DirectX libraries to use at runtime. As a bonus, I also updated the 'standalone' versions of DDSTextureLoader12 and ScreenGrab12 included in the DirectXTex package to support WSL. The Windows Imaging Component (WIC) is not supported for WSL, so there's no WICTextureLoader12 or other WIC-based reader/writers available.

> There are January 2021 releases of *DirectX Tool Kit* [DX11](https://github.com/microsoft/DirectXTK/releases) / [DX12](https://github.com/microsoft/DirectXTK12/releases), but these *do not* have Linux support. They do include updates for the CMake projects to support 'install' which is leveraged by the latest vcpkg ports for these libraries. I did update a few parts of these libraries to support GCC, specifically SimpleMath, so you can use that module standalone on Linux.

DirectXTex, DirectXMesh, and UVAtlas require the latest [DirectXMath](https://github.com/microsoft/DirectXMath/releases) and [DirectX-Headers](https://github.com/microsoft/DirectX-Headers/releases) to build. These are referenced using the standard CMake package system, so you can always build, install, and provide the paths yourself. Alternatively, you can make use of [vcpkg](https://docs.microsoft.com/en-us/cpp/build/vcpkg). The latest vcpkg ports handle all these dependencies automatically.

## vcpkg for Linux
```
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
sh bootstrap-vcpkg.sh
./vcpkg install directx-headers
./vcpkg install directxmath
./vcpkg install directxtex
./vcpkg install directxmesh
./vcpkg install uvatlas
```

I should mention that I only support Linux for the libraries. There's a lot going in the various command-line tools (``texconv``, ``meshconvert``, ``uvatlastool``, etc.) that I didn't have time to fully work through for a non-Windows platform.

## vcpkg for Windows
```
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
vcpkg install directx-headers
vcpkg install directxmath
vcpkg install directxtex
vcpkg install directxtk
vcpkg install directxtk12
vcpkg install directxmesh
vcpkg install uvatlas
```

<b>Visual C++ Team Blog</b>: <a href="https://devblogs.microsoft.com/cppblog/c-with-visual-studio-2019-and-windows-subsystem-for-linux-wsl/">C++ with Visual Studio 2019 and Windows Subsystem for Linux (WSL)</a>, <a href="https://devblogs.microsoft.com/cppblog/c-with-visual-studio-and-wsl2/">C++ with Visual Studio and WSL2</a>
