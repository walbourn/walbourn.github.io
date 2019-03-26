---
layout: post
title: Where is the DirectX SDK?
date: 2012-03-22 11:45
author: Chuck Walbourn
comments: true
categories: [dxsdk]
---
><strong>See also "<a href="https://walbourn.github.io/where-is-the-directx-sdk-2015-edition/">Where is the DirectX SDK (2015 Edition)?</a>"</strong>

The <em>DirectX SDK</em> is now part of the <em>Windows 8.0 SDK. </em>The new <em>Windows 8.0 SDK</em> is where you'll find <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/direct3d-11-1-features">DirectX 11.1</a>, <a href="https://docs.microsoft.com/en-us/windows/desktop/Direct2D/what-s-new-in-direct2d-for-windows-8-consumer-preview">Direct2D</a>, <a href="https://docs.microsoft.com/en-us/windows/desktop/DirectWrite/what-s-new-in-directwrite-for-windows-8-consumer-preview">DirectWrite</a>, <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3ddxgi/dxgi-1-2-improvements">DXGI 1.2</a>, <a href="http://go.microsoft.com/fwlink/?LinkId=226814">WDDM 1.2</a>, <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a>, <a href="https://walbourn.github.io/direct3d-feature-levels/">Feature Level 11.1 devices</a>, <a href="https://walbourn.github.io/xinput-and-windows-8/">XINPUT 1.4</a>, <a href="https://walbourn.github.io/xaudio2-and-windows-8/">XAUDIO 2.8</a>, <a href="https://walbourn.github.io/windows-imaging-component-and-windows-8/">WIC2</a>, the "<a href="https://walbourn.github.io/direct3d-sdk-debug-layer-tricks/">Developer Runtime</a>" (debugging layers and the REF device), and the latest <a href="https://walbourn.github.io/hlsl-fxc-and-d3dcompile/">HLSL</a> compiler (<code>D3DCompiler_*.DLL</code>). Samples are now shipped online and can be found at the <a href="http://code.msdn.microsoft.com/">MSDN Code Gallery</a>. <em>We recommend using the Windows 8.x SDK instead of the DirectX SDK, or at a minimum using the Windows 8.x SDK primarily with only specific usages of the legacy DirectX SDK.</em>
<!--more-->

The <em>Windows SDK for Windows 8 </em>(aka <em>Windows 8.0 SDK</em>) is included with <a href="https://walbourn.github.io/visual-studio-2012-release-candidate/">Visual Studio 2012</a>, and is also available as a <a href="https://developer.microsoft.com/en-us/windows/downloads/sdk-archive">standalone</a> package for use with Visual Studio 2010.

The <em>Windows SDK for Windows 8</em> supports building both Windows Store apps (a.k.a. Metro style apps) and desktop Win32 applications on <em>Windows 8 </em>and <em>Windows Server 2012</em>. It supports building desktop Win32 applications for Windows 7, Windows Server 2008 R2, Windows Vista, and Windows Server 2008. It cannot be directly installed on Windows Vista or Windows Server 2008.

See the MSDN page "<a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">Where is the DirectX SDK?</a>" for a complete list of "DirectX SDK" content now available in the Windows SDK. Be sure to see the <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a> and <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK</a> libraries as well.

The <a href="https://walbourn.github.io/announcement-directx-sdk-june-2010-is-live/">DirectX SDK (June 2010)</a> is still available as the last release of the standalone <em>DirectX SDK</em>, but we strongly encourage developers to begin to transition to using the Windows SDK instead. Instructions for 'mixing' use of the new <em>Windows SDK</em> and older <em>DirectX SDK</em> content can be found <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">here</a>. Remember that for Windows Store app development, do not use the <em>DirectX SDK.</em>

I'll be posting more articles in the coming weeks to address various aspects of these changes and how it impacts game development on Windows, so stay tuned.

<strong>VS 2010 Users:</strong> The standalone <em>Windows 8.0 SDK</em> does not integrate a new "platform toolset" option for<em> Visual Studio 2010</em> to use the newer headers. See this <a href="https://walbourn.github.io/visual-studio-2012-and-windows-8-0-sdk-rtm-are-now-available/">post</a> for more details.

<strong>``_WIN32_WINNT``: </strong>When building an application that is 'down-level' when using headers in the Windows 8.0 SDK, be sure to explicitly select the correct 'minimum' ``_WIN32_WINNT`` value. For Windows 8, that is 0x0602 (which is the default when building code with Visual Studio 2012 and for all Windows Store apps). For Windows 7 use 0x0601, and for Windows Vista use 0x0600. Typically this is done as part of the project configuration via <em>Preprocessor Definitions</em>. See <a href="https://docs.microsoft.com/en-us/windows/desktop/WinProg/using-the-windows-headers">Using the Windows Headers</a> for more information.

