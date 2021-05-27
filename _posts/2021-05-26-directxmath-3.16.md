---
layout: post
title: DirectXMath 3.16
date: 2021-05-26 21:47
author: Chuck Walbourn
comments: true
categories: [directxmath]
---

DirectXMath 3.16 is now available via [GitHub](https://github.com/microsoft/DirectXMath/releases/tag/jan2021), [NuGet](https://www.nuget.org/packages/directxmath/2021.1.11.2), and [vcpkg](https://github.com/walbourn/vcpkg/tree/master/ports/directxmath). It is included in the **Windows 10 SDK (20348), version 2104**

> Note that the GitHub, vcpkg, and NuGet links above point to DirectXMath 3.16b which is a hot-fixed version compared to the Windows 10 SDK (20348) copy of DirectXMath 3.16. This includes a few minor syntax fixes to support clang/LLVM and GNUC for the ARM64 platform. There are no functional differences.
<!--more-->

# DirectXMath 3.15
There was no Windows 10 SDK release that included version 3.15 beyond the Insider Program, but 3.16 obviously includes all these changes as well:

* Added ``XMMatrixVectorTensorProduct`` for creating a matrix from two vectors.
* Use of ``__m256`` registers and FMA3 with ``/arch:AVX2`` for stream and some matrix functions.
* Optimized load/stores for SSE2 float2 & float3 functions.
* Optimized some instruction choices for better AMD CPU support. If you want to favor Intel like the older code did in these cases, you can define the preprocessor symbol ``_XM_FAVOR_INTEL_``.
* Improved conformance for clang/LLVM, GCC, and MinGW compilers.
* More use of constexpr and noexcept.
* Support for the Visual C++ 2015 compiler toolset was removed.

# DirectXMath 3.16
This release includes several bug fixes:

* Fixed denorm handling for ``XMConvertFloatToHalf`` to match F16C/CVT16 instructions.
* Fixed flush (too small for denorm) handling for ``XMStoreFloat3PK``.
* Fixed clamping bug in ``XMStoreByteN4``.
* Fixed ``GXMVECTOR`` for the x86 ``__vectorcall`` calling-convention to use the in-register passing.
* Cleaned up ARM-NEON intrinsics type issues for improved portability on GNUC.

It also includes new functionality:

* Added ``XMVectorLog10`` / ``XMVectorExp10`` functions (already had base-2 and base-e versions)
* Added ``XMColorRGBToYUV_UHD`` / ``XMColorYUVToRGB_UHD`` for Rec. 2020 YUV
* Added optional *rhcoords* parameter for ``BoundingFrustum::CreateFromMatrix`` which previously only supported left-handed projection matrices.

With VS 2019, there is now optional use of the Intel® Short Vector Matrix Library (SVML). This library provides highly optimized versions of SIMD sin, cos, tan, asin, acos, atan, sinh, cosh, tanh, exp, log, and pow functions. This library is ‘vendor-neutral’ so it works well on all x86/x64 compatible CPUs.

* For the Windows 10 SDK version of DirectXMath 3.16, you enable SVML usage by defining the preprocessor symbol ``_XM_SVML_INTRINSICS_``
* For the other versions, SVML use is enabled automatically with VS 2019. You can opt-out of using it by defining the symbol ``_XM_DISABLE_INTEL_SVML_``

<b>Related:</b> <a href="https://walbourn.github.io/known-issues-directxmath-3-03/">Known Issues: DirectXMath 3.03</a>, <a href="https://walbourn.github.io/directxmath-3-06/">DirectXMath 3.06</a>, <a href="https://walbourn.github.io/directxmath-3-07/">DirectXMath 3.07</a>, <a href="https://walbourn.github.io/directxmath-3-08/">DirectXMath 3.08</a>, <a href="https://walbourn.github.io/directxmath-3-09/">DirectXMath 3.09</a>, <a href="https://walbourn.github.io/directxmath-3-10/">DirectXMath 3.10</a>, <a href="https://walbourn.github.io/directxmath-3-11/">DirectXMath 3.11</a>, <a href="https://walbourn.github.io/directxmath-3-13/">DirectXMath 3.12/3.13</a>, <a href="https://walbourn.github.io/directxmath-3.14/">DirectXMath 3.14</a>
