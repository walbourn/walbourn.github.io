---
layout: post
title: Windows 10 Creators Update SDK
date: 2017-04-06 06:03
author: Chuck Walbourn
comments: true
categories: [uwp, visualc, win10, windowssdk]
---

The <a href="https://blogs.windows.com/buildingapps/2017/04/05/windows-10-creators-update-creators-update-sdk-released/">Windows 10 Creators Update</a> (a.k.a. Version 1703) is now available along with a new <a href="https://blogs.windows.com/buildingapps/2017/04/05/updating-tooling-windows-10-creators-update/">Windows 10 SDK</a> release. The <em>Windows 10 Creators Update SDK</em> (10.0.15063) can be installed via <a href="https://devblogs.microsoft.com/visualstudio/visual-studio-2017-update/">VS 2017 (15.1)</a> or as a <a href="https://go.microsoft.com/fwlink/p/?linkid=845298">standalone installer</a>. This includes <a href="https://walbourn.github.io/directxmath-3-10/">DirectXMath 3.10</a> and updated versions of <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d12/new-releases#windows_10__version_1703">Direct3D 12</a>, DXGI 1.6, <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/direct3d-11-4-features">Direct3D 11.4</a> <a href="https://docs.microsoft.com/en-us/windows/desktop/Direct2D/what-s-new-in-direct2d-for-windows-8-consumer-preview">Direct2D</a>, and <a href="https://docs.microsoft.com/en-us/windows/desktop/DirectWrite/what-s-new-in-directwrite-for-windows-8-consumer-preview">DirectWrite</a>. See <a href="https://docs.microsoft.com/en-us/windows/uwp/whats-new/windows-10-build-15063">What's New in Windows 10 for developers, build 15063</a>.
<!--more-->

<h1>Visual Studio 2017 (15.1/15.2 Updates)</h1>

You can install the new Windows 10 SDK by installing the latest VS 2017 update (<a href="https://devblogs.microsoft.com/visualstudio/visual-studio-2017-update/">15.1</a>, <a href="https://devblogs.microsoft.com/visualstudio/update-to-visual-studio-2017-and-next-preview/">15.2</a>, or later). The new Windows 10 SDK  (15063) is actually three distinct components: <code>Microsoft.VisualStudio.Component.Windows10SDK.15063.Desktop</code>, <code>Microsoft.VisualStudio.Component.Windows10SDK.15063.UWP</code>, and <code>Microsoft.VisualStudio.Component.Windows10SDK.15063.UWP.Native</code>.

The <em>Windows 10 Creators Update SDK</em> resolves a number of conformance errors in Windows system headers enabling the use of the <a href="https://devblogs.microsoft.com/cppblog/permissive-switch/"><code>/permissive-</code> switch</a>.

<strong>VS 2015 Users:</strong> The Windows 10 SDK (15063) is officially only supported for <a href="https://walbourn.github.io/visual-studio-2017/">VS 2017</a>.

<strong>FXC:</strong> With the Windows 10 SDK (15063), the FXC compiler and the <code>D3DCompiler_47.DLL</code> were made side-by-side. From the Developer Command Prompt for VS 2017, using FXC will use the Windows 10 Anniversary Update (14393) version. You need to explicitly select the side-by-side version if you want to use a newer one from the command-line: ``"%WindowsSdkBinPath%%WindowsSDKVersion%\x86\fxc.exe"``

<strong>Related:</strong> <a href="https://walbourn.github.io/windows-10-sdk-rtm/">Windows 10 SDK RTM</a>, <a href="https://walbourn.github.io/windows-10-sdk-november-2015/">Windows 10 SDK (November 2015)</a>, <a href="https://walbourn.github.io/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK</a>
