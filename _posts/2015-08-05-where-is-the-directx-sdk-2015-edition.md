---
layout: post
title: Where is the DirectX SDK (2015 Edition)?
date: 2015-08-05 10:00
author: walbourn
comments: true
categories: [directx, dxsdk, Uncategorized]
---
As noted on <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/ee663275.aspx">MSDN</a>, the DirectX SDK is deprecated. The June 2010 release is the last release, and "DirectX" is now part of the Windows SDK. There are really only three scenarios where you should continue to use the old DirectX SDK:
<ol>
 	<li>You have code (or perhaps an <a href="http://blogs.msdn.com/b/chuckw/archive/2014/04/07/book-recommendations.aspx">older book</a>) that makes use of D3DX9, D3DX10, D3DX11, or XACT Engine.</li>
 	<li>Your application uses use XAudio2 and supports Windows 7 systems.</li>
 	<li>You are targeting Windows XP with the alternate <code>v1x0_xp</code> Platform Toolset.</li>
</ol>
<em>Remember that use of the legacy DirectX SDK is not supported for UWP app or Xbox One development.</em>

<strong>Developer Runtime:</strong> The Windows 8.1 SDK or Windows 10 SDK is where you obtain the latest <a href="http://blogs.msdn.com/b/chuckw/archive/2012/11/30/direct3d-sdk-debug-layer-tricks.aspx">DirectX Developer Runtime</a> that is compatible with Windows 7, Windows 8.0, and Windows 8.1. The DirectX Developer Runtime for Windows 10 is an optional Windows feature you <a href="http://blogs.msdn.com/b/vcblog/archive/2015/03/31/visual-studio-2015-and-graphics-tools-for-windows-10.aspx">enable</a> in the operating system. You can also enable it on Windows 10 via the command-line using an admin prompt:
<p style="padding-left: 30px"><code>Dism /online /add-capability /capabilityname:Tools.Graphics.DirectX~~~~0.0.1.0</code></p>
<strong>D3DX:</strong> All versions of D3DX are deprecated including D3DX9, D3DX10, and D3DX11. See <a href="http://blogs.msdn.com/b/chuckw/archive/2013/08/21/living-without-d3dx.aspx">Living without D3DX</a> for replacements and recommendations including <a href="https://github.com/Microsoft/DirectXTK">DirectX Tool Kit</a>, <a href="https://github.com/Microsoft/DirectXTex">DirectXTex</a>, <a href="https://github.com/Microsoft/DirectXMesh">DirectXMesh</a>, and <a href="https://github.com/Microsoft/UVAtlas">UVAtlas</a> on GitHub.

<strong>FX:</strong> The latest version of Effects for Direct3D 11 is available on <a href="https://github.com/Microsoft/FX11">GitHub</a> and does not require the legacy DirectX SDK or any version of D3DX.

<strong>DXUT:</strong> The latest version of DXUT for Direct3D 11 is available on <a href="https://github.com/Microsoft/DXUT">GitHub</a> and does not require the legacy DirectX SDK or any version of D3DX.

<strong>Tools:</strong> Some of the developer tools are in the Windows SDK others are not. See <a href="http://blogs.msdn.com/b/chuckw/archive/2014/10/28/directx-sdk-tools-catalog.aspx">DirectX SDK Tools Catalog</a> for a complete inventory.

<strong>Samples:</strong> A number of samples from the DirectX SDK (June 2010) release have been updated and posted to <a href="https://github.com/walbourn/directx-sdk-samples">GitHub</a>. They do not require the legacy DirectX SDK or any version of D3DX. See <a href="http://blogs.msdn.com/b/chuckw/archive/2013/09/20/directx-sdk-samples-catalog.aspx">DirectX SDK Samples Catalog</a>.

The <a href="http://blogs.msdn.com/b/chuckw/archive/2015/07/30/windows-10-sdk-rtm.aspx">Windows 10 SDK</a> includes the latest headers and link libraries for DirectX including Direct3D 12.0, Direct3D 11.3, DXGI 1.4, Direct2D/DirectWrite 1.3, and XAudio 2.9.

