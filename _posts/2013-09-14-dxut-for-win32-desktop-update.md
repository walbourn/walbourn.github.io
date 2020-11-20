---
layout: msdnpost
title: DXUT for Win32 Desktop Update
date: 2013-09-14 09:00
author: Chuck Walbourn
comments: true
categories: [codeplex, direct3d]
---
With the deprecation of the DirectX SDK (see <a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a> and <a href="https://walbourn.github.io/where-is-the-directx-sdk-2013-edition/">Where is the DirectX SDK (2013 Edition)?</a>), there's been a lot of guidance both on this blog and on <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">Microsoft Docs</a> on moving to newer, supported solutions. As a number of folks have noticed, DXUT (aka the DirectX SDK samples framework) is not included in the Windows 8.x SDK.  This post provides an updated version of DXUT for Direct3D 11. The primary purpose of this release is to remove dependencies on the DirectX SDK for D3DX9, D3DX11, and DXERR. It also includes some code tidying and a few customer requests.
<!--more-->

<span style="color:red">**The project on [GitHub](https://github.com/Microsoft/DXUT) is marked as archive. It is still available for use for legacy projects, but use of it for new projects is not recommended.**</span>

<ul>
<li>The DXUT framework is for use in <strong>Win32 desktop applications</strong>. It not usable for Windows Store apps on Windows 8.x or Windows RT.</li>
<li>This version of DXUT only supports <strong>Direct3D 11</strong>, and therefore is not compatible with Windows XP or early versions of Windows Vista.</li>
<li>It supports Windows 8.x Win32 desktop, Windows 7, Windows Vista Service Pack 2 with KB 971644, and Windows Server equivalents of these release.</li>
</ul>

<em>If you still need support for Visual Studio 2008, Windows XP, or Direct3D 9 you should continue to use the legacy DirectX SDK (June 2010) version</em>.

<h1>FAQ</h1>

<h2>Q: Is DXUT the official Microsoft samples framework for DirectX?</h2>

Over the years, DXUT has enjoyed a sort of 'semi-official' status because of its use in most of the DirectX SDK samples content. It has been adopted for samples from some video card manufacturer as well. In the past few years, the samples strategy for Microsoft has transitioned away from being packed into SDKs to the online <a href="http://code.msdn.microsoft.com/">MSDN Code Gallery</a> which includes both 'official' Microsoft samples as well as community contributions.  The official samples on MSDN Code Gallery generally do not make use of any samples framework at all, and none use DXUT.  As such, DXUT has no special status as an 'official' or 'supported' samples framework.

> MSDN Code Gallery has been retired in favor of [GitHub](https://github.com/Microsoft/)

<h2>Q: DXUT in the DirectX SDK supported Windows XP. Why is that not in the update?</h2>

The DXUT samples framework in the DirectX SDK provided 'dual' support for both Direct3D 9 and Direct3D 11 (and prior to that Direct3D 9 and Direct3D 10).  This was primarily to support the venerable <a href="https://walbourn.github.io/goodbye-to-an-old-friend/">Windows XP</a> platform. DXUT relied heavily on functionality in the D3DX library, which is now deprecated and only available in the DirectX SDK. There are a host of D3DX replacements for Direct3D 11, but none for Direct3D 9. As such, if you still require Windows XP or Direct3D 9 support, you'll need to stick with the end-of-life DirectX SDK (June 2010) release, and continue to rely on the legacy <a href="https://walbourn.github.io/not-so-direct-setup/">DirectSetup</a> deployment model. If you are using VS 2012, you'll want to read some of the special handling needed to mix the legacy DirectX SDK with the <a href="https://walbourn.github.io/visual-studio-2012-update-1/">v110_xp</a> Platform Toolset.

<h2>Q: Why is there no DXUT support for Windows Store apps?</h2>

The primary purpose of the DXUT framework is to handle the complex needs for device enumeration and selection, to provide GUI elements suitable for use with a full-screen DirectX application, and support a simplistic but useful mouse/keyboard input mechanism. Windows Store apps, however, have an entirely different presentation model, make use of XAML and/or Direct2D for GUI elements, support a touch-first input design, and has a heavily emphasis on power-friendly asynchronous I/O. As such, DXUT is not applicable to Windows Store apps or Windows phone.

<h2>Q: I'm new to Direct3D 11. Is DXUT a good place to start?</h2>

Visual Studio 2012 and 2013 include great DirectX templates for Windows Store apps that use Direct3D 11, and there are many samples on MSDN Code Gallery. This update to DXUT is primarily intended for those already familiar with DXUT who want to continue to develop Win32 desktop samples, prototypes, and demos for Direct3D 11 without requiring the DirectX SDK or Direct Setup be installed.

> You can also find lots of Direct3D templates on [GitHub](https://github.com/walbourn/directx-vs-templates)

<h1>Version History</h1>

<h2>September 2013 (11.03)</h2>
<ul>
<li>Removed dependencies on the D3DX9 and D3DX11 libraries, so DXUT no longer requires the legacy DirectX SDK to build. It does require the d3dcompiler.h header from the Windows 8.x SDK.</li>
<li>Includes standalone DDSTextureLoader, WICTexureLoader, ScreenGrab, and DxErr modules.</li>
<li>Removed support for Direct3D 9 and Windows XP</li>
<li>Deleted the DXUTDevice9.h/.cpp, SDKSound.h/.cpp, and SDKWaveFile.h/.cpp files</li>
<li>Deleted legacy support for MCE relaunch</li>
<li>General C++ code cleanups (nullptr, auto keyword, C++ style casting, Safer CRT, etc.) which are compatible with Visual C++ 2010 and 2012</li>
<li>SAL2 annotation and /analyze cleanup</li>
<li>Added DXUTCompileFromFile, DXUTCreateShaderResourceViewFromFile, DXUTCreateTextureFromFile, DXUTSaveTextureToFile helpers</li>
<li>Added ``-forcewarp`` command-line switch</li>
<li>Added support for DXGI 1.1 and 1.2 formats</li>
<li>Added Direct3D 11.1 Device/Context state</li>
<li>Support Feature Level 11.1 when available</li>
</ul>

<h2>June 2010 (11.02)</h2>
<ul>
<li>The DirectX SDK (June 2010) included an update to DXUT11. This is the last version to support Visual Studio 2008, Windows XP, or Direct3D 9. The source code is located in ``Samples\C++\DXUT11``.</li>
</ul>

<h2>February 2010 (11.01)</h2>
<ul>
<li>An update was shipped with the DirectX SDK (February 2010). This is the last version to support Visual Studio 2005. The source code is located in <code>Samples\C++\DXUT11</code>.</li>
</ul>

<h2>August 2009 (11.00)</h2>
<ul>
<li>The initial release of DXUT11 was in DirectX SDK (August 2009). The source code is located in ``Samples\C++\DXUT11``. This was a port of the original DXUT which supported Direct3D 10 / Direct3D 9 applications on Windows XP and Windows Vista.</li>
</ul>

<strong>Update: </strong>DXUT is now hosted on <a href="https://dxut.codeplex.com/">CodePlex</a> and <a href="https://github.com/Microsoft/DXUT">GitHub</a>. The latest version of the framework, documentation, notes on future work, release history, and other information is now available there.

<strong>Samples</strong>: <a href="https://github.com/walbourn/directx-sdk-samples/tree/master/Direct3D11TutorialsDXUT">DXUT Tutorial Win32 Samples</a>, <a href="https://github.com/walbourn/directx-sdk-samples">DXUT Win32 Samples</a>, <a href="http://code.msdn.microsoft.com/DXUTDirectXTK-Simple-Win32-9cf797e9">DXUT+DirectXTK Simple Sample</a>

> You can use DXUT in combination with <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK</a> in the same project, but you should remove the files <code>DDSTextureLoader.h, DDSTextureLoader.cpp, ScreenGrab.h, ScreenGrab.cpp, WICTextureLoader.h,</code> and <code>WICTextureLoader.cpp</code> from ``DXUT\Core``. Removal of <code>SDKmesh.h</code> and <code>SDKmesh.cpp</code> from ``DXUT\Optional`` is also recommended. You may have to add additional include paths to the DXUT projects to find the ``DirectXTK\Inc`` folder as well.

<strong>Related:</strong> <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a>, <a href="https://walbourn.github.io/effects-for-direct3d-11-update/">Effects 11</a>, <a href="https://walbourn.github.io/wheres-dxerr-lib/">Where's DXERR.lIB?</a>
