---
layout: post
title: Known Issues - DirectXMath 3.03
date: 2013-03-05 16:36
author: Chuck Walbourn
comments: true
categories: [windowssdk, directxmath]
---
The Windows 8.0 SDK includes <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a> version 3.03 for use with Windows Style apps and Win32 desktop applications on Windows 8, Windows RT, Windows 7, and Windows Vista. DirectXMath 3.03 is also part of the Windows phone 8.0 SDK for use on Windows phone 8. There are a number of minor bugs in the library that have been reported by customers since it was released, which will be addressed in future SDK releases. In the meantime, since the code is all inline in the headers, you can make the fix directly to a local copy as needed or work around the issue in your own code.
<!--more-->

<strong>Visual Studio 2013:</strong> <a href="https://walbourn.github.io/directxmath-3-06/">DirectXMath 3.06</a> is included in the Windows 8.1 SDK and in VS 2013. The latest version of DirectXMath includes all these fixes with an additional fix for XMLoadFloat3SE and XMStoreFloat3SE (see below).

<strong>Visual Studio 2013 Update 5 / Windows 10 SDK</strong>: <a href="https://walbourn.github.io/directxmath-3-07/">DirectXMath 3.07</a> is included in the Windows 8.1 SDK (Spring 2015) update. <a href="https://walbourn.github.io/directxmath-3-08/">DirectXMath 3.08</a> is in the Windows 10 SDK update (10586).

<h1>XMVector3Cross</h1>

The ARM-NEON implementation leaves the ``.w`` component undefined instead of setting it to zero as the other versions do. The fix is to change <code>DirectXMathVector.inl</code> line 7678.

```cpp
// Original code
return veorq_u32( vResult, g_XMFlipY );

// Corrected code
vResult = veorq_u32( vResult, g_XMFlipY );
return vandq_u32( vResult, g_XMMask3 );
```

<h1>XMVectorFloor and XMVectorCeiling</h1>

These functions use a naïve implementation that fails when given an odd whole number (such as 105.0) which causes the answer to jump to 104.0 due to round-to-nearest (even) behavior. The solution is to replace these functions with a different implementation in <code>DirectXMathVector.inl</code> starting on line 2426.

```cpp
inline XMVECTOR XMVectorFloor
(
    FXMVECTOR V
)
{
#if defined(_XM_NO_INTRINSICS_)

    XMVECTOR vResult = {
    floorf(V.vector4_f32[0]),
    floorf(V.vector4_f32[1]),
    floorf(V.vector4_f32[2]),
    floorf(V.vector4_f32[3])
    };
    return vResult;

#elif defined(_XM_ARM_NEON_INTRINSICS_)
    float32x4_t vTest = vabsq_f32(V);
    vTest = vcltq_f32(vTest, g_XMNoFraction);
    // Truncate
    int32x4_t vInt = vcvtq_s32_f32(V);
    XMVECTOR vResult = vcvtq_f32_s32(vInt);
    XMVECTOR vLarger = vcgtq_f32(vResult, V);
    // 0 -> 0, 0xffffffff -> -1.0f
    vLarger = vcvtq_f32_s32(vLarger);
    vResult = vaddq_f32(vResult, vLarger);
    // All numbers less than 8388608 will use the round to int
    // All others, use the ORIGINAL value
    return vbslq_f32(vTest, vResult, V);
#elif defined(_XM_SSE_INTRINSICS_)
    // To handle NAN, INF and numbers greater than 8388608, use masking
    __m128i vTest = _mm_and_si128(_mm_castps_si128(V), g_XMAbsMask);
    vTest = _mm_cmplt_epi32(vTest, g_XMNoFraction);
    // Truncate
    __m128i vInt = _mm_cvttps_epi32(V);
    XMVECTOR vResult = _mm_cvtepi32_ps(vInt);
    __m128 vLarger = _mm_cmpgt_ps(vResult, V);
    // 0 -> 0, 0xffffffff -> -1.0f
    vLarger = _mm_cvtepi32_ps(_mm_castps_si128(vLarger));
    vResult = _mm_add_ps(vResult, vLarger);
    // All numbers less than 8388608 will use the round to int
    vResult = _mm_and_ps(vResult, _mm_castsi128_ps(vTest));
    // All others, use the ORIGINAL value
    vTest = _mm_andnot_si128(vTest, _mm_castps_si128(V));
    vResult = _mm_or_ps(vResult, _mm_castsi128_ps(vTest));
    return vResult;
#else // _XM_VMX128_INTRINSICS_
#endif // _XM_VMX128_INTRINSICS_
}
```

