---
layout: msdnpost
title: Effects for Direct3D 11 Update
date: 2012-10-23 16:14
author: Chuck Walbourn
comments: true
categories: [codeplex, direct3d, dxsdk]
---
The <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/d3d11-graphics-programming-guide-effects">Effects 11</a> library (FX11) was made available as shared-source in the DirectX SDK. Previous versions of the Effects library were part of D3DX (FX9) or built into the OS (FX10). With the DirectX SDK now legacy (see <a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a>, <a href="https://walbourn.github.io/where-is-the-directx-sdk-2013-edition/">Where is the DirectX SDK (2013 Edition)?</a>, and <a href="https://walbourn.github.io/where-is-the-directx-sdk-2015-edition/">Where is the DirectX SDK (2015 Edition)?</a>), there are still a number of people looking for the latest version since it is not included in the Windows 8.0 SDK. This post provides an updated version of the Effects 11 (FX11) library. The primary purpose of this release is to remove the dependencies on the legacy DirectX SDK for the D3DX11 headers, but it also includes some code tidying and a few customer requests.
<!--more-->

> If you still need Visual Studio 2008 support, you should keep using the legacy DirectX SDK (June 2010) version.

<h1>Disclaimer</h1>

Effects 11 is primarily being provided as a porting aid for older code that make use of the Effects 10 (FX10) API or Effects 9 (FX9) API in the deprecated <code>D3DX9</code> library. See <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/d3d11-graphics-programming-guide-effects-differences">Microsoft Docs</a> for a list of differences compared to the Effects 10 (FX10) library.

<ul>
 	<li>The Effects 11 library is for use in <strong>Win32 desktop applications</strong>. FX11 requires the <a href="https://walbourn.github.io/hlsl-fxc-and-d3dcompile/">D3DCompiler API</a> be available at runtime to provide shader reflection functionality, and this API is not deployable for Windows Store apps on Windows 8 or Windows RT.</li>
 	<li>The <code>fx_5_0</code> profile support in the HLSL compiler is deprecated, and does not fully support DirectX 11.1 HLSL features such as minimum precision types.  It is supported in the Windows 8.0 SDK version of the HLSL compiler (<code>FXC.EXE</code>) and D3DCompile API (#46),<strong> but could be removed in a future update</strong>.</li>
 	<li>The Visual Studio 2012 graphics diagnostics feature has had some problems when trying to debug <code>fx_5_0</code> profile shaders. You may want to try the latest <a href="http://go.microsoft.com/fwlink/?LinkID=290979">VS 2012 Update</a>.</li>
</ul>

> The new ``DXC.EXE`` DXIL compiler does *not* support the ``fx`` profile or it's constructs. See [GitHub](https://github.com/Microsoft/DirectXShaderCompiler/)

<h1>Porting Notes</h1>

Here's a handy table of equivalents related to Effects (see <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a> for a complete listing):

<table border="1">
<tbody>
<tr>
<td><code>D3DXCreateEffect
D3DXCreateEffectEx
D3DXCreateEffectFromResource
D3DXCreateEffectFromResourceEx
D3D10CompileEffectFromMemory</code></td>
<td><code>D3DX11CompileEffectFromMemory</code></td>
</tr>
<tr>
<td><code>D3DXCreateEffectFromFile
D3DXCreateEffectFromFileEx</code></td>
<td><code>D3DX11CompileEffectFromFile</code></td>
</tr>
<tr>
<td><code>D3D10CreateEffectFromMemory</code></td>
<td><code>D3DX11CreateEffectFromMemory</code></td>
</tr>
<tr>
<td><code>D3DXCreateEffectPool
D3D10CreateEffectPoolFromMemory</code></td>
<td>Effects 11 does not support 'effect pools'
or <code>D3DCOMPILE_EFFECT_CHILD_EFFECT</code>. Effect <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/d3d11-effect-group-syntax">groups</a> provide a more efficient solution for common scenarios previously addressed with 'effect pools'</td>
</tr>
<tr>
<td><code>D3DXDisassembleEffect
D3D10DisassembleEffect</code></td>
<td><code>D3DDisassemble</code>
<code>D3DDisassemble10Effect</code> in D3DCompile</td>
</tr>
</tbody>
</table>

<h1>Version History</h1>

<h2>October 24, 2012 (11.03)</h2>
<ul>
 	<li>Removed the dependency on the D3DX11 headers, so FX11 no longer requires the legacy DirectX SDK to build. It does require the d3dcompiler.h header from either the Windows 8.0 SDK or from the legacy DirectX SDK</li>
 	<li>Removed references to D3D10 constants and interfaces</li>
 	<li>Deleted the d3dx11dbg.cpp and d3dx11dbg.h files</li>
 	<li>Deleted the D3DX11_EFFECT_PASS flags which were never implemented</li>
 	<li>General C++ code cleanups (nullptr, C++ style casting, stdint.h types, Safer CRT, etc.) which are compatible with Visual C++ 2010 and 2012</li>
 	<li>SAL2 annotation and /analyze cleanup</li>
 	<li>Added population of Direct3D debug names for object naming support in PIX and the SDK debug layer; added additional optional parameter to D3DX11CreateEffectFromMemory to provide a debug name</li>
 	<li>Added D3DX11CreateEffectFromFile, D3DX11CompileEffectFromMemory, and D3DX11CompileEffectFromFile</li>
</ul>

<h2>June 2010 (11.02)</h2>

<ul>
 	<li>The DirectX SDK (June 2010) included an update with some minor additional bug fixes. This also included the Effects 11-based sample DynamicShaderLinkageFX11. This is the last version to support Visual Studio 2008. The source code is located in ``Samples\C++\Effects11``.</li>
</ul>

<h2>February 2010 (11.01)</h2>

<ul>
 	<li>An update was shipped with the DirectX SDK (February 2010). This fixed a problem with the library which prevented it from working correctly on 9.x and 10.x feature levels. This is the last version to support Visual Studio 2005. The source code is located in ``Samples\C++\Effects11``.</li>
</ul>

<h2>August 2009 (11.00)</h2>

<ul>
 	<li>The initial release of Effects 11 (FX11) was in DirectX SDK (August 2009). The source code is located in ``Utilities\Source\Effects11``. This is essentially the Effects 10 (FX10) system ported to Direct3D 11.0 with support for effects pools removed and support for groups added.</li>
</ul>

<strong>Update:</strong> Effects 11 is now hosted on <a href="http://go.microsoft.com/fwlink/?LinkId=271568">CodePlex</a> and <a href="https://github.com/Microsoft/FX11">GitHub</a>. The latest version of the library, documentation, release history, and other information is now available there.

<strong>Samples:</strong> Effects 11 Win32 Samples on <a href="https://github.com/walbourn/directx-sdk-samples">GitHub</a>: Direct3D11TutorialsFX11, BasicHLSLFX11, DynamicShaderLinkageFX11, FixedFuncEmuFX11, and InstancingFX11.

<strong>Related:</strong> <a href="https://walbourn.github.io/directxtex-and-effects-11-update/">DirectXTex and Effects 11 Update</a>
