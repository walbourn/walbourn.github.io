---
layout: msdnpost
title: DirectXMath - ARM64
date: 2018-12-05 18:13
author: Chuck Walbourn
comments: true
categories: [directxmath]
---
The Visual Studio 2017 ([15.9 update](https://walbourn.github.io/vs-2017-15-9-update/)) now supports the <a href="https://blogs.windows.com/buildingapps/2018/11/15/official-support-for-windows-10-on-arm-development">ARM64 architecture</a> for the Universal Windows Platform (UWP) apps.

The ARM64 platform supports ARM-NEON using the same intrinsics as the ARM (32-bit) platform. The Windows on ARM (32-bit) platform assumes support for ARMv7, ARM-NEON, and VFPv3. The Windows on ARM (64-bit) platform assumes support for ARMv8, ARM-NEON, and VFPv4.
<!--more-->

# ARMv8

The ARMv8 instruction set implies support for several useful intrinsics for DirectXMath data types:

<ul>
  <li>vector divide: <code>vdivq_f32</code></li>
  <li>vector rounding: <code>vrndq_f32</code>, <code>vrndnq_f32</code>, <code>vrndmq_f32</code>, <code>vrndpq_f32</code></li>
  <li>half-precision conversion: <code>vcvt_f32_f16</code>, <code>vcvt_f16_f32</code></li>
  <li>fused-multiply and accumulate: <code>vfmaq_f32</code>, <code>vfmsq_f32</code></li>
</ul>

In ARM (32-bit), vector division had to be implemented using multiply-by-reciprocal with 2 or 3 iterations of <a href="https://en.wikipedia.org/wiki/Newton%27s_method">Newton-Raphson</a> refinement which is less precise. For the ARM64 platform, I was able to replace all uses of divide in non-Est functions with a 'true divide' in <em>XMVectorDivide</em>, <em>XMVectorReciprocal</em>, and in the implementation for a number of other functions.

For ARM (32-bit) I used a number of tricks to perform the rounding operations. With the ARM64 platform, I can use the new intrinsics to implement <em>XMVectorRound</em>, <em>XMVectorTruncate</em>, <em>XMVectorFloor</em>, and <em>XMVectorCeiling</em>.

The half-precision conversion intrinsics are used when building for the ARM64 platform to implement <em>XMConvertHalfToFloat</em>, <em>XMConvertFloatToHalf</em>, <em>XMConvertHalfToFloatStream</em>, and <em>XMConvertFloatToHalfStream</em>.

# History

<ul>
  <li><a href="https://walbourn.github.io/directxmath-3-07/">DirectXMath 3.07</a> was the first version to include basic ARM64 support using the same ARM-NEON implementation as used for ARM (32-bit).</li>
  <li><a href="https://walbourn.github.io/directxmath-3-10/">DirectXMath 3.10</a> uses ARMv8 intrinsics when building the ``_M_ARM64`` architecture for optimizations of specific functions including the new <em>XMVectorSum</em> horizontal add function.</li>
  <li><a href="https://walbourn.github.io/directxmath-3-13/">DirectXMath 3.12</a> uses ARM64 fused-multiply and accumulate to implement <em>XMVectorMultiplyAdd</em> and <em>XMVectorNegativeMultiplySubtract</em> on the ARM64 platform.</li>
  <li><a href="https://walbourn.github.io/directxmath-3-13/">DirectXMath 3.13</a> - <a href="https://walbourn.github.io/directxmath-3.16/">3.16</a> cleaned up the ARM-NEON implementation for better compiler portability for clang/LLVM and GNUC.</li>
</ul>

<strong>See also</strong>: <a href="https://walbourn.github.io/directxmath-sse-sse2-and-arm-neon/">SSE. SSE2. and ARM-NEON</a>; <a href="https://walbourn.github.io/directxmath-sse3-and-ssse3/">SSE3 and SSSE3</a>; <a href="https://walbourn.github.io/directxmath-sse4-1-and-sse4-2/">SSE4.1 and SSE4.2</a>; <a href="https://walbourn.github.io/directxmath-avx/">AVX</a>; <a href="https://walbourn.github.io/directxmath-f16c-and-fma/">F16C and FMA</a>; <a href="https://walbourn.github.io/directxmath-avx2/">AVX2</a>
