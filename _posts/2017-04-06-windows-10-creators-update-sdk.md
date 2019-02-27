---
layout: post
title: Windows 10 Creators Update SDK
date: 2017-04-06 06:03
author: walbourn
comments: true
categories: [Uncategorized, uwp, visualc, win10, windowssdk]
---
The <a href="https://blogs.windows.com/buildingapps/2017/04/05/windows-10-creators-update-creators-update-sdk-released/">Windows 10 Creators Update</a> (a.k.a. Version 1703) is now available along with a new <a href="https://blogs.windows.com/buildingapps/2017/04/05/updating-tooling-windows-10-creators-update/">Windows 10 SDK</a> release. The <em>Windows 10 Creators Update SDK</em> (10.0.15063) can be installed via <a href="https://blogs.msdn.microsoft.com/visualstudio/2017/04/05/visual-studio-2017-update/">VS 2017 (15.1)</a> or as a <a href="https://go.microsoft.com/fwlink/p/?linkid=845298">standalone installer</a>. This includes <a href="https://blogs.msdn.microsoft.com/chuckw/2017/04/06/directxmath-3-10/">DirectXMath 3.10</a> and updated versions of <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/mt748631(v=vs.85).aspx#windows_10__version_1703">Direct3D 12</a>, DXGI 1.6, <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/mt661819.aspx">Direct3D 11.4</a> <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/hh802478.aspx">Direct2D</a>, and <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/hh802480.aspx">DirectWrite</a>. See <a href="https://docs.microsoft.com/en-us/windows/uwp/whats-new/windows-10-build-15063">What's New in Windows 10 for developers, build 15063</a>.
<h1>Visual Studio 2017 (15.1/15.2 Updates)</h1>
You can install the new Windows 10 SDK by installing the latest VS 2017 update (<a href="https://blogs.msdn.microsoft.com/visualstudio/2017/04/05/visual-studio-2017-update/">15.1</a>, <a href="https://blogs.msdn.microsoft.com/visualstudio/2017/05/10/update-to-visual-studio-2017-and-next-preview/">15.2</a>, or later). The new Windows 10 SDK  (15063) is actually three distinct components: <code>Microsoft.VisualStudio.Component.Windows10SDK.15063.Desktop</code>, <code>Microsoft.VisualStudio.Component.Windows10SDK.15063.UWP</code>, and <code>Microsoft.VisualStudio.Component.Windows10SDK.15063.UWP.Native</code>.

The <em>Windows 10 Creators Update SDK</em> resolves a number of conformance errors in Windows system headers enabling the use of the <a href="https://blogs.msdn.microsoft.com/vcblog/2016/11/16/permissive-switch/"><code>/permissive-</code> switch</a>.

<strong>VS 2015 Users:</strong> The Windows 10 SDK (15063) is officially only supported for <a href="https://blogs.msdn.microsoft.com/chuckw/2017/03/07/visual-studio-2017/">VS 2017</a>.

<strong>FXC:</strong> With the Windows 10 SDK (15063), the FXC compiler and the <code>D3DCompiler_47.DLL</code> were made side-by-side. From the Developer Command Prompt for VS 2017, using FXC will use the Windows 10 Anniversary Update (14393) version. You need to explicitly select the side-by-side version if you want to use a newer one from the command-line: <code>"%WindowsSdkBinPath%%WindowsSDKVersion%\x86\fxc.exe"</code>

<strong>Related:</strong> <a href="https://blogs.msdn.microsoft.com/chuckw/2015/07/30/windows-10-sdk-rtm/">Windows 10 SDK RTM</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2015/11/30/windows-10-sdk-november-2015/">Windows 10 SDK (November 2015)</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2016/08/02/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK</a>
