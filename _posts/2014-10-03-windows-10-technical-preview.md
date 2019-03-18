---
layout: post
title: Windows 10 Technical Preview
date: 2014-10-03 11:00
author: Chuck Walbourn
comments: true
categories: [win10]
---
The next version of Windows is now available as a Technical Preview for developers via the **Windows Insiders** program and for MSDN Subscribers. For more details, see <a href="https://blogs.windows.com/windowsexperience/2014/09/30/announcing-windows-10/">Announcing Windows 10</a>.
<!--more-->

<strong>DirectX SDK Debug Layer: </strong>For Windows 10 Technical Preview (<a href="https://blogs.windows.com/windowsexperience/2015/01/23/january-build-now-available-to-the-windows-insider-program/
">9926</a> or later), you need to enable the debug layer as a Windows optional feature to successfully use <code>D3D11_CREATE_DEBUG_DEVICE</code> or the Visual Studio 2013 Graphics Diagnostics tools: Start -> Settings -> System -> Optional features -> Add a feature; select "Graphics Tools". See <a href="https://devblogs.microsoft.com/cppblog/visual-studio-2015-and-graphics-tools-for-windows-10/">this post</a> for details.

<strong>Win32 desktop games:</strong> The existing guidance for quality Win32 desktop games running on Windows 7, Windows 8.0, and Windows 8.1 all applies to Windows 10 as well (see <a href="https://walbourn.github.io/desktop-games-on-windows-8-x">Desktop Games on Windows 8.x</a>). Note that there is a new ``<compatibility>`` manifest section GUID for Windows 10 (see <a href="https://walbourn.github.io/manifest-madness/">Manifest Madness</a>), and <code>VerifyVersionInfo</code> is now subject to the same manifest-based behavior as <code>GetVersion(Ex)</code>.

<strong>DirectX 12:</strong> If you are looking to try out DirectX 12, you should read the <a href="https://devblogs.microsoft.com/directx/directx-12-and-windows-10/">DirectX Developer Blog</a> post and sign up for the DirectX 12 **Early Access** program.

<strong>Enterprise:</strong> If you are curious about the business version of Windows 10, see this <a href="https://www.microsoft.com/en-us/microsoft-365/blog/2014/09/30/introducing-windows-10-for-business/">post</a>.

<strong>Web developers:</strong> The Technical Preview includes IE11, but there are a few <a href="https://blogs.msdn.microsoft.com/ie/2014/10/01/internet-explorer-and-the-windows-10-technical-preview/">improvements</a> for Windows 10.

<strong>Windows Store and Windows phone developers:</strong> See this <a href="https://blogs.windows.com/buildingapps/2014/09/30/universal-windows-apps-get-better-with-windows-10/">post</a>.

<strong>Command Prompt:</strong> There's some fun features added for Windows 10's command prompt. See this <a href="https://blogs.msdn.microsoft.com/winsdk/2014/10/02/windows-10-threshold-changes-to-the-windows-command-prompt/">post</a>.
