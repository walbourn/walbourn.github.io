---
layout: post
title: Windows 10 SDK (November 2015)
date: 2015-11-30 18:02
author: Chuck Walbourn
comments: true
categories: [uwp, win10, windowssdk]
---
The Windows 10 SDK (10.0.10586) for the <a href="https://blogs.windows.com/windowsexperience/2015/11/12/first-major-update-for-windows-10-available-today/">November 2015 update of Windows 10</a> (a.k.a. Version 1511) is now available. It can be installed via an <a href="https://devblogs.microsoft.com/somasegar/building-apps-for-windows-10-with-visual-studio-2015/">optional install</a> with <a href="https://walbourn.github.io/visual-studio-2015-update-1/">VS 2015 Update 1</a> or as a <a href="http://go.microsoft.com/fwlink/?LinkID=698771">standalone installer</a>. This includes <a href="https://walbourn.github.io/directxmath-3-08/">DirectXMath 3.08</a>, <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/direct3d-11-4-features">Direct3D 11.4</a>, Direct3D 12.0, DXGI 1.5, updates to Direct2D/DirectWrite 1.3, and XAudio 2.9. See <a href="https://docs.microsoft.com/en-us/windows/uwp/whats-new/windows-10-build-10586">What's new in Windows 10 for developers, build 10586</a>.
<!--more-->

<strong>GitHub:</strong> All of my open source project have new releases to support VS 2015 Update 1 and the Windows 10 SDK (10586): <a href="https://github.com/Microsoft/DirectXTK">DirectXTK</a>, <a href="https://github.com/Microsoft/DirectXTex">DirectXTex</a>, <a href="https://github.com/Microsoft/DirectXMesh">DirectXMesh</a>, <a href="https://github.com/Microsoft/UVAtlas">UVAtlas</a>, <a href="https://github.com/Microsoft/FX11">Effects11</a>, and <a href="https://github.com/Microsoft/DXUT">DXUT11</a>.

<strong>DirectX Developer Runtime:</strong> The DirectX Developer Runtime for Windows 10 is an optional feature called <em>Graphics Tools</em> as described in <a href="https://devblogs.microsoft.com/cppblog/visual-studio-2015-and-graphics-tools-for-windows-10/">this blog post</a>. When upgrading from 10240 to 10586, the optional feature can be disabled rather than updated, which can be fixed by re-enabling the optional feature. Note that WARP12 is part of the <em>Graphics Tools</em> optional feature as it's currently intended only for use by developers.

<strong>XInput:</strong> For UWP, you can continue to use the XInput 1.4 API but need to change from linking to <code>xinput.lib</code> to <code>xinputuap.lib</code>. Alternatively, you can make use of the <a href="https://walbourn.github.io/directx-tool-kit-now-with-gamepads/">GamePad</a> class in <a href="https://github.com/Microsoft/DirectXTK">DirectX Tool Kit</a> which uses the new <code><a href="https://docs.microsoft.com/en-us/uwp/api/Windows.Gaming.Input">Windows.Gaming.Input</a></code> API. See <a href="https://walbourn.github.io/xinput-and-windows-8-consumer-preview/">XInput and Windows 8</a>.

<strong>XAudio:</strong> With the Windows 10 SDK, if you are linking with <code>xaudio2.lib</code> you are linking against XAudio 2.9 and should build your application using ``_WIN32_WINNT=0x0A00``. If you want to use XAudio 2.8 with the Windows 10 SDK, you need to set ``_WIN32_WINNT=0x0602`` or ``_WIN32_WINNT=0x0603`` and link against <code>xaudio2_8.lib</code>. See <a href="https://walbourn.github.io/xaudio2-and-windows-8-consumer-preview/">XAudio2 and Windows 8</a> for more details.

<strong>VS 2013 Users: </strong>As with the past few releases, the Windows 10 SDK only integrates with the latest Visual Studio, VS 2015. You can use the Windows 10 SDK with VS 2013 by using the props attached per this <a href="https://devblogs.microsoft.com/cppblog/using-the-windows-8-sdk-with-visual-studio-2010-configuring-multiple-projects/">Visual C+ Team Blog</a>.

<strong>Samples:</strong> As with the Windows 10 SDK RTM, official Windows samples are hosted on GitHub: <a href="https://github.com/Microsoft/Windows-universal-samples">Windows-universal-samples</a>, <a href="https://github.com/Microsoft/Windows-classic-samples">Windows-classic-samples</a>, <a href="https://github.com/Microsoft/Windows-driver-samples">Windows-driver-samples</a>. Additional Direct3D 12 samples can be found in <a href="https://github.com/Microsoft/DirectX-Graphics-Samples">DirectX-Graphics-Samples</a>. See also <a href="https://walbourn.github.io/directx-sdk-samples-catalog/">DirectX SDK Samples Catalog</a>.

<strong>Related: </strong><a href="https://walbourn.github.io/windows-10-sdk-rtm/">Windows 10 SDK RTM,</a> <a href="https://walbourn.github.io/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK</a>

<a href="https://walbourn.github.io/download/Windows10SDKVS13-10586.zip">Windows10SDKVS13-10586.zip</a>
