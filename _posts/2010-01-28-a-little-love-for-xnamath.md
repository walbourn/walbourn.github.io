---
layout: post
title: A little love for XNAMath...
date: 2010-01-28 18:21
author: walbourn
comments: true
categories: [Uncategorized, xnamath]
---
Over the past year or so, one of my projects has been the <em>XNAMath </em>library which shipped for the first time to Windows developers in the DirectX SDK (March 2008). <em>XNAMath </em>began life back in 2004 as "xboxmath" for the Xbox 360, and was originally developed by the Xbox 360 graphics team. The original implementation was a scalar version, which is retained today as the NO_INTRINSICS codepath, and then extended with a VMX128 optimized codepath--VMX128 is the Xbox 360 SIMD instruction set, a variant of PowerPC AltiVec. In late 2008/early 2009, we extended it again for SSE2 to provide optimized cross-platform support with Windows x86 and Windows x64 and <em>XNAMath </em>is the result of this work. Incidentally, this is why XNAMath's version number is 2.0 since it is "xboxmath 2.0" from the perspective of Xbox 360 developers.

Since XNAMath is written using intrinsics rather than inline assembly, the same code compiles in both 32-bit and native 64-bit. This also means it relies heavily on the compiler, and the Visual C++ 2010 team has made use of it in their own work to improve the compiler. If you've not looked at SIMD intrinsics coding before, or if you haven't looked at it in a long time, I encourage you to try it out especially with the <a title="newest" href="http://www.microsoft.com/visualstudio/en-us/products/2010/default.mspx">newest</a> version of Visual C++. The <em>Collision</em> DirectX SDK sample makes extensive use of <em><a title="XNAMath" href="http://msdn.microsoft.com/en-us/library/ee415571.aspx">XNAMath</a>.</em>

A recent Gamaustra <a title="article" href="http://www.gamasutra.com/view/feature/4248/designing_fast_crossplatform_simd_.php">article</a> on SIMD programming mentioned XNAMath, and generally had nice things to say about it.

XNAMath version 2.02 is shipping in the February 2010 releases of the DirectX SDK and the Xbox 360 XDK.

<strong>Update:</strong> See <a title="Games for Windows and the DirectX SDK Blog" href="http://blogs.msdn.com/b/chuckw/archive/2011/02/23/xna-math-version-2-04.aspx">XNAMath v2.04</a> and <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh437833.aspx">DirectXMath</a>.

<strong>GitHub:</strong> Note that DirectXMath is now hosted on <a href="https://github.com/Microsoft/DirectXMath">GitHub</a>.
