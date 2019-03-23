---
layout: post
title: DirectXMath - SSE3 and SSSE3
date: 2012-09-11 12:01
author: Chuck Walbourn
comments: true
categories: [xbox one, directxmath]
---
The <a href="http://en.wikipedia.org/wiki/SSE3">SSE3</a> instruction set adds about a dozen instructions (intrinsics are in the <code>pimmintrin.h</code> header). The main operation these instructions provide is the ability to do "horizontal" adds and subtracts (ARM-NEON refers to these as 'pairwise' operations) for float4 and double2 data.
<!--more-->

```cpp
Result = _mm_hadd_ps(V1,V2);
->
Result[0] = V1[0] + V1[1];
Result[1] = V1[2] + V1[3];
Result[2] = V2[0] + V2[1];
Result[3] = V2[2] + V2[3];
```

There are variants that use different signs for the two values, but otherwise they are basically the same.

The majority of the DirectXMath library is designed around avoiding the needing for these operations, but they are useful for dot-product operations (VMX128 on the Xbox 360 had a specific instruction for doing dot-products across a vector, but not a general pairwise add).

The existing SSE/SSE2 dot-product for float4:

```cpp
inline XMVECTOR XMVector4Dot(FXMVECTOR V1, FXMVECTOR V2)
{
    XMVECTOR vTemp2 = V2;
    XMVECTOR vTemp = _mm_mul_ps(V1, vTemp2);
    vTemp2 = _mm_shuffle_ps(vTemp2, vTemp, _MM_SHUFFLE(1, 0, 0, 0));
    vTemp2 = _mm_add_ps(vTemp2, vTemp);
    vTemp = _mm_shuffle_ps(vTemp, vTemp2, _MM_SHUFFLE(0, 3, 0, 0));
    vTemp = _mm_add_ps(vTemp, vTemp2);
    return XM_PERMUTE_PS(vTemp, _MM_SHUFFLE(2, 2, 2, 2));
}
```

can be rewritten using SSE3 as:

```cpp
inline XMVECTOR XMVector4Dot(FXMVECTOR V1, FXMVECTOR V2)
{
    XMVECTOR vTemp = _mm_mul_ps(V1, V2);
    vTemp = _mm_hadd_ps(vTemp, vTemp);
    return _mm_hadd_ps(vTemp, vTemp);
}
```

This version has the same number of multiply/add operations, but there are three fewer shuffles required. As we'll see in a future installment, there are actually some better options than this in SSE 4.1.

There are also two new instructions which can be used as a special-case substitute for the <code>XMVectorSwizzle<></code> template. We'll make use of these in a future installment.

<table border="1">
<tbody>
<tr>
<td><code>XMVectorSwizzle<0,0,2,2>(V)</code></td>
<td><code>_mm_moveldup_ps(V)</code></td>
</tr>
<tr>
<td><code>XMVectorSwizzle<1,1,3,3>(V)</code></td>
<td><code>_mm_movehdup_ps(V)</code></td>
</tr>
</tbody>
</table>

The Supplemental SSE3 (<a href="http://en.wikipedia.org/wiki/SSSE3">SSSE3</a>) instruction set adds the equivalent "horizontal" adds and subtracts for various integer vectors, so they are not particularly useful for DirectXMath. These intrinsics are located in the <code>tmmintrin.h</code> header. There are also some other useful integer operations that make life simpler for implementing algorithms like Fast Block Compress, codecs, or other image processing on integer data which are a bit out of scope for DirectXMath.

There is one SSSE3 intrinsic of interest for DirectXMath: ``mm_shuffle_epi8``. The purpose of this instruction is to be able to rearrange the bytes in a vector, which makes it an excellent function for doing vector-based Big-Endian/Little-Endian swaps without having to 'spill' the vector to memory and reload it.

```cpp
inline XMVECTOR XMVectorEndian(FXMVECTOR V)
{
    static const XMVECTORU32 idx = { 0x00010203, 0x04050607, 0x08090A0B, 0x0C0D0E0F };
    __m128i Result = _mm_shuffle_epi8(_mm_castps_si128(V), idx);
    return _mm_castsi128_ps(Result);
}
```

There's not enough use for this kind of operation to make this function part of the library (Windows x86, Windows x64, and Windows RT are all Little-Endian platforms), but it can be useful for some cross-platform tools processing (Xbox 360 is Big-Endian).

<h1>Processor Support</h1>

SSE3 is supported by Intel Pentium 4 processors ("Prescott"), AMD Athlon 64 ("revision E"), AMD Phenom, and later processors. This means most, but not quite all, x64 capable CPUs should support SSE3.

Supplemental SSE3 (SSSE3) is supported by Intel Core 2 Duo, Intel Core i7/i5/i3, Intel Atom, AMD Bulldozer, and later processors.

```cpp
int CPUInfo[4] = { -1 };
__cpuid(CPUInfo, 0);
bool bSSE3 = false;
bool bSSSE3 = false;
if (CPUInfo[0] > 0)
{
    __cpuid(CPUInfo, 1);
    bSSE3 = (CPUInfo[2] & 0x1) != 0;
    bSSSE3 = (CPUInfo[2] & 0x200) != 0;
}
```

You can also use the <code>IsProcessorFeaturePresent</code> Win32 API with <code>PF_SSE3_INSTRUCTIONS_AVAILABLE</code> on Windows Vista or later to detect SSE3 support. This API does not report support for SSSE3.

<h1>Utility Code</h1>

<strong>Update:</strong> The source for this project is now available on <a href="https://github.com/Microsoft/DirectXMath">GitHub </a>under the <a href="http://opensource.org/licenses/MIT">MIT license</a>. A <code>XMVectorSum</code> function was added to recent versions of DirectXMath which makes use of horizontal-add.

<strong>Xbox One:</strong> This platform supports SSE3 and SSSE3.

<strong>DirectXMath 3.10:</strong> Added the <code>XMVectorSum</code> method for horizontal adds, as well as the ability to specifically opt-in to just the SSE3 optimizations via ``-D_XM_SSE3_INTRINSICS_``

<strong>Windows 10</strong>: As of Windows 10, x64 editions of the OS require support for a few specific instructions (CMPXCHG16b, PrefetchW, and LAHF/SAHF) which excludes a number of first-generation x64 CPUs from both Intel and AMD. The net result is that it's even more likely that an x64 native application can assume SSE3 is supported even though only SSE/SSE2 is actually in the system requirements.

<strong>See Also:</strong> <a href="https://walbourn.github.io/directxmath-sse-sse2-and-arm-neon/">SSE, SSE2, and ARM-NEON</a>; <a href="https://walbourn.github.io/directxmath-sse4-1-and-sse-4-2/">SSE4.1 and SSE4.2</a>; <a href="https://walbourn.github.io/directxmath-avx/">AVX</a>; <a href="https://walbourn.github.io/directxmath-f16c-and-fma/">F16C an FMA</a>; <a href="https://walbourn.github.io/directxmath-avx2/">AVX2</a>
