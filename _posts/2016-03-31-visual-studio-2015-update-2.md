---
layout: post
title: Visual Studio 2015 Update 2
date: 2016-03-31 01:04
author: walbourn
comments: true
categories: [Uncategorized, visualc]
---
VS 2015 Update 2 is now available for <a href="http://go.microsoft.com/fwlink/?LinkId=691129">download</a>, including the updated Community edition. The <a href="https://www.microsoft.com/en-us/download/details.aspx?id=51682">Visual C++ 2015 Update 2 Redistribution packages</a> are also available (<a href="https://go.microsoft.com/fwlink/?LinkId=615459">x86</a>, <a href="https://go.microsoft.com/fwlink/?LinkId=615460">x64</a>), as well as the Remote Debugging Tools (<a href="https://go.microsoft.com/fwlink/?LinkId=615469">x86</a>, <a href="https://go.microsoft.com/fwlink/?LinkId=615470">x64</a>, <a href="https://go.microsoft.com/fwlink/?LinkId=615471">ARM</a>). For more information, see the <a href="https://blogs.msdn.microsoft.com/visualstudio/2016/03/30/visual-studio-2015-update-2-rtm/">Visual Studio Team blog</a>. Be sure to read the <a href="https://msdn.microsoft.com/en-US/library/mt656697(VS.140).aspx">MSDN</a> page as well.
<h1>Compiler and CRT</h1>
VS 2015 Update 2 includes a new version of the C/C++ compiler (19.00.23918). There is also a new version of the C/C++ Runtime (14.0.23918). See these posts for details of the <a href="https://blogs.msdn.microsoft.com/vcblog/2016/02/11/compiler-improvements-in-vs-2015-update-2/">compiler</a> and <a href="https://blogs.msdn.microsoft.com/vcblog/2016/01/22/vs-2015-update-2s-stl-is-c17-so-far-feature-complete/">library</a> improvements, along with this list of <a href="https://blogs.msdn.microsoft.com/vcblog/2016/03/31/visual-c-2015-update-2-bug-fixes/">bug fixes</a>.

<strong>Windows 10 SDK:</strong> VS 2015 Update 2 includes Windows Tools 1.3 with the <a href="http://blogs.msdn.com/b/chuckw/archive/2015/11/30/windows-10-sdk-november-2015.aspx">Windows 10 SDK for Version 1511</a> (10.0.10586). As before, this is an <a href="http://blogs.msdn.com/b/vcblog/archive/2015/07/29/developing-for-windows-10-with-visual-c-2015.aspx">optional install</a>. The new Windows Tools 1.3 also adds a UI dialog when creating new UWP projects that prompts for which version of the Windows 10 SDK to use. Note that this same dialog is triggered when using my <a href="https://blogs.msdn.microsoft.com/chuckw/2015/12/17/direct3d-game-visual-studio-templates-redux/">Direct3D 12 Win32 Game </a>templates--the <em>minimum version</em> value is not used in Win32 projects.

<strong>Visual C++ Build Tools 2015: </strong>There is a <a href="https://blogs.msdn.microsoft.com/vcblog/2016/03/31/announcing-the-official-release-of-the-visual-c-build-tools-2015/">new edition</a> of Visual Studio available without the IDE for those just looking for the compiler toolset.

<strong>Related:</strong> <a href="https://blogs.msdn.microsoft.com/chuckw/2015/07/24/visual-studio-2015-rtm/">Visual Studio 2015 RTM</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2015/11/30/visual-studio-2015-update-1/">Visual Studio 2015 Update 1</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2016/06/27/visual-studio-2015-update-3/">Visual Studio 2015 Update 3</a>
