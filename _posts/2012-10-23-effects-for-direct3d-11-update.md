---
layout: msdnpost
title: Effects for Direct3D 11 Update
date: 2012-10-23 16:14
author: Chuck Walbourn
comments: true
categories: [codeplex, direct3d, dxsdk]
---
The <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/d3d11-graphics-programming-guide-effects">Effects 11</a> library (FX11) was made available as shared-source in the DirectX SDK. Previous versions of the Effects library were part of D3DX (FX9) or built into the OS (FX10). With the DirectX SDK now legacy (see <a href="https://aka.ms/dxsdk">Where is the DirectX SDK?</a>), there are still a number of people looking for the latest version since it is not included in the Windows 8.0 SDK. This post provides an updated version of the Effects 11 (FX11) library. The primary purpose of this release is to remove the dependencies on the legacy DirectX SDK for the D3DX11 headers, but it also includes some code tidying and a few customer requests.
<!--more-->

<span style="color:red">**The project on [GitHub](https://github.com/Microsoft/FX11) is marked as archive. It is still available for use for legacy projects, but use of it for new projects is not recommended.**</span>

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

See [GitHub](https://github.com/microsoft/FX11/blob/main/HISTORY.md) for the complete version history.

<strong>Update:</strong> Effects 11 is now hosted on <a href="http://go.microsoft.com/fwlink/?LinkId=271568">CodePlex</a> and <a href="https://github.com/Microsoft/FX11">GitHub</a>. The latest version of the library, documentation, release history, and other information is now available there.

<strong>Samples:</strong> Effects 11 Win32 Samples on <a href="https://github.com/walbourn/directx-sdk-samples">GitHub</a>: Direct3D11TutorialsFX11, BasicHLSLFX11, DynamicShaderLinkageFX11, FixedFuncEmuFX11, and InstancingFX11.

<strong>vcpkg</strong>: The vcpkg C++ Package Manager has an [effects11](https://github.com/microsoft/vcpkg/tree/master/ports/effects11) port available.

<strong>NuGet</strong>: This [NuGet](https://www.nuget.org/packages/fx11_desktop_2017) contains the last release of Effects.

<strong>Related:</strong> <a href="https://walbourn.github.io/directxtex-and-effects-11-update/">DirectXTex and Effects 11 Update</a>