Both the Windows 8.1 SDK Spring 2015 update and the Windows 10 SDK include Direct3D 11.0/11.1/11.2, DXGI 1.0/1.1/1.2/1.3, <a href="http://blogs.msdn.com/b/chuckw/archive/2015/04/29/directxmath-3-07.aspx">DirectXMath 3.07</a>, and Direct2D/DirectWrite 1.0/1.1/1.2. They also include the legacy Direct3D 10.0/10.1, Direct3D9Ex, Direct3D 9 headers, DirectSound8, DirectInput8, and DirectMusic "core" APIs. See <a href="http://blogs.msdn.com/b/chuckw/archive/2012/08/22/directx-sdk-s-of-a-certain-age.aspx">DirectX SDKs of a certain age</a> for a full catalog of older DirectX APIs and their locations.

<strong>XInput:</strong> The Windows 10 SDK includes the <code>Windows.Gaming.Input</code> WinRT API which is supported on Windows 10. Both the Windows 8.1 SDK and Windows 10 SDK include XInput 1.4 which is supported on Windows 8.x and Windows 10. You should use XInput 9.1.0 to support Windows 7. See <a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/26/xinput-and-windows-8-consumer-preview.aspx">XINPUT and Windows 8</a> and <a href="http://blogs.msdn.com/b/chuckw/archive/2014/09/05/directx-tool-kit-now-with-gamepads.aspx">DirectX Tool Kit: Now with GamePads</a>.

<strong>XAudio:</strong> The Windows 10 SDK includes XAudio 2.9 which is supported on Windows 10. The Windows 8.1 SDK and Windows 10 SDK include XAudio 2.8 which is supported on Windows 8.x and Windows 10. You have to use the legacy DirectX SDK and XAudio 2.7 to support Windows 7. See <a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/02/xaudio2-and-windows-8-consumer-preview.aspx">XAudio2 and Windows 8</a> and <a href="http://blogs.msdn.com/b/chuckw/archive/2015/10/09/known-issues-xaudio-2-7.aspx">Known Issues: XAudio 2.7</a>.

<strong>DirectX SDK:</strong> If you need to make use of legacy DirectX SDK components such as D3DX9, D3DX10, D3DX11, or XAudio 2.7 with VS 2012, VS 2013 or VS 2015, see <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/ee663275.aspx">MSDN</a> for details on mixing the Windows 8 or Windows 10 SDK correctly with the legacy DirectX SDK. Be sure to <a href="http://blogs.msdn.com/b/chuckw/archive/2015/03/23/the-zombie-directx-sdk.aspx">The Zombie DirectX SDK</a> as well. If you are targeting Windows XP which makes use of the Windows 7.1A SDK, see <a href="http://blogs.msdn.com/b/chuckw/archive/2012/11/26/visual-studio-2012-update-1.aspx">Visual Studio 2012 Update 1</a>.
<h1>DirectX 12</h1>
There is something called the <em>DirectX 12 SDK</em> which was used as a beta vehicle for the development of DirectX 12 through the Early Access Program. Now that the Windows 10 SDK is final, you don't need access to the <em>DirectX 12 SDK</em> at all. The DirectX 12 samples are on <a href="https://github.com/Microsoft/DirectX-Graphics-Samples">GitHub</a>.

<strong>D3DX:</strong> Note that there is also a header file called <code>d3dx12.h</code> which is an all inline header with some utility code shipped in the GitHub samples. D3DX12 is not in any SDK, there's no DLL, and there's no REDIST for it. <a href="https://github.com/Microsoft/DirectXTK12">DirectX Tool Kit</a>, <a href="https://github.com/Microsoft/DirectXTex">DirectXTex</a>, and <a href="https://github.com/Microsoft/DirectXMesh">DirectXMesh</a> also support DirectX 12.

<strong>Related:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2013/07/01/where-is-the-directx-sdk-2013-edition.aspx">Where is the DirectX SDK (2013 Edition)?</a>

<strong>See also:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/24/where-s-dxerr-lib.aspx">Where is DXERR.LIB?</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/31/windows-8-release-preview-and-gdfs.aspx">GDF Tools</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/01/xdsp-h.aspx">XDSP.H</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/07/28/spherical-harmonics-math.aspx">SH Math</a>
