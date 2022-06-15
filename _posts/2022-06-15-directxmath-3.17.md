---
layout: post
title: DirectXMath 3.17
date: 2022-06-15 00:22
author: Chuck Walbourn
comments: true
categories: [general]
---

DirectXMath 3.17 is now available via [GitHub](https://github.com/microsoft/DirectXMath/releases/tag/jan2022), [NuGet](https://www.nuget.org/packages/directxmath/2022.2.11.1), and [vcpkg](https://github.com/walbourn/vcpkg/tree/master/ports/directxmath). It is included in the **Windows SDK (10.0.22621) for Windows 11, Version 22H2**.

<!--more-->

# DirectXMath 3.17

The changes for this release include:

* Added ColorsLinear namespace to DirectXColors.h with linear versions of .NET colors
* Optimized the ``XMMatrixRotationRollPitchYaw(FromVector)`` functions
* Fixed overread problem for 16bpp GPU types Load functions:
  * ``XMUNIBBLE4``, ``XMU555``, ``XMU565``, ``XMBYTEN2``, ``XMBYTE2``, ``XMUBYTEN2``, ``XMUBYTE2``
* ``XM_CACHE_LINE_SIZE`` updated for ARM/ARM64 targets to 128 bytes
* A few comments added to improve IntelliSense experience
* Conformance improvements for GNU compiler
* Minor code cleanup

# DirectXMath 3.17b

I've made a minor hot-fix release since the Windows SDK above was finalized. This version addresses two minor issues:

* Hot-fix to address ``-Wreserved-identifier`` warnings with clang v13
* C++20 spaceship operators for XMFLOAT2, XMFLOAT3, etc. when building with ``/std:c++20 /Zc:_cplusplus``

This version is available from [GitHub](https://github.com/microsoft/DirectXMath/releases/tag/may2022), [NuGet](https://www.nuget.org/packages/directxmath/2022.5.18.1), and [vcpkg](https://github.com/walbourn/vcpkg/tree/master/ports/directxmath). It will be included in a future Windows SDK.

<b>Related:</b> <a href="https://walbourn.github.io/known-issues-directxmath-3-03/">Known Issues: DirectXMath 3.03</a>, <a href="https://walbourn.github.io/directxmath-3-06/">DirectXMath 3.06</a>, <a href="https://walbourn.github.io/directxmath-3-07/">DirectXMath 3.07</a>, <a href="https://walbourn.github.io/directxmath-3-08/">DirectXMath 3.08</a>, <a href="https://walbourn.github.io/directxmath-3-09/">DirectXMath 3.09</a>, <a href="https://walbourn.github.io/directxmath-3-10/">DirectXMath 3.10</a>, <a href="https://walbourn.github.io/directxmath-3-11/">DirectXMath 3.11</a>, <a href="https://walbourn.github.io/directxmath-3-13/">DirectXMath 3.12/3.13</a>, <a href="https://walbourn.github.io/directxmath-3.14/">DirectXMath 3.14</a>, <a href="https://walbourn.github.io/directxmath-3.16/">DirectXMath 3.15/3.16</a>
