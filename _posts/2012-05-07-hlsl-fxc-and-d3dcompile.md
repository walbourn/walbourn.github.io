---
layout: post
title: HLSL, FXC, and D3DCompile
date: 2012-05-07 12:42
author: walbourn
comments: true
categories: [hlsl, Uncategorized, visualc, windowssdk]
---
With the retirement of D3DX (See “<a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">Where is the DirectX SDK?</a>”, "<a href="http://blogs.msdn.com/b/chuckw/archive/2013/07/01/where-is-the-directx-sdk-2013-edition.aspx">Where is the DirectX SDK (2013 Edition)?</a>", and "<a href="http://blogs.msdn.com/b/chuckw/archive/2015/08/05/where-is-the-directx-sdk-2015-edition.aspx">Where is the DirectX SDK (2015 Edition)?</a>"), there is some confusion about how applications access the High-Level Shader Language (<a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb509561.aspx">HLSL</a>) compiler. As mentioned in an earlier post (See “<a href="http://blogs.msdn.com/b/chuckw/archive/2010/04/22/what-s-up-with-d3dcompiler-xx-dll.aspx">What’s up with D3DCompiler_xx.DLL?</a>”), the HLSL compilation functions, shader reflection, and some support functions for the compiler were pulled out of D3DX as of the <em>DirectX SDK (August 2009)</em> release. While many developers continue to use the D3DX functions to compile HLSL and Effects, they are just pass-through functions to the D3DCompile API which can be used directly instead. The latest version of the D3DCompile API includes some new functions as well such as <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh446872.aspx">D3DCompileFromFile</a> and <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh446869.aspx">D3DCompile2</a>.

