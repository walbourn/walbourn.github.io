---
layout: post
title: DXUT for Win32 Desktop Update
date: 2013-09-14 09:00
author: walbourn
comments: true
categories: [codeplex, direct3d, Uncategorized]
---
<p>With the deprecation of the DirectX SDK (see <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">Where is the DirectX SDK?</a> and <a href="http://blogs.msdn.com/b/chuckw/archive/2013/07/01/where-is-the-directx-sdk-2013-edition.aspx">Where is the DirectX SDK (2013 Edition)?</a>), there&rsquo;s been a lot of guidance both on this blog and on <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee663275.aspx">MSDN</a>&nbsp;on moving to newer, supported solutions. As a number of folks have noticed, DXUT (aka the DirectX SDK samples framework) is not included in the Windows 8.x SDK.&nbsp; This post provides an updated version of DXUT for Direct3D 11. The primary purpose of this release is to remove dependencies on the DirectX SDK for D3DX9, D3DX11, and DXERR. It also includes some code tidying and a few customer requests.</p>
<ul>
<li>The DXUT framework is for use in <strong>Win32 desktop applications</strong>. It not usable for Windows Store apps on Windows 8.x or Windows RT.</li>
<li>This version of DXUT only supports <strong>Direct3D 11</strong>, and therefore is not compatible with Windows XP or early versions of Windows Vista.</li>
<li>It supports Windows 8.x Win32 desktop, Windows 7, Windows Vista Service Pack 2 with KB 971644, and Windows Server equivalents of these release.</li>
</ul>
<p><em>If you still need support for Visual Studio 2008, Windows XP, or Direct3D 9 you should continue to use the legacy DirectX SDK (June 2010) version</em>.</p>
<h1>FAQ</h1>
<h2>Q: Is DXUT the official Microsoft samples framework for DirectX?</h2>
<p>Over the years, DXUT has enjoyed a sort of &lsquo;semi-official&rsquo; status because of its use in most of the DirectX SDK samples content. It has been adopted for samples from some video card manufacturer as well. In the past few years, the samples strategy for Microsoft has transitioned away from being packed into SDKs to the online <a href="http://code.msdn.microsoft.com/">MSDN Code Gallery</a> which includes both &lsquo;official&rsquo; Microsoft samples as well as community contributions.&nbsp; The official samples on MSDN Code Gallery generally do not make use of any samples framework at all, and none use DXUT.&nbsp; As such, DXUT has no special status as an &lsquo;official&rsquo; or &lsquo;supported&rsquo; samples framework.</p>
<h2>Q: DXUT in the DirectX SDK supported Windows XP. Why is that not in the update?</h2>
<p>The DXUT samples framework in the DirectX SDK provided &lsquo;dual&rsquo; support for both Direct3D 9 and Direct3D 11 (and prior to that Direct3D 9 and Direct3D 10).&nbsp; This was primarily to support the venerable <a href="http://blogs.msdn.com/b/chuckw/archive/2010/10/22/goodbye-to-an-old-friend.aspx">Windows XP</a> platform. DXUT relied heavily on functionality in the D3DX library, which is now deprecated and only available in the DirectX SDK. There are a host of D3DX replacements for Direct3D 11, but none for Direct3D 9. As such, if you still require Windows XP or Direct3D 9 support, you&rsquo;ll need to stick with the end-of-life DirectX SDK (June 2010) release, and continue to rely on the legacy <a href="http://blogs.msdn.com/b/chuckw/archive/2010/09/08/not-so-direct-setup.aspx">DirectSetup</a>&nbsp;deployment model. If you are using VS 2012, you&rsquo;ll want to read some of the special handling needed to mix the legacy DirectX SDK with the <a href="http://blogs.msdn.com/b/chuckw/archive/2012/11/26/visual-studio-2012-update-1.aspx">v110_xp</a>&nbsp;Platform Toolset.</p>
<h2>Q: Why is there no DXUT support for Windows Store apps?</h2>
<p>The primary purpose of the DXUT framework is to handle the complex needs for device enumeration and selection, to provide GUI elements suitable for use with a full-screen DirectX application, and support a simplistic but useful mouse/keyboard input mechanism. Windows Store apps, however, have an entirely different presentation model, make use of XAML and/or Direct2D for GUI elements, support a touch-first input design, and has a heavily emphasis on power-friendly asynchronous I/O. As such, DXUT is not applicable to Windows Store apps or Windows phone.</p>
<h2>Q: I&rsquo;m new to Direct3D 11. Is DXUT a good place to start?</h2>
<p>Visual Studio 2012 and 2013 include great DirectX templates for Windows Store apps that use Direct3D 11, and there are many samples on MSDN Code Gallery. This update to DXUT is primarily intended for those already familiar with DXUT who want to continue to develop Win32 desktop samples, prototypes, and demos for Direct3D 11 without requiring the DirectX SDK or Direct Setup be installed.</p>
<h1>Version History</h1>
<p><strong>September 2013 (11.03)</strong></p>
<ul>
<li>Removed dependencies on the D3DX9 and D3DX11 libraries, so DXUT no longer requires the legacy DirectX SDK to build. It does require the d3dcompiler.h header from the Windows 8.x SDK.</li>
<li>Includes standalone DDSTextureLoader, WICTexureLoader, ScreenGrab, and DxErr modules.</li>
<li>Removed support for Direct3D 9 and Windows XP</li>
<li>Deleted the DXUTDevice9.h/.cpp, SDKSound.h/.cpp, and SDKWaveFile.h/.cpp files</li>
<li>Deleted legacy support for MCE relaunch</li>
<li>General C++ code cleanups (nullptr, auto keyword, C++ style casting, Safer CRT, etc.) which are compatible with Visual C++ 2010 and 2012</li>
<li>SAL2 annotation and /analyze cleanup</li>
<li>Added DXUTCompileFromFile, DXUTCreateShaderResourceViewFromFile, DXUTCreateTextureFromFile, DXUTSaveTextureToFile helpers</li>
<li>Added '-forcewarp' command-line switch</li>
<li>Added support for DXGI 1.1 and 1.2 formats</li>
<li>Added Direct3D 11.1 Device/Context state</li>
<li>Support Feature Level 11.1 when available</li>
</ul>
<p><strong>June 2010 (11.02)</strong></p>
<ul>
<li>The DirectX SDK (June 2010) included an update to DXUT11. This is the last version to support Visual Studio 2008, Windows XP, or Direct3D 9. The source code is located in <code>Samples\C++\DXUT11</code>.</li>
</ul>
<p><strong>February 2010 (11.01)</strong></p>
<ul>
<li>An update was shipped with the DirectX SDK (February 2010). This is the last version to support Visual Studio 2005. The source code is located in <code>Samples\C++\DXUT11</code>.</li>
</ul>
<p><strong>August 2009 (11.00)</strong></p>
<ul>
<li>The initial release of DXUT11 was in DirectX SDK (August 2009). The source code is located in <code>Samples\C++\DXUT11</code>. This was a port of the original DXUT which supported Direct3D 10 / Direct3D 9 applications on Windows XP and&nbsp;Windows Vista.</li>
</ul>
<p><strong>Update: </strong>DXUT is now hosted on <a href="https://dxut.codeplex.com/">CodePlex</a>&nbsp;and <a href="https://github.com/Microsoft/DXUT">GitHub</a>. The latest version of the framework, documentation, notes on future work, release history, and other information is now available there.</p>
<p><strong>Samples</strong>: <a href="http://code.msdn.microsoft.com/DXUT-Tutorial-Win32-Sample-fe15e440">DXUT Tutorial Win32 Samples</a>, <a href="http://code.msdn.microsoft.com/Basic-DXUT-Win32-Samples-e59c0682">Basic DXUT Win32 Samples</a>, <a href="http://code.msdn.microsoft.com/DXUTDirectXTK-Simple-Win32-9cf797e9">DXUT+DirectXTK Simple Sample</a></p>
<p><strong>DirectXTK Note:</strong> You can use DXUT in combination with <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK</a> in the same project, but you should remove the files <code>DDSTextureLoader.h, DDSTextureLoader.cpp, ScreenGrab.h, ScreenGrab.cpp, WICTextureLoader.h,</code> and <code>WICTextureLoader.cpp</code> from <code>DXUT\Core</code>. Removal of <code>SDKmesh.h</code> and <code>SDKmesh.cpp</code> from <code>DXUT\Optional</code> is also recommended. You may have to add additional include paths to the DXUT projects to find the <code>DirectXTK\Inc</code> folder as well.</p>
<p><strong>Related:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2013/08/21/living-without-d3dx.aspx">Living without D3DX</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/10/24/effects-for-direct3d-11-update.aspx">Effects 11</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/24/where-s-dxerr-lib.aspx">Where&rsquo;s DXERR.lIB?</a></p>
