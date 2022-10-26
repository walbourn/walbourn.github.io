---
layout: msdnpost
title: Visual Studio 2015 Update 3
date: 2016-06-27 19:05
author: Chuck Walbourn
comments: true
categories: [visualc]
---
VS 2015 Update 3 is now available for <a href="http://go.microsoft.com/fwlink/?LinkId=691129">download</a>, including the updated Community edition. The Visual C++ 2015 Update 3 Redistribution packages are also available (<a href="https://go.microsoft.com/fwlink/?LinkId=615459">x86</a>, <a href="https://go.microsoft.com/fwlink/?LinkId=615460">x64</a>), as well as the Remote Debugging Tools (<a href="https://go.microsoft.com/fwlink/?LinkId=615469">x86</a>, <a href="https://go.microsoft.com/fwlink/?LinkId=615470">x64</a>, <a href="https://go.microsoft.com/fwlink/?LinkId=717854">ARM</a>). For more information see the <a href="https://devblogs.microsoft.com/visualstudio/visual-studio-2015-update-3-and-net-core-1-0-available-now/">release notes</a>.
<!--more-->

<em>Note that Update 3 is the last  update for VS 2015. Per the Visual Studio [support lifecycle](https://docs.microsoft.com/lifecycle/products/visual-studio-2015),  "mainstream" support for VS 2015 ended in <b>June 2016</b>. "Extended" support ends <b>October 2025</b>. Platform toolset v140 support is still available in Visual Studio 2019 and Visual Studio 2022 as an optional component.</em>

<strong>Update: </strong>See the <a href="https://docs.microsoft.com/en-us/cpp/porting/visual-cpp-porting-and-upgrading-guide?view=vs-2015">Visual C++ Porting and Upgrading Guide</a> and the <a href="https://github.com/Microsoft/VCSamples">VC++ Samples GitHub</a>.

<h1>Compiler and CRT</h1>

VS 2015 Update 3 includes a new version of the C/C++ compiler (19.00.24215.1 with the latest <a href="https://docs.microsoft.com/en-us/previous-versions/mt752379(v=vs.140)">hot-fixes </a>applied). There is also a new version of the C/C++ Runtime (14.0.24212). See these posts for details about the <a href="https://devblogs.microsoft.com/cppblog/compiler-improvements-in-vs-2015-update-3-rc/">compiler</a>, <a href="https://devblogs.microsoft.com/cppblog/new-code-optimizer/">optimizer</a>, <a href="https://devblogs.microsoft.com/cppblog/stl-fixes-in-vs-2015-update-3/">libraries</a>, and <a href="https://devblogs.microsoft.com/cppblog/standards-version-switches-in-the-compiler/">standards compliance</a> including <a href="https://devblogs.microsoft.com/cppblog/expression-sfinae-improvements-in-vs-2015-update-3/">expression SFINAE</a>.

<strong>Windows 10 SDK: </strong>VS 2015 Update 3 includes new Windows Tools 1.4 with the <a href="https://walbourn.github.io/windows-10-sdk-november-2015/">Windows 10 SDK for Version 1511 </a>(10.0.10586). As before, this is an <a href="https://devblogs.microsoft.com/cppblog/developing-for-windows-10-with-visual-c-2015/">optional install</a>.

<strong>Visual C++ Build Tools 2015: </strong>There is an <a href="http://go.microsoft.com/fwlink/?LinkId=691126"><span style="color: #337ab7">edition</span></a> of Visual Studio available without the IDE for those just looking for the compiler toolset.

<strong>Related:</strong> <a href="https://walbourn.github.io/visual-studio-2015-rtm/">Visual Studio 2015 RTM</a>, <a href="https://walbourn.github.io/visual-studio-2015-update-1/">Visual Studio 2015 Update 1</a>, <a href="https://walbourn.github.io/visual-studio-2015-update-2/">Visual Studio Update 2</a>