<strong>Windows 8.1 / Windows 10:</strong> The latest version of the D3DCompiler (#47) is now <a href="http://msdn.microsoft.com/en-us/library/windows/apps/bg182880.aspx">included</a> with the Windows 8.1 / Windows 10 OS and is available for runtime use by <a href="http://code.msdn.microsoft.com/HLSL-shader-compiler-sample-e5a1d002">Windows Store apps</a> / Universal Windows Platform (UWP) apps. There is a new <a href="http://msdn.microsoft.com/en-us/library/windows/apps/bg182880.aspx">HLSL linker</a> option as well that provides some of this flexibility to compose shaders at runtime without recompiling from the HLSL source.
<h1>Visual Studio and HLSL</h1>
With <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/31/visual-studio-2012-release-candidate.aspx">Visual Studio 2012</a> or later, HLSL and the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb232919.aspx">FXC.EXE</a> tool is now integrated into build environment and the Windows 8.x SDK / Windows 10 SDK. If you add <code>.hlsl</code> and <code>.fx</code> extension files to your project, there are properties for controlling how the HLSL compiler is invoked as part of your build including target profile, entry point name, etc. The resulting compiled shader uses the default extension of <code>.cso</code> (Compiled Shader Object). The texture editor supports HLSL colorization, and the <a href="http://blogs.msdn.com/b/vcblog/archive/2011/11/08/10235150.aspx">Visual Studio Graphics Diagnostics</a> feature provides support for debugging HLSL as well.

There is one quirk of having HLSL integrated into MSBuild that requires some restructuring of existing HLSL source files. The MSBuild system assumes that each source files is built exactly once. If you need to build the same HLSL source multiple times, you'll need individual <code>.hlsl</code> or <code>.fx</code> files for each instance you want to build added to your project. Judicious use of the <code>#include</code> directive should make it fairly easy to share the same source where needed, but this is a bit of a move away from the <code>.fx</code> file model where all variations of shaders were kept in a single file. You of course can still make use of some custom build script and integrate a custom build step for more sophisticated generation of shaders, but this "one .hlsl file per shader combination" model is going to be seen in a lot of samples.

<strong>Note:</strong> This automatic integration only works for C++ projects, not C# projects.

<strong>VS 2013:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2013/10/18/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available.aspx">Visual Studio 2013</a> comes with Windows 8.1 SDK which includes the <code>D3DCompiler_47.DLL</code>. It works essentially the same as it did with VS 2012.

<strong>VS 2015: </strong><a href="https://blogs.msdn.microsoft.com/chuckw/2015/07/24/visual-studio-2015-rtm/">Visual Studio 2015</a> comes with the Windows 8.1 SDK (Spring 2015) and optionally the Windows 10 SDK which includes an updated <code>D3DCompiler_47.DLL</code>.
<h1>Build-time vs. Runtime Compilation</h1>
As we have recommended for many years, developers should compile their HLSL shaders at build-time rather than rely on runtime compilation. There is little benefit to doing runtime compilation for most scenarios, as vendor-specific micro-optimizations are done by the driver at runtime when converting the HLSL binary shader blobs to vendor-specific instructions as part of the shader object creation step. Developers don’t generally want the HLSL compiler results to change ‘in the field’ over time, so it makes more sense to do compilation at build-time. That is the primary usage scenario expected with the Windows 8.0 SDK and Visual Studio 11, and is the only supported scenario for Windows Store apps (a.k.a Metro style apps) in Windows 8.0. FXC and the MSBuild rules above are well suited to this usage.

For development purposes, it is often very convenient to use runtime compilation. Such applications typically keep a ‘shader cache’ file that is generated during execution, and a ‘final’ version of the shader cache is then shipped with the title. This scenario is supported by the D3DCompile API hosted in the <code>D3DComplier_*.DLL</code>. This is fully supported for Win32 desktop applications, and can even be used for Windows Store apps during development although not in deployment with Windows 8.0. In this case, the <code>D3DCompiler_*.DLL</code> from the Windows 8.0 SDK should be included side-by-side with the application itself (i.e. application local deployment). The <code>d3dcomplier.h</code> header and <code>d3dcompiler.lib</code> are part of the Windows 8.0 SDK include and lib paths, and the <code>D3DCompiler_*.DLL</code> itself is located in <code>"%WindowsSdkDir%\redist\d3d".</code> If your application makes use of the D3DCompile API, you will want to add a Custom Build Step for the project to make sure the right DLL is copied as part of your build.
<p style="padding-left: 30px"><em>Platform: Win32 (All Configurations)</em>
<em>Command Line:</em> copy “$(WindowsSdkDir)redist\d3d\x86\D3DCompile*.DLL” “$(TargetDir)”
<em>Outputs:</em>$(TargetDir)D3DCompiler_47.DLL</p>
<p style="padding-left: 30px"><em>Platform: x64 (All Configurations)</em>
<em>Command Line:</em> copy “$(WindowsSdkDir)redist\d3d\x64\D3DCompile*.DLL” “$(TargetDir)”
<em>Outputs:</em>$(TargetDir)D3DCompiler_47.DLL</p>
<p style="padding-left: 30px"><em>Platform: ARM (All Configurations)</em>
<em>Command Line:</em> copy “$(WindowsSdkDir)redist\d3d\arm\D3DCompile*.DLL” “$(TargetDir)”
<em>Outputs:</em>$(TargetDir)D3DCompiler_47.DLL</p>
<em>Note this assumes you are using the Windows 8.1 SDK or Windows 10 SDK</em>

<strong>Windows 8.1 / Windows 10:</strong> For Windows Store apps and Universal Windows Platform (UWP) apps, there's no need to copy the <code>D3DCompiler_*.DLL</code> since there is a copy in the OS available for this use. The <code>D3DCompiler_*.DLL</code> itself won't pass WACK, so you shouldn't use application local deployment.
<h1>Redistribution</h1>
The legacy DirectX SDK versions of D3DCompile (#33 - #43) were deployed using the <a href="http://blogs.msdn.com/b/chuckw/archive/2010/09/08/not-so-direct-setup.aspx">DirectSetup</a> technology and installed to the <code>%WINDIR%\System32</code> (and <code>%WINDIR%\SysWow64</code>) folders using the redistribution package (which requires administrator rights at installation time). With the Windows 8.x SDK / Windows 10 SDK, the D3DCompile DLL is never installed to the <code>%WINDIR%</code> folders. Instead, you should copy it into your applications folder and deploy it 'application local' with your Win32 desktop application.

<strong>Windows 8.1 / Windows 10:</strong> D3DCompile #47 is included with the Windows 8.1 / Windows 10 OS so there is no need to redistribute it for Windows Store apps / Universal Windows Platform (UWP) apps. There is also a copy in the Windows 8.1 SDK (<code>C:\Program Files (x86)\Windows Kits\8.1\Redist\D3D</code>) / Windows 10 SDK (<code>C:\Program Files (x86)\Windows Kits\10\Redist\D3D</code>) you can redistribute application local for Win32 classic desktop applications the same way as you could D3DCompiler #46 from the Windows 8.0 SDK (<code>C:\Program Files (x86)\Windows Kits\8.0\Redist\D3D</code>).
<h1>Effects</h1>
The <a href="http://go.microsoft.com/fwlink/p/?LinkId=271568">Effects 11</a> (aka FX11) shared source library requires the "Effect" Shader Type and the "Shader Model 5" profile. It also requires the <code>D3DCompiler_*.DLL</code> at runtime for the shader reflection APIs, which makes it unsuitable for Windows Store apps.

<em>Note:</em> The "fx" profiles (<code>fx_2_0</code>, <code>fx_4_0</code>, <code>fx_4_1</code>, and <code>fx_5_0</code>) are deprecated and may be removed from a future update of the HLSL compiler.
<h1>Platform Support</h1>
The shader binaries built by the current FXC.EXE and D3DCompile API using the Shader Model 2.0 and Shader Model 3.0 profiles will work on all Direct3D 9.0c compatible platforms including Windows XP. The actual <code>D3DCompiler_*.DLL</code> in the Windows 8.x SDK / Windows 10 SDK itself only supports Windows Vista, Windows 7, Windows 8.x, and Windows 10. Windows XP development requires some additional work as detailed <a href="https://blogs.msdn.microsoft.com/chuckw/2012/11/26/visual-studio-2012-update-1/">here</a>.

For Shader Model 5 shaders, some HLSL language features require the DirectX 11.1 runtime. This uses the existing mechanism that indicates a shader requires the hardware support double-precision shaders for DirectX 11.0. This includes use of Feature Level 11.1 features (UAVs at every stage, 64 UAV slots), DirectX 11.1 runtime features (minimum-precision data-types), and new DirectX 11.1 optional hardware features (extended double-precision instructions, SAD4). A shader blob that indicates one of these requirements will fail to bind at runtime if the system doesn't support them. This information is included in the HLSL disassembly output, and all require some explicit feature usage in the HLSL source.
<h1>Porting Notes</h1>
Here's a handy table of equivalents for replacing legacy D3DX HLSL compiler related functions (see <a href="http://blogs.msdn.com/b/chuckw/archive/2013/08/21/living-without-d3dx.aspx">Living without D3DX</a> for a complete listing).
<table border="1">
<tbody>
<tr>
<td><code>D3DXCompileShaderFromFile
D3DX10CompileFromFile
D3DX11CompileFromFile</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh446872.aspx">D3DCompileFromFile</a></td>
</tr>
<tr>
<td><code>D3DXCompileShader
D3D10CompileShader
D3DX10CompileFromMemory
D3DX11CompileFromMemory</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/dd607324.aspx">D3DCompile</a></td>
</tr>
<tr>
<td><code>D3DXCompileShaderFromResource
D3DX10CompileFromResource
D3DX11CompileFromResource</code></td>
<td>No direct equivalent. Can use resource APIs and then <code>D3DCompile</code> above.</td>
</tr>
<tr>
<td><code>D3DXPreprocessShader
D3DXPreprocessShaderFromFile
D3DXPreprocessShaderFromResource
D3D10PreprocessShader
D3DX10PreprocessShaderFromFile
D3DX10PreprocessShaderFromMemory
D3DX10PreprocessShaderFromResource
D3DX11PreprocessShaderFromFile
D3DX11PreprocessShaderFromMemory
D3DX11PreprocessShaderFromResource</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/dd607332.aspx">D3DPreprocess</a></td>
</tr>
<tr>
<td><code>D3DXDisassembleShader
D3D10DisassembleShader
D3DX10DisassembleShader</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/dd607326.aspx">D3DDisassemble</a></td>
</tr>
<tr>
<td><code>D3D10ReflectShader
D3DX10ReflectShader</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/dd607334.aspx">D3DReflect</a>
<a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff728670.aspx">D3D11Reflect</a></td>
</tr>
<tr>
<td><code>ID3DXBuffer
ID3D10Blob</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff728743.aspx">ID3DBlob</a></td>
</tr>
<tr>
<td><code>D3DXCreateBuffer
D3D10CreateBlob</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff728672.aspx">D3DCreateBlob</a></td>
</tr>
<tr>
<td><code>D3D10GetInputSignatureBlob
D3D10GetOutputSignatureBlob
D3D10GetInputAndOutputSignatureBlob
D3D10GetShaderDebugInfo</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff728674.aspx">D3DGetBlobPart</a></td>
</tr>
</tbody>
</table>
<h1>Version History</h1>
<ul>
 	<li>D3DCompiler_47 - Windows 10 (inbox), Windows 10 SDK; Windows 8.1 (inbox), Windows 8.1 SDK, Visual Studio 2013/2015</li>
 	<li>D3DCompiler_46 - Windows 8.0 SDK, Visual Studio 2012</li>
 	<li>D3DCompiler_43 - DirectX SDK (June 2010)</li>
 	<li>D3DCompiler_42 - DirectX SDK (February 2010)</li>
 	<li>D3DCompiler_41 - DirectX SDK (March 2009)</li>
 	<li>D3DCompiler_40 - DirectX SDK (November 2008)</li>
 	<li>D3DCompiler_39 - DirectX SDK (August 2008)</li>
 	<li>D3DCompiler_38 - DirectX SDK (June 2008)</li>
 	<li>D3DCompiler_37 - DirectX SDK (March 2008)</li>
 	<li>D3DCompiler_36 - DirectX SDK (November 2007)</li>
 	<li>D3DCompiler_35 - DirectX SDK (August 2007)</li>
 	<li>D3DCompiler_34 - DirectX SDK (June 2007)</li>
 	<li>D3DCompiler_33 - DirectX SDK (Aprli 2007)</li>
</ul>
<h1>Presentations</h1>
<a href="http://www.microsoft.com/en-us/download/details.aspx?displaylang=en&amp;id=16975">High Level Shader Language (HLSL) Update—Introducing Version 5.0</a> (Gamefest 2008)

<a href="http://blogs.msdn.com/b/chuckw/archive/2011/03/08/hlsl-compiler-support-for-symbolic-derivatives.aspx">Symbolic Differentiation in GPU Shaders
</a>

<strong>Related:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2011/07/11/getting-started-with-direct3d-11.aspx">Getting Started with Direct3D 11</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2010/04/22/what-s-up-with-d3dcompiler-xx-dll.aspx">What's up with D3DCompiler_xx.DLL</a>
