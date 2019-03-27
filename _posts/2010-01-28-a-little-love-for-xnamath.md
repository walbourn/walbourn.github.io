---
layout: msdnpost
title: A little love for XNAMath...
date: 2010-01-28 18:21
author: Chuck Walbourn
comments: true
categories: [xnamath, directxmath]
---
Over the past year or so, one of my projects has been the <em>XNAMath</em> library which shipped for the first time to Windows developers in the DirectX SDK (March 2008). <em>XNAMath</em> began life back in 2004 as "xboxmath" for the Xbox 360, and was originally developed by the Xbox 360 graphics team. The original implementation was a scalar version, which is retained today as the ``NO_INTRINSICS`` codepath, and then extended with a VMX128 optimized codepath--VMX128 is the Xbox 360 SIMD instruction set, a variant of PowerPC AltiVec. In late 2008/early 2009, we extended it again for SSE2 to provide optimized cross-platform support with Windows x86 and Windows x64 and <em>XNAMath</em> is the result of this work. Incidentally, this is why XNAMath's version number is 2.0 since it is "xboxmath 2.0" from the perspective of Xbox 360 developers.
<!--more-->

Since XNAMath is written using intrinsics rather than inline assembly, the same code compiles in both 32-bit and native 64-bit. This also means it relies heavily on the compiler, and the Visual C++ 2010 team has made use of it in their own work to improve the compiler. If you've not looked at SIMD intrinsics coding before, or if you haven't looked at it in a long time, I encourage you to try it out especially with the latest version of Visual C++. The [Collision](https://github.com/walbourn/directx-sdk-samples/tree/master/Collision) DirectX SDK sample makes extensive use of [XNAMath](https://docs.microsoft.com/en-us/windows/desktop/dxmath/ovw-xnamath-progguide).

A recent Gamaustra [article](http://www.gamasutra.com/view/feature/4248/designing_fast_crossplatform_simd_.php) on SIMD programming mentioned XNAMath, and generally had nice things to say about it.

XNAMath version 2.02 is shipping in the February 2010 releases of the DirectX SDK and the Xbox 360 XDK.

<strong>Update:</strong> See [XNAMath v2.04](https://walbourn.github.io/xna-math-version-2-04/)

<strong>GitHub:</strong> Note that DirectXMath (formerly XNAMath) is now hosted on [GitHub](https://github.com/Microsoft/DirectXMath).
