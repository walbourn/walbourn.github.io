---
layout: msdnpost
title: Desktop Games on Windows 8.x
date: 2012-03-23 12:19
author: Chuck Walbourn
comments: true
categories: [gfwtr, win8]
---
Developers working on games for Windows are already familiar with the <em>DirectX SDK</em>. Important changes to the DirectX family of technologies are included in the new Windows SDK, which is the new home for the DirectX SDK. Be sure to read "<a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a>" for the details.
<!--more-->

<em><strong>Windows 8.1: </strong>Note that these guidelines also apply for Win32 Desktop games running on Windows 8.1. The <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/windows-8-and-windows-server-8-compatibility-cookbook-portal">Windows and Windows Server compatibility cookbook</a> has been updated with notes about Windows 8.1. Pay particular attention to the <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/operating-system-version-changes-in-windows-8-1">OS version detection</a> behavior change, as well as the new <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/high-dpi-for-desktop-apps-in-windows-8-1">200% high-DPI</a> scaling mode. Also note that in Windows 8.1 DirectPlay is now a distinct Windows feature that is <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/windows-components-installed-on-demand">off by default</a>.</em>

<em><strong>Windows 10: </strong>Be sure to read the Windows 8.1 guidance as it also applies to Windows 10 with up to 500% high-DPI scaling. Note that there is an additional ``<compatibility>`` GUID for the new version (see <a href="https://walbourn.github.io/manifest-madness/">Manifest Madness</a>) , and <code>VerifyVersionInfo</code> is now subject to the same manifest-based behavior as <code>GetVersion(Ex)</code>. The <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/windows-8-and-windows-server-8-compatibility-cookbook-portal"><em>Windows and Windows Server compatibility cookbook</em></a><em> has been updated with notes about Windows 10.</em></em>

<h1><strong>Game Compatibility Guidelines</strong></h1>

With a new release of Windows, publishers and developers want to ensure customers running Windows 8.x continue to have a great experience running their current catalog of games for Windows 7. Developers interested in Windows 8.x software certification program should be sure to read the latest version of those <a href="http://go.microsoft.com/fwlink/p/?LinkID=237298">requirements</a>, which can also allow you to have your <a href="">Desktop application listed</a> in the Windows Store. The older <a href="https://docs.microsoft.com/en-us/windows/desktop/DxTechArts/games-for-windows-technical-requirements-1-1-0006"><em>Games for Windows</em> Technical Requirements</a> and <a href="https://docs.microsoft.com/en-us/windows/desktop/DxTechArts/games-for-windows-test-requirements-1-0-0006">Test Requirements</a> documents are still applicable best practices for desktop Win32 games on Windows 8.x. There are some additional things to keep in mind when your game is run on a Windows 8.x machine.

<ul>
 	<li><strong>The Games Explorer UI is not visible</strong>. All games registered with the <em>Game Explorer</em> are surfaced as tiles in the Metro UI, but much of the metadata associated with the title is no longer visible. You still use <a href="https://walbourn.github.io/windows-8-release-preview-and-gdfs/">GDFMaker</a> (latest version is in the <a href="http://go.microsoft.com/fwlink/?LinkID=323507">Windows 8.1 SDK</a> and <a href="https://developer.microsoft.com/en-US/windows/downloads/windows-10-sdk">Windows 10 SDK</a>) to author the data, and use the existing mechanisms for deploying it. Continue to test your GE registration using Windows 7, verify the Start menu tile shows up when installed on Windows 8.x,  and use the <a href="https://github.com/walbourn/directx-sdk-samples/tree/master/GDFTrace">GDF Validator tool</a> to check for known problems with the authored GDF content. <em>Note that on Windows 10 you may find it necessary to create a classic "Start menu shortcut" in addition to using the Game Explorer registration to improve discoverability.</em> [TR 1.1]</li>
</ul>

<ul>
 	<li><strong>Registration with the Game Explorer APIs continues to be the mechanism for registering your game with Windows Parental Controls</strong>. The Windows SDK version of GDFMaker should be run on an up-to-date copy of Windows 7 or Windows 8.x to ensure it can populate all currently supported rating systems. Note that this copy of GDFMaker requires .NET 4.0. The latest version of the Gameux Install Helper sample is available on <a href="https://github.com/walbourn/directx-sdk-samples/tree/master/InstallHelpers/GameuxInstallHelper">GitHub</a>. <em>Note the recent changes to the supported rating systems with <a href="https://walbourn.github.io/windows-8-release-preview-and-gdfs/">Windows 8.x</a> </em>and <em><a href="http://support.microsoft.com/kb/2773072">Windows 7</a> </em>[TR 1.2]</li>
</ul>

<ul>
 	<li><strong>There are now three choices for using the </strong><a href="https://walbourn.github.io/xinput-and-windows-8/"><strong>XINPUT</strong></a><strong> API depending on your requirements</strong>: XINPUT 1.4 is built into Windows 8.x and Windows 10 (useable by both Windows Store apps and desktop Win32 applications), XINPUT 9.1.0 for simplified common-controller usage across all versions of Windows without any redistribution package, and the existing DirectX SDK version XINPUT 1.3 which requires DirectSetup to deploy. [TR 1.4]</li>
