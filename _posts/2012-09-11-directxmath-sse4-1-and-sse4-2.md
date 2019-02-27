---
layout: post
title: DirectXMath: SSE4.1 and SSE4.2
date: 2012-09-11 12:18
author: walbourn
comments: true
categories: [Uncategorized, xbox one, xnamath]
---
The <a href="http://en.wikipedia.org/wiki/SSE4">SSE4</a> instruction set consists of two parts, referred as SSE4.1 and 4.2. The intrinsics are located in the <code>smmintrin.h</code> header. The SSE4.1 instruction set is the most interesting for DirectXMath, while SSE 4.2 adds some more specialized instructions for CRC checks and string handling. The key new features are a flexible dot-product instruction, float4 vector rounding, a 2-vector ‘mux’ blend, and some specialized extract/insert operations.

A number of DirectXMath functions can be replaced with a single intrinsic when using SSE4.1.
<table border="1">
<tbody>
<tr>
<td><code>XMVector2Dot(V1,V2)</code></td>
<td><code>_mm_dp_ps( V1, V2, 0x3f )</code></td>
</tr>
<tr>
<td><code>XMVector3Dot(V1,V2)</code></td>
<td><code>_mm_dp_ps( V1, V2, 0x7f )</code></td>
</tr>
<tr>
<td><code>XMVector4Dot(V1,V2)</code></td>
<td><code>_mm_dp_ps( V1, V2, 0xff )</code></td>
</tr>
<tr>
<td><code>XMVectorRound(V)</code></td>
<td><code>_mm_round_ps( V, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC )</code></td>
</tr>
<tr>
<td><code>XMVectorTruncate(V)</code></td>
<td><code>_mm_round_ps( V, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC )</code></td>
</tr>
<tr>
<td><code>XMVectorFloor(V)</code></td>
<td><code>_mm_floor_ps( V )</code></td>
</tr>
<tr>
<td><code>XMVectorCeiling(V)</code></td>
<td><code>_mm_ceil_ps( V )</code></td>
</tr>
</tbody>
</table>
The bit insert/extract instructions provide some specific optimization cases for vector accessors and setters. Here are the “Y” element versions, which can be extrapolated to the “Z” and “W” element versions very easily. Note that the standard scalar SSE/SSE2 mov already provides efficient support for the “X” element.
<pre class="scroll"><code class="cplusplus"> inline void XMVectorGetYPtr(float *y, FXMVECTOR V)
 {
 *((int*)y) = _mm_extract_ps( V, 1 );
 }

 inline uint32_t XMVectorGetIntY(FXMVECTOR V)
 {
 __m128i V1 = _mm_castps_si128( V );
 return static_cast&lt;uint32_t&gt;( _mm_extract_epi32( V1, 1 ) );
 }

 inline void XMVectorGetIntYPtr(uint32_t *y, FXMVECTOR V)
 {
 __m128i V1 = _mm_castps_si128( V );
 *y = static_cast&lt;uint32_t&gt;( _mm_extract_epi32( V1, 1 ) );
 }

 inline XMVECTOR XMVectorSetY(FXMVECTOR V, float y)
 {
 XMVECTOR vResult = _mm_set_ss(y);
 vResult = _mm_insert_ps( V, vResult, 0x10 );
 return vResult;
 }

 inline XMVECTOR XMVectorSetIntY(FXMVECTOR V, uint32_t y)
 {
 __m128i vResult = _mm_castps_si128( V );
 vResult =
 _mm_insert_epi32( vResult, static_cast&lt;int&gt;(y), 1 );
 return _mm_castsi128_ps( vResult );
 }
 </code></pre>
The <code>_mm_blend_ps</code> instruction can be used as special-cases for the <code>XMVectorPermute&lt;&gt;</code> template. We’ll make more use of these in a future installment.
<table border="1">
<tbody>
<tr>
<td><code>XMVectorPermute&lt;4,1,2,3&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0x1)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;0,5,2,3&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0x2)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;4,5,2,3&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0x3)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;0,1,6,3&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0x4)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;4,1,6,3&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0x5)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;0,5,6,3&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0x6)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;4,5,6,3&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0x7)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;0,1,2,7&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0x8)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;4,1,2,7&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0x9)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;0,5,2,7&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0xA)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;4,5,2,7&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0xB)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;0,1,6,7&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0xC)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;4,1,6,7&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0xD)</code></td>
</tr>
<tr>
<td><code>XMVectorPermute&lt;0,5,6,7&gt;(V1,V2)</code></td>
<td><code>_mm_blend_ps(V1,V2,0xE)</code></td>
</tr>
</tbody>
</table>
<h1>Processor Support</h1>
SSE4.1 is supported on Intel Core 2 (“Penryn”), Intel Core i7 (“Nehalem”), AMD Bulldozer, and later processors.

SSE 4.1 and SSE4.2 are supported on Intel Core i7 (“Nehalem”), AMD Bulldozer, and later processors.
<pre class="scroll"><code class="cplusplus">int CPUInfo[4] = {-1};
 __cpuid( CPUInfo, 0 );
 bool bSSE4_1 = false;
 bool bSSE4_2 = false;
 if ( CPUInfo[0] &gt; 0 )
 {
 __cpuid(CPUInfo, 1 );
 bSSE4_1 = (CPUInfo[2] &amp; 0x80000) != 0;
 bSSE4_2 = (CPUInfo[2] &amp; 0x100000) != 0;
 }
 </code></pre>
<h1>Compiler Support</h1>
Support for SSE4.1 and SSE4.2 intrinsics was added to Visual Studio 2010.
<h1>Utility Code</h1>
<strong>Update:</strong> The source for this project is now available on <a href="https://github.com/Microsoft/DirectXMath">GitHub</a> under the <a href="http://opensource.org/licenses/MIT">MIT license</a>.

<strong>Xbox One: </strong>This platform supports SSE4a, SSE4.1, and SSE4.2.

<strong>See also</strong>: <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-sse-sse2-and-arm-neon.aspx">SSE, SSE2, and ARM-NEON</a>; <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-sse3-and-ssse3.aspx">SSE3 and SSSE3</a>; <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-avx.aspx">AVX</a>; <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-f16c-and-fma.aspx">F16C and FMA</a>; <a href="http://blogs.msdn.com/b/chuckw/archive/2015/06/03/directxmath-avx2.aspx">AVX2</a>
