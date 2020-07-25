---
layout: msdnpost
title: DirectXMath - AVX
date: 2012-09-11 12:36
author: Chuck Walbourn
comments: true
categories: [xbox one, directxmath]
---
The Advanced Vector Extensions (<a href="http://en.wikipedia.org/wiki/Advanced_Vector_Extensions">AVX</a>) instruction set goes beyond just adding more instructions like we've seen in previous installments. AVX also introduces an extended register file and a new x86 instruction encoding prefix.
<!--more-->

The AVX instruction set expands the existing XMM register file of 128-bit registers used by SSE instructions. XMM now refers to the lower 128-bits of the expanded YMM register file of 256-bit registers (analogous to the AX 16-bit vs. EAX 32-bit x86 registers). A full 256-bit YMM register can contain a float8 (``__m256``), a double4 (``__m256d``), or a mixture of various integer types including int/uint8 (``__m256i``). A new set of intrinsics beginning with the prefix ``_mm256`` (such as ``_mm256_mul_ps``) operate on these YMM registers, while existing ``_mm`` intrinsics (such as ``_mm_mul_ps``) operate on the lower 128-bits of the same registers. The AVX intrinsics and types are in the <code>immintrin.h</code> header.

Because of the extended register file, the OS must be updated to save the full 256-bit registers rather than just the lower 128-bits when doing context switches. If the OS does not implement this, none of the AVX instructions (even those that operate on ``__m128`` values) are valid and will generate an invalid instruction hardware exception if executed. This "OXSAVE" feature is implemented in Windows 7 Service Pack 1 / Windows Server 2008 R2 Service Pack 1 and later versions of Windows.

Another aspect of AVX is the use of a new "<a href="http://en.wikipedia.org/wiki/VEX_prefix">VEX</a>" instruction prefix. This can be applied to existing SSE instructions as well as the new AVX instructions, with the mnemonic adding a 'v' letter prefix. The key change is that the VEX prefix encodes "non-destructive destination" instructions. The x86 instruction set uses a "destructive destination" model where one of the inputs is also the destination.

```
mulps xmm0, xmm1
; xmm0 = xmm0 * xmm1</code></pre>
```

Becomes with the VEX prefix

```
vmulps xmm2, xmm0, xmm1
; xmm2 = xmm0 * xmm1
```

This new VEX prefix encoding can help reduce register scheduling pressure by eliminating the need for making copies of registers before operating on them to preserve their current contents.

For DirectXMath, making direct use of YMM registers would require additional types to be introduced to the library, or perhaps can be leveraged in some specific 'stream' scenarios. As such, the immediate applicability of the AVX instruction for DirectXMath is using intrinsics that operate on ``__m128`` data (i.e. <code>XMVECTOR</code>).

There are two simple substitutions that AVX opens up. The first is a replacement for <code>XMVectorReplicatePtr</code>. The DirectXMath library generally avoids this operation elsewhere, so this is the only place this intrinsic can be applied.

```cpp
inline XMVECTOR XMVectorReplicatePtr( const float *pValue )
{
    return _mm_broadcast_ss( pValue );
}
```

The second is an alternative intrinsic for doing a 'shuffle' of a single vector.

```cpp
 _mm_shuffle_ps( V, V, imm )

->

_mm_permute_ps( V, imm )
```

This pattern is used in a lot of places in the library, but the most common use is in <code>XMVectorSplat*</code>, <code>XMVectorPermute<></code>, and <code>XMVectorSwizzle<></code>.

There is also a new ``_mm_permutevar_ps`` intrinsic for generalized permutes using a control vector rather than immediate literals. For DirectXMath, the template forms of <code>XMVectorPermute<></code> and <code>XMVectorSwizzle<></code> are already much more efficient than the function form as they can be compiled down to one or two shuffle operations (``_mm_shuffle_ps`` requires the control indices be literal values), but there are times when the function form is more convenient to use. For SSE/SSE2, these functions have to 'spill' the vector to memory, rearrange them with scalar memory swaps, and then reload the vector. For AVX, we can now implement these function forms more efficiently (or at least avoid the need to spill to memory).