</ul>

<ul>
 	<li><strong>High-DPI scenarios are becoming more common</strong>. Be sure to test your application with 125% and 150% scaling, and populate the EXEs manifest with ``<dpiAware>true</dpiAware>``. <em>Windows 8.1 includes a <a href="http://go.microsoft.com/fwlink/p/?LinkID=307061">200% scaling option</a> as well, and the recommended full-screen Direct3D game manifest element is now ``<dpiAware>True/PM</dpiAware>``.  Windows 10 supports up to 500% scaling. </em>[TR 1.8]</li>
</ul>

<ul>
 	<li><strong>Only a limited set of desktop Win32 applications are supported on Windows RT (aka <a href="https://channel9.msdn.com/posts/Building-Windows-for-the-ARM-processor-architecture">Windows on ARM</a>). </strong>Games that run on Windows 7 can and should run correctly on Windows 8.x and Windows 10 x86 and x64 systems. [TR 2.2]</li>
</ul>

<ul>
 	<li><strong>Note that SHA-1 Code Signing Certificates are deprecated</strong>. Use SHA-256 or better certificates. See <a href="https://aka.ms/sha1">Windows Enforcement of Authenticode Code Signing and Timestamping</a> [TR 2.3]</li>
</ul>

<ul>
 	<li><strong>Ensure any OS checks are done correctly.</strong> Windows 8 is version "6.2", and will pass the current 'minimum bar' tests <a href="https://walbourn.github.io/what-s-in-a-version-number/">recommended</a> for game deployment. <em>Windows 8.1 is version "6.3", but note that GetVersion(Ex) APIs are now deprecated and have <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/operating-system-version-changes-in-windows-8-1">new appcompat behavior</a> by default. With Windows 10  VersionVersionInfo has a similar behavior, and the OS has a version of "10.0" (it was "6.4" the early Technical Previews).</em> [TR 2.5]</li>
</ul>

<ul>
 	<li><strong>The "DirectX End-User Redistribution" package will run successfully on Windows 8.x and Windows 10 machines to deploy D3DX9, D3DX10, D3DX11, XINPUT 1.3, XAUDIO 2.7, XACTEngine, etc. as it does on Windows 7. </strong> There is, however, a known issue with DirectSetup on systems with only .NET 4.0 installed due to the deployment handling of the legacy Managed DirectX 1.1 assemblies. This applies to Windows 10, Windows 8.x (which comes with .NET 4.5 by default), and 'fresh' Windows XP systems with the .NET 4.0 runtime installed but not any version of .NET prior to that. While Windows 8.x has an application compatibility behavior to resolve this automatically (which requires network access), we recommend that games continuing to deploy DirectSetup update to the <a href="https://walbourn.github.io/dxsetup-update/">DirectX SDK (June 2010) refreshed version of the REDIST files</a>. As always, be sure to <a href="https://walbourn.github.io/not-so-direct-setup/">understand</a> if you really need to use DirectSetup at all for your title, and if you do trim it down to the minimum required set of CABs. [TR 3.4]</li>
</ul>

<ul>
 	<li><strong>Games that require the .NET "2.0" compatible runtime (2.0, 3.0, 3.5) should continue to use existing deployment mechanisms.</strong> These will trigger an application compatibility behavior on Windows 8.x to enable the .NET 3.5 runtime automatically (which requires network access). However, we recommend that .NET developers move to the .NET 4.0 runtime. <em>Note that the legacy Managed DirectX 1.1 assemblies are not compatible with the .NET 4.x runtime. </em>Also, the .NET 1.1 framework is <a href="http://support.microsoft.com/kb/2489698">not supported</a> on Windows 7, Windows 8.x, or Windows 10. [TR 3.4]</li>
</ul>

<ul>
 	<li><strong>Use of an 'autorunner' or other pre-install technology that relies on .NET is not recommended</strong>. Only .NET 2.0 compatible runtimes can be assumed present on Windows Vista and Windows 7, and only the .NET 4.0 compatible runtime is present on Windows 8.x and Windows 10 by default. [TR 3.7]</li>
</ul>

<ul>
 	<li><strong>There is an updated Application Verifier for Windows 8.</strong> This is included as part of the <a href="http://dev.windows.com/en-us/develop/downloads">Windows 8.x SDK</a> or <a href="https://developer.microsoft.com/en-US/windows/downloads/windows-10-sdk">Windows 10 SDK</a>. It is recommended you test with all the Basics tests including the new COM, Exceptions, Leak, RPC, SRWLock, and Threadpool. [TR 4.2]</li>
</ul>

In addition to the existing Windows 7 best practices, you should review the <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/windows-8-and-windows-server-8-compatibility-cookbook-portal"><em>Windows 8 and Windows Server 2012 Compatibility Cookbook</em></a> for detailed application compatibility notes on various Windows technologies. In particular, you should review the topics

