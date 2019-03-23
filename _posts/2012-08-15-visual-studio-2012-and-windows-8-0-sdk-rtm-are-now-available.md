---
layout: post
title: Visual Studio 2012 and Windows 8.0 SDK RTM are now available
date: 2012-08-15 13:40
author: Chuck Walbourn
comments: true
categories: [visualc, win7, win8, windowssdk]
---
The <em>Windows SDK for Windows 8</em> (aka Windows 8.0 SDK) RTM version is now available on <a href="https://developer.microsoft.com/en-us/windows/downloads/sdk-archive">Microsoft Docs</a>. See <a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a> for details on DirectX content in the Windows 8.0 SDK. This includes the <code>D3DCompiler_46.DLL</code> release of the <a href="https://walbourn.github.io/hlsl-fxc-and-d3dcompile/">HLSL compiler</a>, <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a> version 3.03, DirectX 11.1 headers/libs, and the <a href="https://walbourn.github.io/windows-8-release-preview-and-gdfs/">GDF tools</a>.
<!--more-->

The Windows 8.0 SDK is included with Visual Studio 2012 (build 50727.1), which is now available on the web. See the <a href="http://blogs.msdn.com/b/jasonz/archive/2012/08/15/visual-studio-2012-and-net-framework-4-5-released-to-the-web.aspx">Visual Studio</a> and <a href="https://devblogs.microsoft.com/cppblog/visual-c-in-visual-studio-2012/">VC blog</a> announcements for more information, as well as the <a href="http://go.microsoft.com/fwlink/?LinkId=255962">ReadMe</a>.You can find a list of <a href="https://devblogs.microsoft.com/cppblog/compiler-bugs-fixed-in-visual-studio-2012/">compiler bugs fixed,</a> <a href="https://devblogs.microsoft.com/cppblog/stl-bugs-fixed-in-visual-studio-2012/">Standard Library bugs fixed</a>, and <a href="https://devblogs.microsoft.com/cppblog/what-bugs-were-fixed-in-mfc-in-visual-studio-2012/">MFC bugs fixed</a> for Visual Studio 2012 as well. As noted on the VC Blog, support for <a href="https://devblogs.microsoft.com/cppblog/targeting-windows-xp-with-c-in-visual-studio-2012/">targeting Windows XP</a> with VS 2012 and the <a href="https://devblogs.microsoft.com/visualstudio/visual-studio-express-2012-for-windows-desktop/">Desktop Express</a> edition will be coming soon. The Visual C++ 2012 CRT redistributable packages are on <a href="http://www.microsoft.com/en-us/download/details.aspx?id=30679">MS Downloads</a>.

<strong>Update:</strong> <a href="https://devblogs.microsoft.com/visualstudio/visual-studio-express-2012-for-windows-desktop-is-here/">VS 2012 Express for Windows Desktop</a> is now available. Support for Windows XP is available with <a href="https://walbourn.github.io/visual-studio-2012-update-1/">VS 2012 Update 1</a>. See also <a href="https://walbourn.github.io/visual-studio-2012-update-2/">VS 2012 Update 2</a>, <a href="https://walbourn.github.io/visual-studio-2012-update-3/">VS 2012 Update 3</a>, and <a href="https://walbourn.github.io/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available/">VS 2013 and Windows 8.1 SDK RTM</a>.

<strong>System requirements: </strong>The <em>Windows SDK for Windows 8</em> can be installed on Windows 7 and Windows 8. It's the same<a href="https://developer.microsoft.com/en-us/windows/downloads/sdk-archive#Requirements"> system requirements</a> as Visual Studio 2012 which includes the new Windows SDK. You need Windows 8 to develop Windows Store apps, but you can use Windows 7 and the Windows SDK 8.0 for development of Win32 desktop applications for Windows 8, Windows 7, Windows Vista, and their Windows Server equivalents.

<strong>VS 2010 users:</strong> You can use the property sheets as described in the <a href="https://devblogs.microsoft.com/cppblog/using-the-windows-8-sdk-with-visual-studio-2010-configuring-multiple-projects/
">Visual C++ Team blog</a> post to use the Windows 8.0 SDK. The .props files are attached to this post as well. Note you cannot target Windows XP with the Windows 8.0 SDK.

<em>The VS team's instructions omit including the ``include\winrt`` directory under the assumption that those are for Windows Store apps only, but that's not strictly true. At a minimum, having access to ``#include <wrl/client.h>`` provides you the extremely useful ``Microsoft::WRL::ComPtr`` smart-pointer that works perfectly fine in Win32 desktop apps and down-level systems.</em>

<strong>Direct3D Debug support:</strong> Installing VS 2012 or the Windows 8.0 SDK also installs the Direct3D 10.x and Direct3D 11.x <a href="https://walbourn.github.io/direct3d-sdk-debug-layer-tricks/">SDK Debug Layers</a> on Windows 7, Windows 8.0, and the Server Equivalents for using <code>D3Dxx_CREATE_DEVICE_DEBUG</code>. Note that this is not the correct version for Windows 8.1, see <a href="https://walbourn.github.io/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available/">Visual Studio 2013 and Windows 8.1 SDK RTM are now available</a>.

<a href="https://walbourn.github.io/download/Windows8SDK.zip">Windows8SDK.zip</a>
