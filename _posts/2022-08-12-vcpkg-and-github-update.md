---
layout: post
title: vcpkg and GitHub Update
date: 2022-08-12 20:33
author: Chuck Walbourn
comments: true
categories: [github]
---

Over the summer I've made a few improvements to my GitHub project's CMake support and [vcpkg](https://vcpkg.io/) C++ Package Manager integration. In addition to updating for the July 2022 releases of *DirectX Tool Kit* [DX11](https://github.com/microsoft/DirectXTK/releases/tag/jul2022) / [DX12](https://github.com/microsoft/DirectXTK12/releases/tag/jul2022), [DirectXTex](https://github.com/microsoft/DirectXTex/releases/tag/jul2022), [DirectXMesh](https://github.com/microsoft/DirectXMesh/releases/tag/jul2022), and [UVAtlas](https://github.com/microsoft/UVAtlas/releases/tag/jul2022), I've done some work on some related vcpkg ports as well, which I've summarized in this blog post.
<!--more-->

First, note that the July 2022 release of *DirectX Tool Kit for DX11* has a minor *breaking change*. The ``bool forceSRGB`` parameter for the DDSTextureLoader Ex functions is now a `DDS_LOADER_FLAGS` typed enum bitmask flag parameter. This may have a breaking change impact to client code. Replace true with `DDS_LOADER_FORCE_SRGB` and false with `DDS_LOADER_DEFAULT`. This makes it consistent with earlier changes to the other libraries covered in [this blog post](https://walbourn.github.io/modern-c++-bitmask-types/).

Second, I updated all my various CMake projects to use the latest recommended build switches for the **Secure Development Lifecycle** (SDL) requirements where supported by the compiler toolset:
``/ZH:SHA_256``, ``/guard:ehcont``, ``/CETCOMPAT``, etc.

# directx-headers

The [DirectX-Headers](https://github.com/microsoft/DirectX-Headers/) GitHub project has done some new releases in support of the [latest DirectX 12 Agility SDK](https://devblogs.microsoft.com/directx/2022-summer-agility-sdks/), specifically v1.606.3. I updated **directxtk12** and **directxtex** for this new version, and verified **directxmesh**  builds with it.

In addition to some new DirectX 12 features, this new version of the headers fixes a Application Binary Interface (ABI) compat issue some DirectX 12 APIs when building with non-MSVC-like compiler, specifically MinGW which vcpkg supports via [community triplets](https://github.com/microsoft/vcpkg/blob/master/docs/users/mingw.md). This requires passing in a description structure as the first parameter for the various ``GetDesc()`` methods when building with MinGW and DirectX 12. I updated  **directxtk12**, **directxtex**, and the copy of D3DX12 in [directx-vs-templates](https://github.com/microsoft/directx-vs-templates) to support this as well. For more details, see [The Old New Thing blog](https://devblogs.microsoft.com/oldnewthing/20220113-00/?p=106152).

I verified the following MinGW triplets build for my libraries on a x64 native host:

```
vcpkg install directxmesh:x64-mingw-static
vcpkg install directxmesh[dx12]:x64-mingw-static --recurse
vcpkg install directxmesh:x86-mingw-static
vcpkg install directxmesh[dx12]:x86-mingw-static --recurse

vcpkg install directxtex:x64-mingw-static
vcpkg install directxtex[dx12]:x64-mingw-static --recurse
vcpkg install directxtex:x86-mingw-static
vcpkg install directxtex[dx12]:x86-mingw-static --recurse

vcpkg install directxtk:x64-mingw-static
vcpkg install directxtk[xaudio2redist]:x64-mingw-static
vcpkg install directxtk:x86-mingw-static
vcpkg install directxtk[xaudio2redist]:x86-mingw-static

vcpkg install directxtk12:x64-mingw-static
vcpkg install directxtk12[xaudio2redist]:x64-mingw-static
vcpkg install directxtk12:x86-mingw-static
vcpkg install directxtk12[xaudio2redist]:x86-mingw-static

vcpkg install uvatlas:x64-mingw-static
vcpkg install uvatlas:x86-mingw-static
```

# directx-dxc

The latest DirectX 12 DXC compiler is available from the [DirectXShaderCompiler](https://github.com/microsoft/DirectXShaderCompiler) project on GitHub. I created the **directx-dxc** port to use the released binaries and dxcompiler library. With their July 2022 release (which added Shader Model 6.7 support), they provide both an x64 and ARM64 native version of the binaries. I make use of the **directx-dxc** port as a ``host: true`` tools port for the **directxt12** port.

# cppwinrt

While working on updating the CMake support for the UWP C++/WinRT template in [directx-vs-templates](https://github.com/microsoft/directx-vs-templates), I noticed the **cppwinrt** port was, well, more than "basic". All it did was error out if you had too old a Windows SDK installed.

I updated the **cppwinrt** port to instead use the ``Microsoft.Windows.CppWinRT`` from NuGet to obtain the latest ``cppwinrt.exe`` tool, and then the "vcpkg install cppwinrt" command will generate the latest version of the C++/WinRT projection from your currently installed Windows SDK.

> Note that currently the ``cppwinrt.exe`` provided on NuGet is x64 native only. It will run on a Windows 11 for ARM64 system via emulation.

# xaudio2redist

This vcpkg port was updated for the v1.2.9 release of ``Microsoft.XAudio2.Redist`` on NuGet. The **directxtk** CMake already supported using this vcpkg port, but I also added support for it to the  **directxtk12** port in order to support building *DirectX Tool Kit for Audio* with XAudio2 using MinGW.

# dstorage

Note that there is also a vcpkg port for the ``Microsoft.Direct3D.DirectStorage``NuGet package version 1.0.2 available.

<strong>Related:</strong> [DirectXTex, DirectXMesh and UVAtlas now support Linux](https://walbourn.github.io/directxtex-directxmesh-and-uvatlas-now-support-linux/), [Legacy D3DX on NuGet](https://walbourn.github.io/legacy-d3dx-on-nuget/), [DirectXMath 3.17](https://walbourn.github.io/directxmath-3.17/)
