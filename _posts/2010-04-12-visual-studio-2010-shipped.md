---
layout: post
title: Visual Studio 2010 shipped!
date: 2010-04-12 16:53
author: Chuck Walbourn
comments: true
categories: [visualc]
---
**Visual Studio 2010** launched today. The DirectX SDK team is very excited about this new version because among the many improvements and new technologies for this release (upgraded IDE, C++ 0x supprt, .NET Framework 4.0, Concurrency Runtime, etc.) there were also some significant changes made to the Visual C++ compiler. Anyone using <strong>XNAMath</strong> will greatly benefit from the new compiler as the code-gen for intrinsics have been improved, as well as including a number of important improvements for 64-bit native codegen. I highly recommended you review this Visual Studio team <a href="https://devblogs.microsoft.com/cppblog/visual-c-code-generation-in-visual-studio-2010/">blog</a> for details on the compiler and linker improvements for the new release.
<!--more-->

We are working to fully support Visual Studio 2010 with our upcoming DirectX SDK (June 2010) release. There have been some changes to the way ``INCLUDE`` and ``LIB`` paths are handled as well as some other project setting changes with the move from VSBUILD to MSBUILD, but the overall experience should be a great one. You should be able to get started with VS 2010 and the current DirectX SDK today, but you'll have to convert the project files and change some Project Directory settings to get things to compile. There are two useful VS team blog posts about the <a href="https://devblogs.microsoft.com/cppblog/project-settings-changes-with-vs2010/">project settings</a> changes and <a href="https://devblogs.microsoft.com/cppblog/to-the-command-line-enthusiasts-some-quick-know-hows-for-upgrading-to-vs-2010/">tools</a> available to do project conversions.

As was noted in the DirectX SDK (February 2010) release notes, this means we are no longer officially supporting Visual Studio 2005 with the next DirectX SDK release, although we will be continuing to support VS 2008 as well as adding VS 2010 support. You will likely be able to get some portions of the new DXSDK working with VS 2005 with the help of the latest Windows SDK, but we won't be officially supporting or testing VS 2005. We are also making use of the new Visual Studio-style SAL annotations as well as relying on some intrinsics added for VS 2008 so you will have difficulty compiling with the older compiler.

I'll be posting more details about the upcoming release of the DirectX SDK as they become available.

One thing to note is that the editions for VS 2010 have changed compared to VS 2005 / 2008. There were Express, Standard, Professional and Team System editions for VS 2005 and VS 2008. There are still four versions available, but they are now the Express, Professional, Premium, and Ultimate editions.

<ul>
<li>The 64-bit (x64) native compiler is available with Professional, Premium, and Ultimate.</li>
<li>Profile Guided Optimization (PGO), Static code analysis (``/analyze``), and the Visual Studio Team System profiler are all included with both Premium and Ultimate.</li>
</ul>
