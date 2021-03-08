---
layout: msdnpost
title: DirectX 11.1 and Windows 7
date: 2012-11-13 16:34
author: Chuck Walbourn
comments: true
categories: [directx, dxsdk, pixw, win7]
---
Windows 8 includes an updated "DirectX 11.1 Runtime" that supports <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/direct3d-11-1-features">Direct3D 11.1</a>, updates <a href="https://docs.microsoft.com/en-us/windows/desktop/Direct2D/what-s-new-in-direct2d-for-windows-8-consumer-preview">Direct2D</a> and <a href="https://docs.microsoft.com/en-us/windows/desktop/DirectWrite/what-s-new-in-directwrite-for-windows-8-consumer-preview">DirectWrite</a>, <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3ddxgi/dxgi-1-2-improvements">DXGI 1.2</a>, and a revision of the <a href="https://docs.microsoft.com/en-us/previous-versions//hh994467(v=vs.85)">Windows Imaging Component (WIC)</a>.
<!--more-->

Portions of the "DirectX 11.1 Runtime" are being made available on <a href="https://walbourn.github.io/windows-7-service-pack-1/">Windows 7 Service Pack 1</a> via the <em>Platform Update for Windows 7 Service Pack 1 and Windows Server 2008 R2 Service Pack 1</em> (KB 2670838) included with <em>Internet Explorer 10 for Windows 7</em>. This includes the updated components above, but is limited to WDDM 1.1 drivers on Windows 7.

Full technical details on what is and is not included in the update are available on <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3darticles/platform-update-for-windows-7">Microsoft Docs</a>. For information about IE10 compatibility, see this <a href="https://docs.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/dev-guides/jj819730(v=vs.85)">article</a>.

<strong>Note:</strong> KB 2670838 does not include XINPUT 1.4 or XAudio 2.8 on Windows 7. These remain Windows 8 or later only. See <a href="https://walbourn.github.io/xinput-and-windows-8/">XINPUT and Windows 8</a> and <a href="https://walbourn.github.io/xaudio2-and-windows-8/">XAudio2 and Windows 8</a> for guidance on handling this difference in Win32 desktop applications.

<strong>Update:</strong> <a href="http://support.microsoft.com/kb/2670838">KB 2670838</a> and <a href="https://blogs.msdn.microsoft.com/ie/2013/02/26/ie10-for-windows-7-globally-available-for-consumers-and-businesses/">Internet Explorer 10 for Windows 7</a> are now available. Users with the prerelease version installed should <a href="http://www.microsoft.com/en-us/download/details.aspx?id=36805">update</a> their systems (<a href="https://walbourn.github.io/directx-11-1-and-windows-7-update/">DirectX 11.1 and Windows 7 Update</a>).

<h1>Notes for users of the DirectX SDK</h1>

The updated headers and link libraries needed to target the new components on Windows 8 and Windows 7 are in the Windows 8.x SDK as indicated in previous posts (see <a href="https://aka.ms/dxsdk">Where is the DirectX SDK?</a>). See <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">Microsoft Docs</a> for details on 'mixing' the Windows 8.x SDK and legacy DirectX SDK if needed.

It is also important to note that the updated "<a href="https://walbourn.github.io/direct3d-sdk-debug-layer-tricks/">Debug Runtime</a>" components in the Windows 8.x SDK are required on Windows 7 once KB 2670838 is installed. The legacy <em>DirectX SDK (June 2010)</em> "Debug Runtime" for Direct3D 10.x and Direct3D 11.0 is not compatible with Windows 10, Windows 8.x or Windows 7 once this update is applied. You can install the <a href="http://go.microsoft.com/fwlink/?LinkID=323507">Windows 8.x SDK standalone</a>, VS 2012 or VS 2013 which includes the Windows 8.x SDK, or the VS 2013 Remote Debugging Tools (<a href="http://go.microsoft.com/?linkid=9832075">x86</a> or <a href="http://go.microsoft.com/?linkid=9832085">x64</a>) to get the updated SDK Debug Layers files.

The legacy <em>PIX for Windows</em> tool in the <em>DirectX SDK (June 2010)</em> release does not support Direct3D 10.x or Direct3D 11.x applications on Windows 8, and after this update is applied it will no longer support these applications on Windows 7. Direct3D 9 application debugging continues to function.

<strong>Related:</strong> <a href="https://walbourn.github.io/directx-sdk-tools-catalog/">DirectX SDK Tools Catalog</a>

<h1>Notes for users of VS 2012</h1>

Visual Studio 2012's <a href="https://docs.microsoft.com/en-us/visualstudio/debugger/visual-studio-graphics-diagnostics?view=vs-2015">Graphics Debugger</a> supports Direct3D 11.0 applications on Windows 7 and DirectX 11.x applications on Windows 8. Improved support for KB 2670838 is in <a href="https://walbourn.github.io/visual-studio-2012-update-2/">VS 2012 Update 2</a>.

When using VS 2012 Update 1's new "<a href="https://walbourn.github.io/visual-studio-2012-update-1/">v110_xp</a>" Platform Toolset the DirectX 11.1, WIC2, and related headers are not available.
