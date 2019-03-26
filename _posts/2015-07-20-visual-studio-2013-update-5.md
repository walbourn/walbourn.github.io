---
layout: post
title: Visual Studio 2013 Update 5
date: 2015-07-20 12:52
author: Chuck Walbourn
comments: true
categories: [visualc, windowssdk]
---
An update for Visual Studio 2013 is available for <a href="http://go.microsoft.com/fwlink/?LinkId=519378">download</a> as announced today on the <a href="https://devblogs.microsoft.com/visualstudio/visual-studio-2015-and-visual-studio-2013-update-5-released/">Visual Studio blog</a>.
<!--more-->

Official KB article <a href="https://support.microsoft.com/en-us/kb/3021976">3021976</a>.

<h1>Compiler and CRT</h1>

<p>The VS 2013 Update 5 includes a new version of the C++ compiler (18.00.40629.0). There's no new C/C++ Runtime--it still uses CRT version 12.0.21005.1 from VS 2013 RTM--, but there are updated <a href="http://go.microsoft.com/fwlink/?LinkId=519380">remote debugging tools</a> packages.

<strong>Windows SDK: </strong>This includes the <em>Windows 8.1 SDK Spring Update 2015</em> with <a href="https://walbourn.github.io/directxmath-3-07/">DirectXMath 3.07</a>. You can also download the standalone <a href="http://go.microsoft.com/fwlink/?LinkID=323507">Windows 8.1 SDK Spring 2015</a> update.

<strong>Windows 10:</strong> VS 2013 Update 5 will enable the <em>Graphics Tools</em> optional feature required to use the Direct3D debug device on Windows 10. See <a href="https://devblogs.microsoft.com/cppblog/visual-studio-2015-and-graphics-tools-for-windows-10/">this post</a> for details.

<strong>DirectX SDK:</strong> If you need to continue to make use of <a href="https://walbourn.github.io/announcement-directx-sdk-june-2010-is-live/">legacy DirectX SDK</a> components such as D3DX9, D3DX10, D3DX11, or XAudio 2.7 with Visual Studio 2013, see <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">Microsoft Docs</a> for details on mixing the paths correctly. See also <a href="https://walbourn.github.io/directx-sdks-of-a-certain-age/">DirectX SDKs of a certain age</a>, <a href="https://walbourn.github.io/the-zombie-directx-sdk/">The Zombie DirectX SDK</a>, <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a>, <a href="https://walbourn.github.io/directx-sdk-tools-catalog/">DirectX SDK Tools Catalog</a>, and <a href="https://walbourn.github.io/directx-sdk-samples-catalog/">DirectX SDK Samples Catalog</a>

<strong>Related:</strong> <a href="https://walbourn.github.io/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available/">Visual Studio 2013 RTM</a>, <a href="https://walbourn.github.io/visual-studio-2013-update-1/">VS 2013 Update 1</a>, <a href="https://walbourn.github.io/visual-studio-2013-update-2/">VS 2013 Update 2,</a> <a href="https://walbourn.github.io/visual-studio-2013-update-3/">VS 2013 Update 3,</a> <a href="https://walbourn.github.io/visual-studio-2013-update-4/">VS 2013 Update 4</a>
