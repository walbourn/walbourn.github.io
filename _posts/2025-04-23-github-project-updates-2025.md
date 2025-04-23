---
layout: post
title: GitHub Project Updates 2025
date: 2025-04-23 09:37
author: Chuck Walbourn
comments: true
categories: [github]
---


I've completed my first releases of 2025 for my various GitHub projects, and there are some changes I felt were worth highlighting. This includes updates to _DirectX Tool Kit_ for both [DX11](https://github.com/microsoft/DirectXTK/releases/tag/mar2025) and [DX12](https://github.com/microsoft/DirectXTK12/releases/tag/mar2025), [DirectXTex](https://github.com/microsoft/DirectXTex/releases/tag/mar2025), [DirectXMesh](https://github.com/microsoft/DirectXMesh/releases/tag/mar2025), [UVAtlas](https://github.com/microsoft/UVAtlas/releases/tag/mar2025), and [DirectXMath](https://github.com/microsoft/DirectXMath/releases/tag/apr2025) as well as a number of changes to my [NuGet](https://docs.microsoft.com/en-us/nuget/what-is-nuget) packages in particular.

<!--more-->

# Windows 7 and Windows 8.0 Retirement

I've removed all codepaths for supporting Windows 7 and Windows 8.0 from my libraries. The minimum supported operating system is now Windows 8.1 or later. Windows 7 hit [end of life](https://walbourn.github.io/twilight-for-windows-7/) five years ago, and Windows 8.0 has been out of support for years as well. I could have gone so far as to remove Windows 8.1 support since that hit [end of life](https://walbourn.github.io/windows-8.x-now-out-of-support/) two years ago, but I kept it for now primarily because I still have legacy Xbox One XDK support for a few of the libraries which uses the `0x0602` codepaths.

As part of these changes I simplified *DirectX Tool Kit for Audio* projects considerabilty and no longer have secondary `vcxproj` files for various XAudio2 versions. Instead, the **DirectXTK_Desktop_20xx** projects build for Windows 8.1 and XAudio 2.8. The **DirectXTK_Desktop_20xx_Win10** projects build for Windows 10 or later and use XAudio 2.9.

> The *directxtk_desktop_2019* NuGet package no longer uses the XAudio2Redist package and just uses XAudio 2.8. The *directxtk\[12\]_desktop_win10* NuGet packages continue to use XAudio 2.9. If you want to use XAudio2Redist, this is still supported by the CMake projects.

For GamePad and building using XInput, I assume XInput 1.4 is present rather than using XInput 9.1.0 for 'downlevel' support which was required for Windows 7. Note I actively avoid using legacy DirectX SDK XInput 1.3 as it requires legacy DXSetup to deploy and has known security bugs.

# GameInput v1 API Support

