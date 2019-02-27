---
layout: post
title: DirectXMath: AVX2
date: 2015-06-03 16:02
author: walbourn
comments: true
categories: [Uncategorized, xnamath]
---
The Advanced Vector Extensions 2 (<a href="http://en.wikipedia.org/wiki/Advanced_Vector_Extensions">AVX2</a>) rounds out the instruction set introduced with AVX. The majority of the new instructions are for 256-bit registers, so they aren't directly applicable to <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/27/introducing-directxmath.aspx">DirectXMath</a>. AVX2 is very useful if trying to make a fully equivalent <code>double4</code> version of all the DirectXMath functionality which is otherwise focused on <code>float4</code> vectors, but that is beyond the scope of this article or the library generally.

The immediate value of targeting AVX2 is that you can make use of the <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-avx.aspx">AVX</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-f16c-and-fma.aspx">FMA3, and F16C</a> optimizations already covered on the blog as all of those are included.

There is one more simple substitution for DirectXMath when using AVX2 which is also a special case for <code>XMVectorSwizzle&lt;0,0,0,0&gt;</code>
<pre class="scroll"><code class="cplusplus">inline XMVECTOR XM_CALLCONV XMVectorSplatX( FXMVECTOR V )
{
 return _mm_broadcastss_ps( V );
}</code></pre>
<h1>Processor Support</h1>
AVX2 is supported by Intel “Haswell”, AMD Excavator, and later processors.

In addition to the hardware supporting the new instruction set, the OS must support saving the new YMM register file or the AVX instructions will remain invalid. This support is included in Windows 7 Service Pack 1, Windows Server 2008 R2 Service Pack 1, Windows 8, and Windows Server 2012. This support is indicated by the OSXSAVE bit in CPUID being set along with the AVX2 support bit.
<pre class="scroll"><code class="cplusplus"> int CPUInfo[4] = {-1};
 __cpuid( CPUInfo, 0 );
 bool bAVX2 = false;
 if ( CPUInfo[0] &gt;= 7 )
 {
 __cpuid(CPUInfo, 1 );
 bool bOSXSAVE = (CPUInfo[2] &amp; 0x8000000) != 0;
 __cpuidex( CPUInfo, 7, 0 );
 bAVX2 = bOSXSAVE &amp;&amp; (CPUInfo[1] &amp; 0x20) != 0;
 }
 </code></pre>
<h1>Compiler Support</h1>
Support for AVX2 intrinsics was added to Visual Studio 2012. The <code>/arch:AVX2</code> switch is supported by <a href="http://blogs.msdn.com/b/vcblog/archive/2014/02/28/avx2-support-in-visual-studio-c-compiler.aspx">VS 2012 Update 2</a>, although IDE support wasn't added until VS 2013.

<em>Note that with this switch, the compiler will optimize code to make use of FMA3 automatically where applicable.</em>
<h1>Utility Code</h1>
The source for this project and the rest of the blog series is now available on <a href="https://github.com/Microsoft/DirectXMath">GitHub </a>under the <a href="http://opensource.org/licenses/MIT">MIT license</a>.

<strong>Xbox One:</strong> This platform does not support AVX2.

<strong>See also</strong>: <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-sse-sse2-and-arm-neon.aspx">SSE. SSE2. and ARM-NEON</a>; <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-sse3-and-ssse3.aspx">SSE3 and SSSE3</a>; <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-sse4-1-and-sse-4-2.aspx">SSE4.1 and SSE4.2</a>; <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-avx.aspx">AVX</a>; <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-f16c-and-fma.aspx">F16C and FMA</a>
