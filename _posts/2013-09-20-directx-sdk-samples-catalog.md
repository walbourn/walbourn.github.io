---
layout: msdnpost
title: DirectX SDK Samples Catalog
date: 2013-09-20 02:00
author: Chuck Walbourn
comments: true
categories: [dxsdk]
---
Microsoft has moved away from providing samples in SDKs for a number of reasons, but primarily to reduce the size of the standalone downloads and to minimize the size of the SDKs when included in other products (such as the Windows SDK being included with Visual Studio). <strike>The <a href="https://docs.microsoft.com/en-us/teamblog/msdn-code-gallery-retired">MSDN Code Gallery</a> provides an online repository for samples, including both official Microsoft samples as well as community contributions.</strike>. Here's a list of the samples from the legacy DirectX SDK (June 2010) and their locations online if available.
<!--more-->

> <strong>Update: </strong>As of the Windows 10 SDK, official Windows samples are hosted on GitHub: <a href="https://github.com/Microsoft/Windows-universal-samples">Windows-universal-samples</a>, <a href="https://github.com/Microsoft/Windows-classic-samples">Windows-classic-samples</a>, <a href="https://github.com/Microsoft/Windows-driver-samples">Windows-driver-samples</a>. You can also use this <a href="https://docs.microsoft.com/en-us/samples/browse/">website</a> to search Microsoft official samples.