Speaking of the *DirectX Tool Kit* input classes. The GameInput implementation now supports both the original `GAMEINPUT_API_VERSION` of 0 and can now build for the new `GAMEINPUT_API_VERSION 1` release from *Game Developer Conference* last month. See [Microsoft Learn](https://learn.microsoft.com/gaming/gdk/_content/gc/input/overviews/input-versioning) for more details. GameInput v1 for PC is available on [NuGet](https://www.nuget.org/packages/Microsoft.GameInput) and [vcpkg](https://github.com/microsoft/vcpkg/tree/master/ports/gameinput). Be sure to run `GameInputRedist.msi` on your development system and include it in your redistribution.

> To make use of GameInput v1 on PC, use the CMake option ``BUILD_GAMEINPUT``. The *directxtk* and *directxk12* vcpkg ports both offer *gameinput* features.

> For Xbox One and Xbox Series X\|S using the Microsoft GDK with Xbox extensions, it still uses the GameInput v0 API.

# DirectX Tool Kit for Audio

In my original implementation using X3DAudio for *DirectX Toolkit for Audio*, I made use of `X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER | X3DAUDIO_CALCULATE_LPF_DIRECT` and if there was reverb I also added `X3DAUDIO_CALCULATE_LPF_REVERB | X3DAUDIO_CALCULATE_REVERB`. I also set the use of `X3DAUDIO_CALCULATE_REDIRECT_TO_LFE` for speaker configs with an LFE channel.

I reworked this implementation as follows:

* **AudioEngine_DisableLFERedirect** turns off the default use of `X3DAUDIO_CALCULATE_REDIRECT_TO_LFE` if the speaker config has a LFE channel.

* **AudioEngine_DisableDopplerEffect** turns off the use of `X3DAUDIO_CALCULATE_DOPPLER` for all cases.

* **AudioEngine_ZeroCenter3D** adds the use of `X3DAUDIO_CALCULATE_ZEROCENTER` for all cases.

* The **SoundEffectInstance_UseRedirectLFE** was originally marked as 'internal only' but is now used to enable `X3DAUDIO_CALCULATE_REDIRECT_TO_LFE` on a per-voice basis if you are also using *AudioEngine_DisableLFERedirect*.

* The **SoundEffectInstance_ZeroCenter3D** flags allows setting `X3DAUDIO_CALCULATE_ZEROCENTER` on a per-voice basis if not using *AudioEngine_ZeroCenter3D*.

> For the *DirectX Tool Kit for DX11* CMake project, I renamed the option `BUILD_XAUDIO_WIN7` to `BUILD_XAUDIO_REDIST` which is consistent with *DirectX Tool Kit for DX12*.

> The latest [XAudio2Redist](https://aka.ms/XAudio2Redist) now includes x86, x64, and ARM64 binaries.

# Deprecation of ARM64 using VS 2019

In a recent service release of [Windows 11 SDK (26100)](https://walbourn.github.io/windows-sdk-for-windows-11,-version-24h2/), support for VS 2019 when building for ARM64 was dropped. I have made all ARM64 binaries use VS 2022 per the recommendation of the compiler team.

* The *xyz_desktop_2019* NuGet packages now support only x86 and x64 and are built with VS 2019. This is forward compatible for VS 2022 as well.

* The *xyz_uwp* NuGet packages all require VS 2022 as of last October 2024 releases.

* The *xyz_desktop_win10* NuGet packges are built with VS 2022 and include x86, x64, and ARM64. Note I added new *directxtk12_desktop_win10* and *uvatlas_desktop_win10* NuGet packages for this scenario.

Windows on ARM 32-bit support was removed last year due to deprecation per [Microsoft Learn](https://learn.microsoft.com/windows/arm/arm32-to-arm64).

# CMake support for generating shared library DLLs

For many years, I have focused on only supporting C++ static linking for my GitHub projects. I have occassionaly gotten requests for DLL shared lib support, but didn't want to manage a lot of extra `vcxproj` files and macros. I've since added support to the CMake projects using `BUILD_SHARED_LIBS`. The GitHub projects can therefore be built as either static C++ libraries or DLLs using CMake. The MSBuild projects are all still C++ static libraries only.

For vcpkg scenarios, this means that if you use *x64-windows* then you will get a DLL instead of a static C++ library for these projects. The CMake target will automatically set the required import preprocessor define. For vcpkg+MSBuild integration, you have to define it in your project settings directly.

|Library as a DLL|Preprocessor define|
|---|---|
|DirectXTex|<code>DIRECTX_TEX_IMPORT</code>|
|DirectXMesh|<code>DIRECTX_MESH_IMPORT</code>|
|DirectXTK<br />DirectXTK12|<code>DIRECTX_TOOLKIT_IMPORT</code>|
|UVAtlas|<code>UVATLAS_IMPORT</code>|

If you still want a static C++ library, then use *-static* or *-static-md* triplets instead (i.e. *x64-windows-static-md*).

> In the process of adding this functionality, I found a bug in the [xbox community triplets](https://walbourn.github.io/vcpkg-now-supports-targeting-xbox/) toolchain file when building for a DLL instead of as a static library. This is fixed as of [this commit](https://github.com/microsoft/vcpkg/commit/20224c957c951946400d69c8a2891f31dfbce2cf).

BTW, the *ctest* test suites for these projects all support either `BUILD_SHARED_LIBS` setting. Some of the additional 'white box' tests are skipped in the DLL version since those entry-points are not exported.

# DirectXMath

The DirectXMath 3.20b release is a minor update. The only code change is that the `XM_DEPRECATED` macro will use the C++14 ``[[deprecated]]`` standard attribute instead of various compiler-specific solutions when appropriate.

The primary purpose of this release was to update the CMake project to add ``BUILD_XDSP``, ``BUILD_SHMATH``, ``BUILD_DX11``, and ``BUILD_DX12`` options for the optional [XDSP](https://walbourn.github.io/xdsp-h-digital-signal-processing-helper-functions/) and [SHMath](https://walbourn.github.io/spherical-harmonics-math/) libraries, which are used by the latest vcpkg port.

# Future plans

I have a few feature requests pending that I will be working on over the coming months. The main 'break change' I plan for later this year is to move the CMake minimum version up to 3.21 instead of 3.20. Visual Studio 2019 16.11 only came with CMake 3.20 which is why I currently use that, and Visual Studio 2022 originally shipped with 3.21. You can combine newer CMake installs with the VS 2019 toolset, but for now I wanted to keep it simple.
