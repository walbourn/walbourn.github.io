---
layout: msdnpost
title: Visual Studio 2012 Release Candidate
date: 2012-05-31 15:59
author: Chuck Walbourn
comments: true
categories: [dxsdk, visualc]
---
The <a href="http://www.microsoft.com/visualstudio/11/en-us/downloads">Visual Studio 2012 Release Candidate</a> (formerly known as "Visual Studio 11") is now available including all editions: Express, Professional, Premium, and Ultimate. See the <a href="http://blogs.msdn.com/b/jasonz/archive/2012/05/31/announcing-the-release-candidate-rc-of-visual-studio-2012-and-net-framework-4-5.aspx">Visual Studio blog</a> entry for more information. As with the <a href="https://walbourn.github.io/visual-studio-11-beta/">Visual Studio 11 Beta</a>, this release includes a new C++ compiler, Standard Library with <a href="https://devblogs.microsoft.com/cppblog/c11-features-in-visual-c-11/">C++11</a> support, a <a href="https://devblogs.microsoft.com/cppblog/game-debugging-in-visual-studio-11/">graphics debugger</a>, and integrated HLSL compiler. There's a nice <a href="https://devblogs.microsoft.com/cppblog/c-build-throughput-visual-studio-11-pre-release-compared-to-visual-studio-2010-sp1/">write-up</a> on the performance of the new compiler and build system as well.
<!--more-->

The Visual Studio 2012 RC includes the <i>Windows SDK for <a href="https://walbourn.github.io/windows-8-release-preview-and-gdfs/">Windows 8 Release Preview</a></i> (which is also available as a <a href="https://developer.microsoft.com/en-us/windows/downloads/sdk-archive">standalone</a> package for use with Visual Studio 2010). This release of the Windows SDK integrates many aspects of the DirectX SDK (see <a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a>) including <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a> version 3.03, the RC version of DirectX 11.1 headers, <a href="https://walbourn.github.io/hlsl-fxc-and-d3dcompile/">D3DCompiler_45.DLL</a>, D3DCSX_45.DLL, the latest GDFMaker.EXE, and the DirectX Capabilities Viewer utility.

<strong>Update:</strong> The Visual C++ team <a href="https://devblogs.microsoft.com/cppblog/targeting-windows-xp-with-c-in-visual-studio-2012/">announced</a> they will be adding support to VS 2012 to target Windows XP, which is currently not supported by VS 2012 RC. The Windows 8.0 SDK included with VS 2012 does not support Windows XP, so developers will need to install and use the system headers/libraries from the <a href="https://walbourn.github.io/windows-sdk-7-1/">Windows 7.1 SDK</a>.

<strong>Windows 7 users: </strong>When looking for Win32 desktop samples on <a href="http://code.msdn.microsoft.com/">MSDN Code Gallery</a>, be sure to filter by "Desktop" as the platform and "Win32" as the technology. If you just select "Desktop" you'll see a lot of Windows Store apps as well as Win32 desktop apps. Windows Store apps will not <em>build</em> or <em>run</em> on Windows 7. If you are looking for a 'starting template', just use the standard Win32 Project (under Templates \ Visual C++ \ Win32). You can cut & paste code in from the <a href="http://code.msdn.microsoft.com/Direct3D-Tutorial-Win32-829979ef">Win32 version of the Direct3D 11 tutorials</a>, and use DirectXMath, Direct3D, D3DCompiler, etc. from there. You only need to do editing of VC++ Directory settings if you are trying to mix the Windows 8.0 SDK with the legacy DirectX SDK to use XAUDIO 2.7, XINPUT 1.3, XACT, or D3DX.

<strong>RTM:</strong> The Visual Studio team has announced the final build of VS 2012 is now ready. It will be available to MSDN subscribers August 15th along with Windows 8 RTM.

<h1>Auto-vectorization</h1>

The Visual Studio 2012 RC supports new optimization features enabled with the <code>/O2</code> and <code>/Ox</code> optimization levels. More details are available on <a href="https://devblogs.microsoft.com/cppblog/auto-vectorization-on-channel9/">Channel 9</a>.

<h1>Security Features</h1>

Visual Studio 2012 RC includes a new <code>/sdl</code> command-line switch and some enhancements to the <code>/gs</code> switch, as well as support for <code>/analyze</code> in all editions.
