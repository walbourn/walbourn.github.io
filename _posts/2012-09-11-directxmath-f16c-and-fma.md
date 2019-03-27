---
layout: msdnpost
title: DirectXMath - F16C and FMA
date: 2012-09-11 12:50
author: Chuck Walbourn
comments: true
categories: [xbox one, directxmath]
---
In this installment in our series, we cover a few additional instructions that extend the <a href="http://en.wikipedia.org/wiki/Advanced_Vector_Extensions">AVX</a> instruction set. These instructions make use of the <a href="http://en.wikipedia.org/wiki/VEX_prefix">VEX</a> prefix and require the OS implement "OXSAVE". Without this support, these instructions are all invalid and will generate an invalid instruction hardware exception.
<!--more-->

<h1>Half-precision Floating-point Conversion</h1>

The F16C instruction set (also called <a href="http://en.wikipedia.org/wiki/CVT16_instruction_set">CVT16</a> by AMD) provides support for doing <a href="http://en.wikipedia.org/wiki/Half-precision">half-precision</a> <-> single-precision floating-point conversions. These intrinsics are in the <code>immintrin.h</code> header.

```cpp
inline float XMConvertHalfToFloat(HALF Value)
{
    __m128i V1 = _mm_cvtsi32_si128(static_cast<uint32_t>(Value));
    __m128 V2 = _mm_cvtph_ps(V1);
    return _mm_cvtss_f32(V2);
}

inline HALF XMConvertFloatToHalf(float Value)
{
    __m128 V1 = _mm_set_ss(Value);
    __m128i V2 = _mm_cvtps_ph(V1, 0);
    return static_cast<HALF>(_mm_cvtsi128_si32(V2));
}
```

This instruction actually converts 4 HALF <-> float values at a time, so this can be used to improve the performance of both <code>XMConvertHalfToFloatStream</code> and <code>XMConvertFloatToHalfStream</code>.

<h1>Fused Multiply-Add</h1>

Computations often contain steps where two values are multiplied and then the result is accumulated with previous results. This can be done in single instruction using a 'fused' multiply-add operation:

```
V = V1 * V2 + V3
```

DirectXMath provides this functionality with the <code>XMVectorMultiplyAdd</code> function. The challenge in making use of <a href="http://en.wikipedia.org/wiki/FMA_instruction_set">FMA</a> is that Intel and AMD took a while to agree on the exact details—thankfully ARM-NEON has a fused multiply-add instruction.

AMD Bulldozer implements FMA4. which uses a non-destructive destination form using 4 registers. These intrinsics are located in the <code>ammintrin.h</code> header.

```cpp
inline XMVECTOR XMVectorMultiplyAdd(FXMVECTOR V1, FXMVECTOR V2, FXMVECTOR V3)
{
    return _mm_macc_ps( V1, V2, V3 );
}

inline XMVECTOR XM_CALLCONV XMVectorNegativeMultiplySubtract(FXMVECTOR V1, FXMVECTOR V2, FXMVECTOR V3)
{
    return _mm_nmacc_ps( V1, V2, V3 );
}
```

Intel "Haswell" is expected to implement FMA3, which uses a destructive destination form using only 3 registers. The intrinsics are located in the <code>immintrin.h</code> header.

```cpp
inline XMVECTOR XMVectorMultiplyAdd(FXMVECTOR V1, FXMVECTOR V2, FXMVECTOR V3)
{
    return _mm_fmadd_ps( V1, V2, V3 );
}

inline XMVECTOR XM_CALLCONV XMVectorNegativeMultiplySubtract(FXMVECTOR V1, FXMVECTOR V2, FXMVECTOR V3)
{
    return _mm_fnmadd_ps( V1, V2, V3 );
}
```

AMD has announced it is planning to implement FMA3 with "Piledriver". It is also fairly easy to use the same source code to generate both versions by just substituting one intrinsic for the other.

<h1>Processor Support</h1>

F16C/CVT16 is supported by AMD "Piledriver", Intel "Ivy Bridge", and later processors.

FMA4 is supported by AMD Bulldozer.

FMA3 will be supported by Intel "Haswell" and AMD "Piledriver" processors.

As extensions of the AVX instruction set, these instructions all require OSXSAVE support. This support is included in Windows 7 Service Pack 1, Windows Server 2008 R2 Service Pack 1, Windows 8, and Windows Server 2012.

```cpp
int CPUInfo[4] = { -1 };
__cpuid(CPUInfo, 0);
bool bOSXSAVE = false;
bool bAVX = false;
bool bF16C = false;
bool bFMA3 = false;
bool bFMA4 = false;
if (CPUInfo[0] > 0)
{
    __cpuid(CPUInfo, 1);
    bOSXSAVE = (CPUInfo[2] & 0x8000000) != 0;
    bF16C = bOSXSAVE && (CPUInfo[2] & 0x20000000) != 0;
    bAVX = bOSXSAVE && (CPUInfo[2] & 0x10000000) != 0;
    bFMA3 = bOSXSAVE && (CPUInfo[2] & 0x1000) != 0;
}
__cpuid(CPUInfo, 0x80000000);
if (CPUInfo[0] > 0x80000000)
{
    _cpuid(CPUInfo, 0x80000001);
    bFMA4 = bOSXSAVE && (CPUInfo[2] & 0x10000) != 0;
}
```

<h1>Compiler Support</h1>

FMA4 intrinsics were added to Visual Studio 2010 via Service Pack 1.

FMA3 and F16C/CVT16 intrinsic support requires Visual Studio 2012.

<h1>Utility Code</h1>

<strong>Update:</strong> The source for this project is now available on <a href="https://github.com/Microsoft/DirectXMath">GitHub</a> under the <a href="http://opensource.org/licenses/MIT">MIT license</a>.

<strong>Xbox One:</strong> This platform supports F16C, but does not support FMA3 or FMA4.

<strong>See also</strong>: <a href="https://walbourn.github.io/directxmath-sse-sse2-and-arm-neon/">SSE. SSE2. and ARM-NEON</a>; <a href="https://walbourn.github.io/directxmath-sse3-and-ssse3/">SSE3 and SSSE3</a>; <a href="https://walbourn.github.io/directxmath-sse4-1-and-sse4-2/">SSE4.1 and SSE4.2;</a> <a href="https://walbourn.github.io/directxmath-avx/">AVX</a>; <a href="https://walbourn.github.io/directxmath-avx2/">AVX2</a>
