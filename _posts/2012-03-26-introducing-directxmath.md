---
layout: post
title: Introducing DirectXMath
date: 2012-03-26 16:28
author: walbourn
comments: true
categories: [Uncategorized, xnamath]
---
The <em>Windows SDK for Windows 8 </em>(included with Visual Studio 2012) ships with the DirectXMath library which is the next major revision of the C++ SIMD graphics math library known as “XNAMath” in the DirectX SDK and Xbox 360 XDK. Think of it as “XNAMath version 3”—for the historically inclined, XNAMath itself was essentially “xboxmath version 2”

DirectXMath started life as “<a href="http://blogs.msdn.com/b/chuckw/archive/2011/02/23/xna-math-version-2-04.aspx">XNAMath 2.04</a>”. The primary goals were to provide an excellent C++ SIMD math library for use for Windows Store apps (a.k.a. Metro style apps) on Windows 8 including ARM-NEON optimizations for the new <a href="http://blogs.msdn.com/b/b8/archive/2012/02/09/building-windows-for-the-arm-processor-architecture.aspx">Windows on ARM</a> (aka Windows RT) platform, keep all the goodness of XNAMath in the <em>DirectX SDK</em> for existing Windows graphics developers targeting Windows x86 and Windows x64 using SSE2, and generally be easily compatible with existing ‘client code’ using XNAMath. We also wanted to improve usability and more closely match the functionality available for C# developers using <em>XNA Game Studio</em>.

The first major design decision was to drop support for older Visual C++ compilers that did not support <a href="http://blogs.msdn.com/b/vcblog/archive/2011/09/12/10209291.aspx">C++11</a> (known as C++0x at the time), and this means Visual C++ 2010 or Visual Studio 2012 (aka Visual Studio 11) is required. This allows removal of all the various “<span style="font-family: courier new,courier">windows.h</span>” specific types (<span style="font-family: courier new,courier">UINT</span>, <span style="font-family: courier new,courier">BYTE</span>, etc.) and using standard C++ types in “<span style="font-family: courier new,courier">stdint.h</span>” (<span style="font-family: courier new,courier">size_t</span>, <span style="font-family: courier new,courier">uint32_t</span>, <span style="font-family: courier new,courier">uint8_t</span>, etc.). The headers were reorganized and use of C++ namespaces introduced to make it easier to use the library, especially in reducing the clutter when using IntelliSense.

The second major decision was to not support the Xbox 360 platform. This was a tough one, but the reality is that xboxmath is deeply entwined with Xbox 360 codebase, particularly the graphics components. XNAMath was able to replace xboxmath, but only by maintaining 100% support for every possible use of xboxmath including numerous older compilers, pure C contexts, etc. xboxmath was also designed to exactly match every quirk of the Xbox 360’s VMX128 intrinsics set which made it difficult to make optimal design decisions for Windows and SSE. In general, it should be possible to make the same code compile with DirectXMath on Windows and XNAMath on Xbox 360 without too many <span style="font-family: courier new,courier">#ifdef</span>s with some judicious use of <span style="font-family: courier new,courier">typedef</span>.

The primary ‘breaking change’ in DirectXMath compared to XNAMath are the parameters for <span style="font-family: courier new,courier">XMVectorPermute</span> which now takes four 0-7 indices instead of a VMX128 <span style="font-family: courier new,courier">__vperm</span> control word (possibly created by <span style="font-family: courier new,courier">XMVectorPermuteControl</span> from 0-7 indices). There are now template forms of <span style="font-family: courier new,courier">XMVectorPermute</span> and <span style="font-family: courier new,courier">XMVectorSwizzle</span> (as well as <span style="font-family: courier new,courier">XMVectorShiftLeft</span>, <span style="font-family: courier new,courier">XMVectorRotateLeft</span>, <span style="font-family: courier new,courier">XMVectorRotateRight</span>, and <span style="font-family: courier new,courier">XMVectorInsert</span>) which can for SSE end up being  executed with a single or just a few intrinsics—the XNAMath version currently has to spill to memory to emulate the VMX128 <span style="font-family: courier new,courier">__vperm</span> instruction. Template specialization is used to provide similar performance for common ARM-NEON ‘swizzles’ and ‘permutes’.

The <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh437833.aspx">DirectXMath</a> <em>Programming Guide</em> on MSDN provides full detail on <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh855941.aspx">What’s New</a> in the library, and a <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee418730.aspx">Code Migration</a> guide for current users of XNAMath. For developers using DirectXMath for the first time, the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee418725.aspx">Getting Started</a> page has been expanded to provide more basic usage information.

