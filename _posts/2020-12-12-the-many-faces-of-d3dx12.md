---
layout: post
title: The Many Faces of D3DX12
date: 2020-12-12 12:01
author: Chuck Walbourn
comments: true
categories: [direct3d]
---

The "DirectX Utility Library" (a.k.a. D3DX) has a long and complex history, which has resulted in a lot of confusion for developers. A key design point for D3DX is that it's not meant to be "required", and started life as a way to simplify DirectX programming for new developers. The library was it's most "feature rich" with D3DX9 with helpers for sprite rendering, drawing text, 3D graphics linear algebra math, loading/saving textures in bitmaps, image resizing & format conversion, DXT texture codecs, tangent frame & mipmap generation, the HLSL compiler, an effects (FX) system, shader reflection, a model & animation system, and a slew of other technology projects such as progressive mesh (p-mesh), vertex cache optimization, isochart texture atlasing, and Precomputed Radiance Transfer (RPT) using Spherical Harmonics.

In other words it became an untenable mess of closed-source software that you couldn't really avoid, rife with potential security risks, which had a complex servicing and deployment story. From the lessons of those years, the DirectX team took a very different approach for D3DX for DirectX 12, a.k.a. D3DX12.
<!--more-->

The D3DX12 library is first of all, truly **optional**. It's not included in the Windows 10 SDK with the ``d3d12.h`` or DXGI headers--a fact which does have some complexities discussed below.

D3DX12 is **open-source** under the [MIT License](https://opensource.org/licenses/MIT). In fact, it's an all inline header so all the code is visible. There is no link library, no DLL to deploy, and developers can change any aspect of the code as they need to. It can be cut & pasted into their projects, or used "as is".

The D3DX12 Utility header is **focused** on use for runtime rendering with the DirectX 12 API. It does not include any functionality tied to other APIs like math, image loaders, or sprites. It doesn't implement any of it's own file formats, or do any I/O.

# What's in it?

The bulk of the ``D3DX12.h`` header are C++ class versions of the core C-style API structs. For Direct3D 11, these were in the core ``d3d11.h`` headers--you could define the preprocessor symbols  ``D3D11_NO_HELPERS`` and/or ``D3D11_VIDEO_NO_HELPERS`` to turn them off. Things like ``CD3D12_RECT``, ``CD3DX12_VIEWPORT``, ``CD3DX12_BLEND_DESC``, ``CD3DX12_RASTERIZER_DESC``, etc. which provides C++ constructors and reasonable defaults. There are also a few utility functions sprinkled in as well, such as ``D3D12CalcSubresource``.

D3DX12 does not include code for loading/saving bitmaps as textures, but it does have the ``UpdateSubresources`` helpers to simplify basic texture transfer from CPU memory to GPU memory--something that in DirectX 11 was handled behind the scenes.

Lastly there's a set of "State Object Creation Helpers" intended for use with DirectX Raytracing (DXR) and the new Amplification & Mesh shaders. These shader stages do not have dedicated description structures in the Pipeline State Object (PSO), and instead make use of a 'stream' data description which these helpers can build. Note you can disable these by defining ``D3DX12_NO_STATE_OBJECT_HELPERS`` if you don't need them in your application.

There's a summary of the content in the header on my [DirectX Tool Kit for DX12 wiki](https://github.com/microsoft/DirectXTK12/wiki/DirectXHelpers) and they are documented on [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/direct3d12/helper-structures-and-functions-for-d3d12)

# Getting the latest D3DX12 header

Since it's optional and not the Windows 10 SDK, there's a number of ways to obtain ``d3dx12.h``. The Visual Studio "DirectX12 App" templates for UWP development come with a copy if it. I include the header in my [Direct3D 12 Game VS Templates](https://walbourn.github.io/direct3d-game-visual-studio-templates-redux/) for similar reasons.

Officially the 'latest and greatest' version can be obtained from [GitHub](https://github.com/Microsoft/DirectX-Graphics-Samples/tree/master/Libraries/D3DX12). The key thing to remember is that this version assumes you are using the latest public Windows 10 SDK (at this point, that would be Windows 10 SDK 19041). If you use an older SDK, that version of ``d3dx12.h`` won't compile.

While you can use an older version, there's been a number of minor fixes and I've done a lot of clang/LLVM C++ conformance work for the latest versions as well. I maintain the version on [directx-vs-templates](https://github.com/walbourn/directx-vs-templates/blob/master/d3d12game_win32_dr/d3dx12.h) to match the latest public one, but mine has a bunch of conditional compilation preprocessor stuff so it will build with older Windows 10 SDKs.

> Because Xbox developers use a specialized version of DirectX for their development, the matching D3DX12 utility header is called ``d3dx12_x.h`` and/or ``d3dx12_xs.h`` which are  part of that development environment's include paths.

# What about everything else?

Of course, there was a lot of really *useful* stuff in the legacy D3DX library. It was just trying to be too many things at once. In the years since the standalone DirectX SDK was [deprecated](https://docs.microsoft.com/en-us/windows/win32/directx-sdk--august-2009-) in favor of a integrated Windows SDK, I've put a lot of effort into extracting and refactoring that old code base into a more modern, open-source form. [DirectXMath](https://walbourn.github.io/introducing-directxmath/), [DirectXTex](https://walbourn.github.io/directxtex/), *DirectX Tool Kit* [DX11](https://walbourn.github.io/directxtk/) / [DX12](https://walbourn.github.io/directx-tool-kit-for-directx-12/), [DirectXMesh](https://walbourn.github.io/directxmesh/), and [UVAtlas](https://walbourn.github.io/uvatlas-return-of-the-isochart/) are all direct results of that work. These support DirectX 11 and DirectX 12 development, and in a [few cases](https://walbourn.github.io/directx-tool-kit-for-audio-updates-and-a-direct3d-9-footnote/) some legacy Direct3D 9 scenarios.

> The D3DCompiler API and HLSL Compiler for Shader Model 2 through 5 is still closed-source, but is in it's own DLL and is side-by-side redistributable with applications. See [HLSL, FXC, and D3DCompile](https://walbourn.github.io/hlsl-fxc-and-d3dcompile/).

> The Shader Model 6 DXIL compiler is on [GitHub](https://github.com/Microsoft/DirectXShaderCompiler)

# Credit where credit is due

I did want to end this post with a big thank you to all the Microsoft engineers who worked on D3DX over the years. Like most large corporations, the products Microsoft ships are a reflection of the organization, culture, and processes at the time and D3DX is no exception. In it's heyday, it was the best way to innovate and ship useful technology to game developers quickly, much faster than the traditional Windows development cycle.

I believe the open source approach is a much improved model for this kind of 'useful optional stuff', and that also is a reflection of changes in Microsoft culture and processes. The GitHub libraries I created were all intended to honor the great work done for D3DX over the years, and keep it relevant for modern DirectX development.

**See also:** [Living without D3DX](https://walbourn.github.io/living-without-d3dx/), [The Zombie DirectX SDK](https://walbourn.github.io/the-zombie-directx-sdk/)