<strong>Developer Runtime:</strong> One of the reasons for installing the <em>DirectX SDK i</em>s to get the '<a href="https://walbourn.github.io/direct3d-sdk-debug-layer-tricks/">developer runtime</a>' with debug versions of various components and the reference devices. The <em>Windows 8.0 SDK</em> includes these debugging facilities for Direct3D 10.x/11.x, Direct2D, and DXGI for Windows 7 and Windows 8. Parts of the <em>DirectX SDK (June 2010)</em> developer runtime are not compatible with Windows 8, and won't install, so the <em>Windows 8.0 SDK</em> is required for DirectX debugging support on Windows 8. The <em>Windows 8.0 SDK</em> does not include support for debugging Direct3D 9 applications. The only way to get the debug version of Direct3D 9 for Windows 8 is to install a 'checked' version of the OS.

<strong>IE10 Note:</strong> Be sure to read up on <a href="https://walbourn.github.io/directx-11-1-and-windows-7-update/">KB 2670838</a> as it impacts DirectX development on Windows 7 Service Pack 1.</p>
<p><strong>Redist:</strong> The vast majority of components in <em>Windows 8.0 SDK</em> are 'in box' with the supported versions of the OS, or have no DLL component (such as DirectXMath). There is a <code>redist\D3D</code> folder in the <em>Windows 8.0 SDK</em> with the <code>D3DCompiler_*.DLL</code> and <code>D3DCSX_*.DLL</code> which can be redistributed directly with your Win32 desktop applications (see <a href="https://walbourn.github.io/hlsl-fxc-and-d3dcompile/">HLSL, FXC, and D3DCompile</a>). These DLLs support Windows Vista, Windows 7, and Windows 8. For any legacy DirectX SDK components, you must still make use of DirectSetup (be sure to read <a href="https://walbourn.github.io/not-so-direct-setup/">Not So Direct Setup</a> and <a href="https://walbourn.github.io/dxsetup-update/">DXSETUP Update</a>)

<strong>Windows 7 SDK:</strong> Note that many components of "DirectX" have been included in the Windows SDKs for years. Windows SDK 7.0A (included with VS 2010) and <a href="https://walbourn.github.io/windows-sdk-7-1/">Windows SDK 7.1</a> include headers and import libraries for Direct3D9, Direct3D9Ex, Direct3D 10.x, Direct3D 11.0, Direct2D, DirectWrite, DXGI, DirectSound, DirectInput, DirectMusic "core", DirectShow, and XINPUT 9.1.0.

<strong>DXUT:</strong> The version of DXUT11 in the DirectX SDK (June 2010) is heavily tied to D3DX which requires the legacy DirectX SDK. See <a href="https://walbourn.github.io/dxut-for-win32-desktop-update/">DXUT for Win32 Desktop Update</a> for a newer release.

<strong>FX:  </strong>The version of Effects 11 in the DirectX SDK (June 2010) needs the a few includes from the legacy DirectX SDK. See <a href="https://walbourn.github.io/effects-for-direct3d-11-update/">Effects for Direct3D 11 Update</a> for a newer release.

<strong>D3DX:</strong> As noted on MDSN, all versions of D3DX are deprecated including D3DX11. See <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a>.

<strong>Tools:</strong> Some of the developer tools are in the Windows 8.x SDK, others are not. See <a href="https://walbourn.github.io/directx-sdk-tools-catalog/">DirectX SDK Tools Catalog</a>.</p>
<p><strong>Samples:</strong> A number of samples from the DirectX SDK (June 2010) release have been updated and posted to MSDN Code Gallery. See <a href="https://walbourn.github.io/directx-sdk-samples-catalog/">DirectX SDK Samples Catalog</a>.

<strong>Related:</strong> <a href="https://walbourn.github.io/directx-sdks-of-a-certain-age/">DirectX SDKs of a certain age</a>, <a href="https://walbourn.github.io/visual-studio-2012-and-windows-8-0-sdk-rtm-are-now-available/">VS 2012 and Windows 8.0 SDK RTM</a>

<strong>See also</strong>: <a href="https://walbourn.github.io/wheres-dxerr-lib/">Where is DXERR.LIB?</a>, <a href="https://walbourn.github.io/windows-8-release-preview-and-gdfs/">GDF Tools</a>, <a href="https://walbourn.github.io/xdsp-h/">XDSP.H</a>, <a href="https://walbourn.github.io/spherical-harmonics-math/">SH Math</a>, <a href="https://github.com/walbourn/directx-sdk-samples/tree/master/BC6HBC7EncoderCS">BC6H/BC7Encoder</a>