and <code>DirectXMathVector.inl</code> starting on line 2467

```cpp
inline XMVECTOR XMVectorCeiling
(
    FXMVECTOR V
)
{
#if defined(_XM_NO_INTRINSICS_)
    XMVECTOR vResult = {
    ceilf(V.vector4_f32[0]),
    ceilf(V.vector4_f32[1]),
    ceilf(V.vector4_f32[2]),
    ceilf(V.vector4_f32[3])
    };
    return vResult;

#elif defined(_XM_ARM_NEON_INTRINSICS_)
    float32x4_t vTest = vabsq_f32(V);
    vTest = vcltq_f32(vTest, g_XMNoFraction);
    // Truncate
    int32x4_t vInt = vcvtq_s32_f32(V);
    XMVECTOR vResult = vcvtq_f32_s32(vInt);
    XMVECTOR vSmaller = vcltq_f32(vResult, V);
    // 0 -> 0, 0xffffffff -> -1.0f
    vSmaller = vcvtq_f32_s32(vSmaller);
    vResult = vsubq_f32(vResult, vSmaller);
    // All numbers less than 8388608 will use the round to int
    // All others, use the ORIGINAL value
    return vbslq_f32(vTest, vResult, V);
#elif defined(_XM_SSE_INTRINSICS_)
    // To handle NAN, INF and numbers greater than 8388608, use masking
    __m128i vTest = _mm_and_si128(_mm_castps_si128(V), g_XMAbsMask);
    vTest = _mm_cmplt_epi32(vTest, g_XMNoFraction);
    // Truncate
    __m128i vInt = _mm_cvttps_epi32(V);
    XMVECTOR vResult = _mm_cvtepi32_ps(vInt);
    __m128 vSmaller = _mm_cmplt_ps(vResult, V);
    // 0 -> 0, 0xffffffff -> -1.0f
    vSmaller = _mm_cvtepi32_ps(_mm_castps_si128(vSmaller));
    vResult = _mm_sub_ps(vResult, vSmaller);
    // All numbers less than 8388608 will use the round to int
    vResult = _mm_and_ps(vResult, _mm_castsi128_ps(vTest));
    // All others, use the ORIGINAL value
    vTest = _mm_andnot_si128(vTest, _mm_castps_si128(V));
    vResult = _mm_or_ps(vResult, _mm_castsi128_ps(vTest));
    return vResult;
#else // _XM_VMX128_INTRINSICS_
#endif // _XM_VMX128_INTRINSICS_
}
```

This problem does not apply to the <a href="https://walbourn.github.io/directxmath-sse4-1-and-sse-4-2/">SSE 4.1 versions</a> of these functions.

<h1>XMConvertHalfToFloat and XMConvertFloatToHalf</h1>

These functions convert to the Xbox 360 variant of float16 rather than the IEEE 754 standard version of float16. This means values greater than +- 65504.0 map to QNAN rather than +/- INF as would be expected. The implementation makes sense for XNAMath (aka xboxmath 2.x), but doesn't make any sense in DirectXMath since it <a href="https://walbourn.github.io/xna-math-version-2-05-smoothing-the-transition-to-directxmath/">does not support</a> the Xbox 360 platform. The solution is to change <code>DirectXPackedVector.inl</code> starting on line 34.

```cpp
// Original code
uint32_t Exponent;
if ((Value & 0x7C00) != 0) // The value is normalized
{
    Exponent = (uint32_t)((Value >> 10) & 0x1F);
}

// Corrected code
uint32_t Exponent = (Value & 0x7C00);
if (Exponent == 0x7C00) // INF/NAN
{
    Exponent = (uint32_t)143;
}
else if (Exponent != 0) // The value is normalized
{
    Exponent = (uint32_t)((Value >> 10) & 0x1F);
}
```

and in <code>DirectXPackedVector.inl</code> starting on line 111.

```cpp
// Original code
if (IValue > 0x47FFEFFFU)
{
    // The number is too large to be represented as a half. Saturate to infinity.
    Result = 0x7FFFU;
}
else

// Corrected code
if (IValue > 0x477FE000U)
{
    // The number is too large to be represented as a half. Saturate to infinity.
    if (((IValue & 0x7F800000) == 0x7F800000) && ((IValue & 0x7FFFFF) != 0))
    {
        Result = 0x7FFF; // NAN
    }
    else
    {
        Result = 0x7C00U; // INF
    }
}
else
```

This problem does not apply to the <a href="https://walbourn.github.io/directxmath-f16c-and-fma/">F16C / CVT16 versions</a> of these functions

<h1>BoundingOrientedBox::Transform and BoundFrustum::Transform</h1>

