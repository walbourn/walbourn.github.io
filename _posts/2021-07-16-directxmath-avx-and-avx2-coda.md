---
layout: post
title: DirectXMath AVX and AVX2 - A Coda
date: 2021-07-16 16:49
author: Chuck Walbourn
comments: true
categories: [directxmath, xbox]
---

Over the years, I've done a number of optimizations for [DirectXMath](https://github.com/Microsoft/DirectXMath) using advanced instruction sets available on x86/x64 CPUs. For Xbox developers, making the choice to use these is very easy since you can count on them along with AVX. For PC developers, modern x64 development means you can rely on SSE, SSE2--and at this point, SSE3--without sacrificing any target market. I've recently done some work for another project unrelated to DirectMath per se, but I wanted to add some notes about using other advanced instruction sets.
<!--more-->

The original blog series that summed up the advanced instructions applicable for DirectXMath are:

<ul>
  <li><a href="https://walbourn.github.io/directxmath-sse-sse2-and-arm-neon/"> SSE, SSE2, and ARM-NEON</a></li>
 	<li><a href="https://walbourn.github.io/directxmath-sse3-and-ssse3/">SSE3 and SSSE3</a></li>
 	<li><a href="https://walbourn.github.io/directxmath-sse4-1-and-sse4-2/">SSE4.1 and SSE 4.2</a></li>
 	<li><a href="https://walbourn.github.io/directxmath-avx/">AVX</a></li>
 	<li><a href="https://walbourn.github.io/directxmath-f16c-and-fma/">F16C and FMA</a></li>
 	<li><a href="https://walbourn.github.io/directxmath-avx2/">AVX2</a></li>
 	<li><a href="https://walbourn.github.io/directxmath-arm64/">ARM64</a></li>
</ul>

# ABM

ABM (Advanced Bit Manipulation) was an instruction set originally introduced by AMD. It includes ``LZCNT`` (leading-zero count) and ``POPCNT`` (population count). After some back and forth with Intel over this and other instruction set extensions at the time, these are both supported by AMD and Intel, but you need to check more than one bit in CPUID: ABM indicates ``LZCNT`` and POPCNT indicates the population count instruction is supported.

> For more on the convoluted history here, see [Wikipedia](https://en.wikipedia.org/wiki/X86_Bit_manipulation_instruction_set).

Generally if the PC you are using supports AVX2, it will support both of these instructions. The Visual C++20 Standard Library header ``<bit>`` will therefore use ``LZCNT`` and ``POPCNT`` when building with ``/arch:AVX2`` if you use ``std::popcnt`` and/or ``std::countl_zero``.

# BMI1

BMI (Bit Manipulation Instruction) adds some interesting new instructions like ``ANDN`` (Logical and not) and ``BEXTR`` (Bit field extract) that can be useful for compiler code-generation when using ``/arch:AVX2``. The ``TZCNT`` instruction is also used to implement C++20 ``std::countr_zero`` as well.

# BMI2

The BMI 2 instruction set adds a few more instructions, like variants of basic Intel ISA ``MUL``, ``ROR``, ``SAR``, ``SHR``, and ``SHL`` that don't affect eflags. Again, mostly useful for compilers building with ``/arch:AVX2``.

> It's generally advised to avoid using ``PEXT`` an ``PDEP`` on [AMD prior to Zen 3](https://en.wikichip.org/wiki/amd/microarchitectures/zen_3#Key_changes_from_Zen_2).

# AES

The AES (Advanced Encryption Standard) instructions provide hardware acceleration support for the AES cipher. Any PC that supports AVX or AVX2 is likely to support AES.

For more details, see [Wikipedia](https://en.wikipedia.org/wiki/AES_instruction_set).

# MOVBE

The ``MOVBE`` instruction (officially called "Move Data After Swapping Bytes" but the mnemonic means "Move Big-Endian") is an instruction for swapping Big-Endian/Little-Endian 16-bit, 32-bit, and 64-bit data. Much like [SSSE3](https://walbourn.github.io/directxmath-sse3-and-ssse3/)'s ``PSHUFB`` which can be used to implement BE swapping for SIMD data vectors, it's pretty specialized, but useful when you need it.

# CPUID Example

This code example show checking each of the CPUID bits mentioned in this blog post.

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

bool bABM = false;
bool bAES = false;
bool bBMI1 = false;
bool bBMI2 = false;
bool bMOVBE = false;
bool bPOPCNT = false;

const bool checkextfeature = (CPUInfo[0] >= 7);

if (CPUInfo[0] > 0)
{
#if defined(__clang__) || defined(__GNUC__)
    __cpuid(1, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#else
    __cpuid(CPUInfo, 1);
#endif

    bAES    = (CPUInfo[2] & 0x2000000) != 0;
    bPOPCNT = (CPUInfo[2] & 0x800000) != 0;
    bMOVBE  = (CPUInfo[2] & 0x400000) != 0;
}

if ( checkextfeature )
{
#if defined(__clang__) || defined(__GNUC__)
    __cpuid_count(7, 0, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#else
    __cpuidex(CPUInfo, 7, 0);
#endif

    bBMI2 = (CPUInfo[1] & 0x100) != 0);
    bBMI1 = (CPUInfo[1] & 0x8) != 0;
}

#if defined(__clang__) || defined(__GNUC__)
__cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#else
__cpuid(CPUInfo, 0x80000000);
#endif
if (uint32_t(CPUInfo[0]) > 0x80000000)
{
#if defined(__clang__) || defined(__GNUC__)
    __cpuid(0x80000001, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#else
    __cpuid(CPUInfo, 0x80000001);
#endif

   bABM = (CPUInfo[2] & 0x20) != 0;
}
```

<strong>Xbox:</strong> Xbox One supports ABM, AES, BMI1, and MOVBE. Xbox Series X\|S supports those as well plus BMI2.

<strong>Windows on ARM64:</strong> Windows 11 on ARM64 emulation of x64 now supports AVX instructions and others [per this blog post](https://blogs.windows.com/windows-insider/2024/11/06/announcing-windows-11-insider-preview-build-27744-canary-channel/). Initially it only supported up to SSE 4.2.

<strong>Related</strong>: See [Visual C++ Team Blog](https://devblogs.microsoft.com/cppblog/bit-in-visual-studio-2019-version-16-8-preview-2/)
