---
layout: msdnpost
title: Where is the DirectX SDK (2015 Edition)?
date: 2015-08-05 10:00
author: Chuck Walbourn
comments: true
categories: [directx, dxsdk]
---
<strong>See "<a href="https://walbourn.github.io/where-is-the-directx-sdk-2021-edition/">Where is the DirectX SDK (2021 Edition)?</a>"</strong>

As noted on <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">Microsoft Docs</a>, the DirectX SDK is deprecated. The June 2010 release is the last release, and "DirectX" is now part of the Windows SDK. There are really only three scenarios where you should continue to use the old DirectX SDK:
<!--more-->

<ol>
 	<li>You have code (or perhaps an <a href="https://walbourn.github.io/book-recommendations/">older book</a>) that makes use of D3DX9, D3DX10, D3DX11, or XACT Engine.</li>
 	<li><strike>Your application uses use XAudio2 and supports Windows 7 systems.</strike></li>
 	<li>You are targeting Windows XP with the alternate <code>v1x0_xp</code> Platform Toolset.</li>
</ol>

<em>Remember that use of the legacy DirectX SDK is not supported for UWP app or Xbox One development.</em>

> **NOTICE:** The *DirectX SDK*, the *DirectX End-User Runtime*, and the files for the *DirectX End-User Web Installer* were all SHA-1 signed, and therefore have been removed from Microsoft Downloads per [this policy](https://techcommunity.microsoft.com/t5/windows-it-pro-blog/sha-1-windows-content-to-be-retired-august-3-2020/ba-p/1544373).

<strong>Developer Runtime:</strong> The Windows 8.1 SDK or Windows 10 SDK is where you obtain the latest <a href="https://walbourn.github.io/direct3d-sdk-debug-layer-tricks/">DirectX Developer Runtime</a> that is compatible with Windows 7, Windows 8.0, and Windows 8.1. The DirectX Developer Runtime for Windows 10 is an optional Windows feature you <a href="https://devblogs.microsoft.com/cppblog/visual-studio-2015-and-graphics-tools-for-windows-10/">enable</a> in the operating system. You can also enable it on Windows 10 via the command-line using an admin prompt:

    Dism /online /add-capability /capabilityname:Tools.Graphics.DirectX~~~~0.0.1.0

<strong>D3DX:</strong> D3DX9, D3DX10, and D3DX11 are all deprecated. See <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a> for replacements and recommendations including <a href="https://github.com/Microsoft/DirectXTK">DirectX Tool Kit</a>, <a href="https://github.com/Microsoft/DirectXTex">DirectXTex</a>, <a href="https://github.com/Microsoft/DirectXMesh">DirectXMesh</a>, and <a href="https://github.com/Microsoft/UVAtlas">UVAtlas</a> on GitHub.

<strong>XNAMath:</strong> The C++ SIMD math library "xnamath" has been replaced by [DirectXMath](https://walbourn.github.io/introducing-directxmath/). It's in the Windows 10 SDK as well as being hosted on [GitHub](https://github.com/Microsoft/DirectXMath).

<strong>FX:</strong> The latest version of Effects for Direct3D 11 is available on <a href="https://github.com/Microsoft/FX11">GitHub</a> and does not require the legacy DirectX SDK or any version of D3DX. <i>The ``fx_*`` shader profile support in the HLSL complier is deprecated.</i>

<strong>DXUT:</strong> The latest version of DXUT for Direct3D 11 is available on <a href="https://github.com/Microsoft/DXUT">GitHub</a> and does not require the legacy DirectX SDK or any version of D3DX.

<strong>Tools:</strong> Some of the developer tools are in the Windows SDK others are not. See <a href="https://walbourn.github.io/directx-sdk-tools-catalog/">DirectX SDK Tools Catalog</a> for a complete inventory.

<strong>Samples:</strong> A number of samples from the DirectX SDK (June 2010) release have been updated and posted to <a href="https://github.com/walbourn/directx-sdk-samples">GitHub</a>. They do not require the legacy DirectX SDK or any version of D3DX. See <a href="https://walbourn.github.io/directx-sdk-samples-catalog/">DirectX SDK Samples Catalog</a>.

The <a href="https://walbourn.github.io/windows-10-sdk-rtm/">Windows 10 SDK</a> includes the latest headers and link libraries for DirectX including Direct3D 12.0, Direct3D 11.3, DXGI 1.4, Direct2D/DirectWrite 1.3, and XAudio 2.9.

Both the Windows 8.1 SDK Spring 2015 update and the Windows 10 SDK include Direct3D 11.0/11.1/11.2, DXGI 1.0/1.1/1.2/1.3, <a href="https://walbourn.github.io/directxmath-3-07/">DirectXMath 3.07</a>, and Direct2D/DirectWrite 1.0/1.1/1.2. They also include the legacy Direct3D 10.0/10.1, Direct3D9Ex, Direct3D 9 headers, DirectSound8, DirectInput8, and DirectMusic "core" APIs. See <a href="https://walbourn.github.io/directx-sdks-of-a-certain-age/">DirectX SDKs of a certain age</a> for a full catalog of older DirectX APIs and their locations.

<strong>XInput:</strong> The Windows 10 SDK includes the <code>Windows.Gaming.Input</code> WinRT API which is supported on Windows 10. Both the Windows 8.1 SDK and Windows 10 SDK include XInput 1.4 which is supported on Windows 8.x and Windows 10. You should use XInput 9.1.0 to support Windows 7. See <a href="https://walbourn.github.io/xinput-and-windows-8/">XINPUT and Windows 8</a> and <a href="https://walbourn.github.io/directx-tool-kit-now-with-gamepads/">DirectX Tool Kit: Now with GamePads</a>.

<strong>XAudio:</strong> The Windows 10 SDK includes XAudio 2.9 which is supported on Windows 10. The Windows 8.1 SDK and Windows 10 SDK include XAudio 2.8 which is supported on Windows 8.x and Windows 10. <strike>You have to use the legacy DirectX SDK and XAudio 2.7 to support Windows 7. See <a href="https://walbourn.github.io/xaudio2-and-windows-8/">XAudio2 and Windows 8</a> and <a href="https://walbourn.github.io/known-issues-xaudio-2-7/">Known Issues: XAudio 2.7</a></strike>. There is now a [NuGet package](https://www.nuget.org/packages/Microsoft.XAudio2.Redist/) for using XAudio 2.9 down-level on Windows 7 Service Pack 1, Windows 8.0, and Windows 8.1. See [Microsoft Docs](https://aka.ms/XAudio2Redist) for details.

<strong>DirectX SDK:</strong> If you need to make use of legacy DirectX SDK components such as D3DX9, D3DX10, D3DX11, or XAudio 2.7 with VS 2012 or later, see <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">Microsoft Docs</a> for details on mixing the Windows 8 or Windows 10 SDK correctly with the legacy DirectX SDK. Be sure to <a href="https://walbourn.github.io/the-zombie-directx-sdk/">The Zombie DirectX SDK</a> as well. If you are targeting Windows XP which makes use of the Windows 7.1A SDK, see <a href="https://walbourn.github.io/visual-studio-2012-update-1/">Visual Studio 2012 Update 1</a>.

<h1>DirectX 12</h1>

There is something called the <em>DirectX 12 SDK</em> which was used as a beta vehicle for the development of DirectX 12 through the Early Access Program. Now that the Windows 10 SDK is final, you don't need access to the <em>DirectX 12 SDK</em> at all. The DirectX 12 samples are on <a href="https://github.com/Microsoft/DirectX-Graphics-Samples">GitHub</a>.

<strong>D3DX:</strong> Note that there is also a header file called <code>d3dx12.h</code> which is an all inline header with some utility code shipped in the GitHub samples and [DirectX 12 Visual Studio templates](https://github.com/walbourn/directx-sdk-samples). D3DX12 is not in any SDK, there's no DLL, and there's no REDIST for it. You can obtain the latest version from [GitHub](https://github.com/microsoft/DirectX-Graphics-Samples/tree/master/Libraries/D3DX12). <a href="https://github.com/Microsoft/DirectXTK12">DirectX Tool Kit</a>, <a href="https://github.com/Microsoft/DirectXTex">DirectXTex</a>, and <a href="https://github.com/Microsoft/DirectXMesh">DirectXMesh</a> also support DirectX 12.

<strong>Related:</strong> <a href="https://walbourn.github.io/where-is-the-directx-sdk-2013-edition/">Where is the DirectX SDK (2013 Edition)?</a>

<strong>See also:</strong> <a href="https://walbourn.github.io/wheres-dxerr-lib/">Where is DXERR.LIB?</a>, <a href="https://walbourn.github.io/windows-8-release-preview-and-gdfs/">GDF Tools</a>, <a href="https://walbourn.github.io/xdsp-h-digital-signal-processing-helper-functions/">XDSP.H</a>, <a href="https://walbourn.github.io/spherical-harmonics-math/">SH Math</a>
