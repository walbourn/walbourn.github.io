---
layout: msdnpost
title: Where is the DirectX SDK (2013 Edition)?
date: 2013-07-01 02:00
author: Chuck Walbourn
comments: true
categories: [directx, dxsdk]
---
<strong>See also "<a href="https://walbourn.github.io/where-is-the-directx-sdk-2015-edition/">Where is the DirectX SDK (2015 Edition)?</a>"</strong>

At <a href="http://www.buildwindows.com/">BUILD 2013</a> last week, Microsoft released the <a href="http://go.microsoft.com/fwlink/p/?LinkID=302144">Windows 8.1 Preview</a>, <a href="http://go.microsoft.com/fwlink/?LinkId=306566">Visual Studio 2013 Preview</a>, and the <a href="https://developer.microsoft.com/en-us/windows/downloads/sdk-archive">Windows SDK for Windows 8.1 Preview</a> (included in the VS 2013 Preview). <em>Note that RTM was released on </em><em>October 17th, 2013.</em>
<!--more-->

> **NOTICE:** The *DirectX SDK*, the *DirectX End-User Runtime*, and the files for the *DirectX End-User Web Installer* were all SHA-1 signed, and therefore have been removed from Microsoft Downloads per [this policy](https://techcommunity.microsoft.com/t5/windows-it-pro-blog/sha-1-windows-content-to-be-retired-august-3-2020/ba-p/1544373).

As with the Windows 8.0 SDK, the Windows 8.1 SDK is where you'll find <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/direct3d-11-2-features">Direct3D 11.2</a>, <a href="https://docs.microsoft.com/en-us/windows/desktop/Direct2D/what-s-new-in-direct2d-for-windows-8-consumer-preview">Direct2D 1.2</a>, <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3ddxgi/dxgi-1-3-improvements">DXGI 1.3</a>, <a href="https://docs.microsoft.com/en-us/windows/desktop/dxmath/pg-xnamath-whatsnew">DirectXMath 3.05</a>, a new <a href="https://walbourn.github.io/hlsl-fxc-and-d3dcompile/">HLSL complier</a> (#47), and some updates to <a href="https://docs.microsoft.com/en-us/windows/desktop/wic/what-s-new-in-wic-for-windows-8-1">WIC</a>.

> We recommend using the Windows 8.x SDK instead of the DirectX SDK, or at a minimum using the Windows 8.x SDK primarily with only specific usages of the legacy DirectX SDK.

The 18.0 C++ compiler in the Visual Studio 2013 Preview includes support for a <a href="https://devblogs.microsoft.com/cppblog/introducing-vector-calling-convention/">new ``__vectorcall`` x86 and x64 calling-convention</a>, and DirectXMath 3.05 has been updated to take advantage of it. I refreshed the <a href="https://walbourn.github.io/directxmath-sse-sse2-and-arm-neon/">DirectXMath extensions</a> series, <a href="https://walbourn.github.io/xdsp-h-digital-signal-processing-helper-functions/">XDSP</a>, and <a href="http://go.microsoft.com/fwlink/p/?LinkId=262885">SHmath</a> to integrate smoothly with this new version. The 18.0 C++ compiler supports <a href="https://devblogs.microsoft.com/cppblog/announcing-november-ctp-of-the-c-compiler-now-with-more-c11/">additional C++11</a>, <a href="https://devblogs.microsoft.com/cppblog/c1114-stl-features-fixes-and-breaking-changes-in-vs-2013/">Standard Library/STL</a>, and <a href="https://devblogs.microsoft.com/cppblog/c99-library-support-in-visual-studio-2013/">C99 library</a> features as well. See the <a href="https://devblogs.microsoft.com/cppblog/whats-new-for-visual-c-developers-in-vs2013-preview/">Visual C++ Team blog</a>, <a href="">Somasegar's blog</a>, and the<a href="https://devblogs.microsoft.com/somasegar/build-2013-and-visual-studio-2013-preview/"> Visual Studio blog</a>. Remote Debugging Tools packages are also <a href="http://www.microsoft.com/en-us/download/details/?id=39312">available</a>.

You'll find VS 2013 projects for <a href="https://github.com/Microsoft/DirectXTex">DirectXTex</a>, <a href="https://github.com/Microsoft/DirectXTK"> DirectXTK,</a> and <a href="https://github.com/Microsoft/FX11">Effects 11</a> on their respective CodePlex/GitHub sites. There is a Windows Store app for Windows 8.1 version of <em>DirectXTK Simple Sample</em> available on <a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Sample-a0b6de36">MSDN Code Gallery</a>.

The <a href="https://walbourn.github.io/announcement-directx-sdk-june-2010-is-live/">DirectX SDK (June 2010)</a> is still available as the last release of the standalone <em>DirectX SDK</em>, but we strongly encourage developers to begin to transition to using the Windows SDK instead. Instructions for 'mixing' use of the new <em>Windows SDK</em> and older <em>DirectX SDK</em> content can be found <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">here</a>. Remember that for Windows Store app development, do not use the <em>DirectX SDK.</em>

<strong>VS 2010 Users:</strong> The standalone <em>Windows 8.1 SDK</em> does not integrate a new "platform toolset" option for<em> Visual Studio 2010</em> to use the newer headers. See this <a href="https://walbourn.github.io/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available/">post</a> for more details.

<strong>Game Compatibility: </strong>For developers and publishers of Windows Desktop PC games, be sure to review the <a href="https://walbourn.github.io/desktop-games-on-windows-8-x">Desktop Games on Windows 8.x</a> recommendations, the latest <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/windows-8-and-windows-server-8-compatibility-cookbook-portal">Windows and Windows Server compatibility cookbook</a>, and pay particular attention to the <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/operating-system-version-changes-in-windows-8-1">new appcompat behavior</a> of the <code>GetVersion(Ex)</code> API--which you <a href="https://walbourn.github.io/whats-in-a-version-number/">aren't using</a>, right?

The key takeaway is if your game or launcher uses this API to collect user telemetry, be sure to add the <a href="https://walbourn.github.io/manifest-madness/">compatibility manifest elements</a> to your EXEs. Otherwise, get rid of any crusty OS version checks that still use this API.

<strong>Direct3D 11.2:</strong> Note that there is no ``D3D_FEATURE_LEVEL_11_2`` hardware feature level defined as of yet. New hardware features exposed by DirectX 11.2 are optional.

<strong>Windows Family Safety / Parental Controls: </strong>Windows 8.1 supports the <a href="http://go.microsoft.com/fwlink/?LinkId=282715">Russian Age Rating System</a>--see the <a href="https://walbourn.github.io/windows-8-release-preview-and-gdfs/">Windows 8.x and GDFs</a> post as well as the updated <a href="https://github.com/walbourn/directx-sdk-samples/tree/master/GDFTrace">GDFTrace</a> utility. If you run <a href="http://go.microsoft.com/fwlink/?LinkId=252091">GDFMaker</a> from the Windows 8.x SDK on Windows 8.1, you'll have the option of populating the new rating system. Note support for RARS is added to Windows 8.0 via <a href="http://support.microsoft.com/kb/2838466">KB 2838466</a>.

<strong>``_WIN32_WINNT``:</strong> When building an application that is 'down-level' using headers in the Windows 8.1 SDK, be sure to explicitly select the correct 'minimum' ``_WIN32_WINNT`` value. VS 2013 Preview and the Windows 8.1 SDK default to 0x0603. For Windows 8 compatibility, use 0x0602; for Windows 7 use 0x0601; and for Windows Vista use 0x0600. Typically this is done as part of the project configuration via Preprocessor Definitions. See Using the <a href="https://docs.microsoft.com/en-us/windows/desktop/WinProg/using-the-windows-headers">Windows Headers</a> for more information.

<strong>Developer Runtime:</strong> The Windows 8.1 SDK (also included with Visual Studio 2013) is where you obtain the <a href="https://walbourn.github.io/direct3d-sdk-debug-layer-tricks/">latest Developer Runtime</a> that is compatible with Windows 8.1.

<strong>Windows Store app developers:</strong> Be sure to review the <a href="http://go.microsoft.com/fwlink/?LinkID=304117">Migration Guide</a> and how to <a href="http://go.microsoft.com/fwlink/?LinkID=309366">Retarget to Windows 8.1 Preview</a>.

<strong>System requirements:</strong> Windows 8.1 will run on the majority of hardware that can run Windows 8. The 64-bit version does require CPU support for some additional instructions which are not present on early first-generation 64-bit processors. See the <a href="http://windows.microsoft.com/en-us/windows-8/preview-faq">Windows 8.1 Preview FAQ</a> for details.

Visual Studio 2013 can be installed on Windows 8.1, Windows 8, and Windows 7 Service Pack 1. For Windows 7 SP1, installing <a href="https://walbourn.github.io/directx-11-1-and-windows-7-update/">KB 2670838</a> is required as part of the setup.

<strong>DirectX SDK:</strong> If you want to make use of <a href="https://walbourn.github.io/announcement-directx-sdk-june-2010-is-live/">legacy DirectX SDK</a> components such as D3DX9, D3DX10, D3DX11, or XAudio 2.7 with Visual Studio 2013, see <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">Microsoft Docs</a> for details on mixing the paths correctly.

<strong>DXUT:</strong> The version of DXUT11 in the DirectX SDK (June 2010) is heavily tied to D3DX which requires the legacy DirectX SDK. See <a href="https://walbourn.github.io/dxut-for-win32-desktop-update/">DXUT for Win32 Desktop Update</a> for a newer release.

<strong>FX:  </strong>The version of Effects 11 in the DirectX SDK (June 2010) needs the a few includes from the legacy DirectX SDK. See <a href="https://walbourn.github.io/effects-for-direct3d-11-update/">Effects for Direct3D 11 Update</a> for a newer release.

<strong>D3DX:</strong> As noted on MDSN, all versions of D3DX are deprecated including D3DX11. See <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a>.

<strong>Tools:</strong> Some of the developer tools are in the Windows 8.x SDK, others are not. See <a href="https://walbourn.github.io/directx-sdk-tools-catalog/">DirectX SDK Tools Catalog</a>.

<strong>Samples:</strong> A number of samples from the DirectX SDK (June 2010) release have been updated and posted to MSDN Code Gallery. See <a href="https://walbourn.github.io/directx-sdk-samples-catalog/">DirectX SDK Samples Catalog</a>.

<strong>Related:</strong> <a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?,</a> <a href="https://walbourn.github.io/directx-sdks-of-a-certain-age/">DirectX SDKs of a certain age</a>, <a href="https://walbourn.github.io/visual-studio-2013-release-candidate/">Visual Studio 2013 Release Candidate</a>, <a href="https://walbourn.github.io/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available/">Visual Studio 2013 and Windows 8.1 SDK RTM are now available</a>, <a href="https://walbourn.github.io/the-zombie-directx-sdk/">The Zombie DirectX SDK</a>

<strong>See also</strong>: <a href="https://walbourn.github.io/wheres-dxerr-lib/">Where is DXERR.LIB?</a>, <a href="https://walbourn.github.io/windows-8-release-preview-and-gdfs/">GDF Tools</a>, <a href="https://walbourn.github.io/xdsp-h-digital-signal-processing-helper-functions/">XDSP.H</a>, <a href="https://walbourn.github.io/spherical-harmonics-math/">SH Math</a>, <a href="https://github.com/walbourn/directx-sdk-samples/tree/master/BC6HBC7EncoderCS">BC6H/BC7Encoder</a>