The matrix form of these functions do not properly handle scaling transformations. The same change is applied in <code>DirectXCollision.inl</code> on line 1952 and again on line 2824

```cpp
//Original code
XMVECTOR Rotation = XMQuaternionRotationMatrix(M);

// Corrected code
XMMATRIX nM;
nM.r[0] = XMVector3Normalize(M.r[0]);
nM.r[1] = XMVector3Normalize(M.r[1]);
nM.r[2] = XMVector3Normalize(M.r[2]);
nM.r[3] = g_XMIdentityR3;
XMVECTOR Rotation = XMQuaternionRotationMatrix(nM);
```

<h1>XMStoreFloat3PK</h1>

These functions have some minor typos in the exact bits that are used in specials-generation. This doesn't really impact the functionality in any obvious way, but it's also an easy fix. In <code>DirectXPackedVector.inl</code> on line 1709.

```cpp
// Original code
Result[j] = 0x7c0 | (((I >> 17) | (I > 11) | (I >> 6) | (I)) & 0x3f);

// Corrected code
Result[j] = 0x7c0 | (((I >> 17) | (I >> 11) | (I >> 6) | (I)) & 0x3f);
```

and <code>DirectXPackedVector.inl</code> line 1756.

```cpp
// Original code
Result[2] = 0x3e0 | (((I >> 18) | (I > 13) | (I >> 3) | (I)) & 0x1f);

// Corrected code
Result[2] = 0x3e0 | (((I >> 18) | (I >> 13) | (I >> 3) | (I)) & 0x1f);
```

<h1>XMLoadFloat3SE / XMStoreFloatSE (3.06)</h1>

These functions were intended to match ``DXGI_FORMAT_R9G9B9E5_SHAREDEXP``, but were not properly implemented. The DXGI format does not support specials or denormals, and has no implicit lead value of 1. Here are the correct implementations. In <code>DirectXPackedVector.inl</code> starting on line 590.

```cpp
inline XMVECTOR PackedVector::XMLoadFloat3SE
(
    const XMFLOAT3SE* pSource
)
{
    assert(pSource);

    union { float f; int32_t i; } fi;
    fi.i = 0x33800000 + (pSource->e << 23);
    float Scale = fi.f;

    XMVECTORF32 v = {
    Scale * float(pSource->xm),
    Scale * float(pSource->ym),
    Scale * float(pSource->zm),
    1.0f };
    return v;
}
```

and <code>DirectXPackedVector.inl</code> starting on line 1800.

```cpp
inline void PackedVector::XMStoreFloat3SE
(
    XMFLOAT3SE* pDestination,
    FXMVECTOR V
)
{
    assert(pDestination);

    XMFLOAT3A tmp;
    XMStoreFloat3A(&tmp, V);

    static const float maxf9 = float(0x1FF << 7);
    static const float minf9 = float(1.f / (1 << 16));

    float x = (tmp.x >= 0.f) ? ((tmp.x > maxf9) ? maxf9 : tmp.x) : 0.f;
    float y = (tmp.y >= 0.f) ? ((tmp.y > maxf9) ? maxf9 : tmp.y) : 0.f;
    float z = (tmp.z >= 0.f) ? ((tmp.z > maxf9) ? maxf9 : tmp.z) : 0.f;

    const float max_xy = (x > y) ? x : y;
    const float max_xyz = (max_xy > z) ? max_xy : z;

    const float maxColor = (max_xyz > minf9) ? max_xyz : minf9;

    union { float f; int32_t i; } fi;
    fi.f = maxColor;
    fi.i &= 0xFF800000; // cut off fraction

    pDestination->e = (fi.i - 0x37800000) >> 23;

    fi.i = 0x83000000 - fi.i;
    float ScaleR = fi.f;

    pDestination->xm = static_cast<uint32_t>(Internal::round_to_nearest(x * ScaleR));
    pDestination->ym = static_cast<uint32_t>(Internal::round_to_nearest(y * ScaleR));
    pDestination->zm = static_cast<uint32_t>(Internal::round_to_nearest(z * ScaleR));
}
```

> Attached are the relevant files with these fixes applied. It requires you use the rest of the library in the Windows 8.0 SDK or the Windows phone 8.0 SDK, and the code is subject to the respective SDK's license agreement. Was refreshed on September 9, 2013

<strong>GitHub:</strong> Note that DirectXMath is now hosted on <a href="https://github.com/Microsoft/DirectXMath">GitHub</a>.

<a href="https://walbourn.github.io/download/DirectXMath_303_hotfixes.zip">DirectXMath_303_hotfixes.zip</a>
