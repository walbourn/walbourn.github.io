---
layout: post
title: Visual Studio 2013 Update 3
date: 2014-08-04 22:10
author: Chuck Walbourn
comments: true
categories: [visualc, win8, windowssdk]
---
An update to Visual Studio 2013 is now available for <a href="http://go.microsoft.com/fwlink/p/?LinkId=390465">download</a>.
<!--more-->

For more details see <a href="https://devblogs.microsoft.com/visualstudio/visual-studio-2013-update-3-rtm-available/">Visual Studio Team Blog</a>, <a href="https://devblogs.microsoft.com/bharry/vstfs-2013-3-update-3-released/
">Brian Harry's blog</a>, and <a href="https://devblogs.microsoft.com/somasegar/visual-studio-2013-update-3-azure-sdk-2-4-windows-phone-8-1-update-and-apache-cordova-tools-ctp-2/">Somasegar's blog</a>.

Official KB article <a href="http://support.microsoft.com/kb/2933779/">2933779</a>. There's also a list of <a href="https://devblogs.microsoft.com/cppblog/bugs-fixed-in-visual-studio-2013-update-3/">bugs fixed</a> for this release.

<h1>Compiler and CRT</h1>

VS 2013 Update 3 includes a new version of the C++ compiler (18.00.30723.0). There's no new C/C++ Runtime--it still uses CRT version 12.0.21005.1 from VS 2013 RTM), but there are updated <a href="http://go.microsoft.com/fwlink/?LinkId=402291">remote debugging tools</a> packages.

<strong>Windows SDK: </strong>VS 2013 Update 3 includes the <a href="https://docs.microsoft.com/en-us/previous-versions/windows/desktop/whatsnew/windows-8-technologies#windows_8.1_update_api_notes">April 2014</a> refresh of the Windows 8.1 SDK for the <a href="https://walbourn.github.io/windows-8-1-update/">Windows 8.1 Update</a>.

<strong>Windows phone: </strong>The Windows Phone 8.1 Update emulators are now also available for <a href="http://www.microsoft.com/en-us/download/details.aspx?id=43719">download</a>.

<strong>VS Graphics Diagnostics:</strong> See this <a href="https://devblogs.microsoft.com/cppblog/graphics-diagnostics-in-visual-studio-2013-update-3-rc/">article</a> for details. See also KB <a href="http://support.microsoft.com/kb/2955817/">2955817</a>.

<strong>Improved optimized debugging: </strong>The <code>/Zo</code> switch is now officially supported. See <a href="http://randomascii.wordpress.com/2013/09/11/debugging-optimized-codenew-in-visual-studio-2012/">Bruce Dawson's blog</a> for the gory details.

<strong>Related:</strong> <a href="https://walbourn.github.io/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available/">Visual Studio 2013 RTM</a>, <a href="https://walbourn.github.io/visual-studio-2013-update-1/">VS 2013 Update 1</a>, <a href="https://walbourn.github.io/visual-studio-2013-update-2/">VS 2013 Update 2</a>, <a href="https://walbourn.github.io/visual-studio-2013-update-4/">VS 2013 Update 4</a>, <a href="https://walbourn.github.io/visual-studio-2013-update-5/">VS 2013 Update 5</a>