> These republished legacy DirectX SDK samples are now found on GitHub <a href="https://github.com/walbourn/directx-sdk-samples">directx-sdk-samples</a> and <a href="https://github.com/walbourn/directx-sdk-legacy-samples">directx-sdk-legacy-samples</a> as <i>MSDN Code Gallery</i> has been retired. DirectX 12 samples have their own [repo](https://github.com/Microsoft/DirectX-Graphics-Samples/), and also [this one](https://github.com/Microsoft/Xbox-ATG-Samples/) which hosts samples on DirectX and game development.

<table border="1">
<tbody>
<tr>
<td>
<p><strong>Direct3D 11</strong></p>
<p>Tutorials</p>
</td>
<td>
<p>Tutorial01 - 07<br /> <a href="https://github.com/walbourn/directx-sdk-samples/tree/main/Direct3D11Tutorials">Direct3D Tutorial Win32 Sample</a></p>
<p>Tutorial08-10<br /> <a href="https://github.com/walbourn/directx-sdk-samples/tree/main/Direct3D11TutorialsDXUT">DXUT Tutorial Win32 Sample</a></p>
<p>Tutorial11-14<br /> <a href="https://github.com/walbourn/directx-sdk-samples/tree/main/Direct3D11TutorialsFX11">Effects Tutorial Win32 Sample</a></p>
</td>
</tr>
<tr>
<td>AdaptiveTessellationCS40<br /> FluidCS11<br /> HDRToneMappingCS11<br /> NBodyGravityCS11<br /> OIT11</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples">DirectCompute Graphics Win32 Samples</a></p>
</td>
</tr>
<tr>
<td>BasicCompute11<br /> ComputeShaderSort11</td>
<td><a href="https://github.com/walbourn/directx-sdk-samples">DirectCompute Basic Win32 Samples</a></td>
</tr>
<tr>
<td>BasicHLSL11<br /> EmptyProject11<br /> SimpleSample11</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples">Basic DXUT Win32 Samples</a></p>
</td>
</tr>
<tr>
<td>BasicHLSL10<br /> DynamicShaderLinkageFX11<br /> FixedFuncEMU<br />Instancing10</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples">Effects 11 Win32 Samples</a></p>
<p>These samples make use of the <a href="http://go.microsoft.com/fwlink/p/?LinkId=271568">Effects 11 (FX11) library</a>.</p>
</td>
</tr>
<tr>
<td>BC6HBC7EncoderDecoder11</td>
<td>
<p><a href="http://go.microsoft.com/fwlink/?LinkId=254494">BC6H/BC7 DirectCompute Encoder Tool</a> (Win32)</p>
<p>Note this functionality is also present in the <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a>.</p>
</td>
</tr>
<tr>
<td>CascadedShadowMaps11<br /> VarianceShadows11</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples/">Direct3D Shadow Win32 Samples</a></p>
</td>
</tr>
<tr>
<td>DDSWithoutD3DX<br /> DDSWithoutD3DX11</td>
<td>
<p>An updated version of this sample is posted <a href="https://walbourn.github.io/ddswithoutd3dx-sample-update/">here</a>.</p>
<p>The DDSTextureLoader is available in both <i>DirectX Tool Kit</i> (<a href="http://go.microsoft.com/fwlink/?LinkId=248929">DX11</a> / <a href="http://go.microsoft.com/fwlink/?LinkID=615561">DX12</a>) and <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a>. There are versions for Direct3D 12, Direct3D 11, and Direct3D 9.</p>
</td>
</tr>
<tr>
<td>DynamicShaderLinkage11 / DynamicShaderLinkageFX11</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples/">Dynamic Shader Linkage Win32 Sample</a></p>
</td>
</tr>
<tr>
<td>MultithreadedRendering11</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples/tree/main/MultithreadedRendering11">Direct3D Multithreaded Rendering Win32 Sample</a></p>
</td>
</tr>
<tr>
<td>SimpleBezier11<br /> SubD11</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples">Direct3D Tessellation Win32 Samples</a></p>
</td>
</tr>
<tr>
<td>
<p>UVAtlas</p>
</td>
<td>
<p><a href="http://go.microsoft.com/fwlink/?LinkID=512686">UVAtlas</a></p>
</td>
</tr>
<tr>
<td>
<p><strong>Misc</strong></p>
<p>Collision</p>
</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples/tree/main/Collision">DirectXMath Win32 Sample</a></p>
</td>
</tr>
<tr>
<td>
<p>ContentExporter</p>
</td>
<td>
<p><a href="https://aka.ms/dxsdkcontentexporter">Samples Content Exporter Update</a></p>
</td>
</tr>
<tr>
<td>CoreDetection</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples/tree/main/CoreDetection">Core Detection Sample</a> (Win32)</p>
</td>
</tr>
<tr>
<td>D3D11InstallHelper</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples/tree/main/InstallHelpers/D3D11InstallHelper">Direct3D 11 Install Helper</a> (Win32)</p>
</td>
</tr>
<tr>
<td>FirewallInstallHelper</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples/tree/main/InstallHelpers/FirewallInstallHelper">Windows Firewall Install Helper</a> (Win32)</p>
</td>
</tr>
<tr>
<td>GameuxInstallHelper</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples/tree/main/InstallHelpers/GameuxInstallHelper">Gameux Install Helper</a> (Win32)</p>
</td>
</tr>
<tr>
<td>VideoMemory</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples/tree/main/VideoMemory">DirectX Video Memory</a> (Win32)</p>
</td>
</tr>
<tr>
<td>
<p><strong>XInput</strong></p>
SimpleController<br /> RumbleController<br /><br />XInputGame</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples/tree/main/XInput">XInput Samples</a> (Win32)</p>
<p>XInputGame can be found <a href="https://github.com/walbourn/directx-sdk-legacy-samples/tree/main/XInput">here.</a></p>
<p>XInput 1.4 is supported on Windows 8.x and Windows 10. XInput 9.1.0 is in all versions of Windows since Windows Vista.</p>
<p>See <a href="https://walbourn.github.io/xinput-and-windows-8/">XINPUT and Windows 8</a> for more information.</p>
</td>
</tr>
<tr>
<td>
<p><strong>XAudio2</strong></p>
XAudio2BasicSound<br /> XAudio2BasicStream<br /> XAudio2Sound3D<br /> XAudio2CustomAPO</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples/tree/main/XAudio2">XAudio2 Samples</a> (Win32)</p>
<p>XAudio 2.8 is supported on Windows 8.x or Windows 10. Windows 10 includes XAudio 2.9 and is available through <a href="https://aka.ms/XAudio2Redist">XAudio2Redist</a> on Windows 7 SP1 or Windows 8.x as well.</p>
<p>See <a href="https://walbourn.github.io/xaudio2-and-windows-8/">XAudio2 and Windows 8</a> for more information.</p>
<p><em><a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK for Audio</a> is also a sample of XAudio2 usage, and is demonstrated in the <a href="https://github.com/walbourn/directxtk-samples">DirectX Tool Kit Simple Samples</a>.</em></p>
</td>
</tr>
<tr>
<td>
<p><strong>DirectInput</strong></p>
<p>Customformat<br /> FFConst<br /> Joystick</p>
</td>
<td>
<p><a href="https://github.com/walbourn/directx-sdk-samples/tree/main/DirectInput">DirectInput Samples</a> (Win32)</p>
<p><em>Keyboard and Mouse samples are not included as use of DirectInput for these scenarios is not recommended. See <a href="https://walbourn.github.io/directx-tool-kit-keyboard-and-mouse-support/">this blog post</a>.</em></p>
</td>
</tr>
<tr>
<td>
<p><strong>Direct3D 9</strong></p>
<p>AntiAlias<br />-<br />Text3D</p>
</td>
<td>
<p>The Direct3D 9 samples require D3DX9, and therefore make use of the Microsoft.DXSDK.D3DX NuGet package. They can be found in the <a href="https://github.com/walbourn/directx-sdk-legacy-samples/tree/main/Direct3D">directx-sdk-legacy-samples</a> repository.</p>
</td>
</tr>
<tr>
<td>
<p><strong>Direct3D 10</strong></p>
<p>10BitScanout10<br />-<br />TransparencyAA10.1</p>
</td>
<td>
<p>The Direct3D 10 samples require D3DX10, and therefore make use of the Microsoft.DXSDK.D3DX NuGet package. They can be found in the <a href="https://github.com/walbourn/directx-sdk-legacy-samples/tree/main/Direct3D10">directx-sdk-legacy-samples</a> repository.</p>
</td>
</tr>
<tr>
<td>
<p><strong>DirectSound</strong></p>
<p>AdjustSound<br />-<br />VoiceManagement</p>
</td>
<td>
<p>The DirectX SDK (November 2007) release was the last time the DirectSound samples were shipped. They can be found in the <a href="https://github.com/walbourn/directx-sdk-legacy-samples/tree/main/DirectSound">directx-sdk-legacy-samples</a> repository.</p>
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
<p>A list of Windows 7.x SDK DirectShow samples is available on <a href="https://docs.microsoft.com/en-us/windows/desktop/DirectShow/directshow-samples">Microsoft Docs</a>.</p>
<p>Note: You can find them on <a href="https://github.com/Microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/multimedia/directshow ">GitHub</a>.</p>
</td>
</tr>
<tr>
<td><strong>Windows Imaging Component</strong>
</td>
<td>
<p>WIC Progressive Decode Win32 Sample<br />WIC Animated GIF Win32 Sample<br />WIC and Direct2D Image Viewer Win32 Sample</p>
<p>You can find them on <a href="https://github.com/Microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples/multimedia/wic">GitHub</a>.</p>
</td>
</tr>
</tbody>
</table>

> The Windows 7.1A SDK is integrated with VS 2012 - VS 2019 as part of the ``v1xx_xp`` Platform Toolset, but does not include the samples. The easiest place to get these legacy samples now is on [GitHub](https://github.com/Microsoft/Windows-classic-samples/tree/main/Samples/Win7Samples).

<h1>AMD Samples</h1>

These samples shipped in the DirectX SDK (June 2010) and were contributed by AMD.

<table border="1">
<tbody>
<tr>
<td>DepthOfField10.1<br /> HDAO10.1<br /> TransparencyAA10.1<br /> <br /> ContactHardeningShadows11<br /> DecalTessellation11<br /> DetailTessellation11<br /> PNTriangles11</td>
<td>
<p>This samples make use of D3DX10/D3DX11 and therefore require the use of the Microsoft.DXSDK.D3DX NuGet package. These are included in the <a href="https://github.com/walbourn/directx-sdk-legacy-samples">directx-sdk-legacy-samples</a> repository.</p>
</td>
</tr>
</tbody>
</table>

<h1>Retired Samples</h1>

<table border="1">
<tbody>
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
<td>Managed DirectX 1.1</td>
<td>
<p>The DirectX SDK (August 2006) release was the last time the C# samples for <a href="https://walbourn.github.io/directx-and-net/">legacy Managed DirectX 1.1</a> were shipped</p>
</td>
</tr>
<tr>
<td>XACT</td>
<td>
<p>The DirectX SDK (June 2010) contains the last release of XACT and related samples.</p>
<p>Note that the <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectX Tool Kit for Audio</a> includes a <code>XWBTool</code> command-line utility for creating/using XACT-style wave banks for both in-memory playback and streaming.
</p>
</td>
</tr>
</tbody>
</table>

<strong>Related:</strong> <a href="https://walbourn.github.io/dxut-for-win32-desktop-update/">DXUT for Win32 Desktop Update</a>, <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a>, <a href="https://walbourn.github.io/directx-sdk-tools-catalog/">DirectX SDK Tools Catalog</a>, <a href="https://walbourn.github.io/where-is-the-directx-sdk-2021-edition/">Where is the DirectX SDK (2021 Edition)?</a>
