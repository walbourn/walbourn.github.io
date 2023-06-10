---
layout: post
title: Vcpkg now supports targeting Xbox
date: 2023-03-31 22:35
author: Chuck Walbourn
comments: true
categories: [vcpkg]
---

The [Vcpkg C++ library manager](https://vcpkg.io/) now supports targeting the Xbox platform using four new ‘community triplets’. This makes it easy for Xbox registered developers to take advantage of the thousands of open-source C++ libraries supported by vcpkg, and build them in a way that is compatible with the Xbox Game OS. This also provides a mechanism for open-source library maintainers to validate that their code will build against the `WINAPI_FAMILY_GAMES` partition used on Xbox.
<!--more-->

|Triplet|Description|
|---|---|
|x64-xbox-scarlett|Builds DLLs for Xbox Series X\|S|
|x64-xbox-scarlett-static|Builds static C++ libraries for Xbox Series X\|S|
|x64-xbox-xboxone|Builds DLLs for Xbox One|
|x64-xbox-xboxone-static|Builds static C++ libraries for Xbox One|

When using these triplets, code is built using the `WINAPI_FAMILY_GAMES` partition defined in the Windows SDK ([19041](https://walbourn.github.io/windows-10-may-2020-update-sdk/)) or later. DLLs are linked using API Sets rather than legacy `KERNEL32.DLL` and friends. The code is always built using the Dynamic CRT as static C/C++ Runtime linking is not generally supported for Xbox development. The choice of Xbox console then determines if `/arch:AVX` or `/arch:AVX2` is used for code-generation.

# Xbox Registered Developers

For Xbox developers who have access to the *Microsoft GDK with Xbox Extensions*, these triplets are fully supported for both MSBuild and CMake-based build systems.

For MSBuild, the *Gaming.Xbox.Scarlett.x64* and *Gaming.Xbox.XboxOne.x64* custom platforms will select the appropriate triplet when using MSBuild integration. Note that vcpkg triplets use the `GameDKLatest`, `GameGXDKLatest`, and `GameGRDKLatest` environment variables to locate installed GDKs.

For CMake-based builds, Xbox makes use of the "Windows" `CMAKE_SYSTEM_NAME` with a custom variable `XBOX_CONSOLE_TARGET` set to either "xboxone" or "scarlett". This is used both to communicate from the trip to CMake files within vcpkg, and for CMake projects making use of vcpkg to community their triplet requirements.

The majority of open source libraires build against the Window SDK’s headers rather than make use of any Xbox-specific headers or libraries. There are a currently just a few ports implemented in vcpkg which make use of DirectX 12.X ([directxtex](https://github.com/microsoft/vcpkg/tree/master/ports/directxtex), [directxtk12](https://github.com/microsoft/vcpkg/tree/master/ports/directxtk12), [directxmesh](https://github.com/microsoft/vcpkg/tree/master/ports/directxmesh), and [uvatlas](https://github.com/microsoft/vcpkg/tree/master/ports/uvatlas)). These depend on a new "stub" port **ms-gdkx** to indicate this requirement.

> Note that Xbox developers are responsible for ensuring they and their publisher have appropriate and correct licensing terms for use of any 3rd party software components per the terms of their Title License Agreement. In other words, just because a library is supported by vcpkg does not mean it’s part of any official Xbox middleware program. In general, [*permissive*](https://wikipedia.org/wiki/Permissive_software_license) licenses are fine, while [*copyleft*](https://wikipedia.org/wiki/Copyleft) licenses are problematic. **Be sure to seek appropriate legal advice for any use of open-source components in your title.**

# Open-Source Libraries for Xbox

The vast majority of libraries can be built using the Xbox community triplets using only the publicly available Windows SDK, so this allows open-source maintainers to work on platform compatibility without having access to the *Microsoft GDK with Xbox Extensions*.

* Prefer Unicode Win32 APIs, and if you are using the ANSI version be sure to explicitly use the `A` variants of Win32 APIs to support building with `_UNICODE` defined. You should also take a moment to review the [UTF-8 Everywhere](http://utf8everywhere.org/) manifesto for best practices.

* The Xbox platform does not support text console I/O, although it is possible to run command-line tools and 'echo' the output back to the host PC. As such, console APIs, `printf`, etc. are not well-suited to Xbox code.

* The Xbox Game OS utilizes a variant of DirectX called DirectX 12.X. Building graphics code therefore requires access to the *Microsoft GDK with Xbox Extensions*. The Xbox Game OS does not support Direct3D 11, Direct2D/DirectWrite, OpenGL, GDI, or any older version of Direct3D.

  * The Universal Windows Platform (UWP) on Xbox supports stock Direct3D 12, Direct3D 11, and Direct2D/DirectWrite. Such code is built using the existing **x64-uwp** vcpkg triplet. See [DirectX and UWP on Xbox One](https://walbourn.github.io/directx-and-uwp-on-xbox-one/) and [DirectX and UWP on Xbox Series X\|S](https://walbourn.github.io/directx-and-uwp-on-xbox-series-x-s/).

* Windows Imaging Component (WIC) is supported, although some extensions and codecs are not available.

Code built using the xbox community triplets without making use of the *Microsoft GDK with Xbox Extensions* will generally run on Windows 10 and Windows 11 PCs assuming the appropriate CPU support (AVX or AVX2). This again allows open-source developers to test these components without having access to Xbox developer kits.

# Platform support

For this initial release of the Xbox triplets, almost all existing ports that claim support for `windows` are considered potential candidates for the new xbox community triplets. A few specific ports have been updated to express `windows & !xbox` or `windows & !uwp & !xbox` due to known platform limitations (see above).

As such, currently around 1000 ports succeed in building against the triplets, and around 1100 ports fail to build. Over time, we hope library maintainers will take advantage of the flexibility offered by these triplets, and help improve the support for the Xbox platform.

<strong>See Also</strong>: [Visual C++ Team Blog](https://devblogs.microsoft.com/cppblog/vcpkg-2023-04-15-release-vcpkg-ships-in-visual-studio-xbox-triplets-github-actions-cache-support-and-more/), [Visual Studio Developer Blog](https://devblogs.microsoft.com/cppblog/category/vcpkg/)
