---
layout: post
title: DirectX SDK Samples Catalog
date: 2013-09-20 02:00
author: Chuck Walbourn
comments: true
categories: [dxsdk]
---
Microsoft has moved away from providing samples in SDKs for a number of reasons, but primarily to reduce the size of the standalone downloads and to minimize the size of the SDKs when included in other products (such as the Windows 8.x SDK being included with VS 2012 and VS 2013). The <a href="http://code.msdn.microsoft.com/">MSDN Code Gallery</a> provides an online repository for samples, including both official Microsoft samples as well as community contributions. Here's a list of the samples from the legacy DirectX SDK (June 2010) and their locations online if available.
<!--more-->

> <strong>Update: </strong>As of the Windows 10 SDK, official Windows samples are hosted on GitHub: <a href="https://github.com/Microsoft/Windows-universal-samples">Windows-universal-samples</a>, <a href="https://github.com/Microsoft/Windows-classic-samples">Windows-classic-samples</a>, <a href="https://github.com/Microsoft/Windows-driver-samples">Windows-driver-samples</a>.

> Most of these republished legacy DirectX SDK samples can be found on <a href="https://github.com/walbourn/directx-sdk-samples">GitHub</a> as well. DirectX 12 samples have their own [repo](https://github.com/Microsoft/DirectX-Graphics-Samples/), and I also maintain [this one](https://github.com/Microsoft/Xbox-ATG-Samples/) which hosts samples on DirectX and game development.

<em>The majority of these samples are Windows desktop applications. Where applicable, the table also notes similar samples for Windows Store apps on Windows 8.x.</em>

<table border="1">
<tbody>
<tr>
<td>
<p><strong>Direct3D 11</strong></p>
<p>Tutorials</p>
</td>
<td>
<p>Tutorial01 - 07<br /> <a href="http://code.msdn.microsoft.com/Direct3D-Tutorial-Win32-829979ef">Direct3D Tutorial Win32 Sample</a></p>
<p>Windows Store apps version:<br /> <a href="http://code.msdn.microsoft.com/windowsapps/Direct3D-Tutorial-Sample-08667fb0">Direct3D tutorial sample</a></p>
<p>Tutorial08-10<br /> <a href="http://code.msdn.microsoft.com/DXUT-Tutorial-Win32-Sample-fe15e440">DXUT Tutorial Win32 Sample</a></p>
<p>Tutorial11-14<br /> <a href="http://code.msdn.microsoft.com/Effects-Tutorial-Win32-b03b8501">Effects Tutorial Win32 Sample</a></p>
</td>
</tr>
<tr>
<td>AdaptiveTessellationCS40<br /> FluidCS11<br /> HDRToneMappingCS11<br /> NBodyGravityCS11<br /> OIT11</td>
<td>
<p><a href="http://code.msdn.microsoft.com/DirectCompute-Graphics-425de5a8">DirectCompute Graphics Win32 Samples</a></p>
<p>Windows Store app samples:<br /><a href="http://code.msdn.microsoft.com/Direct3D-HLSL-fractal-e3fb86d9">Direct3D HLSL fractal generator sample</a></p>
</td>
</tr>
<tr>
<td>BasicCompute11<br /> ComputeShaderSort11</td>
<td><a href="http://code.msdn.microsoft.com/DirectCompute-Basic-Win32-7d5a7408">DirectCompute Basic Win32 Samples</a></td>
</tr>
<tr>
<td>BasicHLSL11<br /> EmptyProject11<br /> SimpleSample11</td>
<td>
<p><a href="http://code.msdn.microsoft.com/Basic-DXUT-Win32-Samples-e59c0682">Basic DXUT Win32 Samples</a></p>
<p><a href="http://code.msdn.microsoft.com/DXUTDirectXTK-Simple-Win32-9cf797e9">DXUT+DirectXTK Simple Win32 Sample</a></p>
</td>
</tr>
<tr>
<td>BasicHLSL10<br /> DynamicShaderLinkageFX11<br /> FixedFuncEMU<br />Instancing10</td>
<td>
<p><a href="http://code.msdn.microsoft.com/Effects-11-Win32-Samples-cce82a4d">Effects 11 Win32 Samples</a></p>
<p>These samples make use of the <a href="http://go.microsoft.com/fwlink/p/?LinkId=271568">Effects 11 (FX11) library</a>.</p>
</td>
</tr>
<tr>
<td>BC6HBC7EncoderDecoder11</td>
<td>
<p><a href="http://go.microsoft.com/fwlink/?LinkId=254494">BC6H/BC7 DirectCompute Encoder Tool</a> (Win32)</p>
<p>Note this functionality is also present in the latest <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a>.</p>
</td>
</tr>
<tr>
<td>CascadedShadowMaps11<br /> VarianceShadows11</td>
<td>
<p><a href="http://code.msdn.microsoft.com/Direct3D-Shadow-Win32-2d72a4f2">Direct3D Shadow Win32 Samples</a></p>
<p>Windows Store app samples:<br /> <a href="http://code.msdn.microsoft.com/Shadow-mapping-sample-3fbc3423">Shadow mapping sample</a></p>
</td>
</tr>
<tr>
<td>DDSWithoutD3DX<br /> DDSWithoutD3DX11</td>
<td>
<p>An updated version of this sample is posted <a href="https://walbourn.github.io/ddswithoutd3dx-sample-update/">here</a>.</p>
<p>The DDSTextureLoader for Direct3D 11 from this sample is available in both <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK</a> and <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a>.</p>
</td>
</tr>
<tr>
<td>DynamicShaderLinkage11</td>
<td>
<p><a href="http://code.msdn.microsoft.com/Dynamic-Shader-Linkage-504eda2d">Dynamic Shader Linkage Win32 Sample</a></p>
</td>
</tr>
<tr>
<td>MultithreadedRendering11</td>
<td>
<p><a href="http://code.msdn.microsoft.com/Direct3D-Multithreaded-d02193c0">Direct3D Multithreaded Rendering Win32 Sample</a></p>
</td>
</tr>
<tr>
<td>SimpleBezier11<br /> SubD11</td>
<td>
<p><a href="http://code.msdn.microsoft.com/Direct3D-Tessellation-70afba2c">Direct3D Tessellation Win32 Samples</a></p>
</td>
</tr>
<tr>
<td>
<p>UVAtlas</p>
</td>
<td>
<p><a href="https://github.com/Microsoft/UVAtlas">UVAtlas</a></p>
</td>
</tr>
<tr>
<td>
<p><strong>Misc</strong></p>
<p>Collision</p>
</td>
<td>
<p><a href="http://code.msdn.microsoft.com/DirectXMath-Win32-Sample-f365b9e5">DirectXMath Win32 Sample</a></p>
</td>
</tr>
<tr>
<td>
<p>ContentExporter</p>
</td>
<td>
<p><a href="http://go.microsoft.com/fwlink/?LinkId=226208">Samples Content Exporter Update</a></p>
</td>
</tr>
<tr>
<td>CoreDetection</td>
<td>
<p><a href="http://code.msdn.microsoft.com/Core-Detection-Sample-7afd28f0">Core Detection Sample</a> (Win32)</p>
</td>
</tr>
<tr>
<td>D3D11InstallHelper</td>
<td>
<p><a href="http://code.msdn.microsoft.com/Direct3D-11-Install-Helper-3044575e">Direct3D 11 Install Helper</a> (Win32)</p>
</td>
</tr>
<tr>
<td>FirewallInstallHelper</td>
<td>
<p><a href="http://code.msdn.microsoft.com/Windows-Firewall-Install-c87391b9">Windows Firewall Install Helper</a> (Win32)</p>
</td>
</tr>
<tr>
<td>GameuxInstallHelper</td>
<td>
<p><a href="http://code.msdn.microsoft.com/GameuxInstallHelper-6a9335ca">Gameux Install Helper</a> (Win32)</p>
</td>
</tr>
<tr>
<td>VideoMemory</td>
<td>
<p><a href="http://code.msdn.microsoft.com/DirectX-Video-Memory-ee7d8319">DirectX Video Memory</a> (Win32)</p>
</td>
</tr>
<tr>
<td>
<p><strong>XInput</strong></p>
SimpleController<br /> RumbleController</td>
<td>
<p><a href="http://code.msdn.microsoft.com/XInput-Win32-Samples-cc25ce24">XInput Samples</a> (Win32)</p>
<p>XInput 1.4 is only supported on Windows 8.x. XInput 1.3 is only available in the DirectX SDK.</p>
<p>See <a href="https://walbourn.github.io/xinput-and-windows-8/">XINPUT and Windows 8</a> for more information.</p>
<p>Windows Store sample:<br /><a href="http://code.msdn.microsoft.com/windowsapps/Simple-XInput-Controller-77c4b8e5">Game controller sample</a></p>
</td>
</tr>
<tr>
<td>
<p><strong>XAudio2</strong></p>
XAudio2BasicSound<br /> XAudio2BasicStream<br /> XAudio2Sound3D<br /> XAudio2CustomAPO</td>
<td>
<p><a href="http://code.msdn.microsoft.com/XAudio2-Win32-Samples-024b3933">XAudio2 Samples</a> (Win32)</p>
<p>XAudio 2.8 is only supported on Windows 8.x. XAudio 2.7 is only available in the DirectX SDK.</p>
<p>See <a href="https://walbourn.github.io/xaudio2-and-windows-8/">XAudio2 and Windows 8</a> for more information.</p>
<p>Windows Store app samples:<br /><a href="http://code.msdn.microsoft.com/windowsapps/Basic-Audio-Sample-9a5bb0b7">Audio file playback sample</a><br /><a href="http://code.msdn.microsoft.com/windowsapps/XAudio2-Stream-Effect-3f95c8f2">Audio stream effect sample</a></p>
<p><em><a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK for Audio</a> is also a sample of XAudio2 usage, and is demonstrated in the <a href="https://github.com/walbourn/directxtk-samples">DirectX TK Simple Samples</a>.</em></p>
</td>
</tr>
<tr>
<td>
<p><strong>DirectInput</strong></p>
<p>Customformat<br /> FFConst<br /> Joystick</p>
</td>
<td>
<p><a href="http://code.msdn.microsoft.com/DirectInput-Samples-8ac6f5e3">DirectInput Samples</a> (Win32)</p>
<p><em>Keyboard and Mouse samples are not included as use of DirectInput for these scenarios is not recommended.</em></p>
</td>
</tr>
</tbody>
</table>
<h1>Windows 7.1 SDK Samples</h1>
<table border="1">
<tbody>
<tr>
<td><strong>DirectShow</strong></td>
<td>
<p>A list of Windows 7.x SDK DirectShow samples is available on <a href="https://docs.microsoft.com/en-us/windows/desktop/DirectShow/directshow-samples">Microft Docs</a>.</p>
<p>Note: You can find them on [GitHub](https://github.com/Microsoft/Windows-classic-samples/tree/master/Samples/Win7Samples/multimedia/directshow)</p>
</td>
</tr>
<tr>
<td><strong>Windows Imaging Component</strong>
<p>``multimedia\wic\progressivedecoding``<br />``multimedia\wic\wicanimatedgif``<br />``multimedia\wic\wicviewerd2d``</p>
</td>
<td>
<p><a href="https://code.msdn.microsoft.com/Windows-Imaging-Component-3af3cd49">WIC Progressive Decode Win32 Sample</a><br /><a href="https://code.msdn.microsoft.com/Windows-Imaging-Component-65abbc6a">WIC Animated GIF Win32 Sample</a><br /><a href="https://code.msdn.microsoft.com/Windows-Imaging-Component-c5191dfc">WIC and Direct2D Image Viewer Win32 Sample</a></p>
<p>Note: You can find them on [GitHub](https://github.com/Microsoft/Windows-classic-samples/tree/master/Samples/Win7Samples/multimedia/wic)</p>
</td>
</tr>
</tbody>
</table>

> The Windows 7.1A SDK is integrated with VS 2012 or later as part of the ``v1xx_xp`` Platform Toolset, but does not include the samples. The easiest place to get these legacy samples now is on [GitHub](https://github.com/Microsoft/Windows-classic-samples/tree/master/Samples/Win7Samples)

<h1>Vendor Samples</h1>

<table border="1">
<tbody>
<tr>
<td>DepthOfField10.1<br /> HDAO10.1<br /> TransparencyAA10.1<br /> <br /> ContactHardeningShadows11<br /> DecalTessellation11<br /> DetailTessellation11<br /> PNTriangles11</td>
<td>
<p><a href="http://developer.amd.com/tools-and-sdks/graphics-development/amd-radeon-sdk/">AMD Radeon SDK</a> (see the <a href="http://developer.amd.com/tools-and-sdks/graphics-development/amd-radeon-sdk/archive/">archive</a> page)</p>
</td>
</tr>
</tbody>
</table>
<h1>Retired Samples</h1>
<table border="1">
<tbody>
<tr>
<td>Direct3D9</td>
<td>
<p>The Direct3D 9 samples require D3DX9, so these remain available only in the DirectX SDK.</p>
</td>
</tr>
<tr>
<td>DirectDraw</td>
<td>
<p>The DirectX SDK 8.1 was the last to contain the DirectDraw samples.</p>
</td>
</tr>
<tr>
<td>DirectMusic<br /> DirectPlay</td>
<td>
<p>DirectX 9.0b (Summer 2003) was the last release of the DirectMusic or DirectPlay samples.</p>
</td>
</tr>
<tr>
<td>DirectSound</td>
<td>
<p>The DirectX SDK (November 2007) release was the last time the DirectSound samples were shipped.</p>
</td>
</tr>
<tr>
<td>Managed DirectX 1.1</td>
<td>
<p>The DirectX SDK (August 2006) release was the last time the C# samples for <a href="https://walbourn.github.io/directx-and-net/">legacy Managed DirectX 1.1</a> were shipped</p>
</td>
</tr>
<tr>
<td>XACT</td>
<td>
<p>The DirectX SDK (June 2010) contains the last release of XACT and related samples.</p>
</td>
</tr>
</tbody>
</table>

<strong>Related:</strong> <a href="https://walbourn.github.io/dxut-for-win32-desktop-update/">DXUT for Win32 Desktop Update</a>, <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a>, <a href="https://walbourn.github.io/directx-sdk-tools-catalog/">DirectX SDK Tools Catalog</a>