<ul>
 	<li><a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/operating-system-version-changes-in-windows-8-1">Operating system versioning</a></li>
 	<li><a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/application--executable--manifest">App (executable) manifest</a></li>
 	<li><a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/queued-present-model-is-being-deprecated">Queued present model is being deprecated</a></li>
 	<li><a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/pca-scenarios-for-windows-8">Program Compatibility Assistant scenarios for Windows 8</a></li>
 	<li><a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/desktop-window-manager-is-always-on">Desktop Window Manager is always on</a></li>
 	<li><a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/changes-in-dx9-legacy-hardware-support">Changes in DX9 legacy hardware support</a> (as well as a related <a href="https://walbourn.github.io/anatomy-of-direct3d-11-create-device/">post</a>)</li>
 	<li><a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/availability-of-applicable-graphics-drivers-on-windows-update">Availability of applicable graphics drivers on Windows Update</a></li>
 	<li><a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/graphics-driver-migration-to-windows-10">Graphics driver migration to Windows 10</a></li>
</ul>

<h1>Recommendations for desktop Win32 Titles</h1>

In addition to learning about the new Windows Store app model (a.k.a. Metro style apps), here are some important things to consider when creating Windows game titles for Windows 7 and for the desktop of Windows 8.

<ul>
 	<li><strong>Invest in the Direct3D 11 graphics API</strong>. The Direct3D 11 API provides a broad range of hardware support through the 9.x<a href="https://walbourn.github.io/direct3d-feature-levels/"> feature levels</a> on Windows 8, Windows 7, and Windows Vista machines with DirectX 11 installed. Continuing to rely on the legacy Direct3D 9 poses a number of challenges including limited access to debugging support, and limited driver support. <a href="https://docs.microsoft.com/en-us/previous-versions/windows/hardware/cert-program/">Windows 8 Hardware Certification Requirements</a> will ensure that that the majority of desktop form-factor x86/x64 machines will have Feature Level 10.0 or later device support. Windows Store apps must use the Direct3D 11 API and cannot use the Direct3D 9 API.</li>
</ul>

<strong>Windows 10:</strong> <em>Direct3D 12 is also an option for games on Windows 10. Keep in mind updated WDDM 2.0 drivers are required to support Direct3D 12, and only Feature Level 11.0 or better graphics hardware is getting new drivers.</em>

<ul>
 	<li><strong>Minimize or eliminate dependencies on legacy technology.</strong> D3DX9, D3DX10, and D3DX11 are deprecated components. There are a number of recommended replacement technologies that should be used instead: <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a>, <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK</a>, <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a>, <a href="https://walbourn.github.io/directxmesh/">DirectXMesh</a>. XACT is also deprecated. No version of D3DX is supported for Windows Store apps. DirectInput and DirectSound are not available for Windows Store apps or on the Windows RT platform. <em>For a full list of D3DX replacements, see this <a href="https://walbourn.github.io/living-without-d3dx/">post</a>.</em></li>
</ul>

<ul>
 	<li><strong>Minimize or eliminate the dependencies on the "DirectSetup" redistribution package. </strong>"DirectX" technologies are included with the Windows OS, and these are never updated by the use of the "<a href="https://walbourn.github.io/not-so-direct-setup/">DirectX End-User Runtime</a>" packages. Solutions for removing the remaining dependencies exist and should be adopted. The latest D3DCompiler and D3DSCX from the new Windows SDK can be deployed "application local" with desktop applications without requiring a redistribution package. Note these DLLs may not be redistributed with Windows Store apps.</li>
</ul>

<ul>
 	<li><strong>Adopt C++11 compilers, standard libraries, and features</strong>. Visual Studio 2010 and later support modern C++ constructs which can eliminate direct dependences on some legacy APIs, improve the portability of the code, and can provide a bridge to Windows Store apps. See the <a href="https://devblogs.microsoft.com/cppblog/c11-features-in-visual-c-11/">Visual C++ Team Blog</a> for more information. Also be sure to enable compiler security features such as <code>/SAFESEH</code>, <code>/NXCOMPAT</code>, and <code>/DYNAMICBASE</code> which are required for the Windows 8 certifications for both Windows Store apps and Win32 desktop apps.</li>
</ul>

<strong>VS 2015:</strong> Note that Visual C++ 2015 can target Windows Vista SP2, Windows 7 SP1, Windows 8.1, and Windows 10. It does not support targeting Windows 7 RTM or Windows 8.0 which are both out-of-support.

<strong>Update:</strong> This page has been updated on October 25, 2012 for Windows 8 GA (was originally written for Windows 8 Consumer Preview).

<strong>Related:</strong> <a href="https://walbourn.github.io/dual-use-coding-techniques-for-games/">Dual-use Coding Techniques for Games</a>, <a href="https://walbourn.github.io/directx-sdks-of-a-certain-age/">DirectX SDKs of a certain age</a>, <a href="https://walbourn.github.io/manifest-madness/">Manifest Madness</a>
