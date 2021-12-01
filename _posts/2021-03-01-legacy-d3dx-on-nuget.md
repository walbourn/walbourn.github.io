---
layout: post
title: Legacy D3DX on NuGet
date: 2021-03-01 15:45
author: Chuck Walbourn
comments: true
categories: [dxsdk]
---

If you've been following this blog for any period of time, you know that much of it has been spent explaining the [deprecated](https://docs.microsoft.com/en-us/windows/win32/directx-sdk--august-2009-) nature of the legacy DirectX SDK, and the options for avoiding the need for it. For Direct3D 11 or later, there's plenty of [good replacement options](https://walbourn.github.io/living-without-d3dx/) that are open source, written in modern C++, and simple to include without using a [legacy redist](https://walbourn.github.io/not-so-direct-setup/) solution. Despite all that, there are still some scenarios where D3DX9, D3DX10, and/or D3DX11 are a necessity. There's now a new option for using D3DX that avoids the need for both the legacy *DirectX SDK* and the *DirectX End-User Runtime* (DXSETUP): The [Microsoft.DXSDK.D3DX](https://www.nuget.org/packages/Microsoft.DXSDK.D3DX) NuGet package ([dxsdk-d3dx](https://github.com/microsoft/vcpkg/tree/master/ports/dxsdk-d3dx) on [vcpkg](https://vcpkg.io/)).
<!--more-->

As part of working through the mitigations for the [recent SHA-1 deprecation](https://walbourn.github.io/where-is-the-directx-sdk-2021-edition/), we were able to revisit the way that legacy D3DX9, D3XD10, and D3DX11 were provided. The NuGet package provides a method for using these deprecated libraries completely independent of the legacy DirectX SDK. Furthermore, the runtime DLLs required are now licensed for "application-local" deployment -and- are SHA-2 Authenticode signed. These *are functionality the same binaries* as the DirectX SDK (June 2010) release so there's no bug-fixes or other changes.

This NuGet package is intended to provide a supportable option for existing codebases, as well as for Direct3D 9 and/or Direct3D 10-based games. It can also be used for middleware engines or content tools that continue to rely on the D3DX11 deprecated utility library. **For new projects you should prefer to use the open source replacements instead. For on-going projects, plan to move to the open source replacements when feasible.**

* For the HLSL compiler, use the [D3DCompile API](https://docs.microsoft.com/en-us/windows/win32/api/d3dcompiler/) directly. ``D3DCompiler_47.dll`` is available for "application local" redistribution for Windows 7 or later. See [this blog post](https://walbourn.github.io/hlsl-fxc-and-d3dcompile/). For Windows 8.1 or Windows 10, it's already in the OS.

* For XAudio2 see the [XAudio2Redist](https://aka.ms/XAudio2Redist). The ``xaudio2redist.dll`` supports "application local" redistribution. If you require Windows 10, XAudio 2.9 is already in the OS.

* Use XInput 9.1.0 (Windows 7 or later) or XInput 1.4 (Windows 8 or later) instead of legacy XInput 1.3 per [this blog post](https://walbourn.github.io/xinput-and-windows-8/). These DLLS are included with the OS, so no redistribution is needed.

# Updating old samples

In order to provide test coverage for the NuGet package, I've ported the Direct3D 9, Direct3D 10, and DirectSound samples from the legacy DirectX SDK. I also included a few Direct3D 11 samples, although I'd strongly recommend looking at the fully modernized versions of Direct3D 11 samples on [directx-sdk-samples](https://github.com/walbourn/directx-sdk-samples/wiki) that use open source replacements exclusively.

These older samples build and run without the legacy DirectX SDK, and just use the Windows 10 SDK plus the ``Microsoft.DXSDK.D3DX`` NuGet package. You can find them published on [directx-sdk-legacy-samples](https://github.com/walbourn/directx-sdk-legacy-samples).

> The DirectSound samples use MFC, so you need to have the optional VS 2019 component *C++ MFC for latest v142 build tools (x86 & x64)* installed.

The only changes here were for updating the VC++ project files, a few minor VS 2019 warning fixes, and the NuGet. I removed *all references* to the ``DXSDK_DIR`` environment variable. I also eliminated all references to ``dxerr.lib`` and instead added the [dxerr code](https://walbourn.github.io/wheres-dxerr-lib/) to DXUT / DXUT11 directly.

# Application local deployment

When using the ``Microsoft.DXSDK.D3DX`` NuGet package, you *do not* need to run the *DirectX SDK* installer or the *DirectX End-User Runtime* as they use "application local" copies of the ``D3DX9$(D)_43.DLL``, ``D3DX10$(D)_43.DLL``, and/or ``D3DX11$(D)_43.DLL``.

When it comes time to ship your game or application, just ship the ``D3DX9_43.DLL``, ``D3DX10_43.DLL``, and/or ``D3DX11_43.DLL`` along with ``D3DCompile_43.DLL`` depending on your usage as part of your normal package. No need for administrative rights to install them, no need to use the DirectSetup API, no registry editing needed. See the NuGet [license](https://www.nuget.org/packages/Microsoft.DXSDK.D3DX/9.29.952.3/License) for more details.

> Note you cannot use D3DX9, D3DX10, and/or D3DX11 in a Universal Windows Platforms (UWP) or Xbox app. These DLLs will not pass WACK certification. For those cases, the open source route is the way to go.

> For Desktop Bridge "Centennial" apps in the Windows Store, you can use the "DirectX Framework Package" [Microsoft.DirectX.x86](https://aka.ms/directx_x86_appx) / [Microsoft.DirectX.x64](https://aka.ms/directx_x64_appx) to ship using D3DX9, D3DX10, and/or D3DX11.

# .X file APIs

One bonus here is that ``D3DX9_43.DLL`` includes an implementation of the X-File parser API. These are the [ID3DXFile](https://docs.microsoft.com/en-us/windows/win32/direct3d9/dx9-graphics-reference-d3dx-x-file) interface and related APIs. The ``D3DX9xof.H`` header and ``d3dx9.lib`` import library provide access to these APIs.

I plan to make use of it for ``meshconvert.exe`` in [DirectXMesh](https://github.com/microsoft/DirectXMesh) to support ``.X`` file import.

> You should avoid using the older ``IDirectXFile`` and ``d3dxof.lib`` import library. ``d3dxof.dll`` is a 32-bit only DLL and is not supported for x64 native applications.

<b>UPDATE</b>: The initial release of the ``Microsoft.DXSDK.D3DX`` package contained header files identical to those that shipped in the legacy DirectX SDK (June 2010). I've updated the package with some minor edits to the header files to better integrate with the modern Windows SDKs:

* ``D3DX_DXGIFormatConvert.inl`` updated to rely on DirectXMath rather than XNAMath for C++ support.
* ``WINAPI_FAMILY_DESKTOP_APP`` partitioning for the ``d3dx9.h``, ``d3dx10.h``, and ``d3dx11.h`` headers.
* Converted VS-style SAL to SAL2 for better code analysis support.

<b>See also:</b> [The Zombie DirectX SDK](https://walbourn.github.io/the-zombie-directx-sdk/)
