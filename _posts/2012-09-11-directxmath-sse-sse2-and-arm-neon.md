---
layout: msdnpost
title: DirectXMath - SSE, SSE2, and ARM-NEON
date: 2012-09-11 11:43
author: Chuck Walbourn
comments: true
categories: [xbox one, xnamath, directxmath]
---
The <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a> library provides high-performance linear algebra math support for the typical kinds of operations found in a 3D graphics application. The library achieves this by making use of specialized SIMD (Single-Instruction-Multiple-Data) instruction sets to work on 4 single-precision float values at a time. The design of the library is itself heavily influenced by these instructions to provide data in a way most friendly to efficient computation.
<!--more-->

The original xboxmath library shipped only for the Xbox 360 and the API was designed to expose the majority of the VMX128 instruction set (a custom extension of the PowerPC <a href="http://en.wikipedia.org/wiki/AltiVec">AltiVec</a> SIMD instruction set). These instructions were focused on the kind of SIMD most useful for games: 4-way single-precision float vectors (similar to HLSL's float4) with a few limited integer-based instructions plus some specialized instructions for coping with common Direct3D packed formats.

The <a href="https://walbourn.github.io/a-little-love-for-xnamath/">XNAMath</a> library (aka xboxmath version 2) kept the same API but added optimized support for Windows as well as Xbox 360. The <a href="http://en.wikipedia.org/wiki/Streaming_SIMD_Extensions">SSE</a> instruction set (intrinsics are in the <code>xmmintrin.h</code> header) provides the basic functionality, namely instructions for working with float4-style vectors (``__m128``). The <a href="http://en.wikipedia.org/wiki/SSE2">SSE2</a> instruction set (intrinsics are in the <code>emmintrin.h</code> header) provides support for integer operations on int4/uint4 vectors (``__m128i``). While SSE2 also provides support for other kinds of vectors (double2, byte16, short8, etc.) as well, these were not needed by the XNAMath/xboxmath API.

Historically, making use of SIMD instructions has been complicated by the fact that on a CPU without support for them, these instructions crash the application generating an invalid instruction hardware exception. For the Xbox 360, this was not a concern because as a fixed platform every system had the same VMX128 instruction set. D3DXMath and other math libraries on Windows have made use of dynamic codepaths, typically through function pointers, and included numerous implementations that use a different mix of instructions. One of these used traditional scalar floating point math so that it could be used as the fall back on a system without support for the SIMD instructions.

In theory this is a very sensible solution, but it has a number of problems. The first is that calling conventions (also called ABI – Application Binary Interface) were not designed for efficient passing of SIMD data so the use of a function pointer already introduced some overhead copying SIMD registers to and from the stack on either side of the call. The indirect jump itself caused some additional overhead. This cumulative cost implies that the actual computation itself must be expensive enough to make this worthwhile. Doing a simple dot-product or cross-product was typically not enough work to cover this overhead cost, while more complex operations such as a matrix-matrix multiply was a net win but still lost some efficiency. This also made it less efficient to compose these functions together in an application. Xboxmath avoided all these issues by making all the functions inline and having no dynamic code paths at all. For XNAMath, the 'baseline' instruction set had to have similar "universal" support to keep the 'all inline' model.

SSE and SSE2 fit these requirements rather well. All x64 capable CPUs must support both SSE and SSE2 because the x64 native code standard requires they be used for all float and double computations (the 32-bit x87 instruction set was deprecated for x64 native). In fact, this support is so ubiquitous that the Windows 8 operating system itself <a href="http://windows.microsoft.com/en-US/windows-8/what-is-pae-nx-sse2">requires</a> SSE and SSE2 instruction support even for 32-bit (x86) versions and won't install on a system without them--the same is true for Windows 8.1 and Windows 10.

DirectXMath (aka XNAMath version 3) started from XNAMath's support and was evolved to be more efficient on Windows by removing the requirement of supporting Xbox 360, as well as adding support for the Windows RT (<a href="https://channel9.msdn.com/posts/Building-Windows-for-the-ARM-processor-architecture">Window on ARM</a>) platform. All Windows RT systems are required to support <a href="http://en.wikipedia.org/wiki/ARM_architecture">ARM-NEON</a> which makes it an excellent baseline instruction set for the ARM platform.

As a side note, there are some older instruction sets available on many CPUs including Intel MMX™ and AMD 3DNow!&reg;. These are not used by DirectXMath because they have been deprecated for x64 native code--except ``_m_prefetch`` and ``_m_prefetchw``. These instruction sets actually alias the standard x87 floating-point registers, which themselves have been deprecated. This scheme introduced some state management and some interference with standard float/double operations, and was more challenging to optimize than the XMM register file used by SSE. By avoiding any use of intrinsics that operate on the ``__m64`` type, the code in DirectXMath compiles for both x86 and x64 native.

<h1>Processor Support</h1>

Intel Pentium 4, AMD Athlon 64, Intel Atom, all x64-capable CPUs, and later processors support both SSE and SSE2.

Intel Pentium 3, AMD K7, and some lesser known older x86 clones (VIA C3, Transmeta Crusoe) only support SSE.

For x64 native applications, you can assume that SSE and SSE2 instruction sets are always supported. For Windows RT (Windows on ARM) applications, you can assume that ARM-NEON is always supported. For x86 Windows Store apps, universal Windows apps for Windows 10 x86, or Win32 desktop apps that require Windows 8 (i.e. built with ``_WIN32_WINNT=0x0602``) or later, you can assume SSE and SSE2 is always supported.

DirectXMath provides the <code>XMVerifyCPUSupport</code> method to validate the baseline instruction set support and can be called at application startup as a safety measure. On modern CPUs this will always succeed, but this can be a useful to ensure unsupported legacy CPUs are detected immediately.

You can also use the <code>IsProcessorFeaturePresent</code> Win32 API with <code>PF_XMMI_INSTRUCTIONS_AVAILABLE</code> to detect SSE support, <code>PF_XMMI64_INSTRUCTIONS_AVAILABLE</code> to detect SSE2 support, or <code>PF_ARM_NEON_INSTRUCTIONS_AVAILABLE</code> to detect ARM-NEON support.

For x86/x64 apps, you can use the following code as well:

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
bool bSSE = false;
bool bSSE2 = false;
if (CPUInfo[0] > 0)
{
#if defined(__clang__) || defined(__GNUC__)
    __cpuid(1, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
#else
    __cpuid(CPUInfo, 1);
#endif
    bSSE = (CPUInfo[3] & 0x2000000) != 0;
    bSSE2 = (CPUInfo[3] & 0x4000000) != 0;
}
```

> The Surface X Pro ARM64 device supports x86 with SSE, SSE2, SSE3, SSSE3, and SSE4.1 support.

<h1>Compiler Support</h1>

The x64 native (64-bit) compiler makes use of SSE/SSE2 instructions as a matter of course as it's part of the definition of the x64 architecture. The switches <code>/arch:SSE</code>, <code>/arch:SSE2</code>, and <code>/arch:IA32</code> cannot be used for x64 native builds and will be ignored.

The x86 (32-bit) compiler has historically used x87 instructions for floating-point, and can optionally make use of SSE and/or SSE2 instead by using <code>/arch:SSE</code> or <code>/arch:SSE2</code>. Since SSE2 processor support is so broad, it is recommended that you always use <code>/arch:SSE2</code> which is the default as of Visual Studio 2012. You can force the use of legacy x87 instructions by using <code>/arch:IA32</code>.

<h1>Additional Topics</h1>

In this series of posts, I explore how applications using DirectXMath can take advantage of instruction sets beyond the SSE/SSE2 baseline. Using these advanced instructions require that the application make use of dynamic codepaths, multiple versions of the EXE build for different instruction sets, or simply mandates the system have a higher minimum requirement to run. By leaving this choice to the application, the right trade-offs can be made when looking at using these additional instructions.

<ul>
 	<li><a href="https://walbourn.github.io/directxmath-sse3-and-ssse3/">SSE3 and SSSE3</a></li>
 	<li><a href="https://walbourn.github.io/directxmath-sse4-1-and-sse4-2/">SSE4.1 and SSE 4.2</a></li>
 	<li><a href="https://walbourn.github.io/directxmath-avx/">AVX</a></li>
 	<li><a href="https://walbourn.github.io/directxmath-f16c-and-fma/">F16C and FMA</a></li>
 	<li><a href="https://walbourn.github.io/directxmath-avx2/">AVX2</a></li>
 	<li><a href="https://walbourn.github.io/directxmath-arm64/">ARM64</a></li>
</ul>

<strong>Xbox:</strong> The Xbox One version of DirectXMath in the XDK and ADK includes the majority optimizations discussed in this series as Xbox One supports SSE3, SSSE3, SSE4.1, SSE4.2, AVX, and F16C. Xbox Series X\|S supports all these plus AVX2 and FMA3.

<strong>GitHub:</strong> Note that DirectXMath is now hosted on <a href="https://github.com/Microsoft/DirectXMath">GitHub</a>.

<strong>Update:</strong> DirectXMath version 3.09 or later includes the optimizations from this blog series as well, and is included in the Windows 10 SDK starting with the Anniversary Update SDK (14393). They are enabled automatically when building with ``/arch:AVX`` or ``/arch:AVX2``.
