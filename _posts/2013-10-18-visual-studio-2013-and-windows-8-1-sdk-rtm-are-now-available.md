---
layout: msdnpost
title: Visual Studio 2013 and Windows 8.1 SDK RTM are now available
date: 2013-10-18 13:59
author: Chuck Walbourn
comments: true
categories: [visualc, win8, windowssdk]
---
<a href="http://go.microsoft.com/fwlink/?LinkId=306566">Visual Studio 2013 RTM</a> is now available. The <a href="http://www.microsoft.com/en-us/download/details.aspx?id=40784">VS 2013 RTM Redistribution packages</a> are also available (<a href="http://go.microsoft.com/?linkid=9832156">x86</a>, <a href="http://go.microsoft.com/?linkid=9832146">x64</a>, <a href="http://go.microsoft.com/?linkid=9832136">ARM</a>), as well as the <a href="http://www.microsoft.com/en-us/download/details.aspx?id=40781">Remote Debugging Tools</a> (<a href="http://go.microsoft.com/?linkid=9832075">x86</a>, <a href="http://go.microsoft.com/?linkid=9832085">x64</a>, <a href="http://go.microsoft.com/?linkid=9832095">ARM</a>). For more information, see the <a href="https://devblogs.microsoft.com/cppblog/visual-studio-2013-available-now/">Visual C++ team blog</a>, <a href="https://devblogs.microsoft.com/somasegar/visual-studio-2013-available-for-download/">Somasegar's blog</a>, and the <a href="https://devblogs.microsoft.com/visualstudio/visual-studio-2013-released-to-web/">Visual Studio team blog</a>.
<!--more-->

VS 2013 RTM includes the <em>Windows Software Development Kit (SDK) for Windows 8.1 (October 2013)</em>, which is also available <a href="http://go.microsoft.com/fwlink/?LinkID=323507">standalone</a>. This includes <a href="https://walbourn.github.io/directxmath-3-06/">DirectXMath 3.06</a>, <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/direct3d-11-2-features">Direct3D 11.2</a>/<a href="https://docs.microsoft.com/en-us/windows/desktop/direct3ddxgi/dxgi-1-3-improvements>DXGI 1.3</a>/<a href="https://docs.microsoft.com/en-us/windows/desktop/Direct2D/what-s-new-in-direct2d-for-windows-8-consumer-preview">Direct2D 1.2</a>/DirectWrite 1.2 headers for Windows 8.1, <a href="https://walbourn.github.io/hlsl-fxc-and-d3dcompile/">D3DCompiler #47</a>, and the <a href="https://walbourn.github.io/direct3d-sdk-debug-layer-tricks/">Direct3D Debug Runtime for Windows 8.1</a>. This includes an update of **GDFMaker** with some minor bugs fixes, and a few more caps detection features in **DxCapsViewer** as well.

Today is also <a href="https://blogs.windows.com/windowsexperience/2013/10/17/windows-8-1-now-available/">Windows 8.1</a> and <a href="https://cloudblogs.microsoft.com/windowsserver/2013/10/18/announcing-the-general-availability-of-windows-server-2012-r2-the-heart-of-cloud-os/">Windows Server 2012 R2</a> GA (build 9600). Might be a good time to review and <a href="https://walbourn.github.io/manifest-madness/">Manifest Madness</a>, <a href="https://walbourn.github.io/desktop-games-on-windows-8-x">Desktop Games on Windows 8.x</a>, and the latest <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/windows-8-and-windows-server-8-compatibility-cookbook-portal">AppCompat Cookbook</a>.

<strong>Related:</strong> <a href="https://aka.ms/dxsdk">Where is the DirectX SDK (2021 Edition)?</a>, <a href="https://walbourn.github.io/visual-studio-2013-release-candidate/">Visual Studio 2013 RC</a>, <a href="https://walbourn.github.io/visual-studio-2012-and-windows-8-0-sdk-rtm-are-now-available/">VS 2012 and Windows 8.0 SDK RTM</a>

<strong>Windows XP developers:</strong> as with VS 2012, the "v120_xp" platform toolset in VS 2013 uses a version of the Windows 7.1 SDK, not Windows 8.x SDK. See <a href="https://walbourn.github.io/visual-studio-2012-update-1/">Visual Studio 2012 Update 1</a>.

