---
layout: post
title: DirectXMath 3.14
date: 2020-03-10 23:29
author: Chuck Walbourn
comments: true
categories: [directxmath]
---

DirectXMath 3.14 is now available on [NuGet](https://www.nuget.org/packages/directxmath/2019.8.23.1) and [GitHub](https://github.com/microsoft/DirectXMath/releases/tag/aug2019). It is included in the upcoming Windows 10 "20H1" Update SDK ([19041](https://blogs.windows.com/windowsdeveloper/2019/12/17/windows-10-sdk-preview-build-19041-available-now/)) which is available in [Visual Studio 2019 16.5](https://walbourn.github.io/vs-2019-update-5/) as an optional component.
<!--more-->

The focus for this release was updating for the Visual C++ 2019 compiler, as well as improved clang/LLVM support.

* Added float control around IsNan functions to resolve issue with VS 2019 with ``/fp:fast``

> This issue impacts all versions of Visual Studio 2019. The fix is using DirectXMath 3.14 in combination with VS 2019 ([16.3](https://walbourn.github.io/vs-2019-update-3/)) or later.

* ``XMVerifyCPUSupport`` updated for clang/LLVM cpuid implementation on x86/x64

> The older version builds, but fails at runtime when using the clang/LLVM toolset.

* Added support for clang/LLVM built-in platform defines as well as the MSVC ones

* Cleaned up ARM-NEON intrinsics type issues for improved portability

> There are a few uses of ``_ex`` alignment-hinted ARM-NEON intrinsics which are a Microsoft extension that need a workaround, as does a Microsoft-only intrinsic for the VACLE psuedo-instruction. These are being addressed for the DirectXMath 3.15 release.

* Removed unneeded malloc.h include in DirectXMath.h

* Whitespace cleanup

# Future work

For the next release, version 3.15, I'm focusing on AVX2 optimizations and improved support for clang/LLVM, GCC, and MinGW compilers. I'm also retiring VS 2015 support--the Windows 10 SDK hasn't officially supported VS 2015 since the Windows 10 Anniversary Update ([14393](https://walbourn.github.io/windows-10-anniversary-update-sdk/)) back in 2016.

<b>Related:</b> <a href="https://walbourn.github.io/known-issues-directxmath-3-03/">Known Issues: DirectXMath 3.03</a>, <a href="https://walbourn.github.io/directxmath-3-06/">DirectXMath 3.06</a>, <a href="https://walbourn.github.io/directxmath-3-07/">DirectXMath 3.07</a>, <a href="https://walbourn.github.io/directxmath-3-08/">DirectXMath 3.08</a>, <a href="https://walbourn.github.io/directxmath-3-09/">DirectXMath 3.09</a>, <a href="https://walbourn.github.io/directxmath-3-10/">DirectXMath 3.10</a>, <a href="https://walbourn.github.io/directxmath-3-11/">DirectXMath 3.11</a>, <a href="https://walbourn.github.io/directxmath-3-13/">DirectXMath 3.12/3.13</a>
