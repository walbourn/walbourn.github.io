---
layout: post
title: Known Issues in XNAMath v2.03
date: 2011-01-20 10:57
author: Chuck Walbourn
comments: true
categories: [xnamath, directxmath]
---
Some users of <a href="https://docs.microsoft.com/en-us/windows/desktop/dxmath/ovw-xnamath-progguide">XNAMath</a> have reported a range problem with the <strong>XMVectorFloor</strong> and <strong>XMVectorCeiling</strong> functions with the SSE implementation (i.e. whenever the values are greater than ``INT_MAX``). These fixes will be included in a future release of XNAMath, but since XNAMath is an all-header implementation it can also be fixed directly by affected developers in the <code>xnamathvector.inl</code> file.
<!--more-->

<p>Here are the corrected versions:</p>

```cpp
XMFINLINE XMVECTOR XMVectorFloor
(FXMVECTOR V)
{
#if defined(_XM_NO_INTRINSICS_)
    XMVECTOR vResult = { floorf(V.vector4_f32[0]), floorf(V.vector4_f32[1]), floorf(V.vector4_f32[2]), floorf(V.vector4_f32[3]) };
    return vResult;
#elif defined(_XM_SSE_INTRINSICS_)
    // To handle NAN, INF and numbers greater than 8388608, use masking
    // Get the abs value
    __m128i vTest = _mm_and_si128(reinterpret_cast<const __m128i *>(&V)[0], g_XMAbsMask);
    // Test for greater than 8388608 (All floats with NO fractionals, NAN and INF
    vTest = _mm_cmplt_epi32(vTest, g_XMNoFraction);
    // Convert to int and back to float for rounding
    XMVECTOR vResult = _mm_sub_ps(V, g_XMOneHalfMinusEpsilon);
    __m128i vInt = _mm_cvtps_epi32(vResult);
    // Convert back to floats
    vResult = _mm_cvtepi32_ps(vInt);
    // All numbers less than 8388608 will use the round to int
    vResult = _mm_and_ps(vResult, reinterpret_cast<const XMVECTOR *>(&vTest)[0]);
    // All others, use the ORIGINAL value
    vTest = _mm_andnot_si128(vTest, reinterpret_cast<const __m128i *>(&V)[0]);
    vResult = _mm_or_ps(vResult, reinterpret_cast<const XMVECTOR *>(&vTest)[0]);
    return vResult;
#else // _XM_VMX128_INTRINSICS_
#endif // _XM_VMX128_INTRINSICS_
}

//------------------------------------------------------------------------------
XMFINLINE XMVECTOR XMVectorCeiling(FXMVECTOR V)
{
#if defined(_XM_NO_INTRINSICS_)
    XMVECTOR vResult = { ceilf(V.vector4_f32[0]), ceilf(V.vector4_f32[1]), ceilf(V.vector4_f32[2]), ceilf(V.vector4_f32[3]) };
    return vResult;
#elif defined(_XM_SSE_INTRINSICS_)
    // To handle NAN, INF and numbers greater than 8388608, use masking
    // Get the abs value
    __m128i vTest = _mm_and_si128(reinterpret_cast<const __m128i *>(&V)[0], g_XMAbsMask);
    // Test for greater than 8388608 (All floats with NO fractionals, NAN and INF
    vTest = _mm_cmplt_epi32(vTest, g_XMNoFraction);
    // Convert to int and back to float for rounding
    XMVECTOR vResult = _mm_add_ps(V, g_XMOneHalfMinusEpsilon);
    __m128i vInt = _mm_cvtps_epi32(vResult);
    // Convert back to floats
    vResult = _mm_cvtepi32_ps(vInt);
    // All numbers less than 8388608 will use the round to int
    vResult = _mm_and_ps(vResult, reinterpret_cast<const XMVECTOR *>(&vTest)[0]);
    // All others, use the ORIGINAL value
    vTest = _mm_andnot_si128(vTest, reinterpret_cast<const __m128i *>(&V)[0]);
    vResult = _mm_or_ps(vResult, reinterpret_cast<const XMVECTOR *>(&vTest)[0]);
    return vResult;
#else // _XM_VMX128_INTRINSICS_
#endif // _XM_VMX128_INTRINSICS_
}
```

> Note that this is the same technique used by <strong>XMVectorRound</strong> to get around the same range issue in the SSE2 float<->integer conversion mechanism.

<strong>Updated:</strong> This issue has been fixed for <a href="https://walbourn.github.io/xna-math-version-2-04/">XNAMath v2.04</a> and <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a>.