<strong>Windows 7 users:</strong> VS 2013 originally required IE10 be installed which requires <a href="http://support.microsoft.com/kb/2670838">KB 2670838</a> (<a href="https://walbourn.github.io/directx-11-1-and-windows-7-update/">DirectX 11.1 and Windows 7 Update</a> and <a href="https://walbourn.github.io/directx-11-1-and-windows-7/">DirectX 11.1 and Windows 7</a>). The VS 2013 setup has been refreshed and no longer requires IE10 be installed. KB 2670838 and IE10 are still recommended as there are a number of known issues on Windows 7 if they are not present (see <a href="http://go.microsoft.com/fwlink/?LinkID=330043">KB 2906882</a>) some of which are addressed with <a href="https://walbourn.github.io/visual-studio-2013-update-1/">VS 2013 Update 1</a>.

<strong>Windows 8 users:</strong> If you upgrade to Windows 8.1, remember that all attempts to use ``D3Dxx_CREATE_DEVICE_DEBUG`` will fail until you upgrade the Developer Runtime. You can do this by installing VS 2013, the standalone Windows 8.1 SDK, or by installing the VS 2013 Remote Debugging Tools. If you are missing the updated SDK Debug Layers, you should see the following message in your debug output:

```
D3D11CreateDevice: Flags (0x2) were specified which require the D3D11 SDK Layers for Windows 8.1, but they are not present on the system.
These flags must be removed, or the Windows 8.1 SDK must be installed.
```

<strong>DirectX SDK users:</strong> Using the legacy <em>DirectX SDK (June 2010)</em> with VS 2013 is the same as it was using it with VS 2012. See <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">Microsoft Docs</a>.

<strong>Express users: </strong>VS 2013 Express for Windows edition include Graphics Diagnostics (aka VS PIX) and the Visual Studio content tools. These are not included with the VS 2013 Express for Windows Desktop edition.

<strong>VS 2010/2012 users:</strong> You can use the property sheet technique for the Windows 8.1 SDK that was described in this <a href="https://devblogs.microsoft.com/cppblog/using-the-windows-8-sdk-with-visual-studio-2010-configuring-multiple-projects/">Visual C++ Team blog post</a> originally for VS 2010+Windows 8.0 SDK. For VS 2010, just change the part of the paths with "8.0"/"win8" to "8.1"/"winv6.3" but otherwise use all those instructions. For VS 2012, you can simplify all the paths to just add the 8.1 paths before the existing value for each variable. The updated .props are attached to this blog post. This should only be used for Win32 desktop application development. Windows Store apps should use VS 2013 with the Windows 8.1 SDK. Note you cannot target Windows XP with the Windows 8.1 SDK.

<em>The VS team's instructions omit including the "include\winrt" directory under the assumption that those are for Windows Store apps only, but that's not strictly true. At a minimum, having access to ``#include <wrl/client.h>`` provides you the extremely useful ``Microsoft::WRL::ComPtr`` smart-pointer that works perfectly fine in Win32 desktop apps and down-level systems.</em>

<strong>Windows Store app developers</strong>: Remember if writing Windows Store apps for Windows 8.1, you must use the VS 2013 toolset, the Windows 8.1 SDK, and the Windows 8.1 OS. You can optionally install the VS 2012 toolset and Windows 8.0 SDK as part of your VS 2013 setup (called "Tools for Maintaining Store apps for Windows 8" in the optional features list) to maintain Windows Store apps for Windows 8.0. You cannot install VS 2013 on the Windows 8.0 OS to build Windows Store apps for Windows 8.1. None of these restrictions apply to Win32 desktop development.

<strong>Update:</strong> Refreshed the attached ``.props`` with some fixes on October 21, 2013. There are new releases of <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a>, <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK</a>, <a href="http://go.microsoft.com/fwlink/p/?LinkId=271568">Effects 11</a>, and <a href="http://go.microsoft.com/fwlink/?LinkId=320437">DXUT for Direct3D 11</a> with support for VS 2013 / Windows 8.1 SDK available as well.

<strong>Related:</strong> <a href="https://walbourn.github.io/visual-studio-2013-update-1/">Visual Studio 2013 Update 1</a>, <a href="https://walbourn.github.io/visual-studio-2013-update-2/">VS 2013 Update 2</a>, <a href="https://walbourn.github.io/visual-studio-2013-update-3/">VS 2013 Update 3</a>, <a href="https://walbourn.github.io/visual-studio-2013-update-4/">VS 2013 Update 4</a>, <a href="https://walbourn.github.io/visual-studio-2013-update-5/">VS 2013 Update 5</a>, <a href="https://walbourn.github.io/direct3d-game-visual-studio-templates-redux/">Direct3D Game Visual Studio templates (Redux)</a>

<a href="https://walbourn.github.io/download/Windows81SDK.zip">Windows81SDK.zip</a>