The DirectXMath library is all inline (as was XNAMath) and has very few Windows dependencies. In fact the only dependency on ‘<span style="font-family: courier new,courier">windows.h’</span> is the <span style="font-family: courier new,courier">XMVerifyCPUSupport</span> function which is coded to always return ‘false’ if ‘<span style="font-family: courier new,courier">windows.h’</span> is not included before “<span style="font-family: courier new,courier">DirectXMath.h</span>” so you don’t need the Windows headers except in the module where you handle startup verification. The library is annotated using SAL2 (rather than the older VS-style or Windows-style annotations), so requires the standalone <a href="http://msdn.microsoft.com/en-us/windows/hardware/hh852363">Windows 8.0 SDK</a> or some additional fixups to use with Visual C++ 2010.

BTW, if you want to know what those SAL2 fixups look like:
<pre class="scroll"><code class="cplusplus">#if defined(_MSC_VER) &amp;&amp; (_MSC_VER&lt;1610) &amp;&amp; !defined(_In_reads_)
 #define _Analysis_assume_(exp) __analysis_assume(exp)
 #define _In_reads_(exp) _In_count_c_(exp)
 #define _Out_writes_(exp) _Out_cap_c_(exp)
 #define _In_reads_bytes_(exp) _In_bytecount_x_(exp)
 #define _Out_writes_bytes_(exp) _Out_bytecap_x_(exp)
 #endif
 
 #ifndef _Use_decl_annotations_
 #define _Use_decl_annotations_
 #endif</code></pre>
Additional math functionality that build on DirectXMath's capabilities are also availabl
<ul>
 	<li><a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/01/xdsp-h.aspx">Digital Signal Processing helper functions</a></li>
 	<li><a href="http://blogs.msdn.com/b/chuckw/archive/2012/07/28/spherical-harmonics-math.aspx">Spherical Harmonics math</a></li>
</ul>
<h1>Porting Notes</h1>
A detailed list of D3DXMath mappings to DirectXMath is available on <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff729728.aspx">MSDN</a>.

<strong>Note:</strong> The <em>Windows SDK for Windows 8 Consumer Preview </em>included with <a href="http://blogs.msdn.com/b/chuckw/archive/2012/02/29/visual-studio-11-beta.aspx">Visual Studio 11 Beta</a> has DirectXMath version 3.02. Details on the breaking changes since the Developer Preview are covered in the official <a href="http://go.microsoft.com/fwlink/?LinkID=242888">Migration Guide</a>.

<strong>Update</strong>: The <em>Windows SDK for Windows 8 Release Preview / <a href="http://blogs.msdn.com/b/b8/archive/2012/08/01/releasing-windows-8-august-1-2012.aspx">RTM</a> </em>included with <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/31/visual-studio-2012-release-candidate.aspx">Visual Studio 2012</a> has DirectXMath version 3.03. Details on the breaking changes since the Consumer Preview are covered in the official <a href="http://go.microsoft.com/fwlink/?LinkId=251943">Migration Guide</a>.

<strong>Windows phone:</strong> The <a href="http://go.microsoft.com/fwlink/?LinkID=261873">Windows Phone SDK 8.0</a> includes DirectXMath version 3.03.

<strong>VS 2013 Preview: </strong>The <em>Windows SDK for Windows 8.1 Preview</em> included with the Visual Studio 2013 Preview includes DirectXMath 3.05.

<strong>VS 2013 RC:</strong> The <em>Windows 8.1 SDK </em>included with Visual Studio 2013 RC includes DirectXMath 3.06. See <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh855941.aspx">What's New</a> on MSDN for details.

<strong>SimpleMath:</strong> If you are new to C++ and/or SIMD programming, you might want to take a look at '<a href="https://github.com/Microsoft/DirectXTK/wiki/SimpleMath">simple math</a>' as a starting point.

<strong>Samples:</strong> <a href="http://code.msdn.microsoft.com/DirectXMath-Win32-Sample-f365b9e5">DirectXMath Win32 Sample</a>

<strong>Note:</strong> DirectXMath is now hosted on <a href="https://github.com/Microsoft/DirectXMath">GitHub</a>.

<strong>Related</strong>: <a href="http://blogs.msdn.com/b/chuckw/archive/2012/06/22/xna-math-version-2-05-smoothing-the-transition-to-directxmath.aspx">XNA Math version 2.05</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-sse-sse2-and-arm-neon.aspx">DirectXMath: SSE, SSE2, and ARM-NEON</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/03/06/known-issues-directxmath-3-03.aspx">Known Issues: DirectXMath 3.03</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/10/24/directxmath-3-06.aspx">DirectXMath 3.06</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2015/04/29/directxmath-3-07.aspx">DirectXMath 3.07</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2015/12/01/directxmath-3-08.aspx">DirectXMath 3.08</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2016/08/02/directxmath-3-09/">DirectXMath 3.09</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2017/04/06/directxmath-3-10/">DirectXMath 3.10</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2017/06/28/directxmath-3-11/">DirectXMath 3.11</a>
