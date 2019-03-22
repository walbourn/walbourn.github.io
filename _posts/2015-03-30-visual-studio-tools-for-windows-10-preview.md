---
layout: post
title: Visual Studio Tools for Windows 10 Preview
date: 2015-03-30 14:34
author: Chuck Walbourn
comments: true
categories: [uwp, win10, windowssdk]
---
A preview of Visual Studio 2015 toolset with the Windows 10 SDK is now available through the <a href="https://insider.windows.com/">Windows Insiders</a> program.
<!--more-->

See the <a href="https://blogs.windows.com/buildingapps/2015/03/23/windows-10-developer-tooling-preview-now-available-to-windows-insiders/">Building Apps for Windows blog</a>, <a href="https://devblogs.microsoft.com/visualstudio/visual-studio-tools-for-windows-10-preview/">Visual Studio Team blog</a>, and <a href="https://devblogs.microsoft.com/somasegar/visual-studio-tools-for-windows-10-technical-preview/">Somasegar's blog</a> for additional information.

<strong>DirectX 12: </strong>This preview includes the headers and libraries needed to build DirectX 12 (as well as Direct3D 11.3, DXGI 1.4, and Direct2D/DirectWrite 1.3) applications for the Windows 10 Technical Preview (build 10041). For better support including access to pre-release samples and documentation, join the *DirectX Early Access* program. Also, check out this post on the <a href="http://blogs.msdn.com/b/directx/archive/2015/03/26/directx-12-rocks-in-3dmark-s-api-overhead-test.aspx">DirectX Developer blog</a>.

<strong>Windows 10:</strong> Be sure to read <a href="https://devblogs.microsoft.com/cppblog/visual-studio-2015-and-graphics-tools-for-windows-10/">this post</a> for details on enabling the Direct3D Debug Layer for Windows 10, and check this <a href="https://social.msdn.microsoft.com/Forums/en-US/home?forum=Win10SDKToolsIssues">forum</a> for known issues.

<strong>CodePlex/GitHub:</strong> Project files for both Windows desktop apps and universal Windows apps using VS 2015 are available for <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectX Tool Kit</a>, <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a>, and <a href="http://go.microsoft.com/fwlink/?LinkID=324981">DirectXMesh</a>. Note that currently <em>DirectX Tool Kit</em>'s <code>GamePad</code> class is a 'null' device for universal Windows apps as both the XInput compatibility library and the new gamepad API for universal Windows apps are not yet in the preview Windows 10 SDK.

<em><strong>Update:</strong> With the release of flight <a href="https://blogs.windows.com/windowsexperience/2015/06/12/releasing-windows-10-insider-preview-build-10130-for-pcs-to-the-slow-ring/">10130</a>, the <code>GamePad</code> class in DirectX Tool Kit makes use of the new <code>IGamePad</code> WinRT class for universal Windows apps. Note that this API currently supports Xbox 360 Common Controllers, but does not yet support Xbox One Controllers in this flight.</em>

<strong>DirectXMath:</strong> This Windows 10 SDK preview includes DirectXMath 3.07 which addresses a number of <a href="https://walbourn.github.io/known-issues-directxmath-3-06/">known issues in version 3.06</a>.

<strong>Related:</strong> <a href="https://walbourn.github.io/windows-10-technical-preview/">Windows 10 Technical Preview</a>
