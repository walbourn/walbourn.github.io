---
layout: post
title: What's Coming in the June 2010 DirectX SDK
date: 2010-04-15 11:57
author: walbourn
comments: true
categories: [dxsdk, Uncategorized]
---
<p><strong>The DirectX SDK is now legacy. See "<a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">Where is the DirectX SDK?</a>" and "<a href="http://blogs.msdn.com/b/chuckw/archive/2013/07/01/where-is-the-directx-sdk-2013-edition.aspx">Where is the DirectX SDK (2013 Edition)?</a>"</strong></p>
<p>&nbsp;</p>
<p>The next release of the DirectX SDK is scheduled to ship to developers in early June 2010. This release will be the first update to the Windows Graphics components since the August 2009 release and will also introduce support for Visual Studio 2010.</p>
<p><strong>Visual Studio 2010 Support<br /><br /></strong>The June 2010 DirectX SDK includes support for Visual Studio 2010. The DirectX SDK will continue to support Visual Studio 2008 as well. However, Visual Studio 2005 will no longer be supported.<br /><br /><strong>PIX: Object Naming Support</strong><br /><br />The June 2010 version of PIX supports naming for most resource objects in Direct3D (D3D). Direct3D enables developers to attach arbitrary data to objects in D3D code using the <strong>SetPrivateData</strong> API for application-specific usage. PIX will now display specific string data for objects in the Object Table and other user interface elements where a human-readable object name will provide a much more effective experience for the user.<br /><br /><strong>PIX: Usability Improvements</strong><br /><br />The June 2010 version of PIX includes improvements to the PIX user interface:</p>
<ul>
<li>The Object Table shows the size and shader model for each shader.</li>
<li>In the Shader Debugger, there is a new toolbar button that enables the display of all constant registers/variables immediately, rather than the first time they are read.</li>
<li>In the Shader Debugger, it is possible to copy register and variable data to the clipboard.</li>
<li>The Summary pane has a new "Direct3D Information" section, that shows details about what Direct3D capabilities are present on the computer.</li>
</ul>
<p><strong>XNAMath C++ SIMD Math Library</strong><br /><br />The June 2010 release updates XNAMath to version 2.03, which includes the following changes:<br /><br /></p>
<ul>
<li>Addition of <strong>XMVectorDivide()</strong>to optimize SSE2 vector division operations</li>
<li>Unified handling of floating-point specials between the Windows SSE2 and no-intrinsics implementations</li>
<li>Use of Visual Studio style SAL annotations</li>
<li>Modifications to the C++ declarations for XMFLOAT2A/3A/4A/4X3A/4X4A to better support these types in C++ templates</li>
</ul>
<p><strong>Version-less Naming of Cross-Runtime Data Types</strong><br /><br />The June 2010 DirectX SDK removes versioning from several Direct3D data types that cross runtime versions. This change makes legacy data-type names equivalent to the new version-less data-type names. Therefore, you can use either legacy or version-less names. However, your code will be cleaner and easier to maintain if you use the version-less names.<br /><br /><strong>New D3DCreateBlob Function</strong><br /><br />The June 2010 DirectX SDK includes a D3dcompiler_43.dll that exports the new <strong>D3DCreateBlob</strong> function. Therefore, you are no longer required to use D3d10.dll to create and use an arbitrary length data object.<br /><br /><strong>New ID3D11ShaderReflection Method</strong><br /><br />The June 2010 DirectX SDK adds the following new method to the <strong>ID3D11ShaderReflection</strong> interface:<br /><br /></p>
<ul>
<li><strong>GetThreadGroupSize</strong></li>
</ul>
<p><strong>New HLSL Language fixes and features</strong><br /><br />HLSL has been updated with the following fixes and features:<br /><br /></p>
<ul>
<li>The <strong>frexp</strong>intrinsic function has been updated to return a mantissa in the range of [0.5,1.0).</li>
<li>New intrinsic functions have been added for better debugging support.
<ul>
<li><strong>printf</strong>-- submits custom shader messages to the information queue.</li>
<li><strong>errorf</strong>-- submits custom shader error messages to the information queue.</li>
<li><strong>abort</strong> -- submits custom shader error messages to the information queue and terminates the current <strong>draw</strong> or <strong>dispatch</strong> call being executed.</li>
</ul>
</li>
<li>Left-Hand-Side typecasting is now illegal and will cause a compile error.
<ul>
<li>Expressions such as "(int)myFloat = myInt;" are no longer valid. Use "myFloat = (float)myInt;" type syntax instead.</li>
</ul>
</li>
</ul>
<p><strong>New HLSL Compiler fixes and features</strong><br /><br />The HLSL Effects compiler (fxc.exe) has been updated with the following fixes and features:</p>
<ul>
<li>No-optimization (/Od) compiles will produce less-optimized code than before in order to provide improved debugging.</li>
<li>No-optimization (/Od) now implies (/Gfp).</li>
<li>New compression (/compress) and decompression (/decompress) options have been added to enable the bundling and unbundling of shader files.</li>
<li>A new numbering instructions (/Ni) flag has been added to turn on numbering of instructions in shader disassembly.</li>
<li>Fxc.exe has a new @command.option.file feature for specifying command options in a file. This enables the /compress and /decompress options to be used on many files at once.</li>
</ul>
<p><strong>Documentation Enhancements</strong><br /><br />The June 2010 DirectX SDK includes the following documentation enhancements:</p>
<ul>
<li>Added links to descriptions of data types for parameters and return values to help developers locate related types.</li>
<li>Added additional header and lib information to reference pages for APIs implemented in DirectX samples.</li>
</ul>