```cpp
inline XMVECTOR XMVectorSwizzle(FXMVECTOR V,
    uint32_t E0, uint32_t E1, uint32_t E2, uint32_t E3)
{
    unsigned int elem[4] = { E0, E1, E2, E3 };
    __m128i vControl =
        _mm_loadu_si128(
            reinterpret_cast<const __m128i *>(&elem[0]));
    return _mm_permutevar_ps(V, vControl);
}


inline XMVECTOR XMVectorPermute(FXMVECTOR V1, FXMVECTOR V2,
    uint32_t PermuteX, uint32_t PermuteY,
    uint32_t PermuteZ, uint32_t PermuteW)
{
    static const XMVECTORU32 three = { 3, 3, 3, 3 };
    _declspec(align(16)) unsigned int elem[4] =
    { PermuteX, PermuteY, PermuteZ, PermuteW };
    __m128i vControl = _mm_load_si128(
        reinterpret_cast<const __m128i *>(&elem[0]));
    __m128i vSelect = _mm_cmpgt_epi32(vControl, three);
    vControl = _mm_castps_si128(
        _mm_and_ps(_mm_castsi128_ps(vControl), three));
    __m128 shuffled1 = _mm_permutevar_ps(V1, vControl);
    __m128 shuffled2 = _mm_permutevar_ps(V2, vControl);
    __m128 masked1 = _mm_andnot_ps(_mm_castsi128_ps(vSelect),
        shuffled1);
    __m128 masked2 = _mm_and_ps(_mm_castsi128_ps(vSelect),
        shuffled2);
    return _mm_or_ps(masked1, masked2);
}
```
<h1>Visual C++ and AVX</h1>

With the introduction of the VEX prefix, it is possible to generate all SSE/SSE2 code using it. With Visual Studio 2010 SP1/Visual Studio 2012, there is a new <code>/arch:AVX</code> switch which does exactly this. It causes all explicit ``_mm`` intriniscs to use the VEX prefix, as well making all compiler-generated SSE/SSE2 instructions use VEX as well. This impacts all x64 native floating-point math operations. For x86 it is similar to specifying <code>/arch:SSE2</code> making the compiler prefer the use of SSE/SSE2 to x87 for floating-point math with the additional use of the VEX prefix.

Because the resulting EXE makes extensive use of AVX instructions, the resulting program can only be run on a system with an AVX capable CPU and running an "OSXSAVE" enabled version of Windows.

<h1>Processor Support</h1>

AVX is supported by Intel "Sandy Bridge", AMD Bulldozer, and later processors.

In addition to the hardware supporting the new instruction set, the OS must support saving the new YMM register file or the AVX instructions will remain invalid. This support is included in Windows 7 Service Pack 1, Windows Server 2008 R2 Service Pack 1, Windows 8, and Windows Server 2012. This support is indicated by the ``OSXSAVE`` bit in ``CPUID`` being set along with the AVX support bit.

```cpp
#if defined(__clang__) || defined(__GNUC__)
#include <cpuid.h>
#else
#include <intrin.h>
#endif

int CPUInfo[4] = { -1 };
#if defined(__clang__) || defined(__GNUC__)
__cpuid(0, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#else
__cpuid(CPUInfo, 0);
#endif
bool bAVX = false;
if (CPUInfo[0] > 0)
{
#if defined(__clang__) || defined(__GNUC__)
    __cpuid(1, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#else
    __cpuid(CPUInfo, 1);
#endif
    bool bOSXSAVE = (CPUInfo[2] & 0x8000000) != 0;
    bAVX = bOSXSAVE && (CPUInfo[2] & 0x10000000) != 0;
}
```

<h1>Compiler Support</h1>

Support for AVX intrinsics was added to Visual Studio 2010 via Service Pack 1. The <code>/arch:AVX</code> switch is supported by VS 2010 SP1, although IDE support wasn't added until VS 2012.

<h1>Utility Code</h1>

<strong>Update:</strong> The source for this project is now available on <a href="https://github.com/Microsoft/DirectXMath">GitHub </a>under the <a href="http://opensource.org/licenses/MIT">MIT license</a>.

<strong>Xbox:</strong> Xbox One and [Xbox Series X](https://www.xbox.com/en-US/project-scarlett) support AVX.

<strong>Windows 7 x64 Known Issue with AVX:</strong> See <a href="http://support.microsoft.com/kb/2864432/">KB 2864432</a>

<strong>Update:</strong> Per the latest numbers from the [Value Hardware Survey](https://store.steampowered.com/hwsurvey), for PC games you could support AVX without excluding significant numbers of gamers. You should check for the CPU & OS support at startup to avoid unexplained crashes due to invalid instructions if a customer tries to run it on an older PC.

<strong>See also</strong>: <a href="https://walbourn.github.io/directxmath-sse-sse2-and-arm-neon/">SSE. SSE2. and ARM-NEON</a>; <a href="https://walbourn.github.io/directxmath-sse3-and-ssse3/">SSE3 and SSSE3</a>; <a href="https://walbourn.github.io/directxmath-sse4-1-and-sse4-2/">SSE4.1 and SSE4.2</a>; <a href="https://walbourn.github.io/directxmath-f16c-and-fma/">F16C and FMA</a>; <a href="https://walbourn.github.io/directxmath-avx2/">AVX2</a>; <a href="https://walbourn.github.io/directxmath-arm64/">ARM64</a>
