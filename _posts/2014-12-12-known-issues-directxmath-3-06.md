---
layout: post
title: Known Issues: DirectXMath 3.06
date: 2014-12-12 15:51
author: walbourn
comments: true
categories: [Uncategorized, xnamath]
---
The Windows 8.1 SDK includes <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/27/introducing-directxmath.aspx">DirectXMath</a> version 3.06 for use with Windows Store apps and Win32 desktop applications on Windows 8.x, Windows RT, Windows 7, and Windows Vista. DirectXMath 3.06 is also part of the Windows phone 8.1 SDK for use on Windows phone 8.x. There are a number of minor bugs in the library that have been reported by customers since it was released, which will be addressed in future SDK releases. In the meantime, since the code is all inline in the headers, you can make the fix directly to a local copy as needed or work around the issue in your own code.
<h1>BoundingBox::Contains</h1>
The triangle/oriented box/frustum in axis-aligned tests often return INTERSECTS when they should return CONTAINS. The fix is in <code>DirectXCollision.inl</code> change <code>XMVector3LengthSq</code> to <code>XMVectorAbs</code> in 3 places for the triangle in axis-aligned box test (lines 1293, 1296, and 1299), once in the oriented box in axis-aligned test (line 1409), and once in the frustum in axis-aligned box test (line 1437).
<h1>XMVectorRound</h1>
The rounding function works fine unless the number has a magnitude larger than 8388608 (or is a floating-point special) in which case it returns the wrong result. The fix is to put a new version of the function into <code>DirectXMathVector.inl</code> starting on line 2353:
<pre class="scroll"><code class="cplusplus">inline XMVECTOR XM_CALLCONV XMVectorRound
 (
 FXMVECTOR V
 )
 {
 #if defined(_XM_NO_INTRINSICS_)
 
 XMVECTOR vResult = {
 Internal::round_to_nearest(V.vector4_f32[0]),
 Internal::round_to_nearest(V.vector4_f32[1]),
 Internal::round_to_nearest(V.vector4_f32[2]),
 Internal::round_to_nearest(V.vector4_f32[3])
 };
 return vResult;
 
 #elif defined(_XM_ARM_NEON_INTRINSICS_)
 uint32x4_t sign = vandq_u32( V, g_XMNegativeZero );
 uint32x4_t sMagic = vorrq_u32( g_XMNoFraction, sign );
 float32x4_t R1 = vaddq_f32( V, sMagic );
 R1 = vsubq_f32( R1, sMagic );
 float32x4_t R2 = vabsq_f32( V );
 uint32x4_t mask = vcleq_f32( R2, g_XMNoFraction );
 XMVECTOR vResult = vbslq_f32( mask, R1, V );
 return vResult;
 #elif defined(_XM_SSE_INTRINSICS_)
 __m128 sign = _mm_and_ps( V, g_XMNegativeZero );
 __m128 sMagic = _mm_or_ps( g_XMNoFraction, sign );
 __m128 R1 = _mm_add_ps( V, sMagic );
 R1 = _mm_sub_ps( R1, sMagic );
 __m128 R2 = _mm_and_ps( V, g_XMAbsMask );
 __m128 mask = _mm_cmple_ps( R2, g_XMNoFraction );
 R2 = _mm_andnot_ps(mask,V);
 R1 = _mm_and_ps(R1,mask);
 XMVECTOR vResult = _mm_xor_ps(R1, R2);
 return vResult;
 #endif
 }</code></pre>
Thanks to <a href="http://randomascii.wordpress.com/2014/01/27/theres-only-four-billion-floatsso-test-them-all/">Bruce Dawson</a> for the report and fix. This issue does not affect the SSE4 version of <code>XMVectorRound</code> from this <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-sse4-1-and-sse-4-2.aspx">post</a>.
<h1>XMVectorATan2, XMVectorATan2Est</h1>
This is a really subtle bug with a specific special-case of X == INF, Y is finite &lt; 0. It was returning +0 instead of -0. The fix is in <code>DirectXMathVector.inl</code> on lines 5148 and 5790 change:
<pre class="scroll"><code class="cplusplus"> R1 = XMVectorSelect( Pi, Zero, XIsPositive );
</code></pre>
-&gt;
<pre class="scroll"><code class="cplusplus"> R1 = XMVectorSelect( Pi, g_XMNegativeZero, XIsPositive ); </code></pre>
<h1>XMStoreFloat3SE</h1>
While DirectXMath 3.06 did fix this format, there was still a subtle bug in it. The fix is in <code>DirectXPackedVector.inl</code> line 1771, change:
<pre class="scroll"><code class="cplusplus"> fi.i &amp;= 0xFF800000; // cut off fraction </code></pre>
<strong>-&gt;</strong>
<pre class="scroll"><code class="cplusplus"> fi.i += 0x00004000; // round up leaving 9 bits in fraction (including assumed 1)</code></pre>
<strong>Related: </strong><a href="http://blogs.msdn.com/b/chuckw/archive/2013/03/06/known-issues-directxmath-3-03.aspx">Known Issues: DirectXMath 3.03</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/10/24/directxmath-3-06.aspx">DirectXMath 3.06</a>

<strong>Note:</strong> Attached are the relevant files with these fixes applied. It requires you use the rest of the library in the Windows 8.1 SDK or the Windows phone 8.1 SDK, and the code is subject to the respective SDK's license agreement.

<strong>Update:</strong> These fixes all shipped in <a href="http://blogs.msdn.com/b/chuckw/archive/2015/04/29/directxmath-3-07.aspx">DirectXMath 3.07</a>.

<strong>GitHub:</strong> Note that DirectXMath is now hosted on <a href="https://github.com/Microsoft/DirectXMath">GitHub</a>.

<a href="https://msdnshared.blob.core.windows.net/media/MSDNBlogsFS/prod.evol.blogs.msdn.com/CommunityServer.Components.PostAttachments/00/10/58/04/91/DirectXMath_306_hotfixes.zip">DirectXMath_306_hotfixes.zip</a>
