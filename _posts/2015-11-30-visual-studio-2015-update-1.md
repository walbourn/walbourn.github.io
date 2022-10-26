---
layout: msdnpost
title: Visual Studio 2015 Update 1
date: 2015-11-30 12:03
author: Chuck Walbourn
comments: true
categories: [visualc]
---
VS 2015 Update 1 is now available for <a href="http://go.microsoft.com/fwlink/?LinkId=691129">download</a>, including the updated Community edition. The <a href="https://www.microsoft.com/en-us/download/details.aspx?id=49984">VS 2015 Update 1 Redistribution packages</a> are also available (<a href="https://go.microsoft.com/fwlink/?LinkId=615459">x86</a>, <a href="https://go.microsoft.com/fwlink/?LinkId=615460">x64</a>), as well as the Remote Debugging Tools (<a href="https://go.microsoft.com/fwlink/?LinkId=615469">x86</a>, <a href="https://go.microsoft.com/fwlink/?LinkId=615470">x64</a>, <a href="https://go.microsoft.com/fwlink/?LinkId=615471">ARM</a>). For more information, see <a href="https://devblogs.microsoft.com/bharry/vs-2015-update-1-and-tfs-2015-update-1-are-available/">Brian Harry's blog</a>, the <a href="https://devblogs.microsoft.com/cppblog/visual-studio-2015-update-1-is-here/">Visual C++ Team blog</a>, and the <a href="https://devblogs.microsoft.com/visualstudio/visual-studio-update-1-rtm/">Visual Studio Team blog</a>. Be sure to read the <a href="https://docs.microsoft.com/en-us/cpp/porting/visual-cpp-what-s-new-2003-through-2015">Microsoft Docs</a> page as well.
<!--more-->

<em>Per the Visual Studio [support lifecycle](https://docs.microsoft.com/lifecycle/products/visual-studio-2015), "mainstream" support for VS 2015 ended in <b>June 2016</b>. "Extended" support ends <b>October 2025</b>. Platform toolset v140 support is still available in Visual Studio 2019 and Visual Studio 2022 as an optional component.</em>

<h1>Compiler and CRT</h1>

VS 2015 Update 1 includes a new version of the C/C++ compiler (19.00.23506). There is also a new version of the C/C++ Runtime (14.0.23506). Here are a list of <a href="https://devblogs.microsoft.com/cppblog/stl-fixes-in-vs-2015-update-1/">STL fixes</a> included in VS 2015 Update 1. The new compiler also includes support for the C++11 language feature<a href="https://devblogs.microsoft.com/cppblog/partial-support-for-expression-sfinae-in-vs-2015-update-1/"> Expression SFINAE</a>.

Note that VS 2015 can target Windows 10, <a href="https://walbourn.github.io/windows-8-1-update/">Windows 8.1, Windows 8.0</a>, <a href="https://walbourn.github.io/windows-7-service-pack-1/">Windows 7 Service Pack 1</a>, Windows Vista Service Pack 2, and <a href="https://walbourn.github.io/visual-studio-2012-update-1/">optionally Windows XP Service Pack 3</a>. The Visual C++ 2015 REDIST does <strong>not</strong> support Windows 7 RTM, Windows Vista RTM, Windows Vista Service Pack 1, Windows XP RTM, Windows XP Service Pack 1, or Windows XP Service Pack 2 as these platforms are all outside their <a href="http://windows.microsoft.com/en-us/windows/lifecycle">support lifecycle</a>. See <a href="https://support.microsoft.com/en-us/kb/2661358">KB2661358</a>.

<strong>Windows 10 SDK: </strong>VS 2015 Update 1 includes an updated Windows Tools 1.2 with the <a href="https://walbourn.github.io/windows-10-sdk-november-2015/">Windows 10 SDK for Version 1511</a> (10.0.10586). As before, this is an <a href="https://devblogs.microsoft.com/cppblog/developing-for-windows-10-with-visual-c-2015/">optional install</a>.

<strong>.NET:</strong> There is now a <a href="https://devblogs.microsoft.com/dotnet/net-framework-4-6-1-is-now-available/">4.6.1</a> release including a number of Windows Presentation Foundation (WPF) improvements including a D3DImage for Direct3D 11 available on <a href="https://github.com/Microsoft/WPFDXInterop">GitHub</a>.

<strong>Related:</strong> <a href="https://walbourn.github.io/visual-studio-2015-rtm/">Visual Studio 2015 RTM</a>, <a href="https://walbourn.github.io/visual-studio-2015-update-2/">Visual Studio 2015 Update 2</a>, <a href="https://walbourn.github.io/visual-studio-2015-update-3/">Visual Studio 2015 Update 3</a>
