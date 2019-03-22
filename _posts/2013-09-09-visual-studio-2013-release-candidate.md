---
layout: post
title: Visual Studio 2013 Release Candidate
date: 2013-09-09 13:45
author: Chuck Walbourn
comments: true
categories: [dxsdk, visualc]
---
The <a href="http://go.microsoft.com/fwlink/?LinkId=306566">Visual Studio 2013 Release Candidate</a> is now available. The <a href="http://www.microsoft.com/en-us/download/details.aspx?id=40007">VC 2013 RC Redistribution packages</a> are also available (<a href="http://go.microsoft.com/fwlink/?LinkId=313517">x86</a>, <a href="http://go.microsoft.com/fwlink/?LinkId=313518">x64</a>, <a href="http://go.microsoft.com/fwlink/?LinkId=313519">ARM</a>), as well as the <a href="http://www.microsoft.com/en-us/download/details.aspx?id=39985">Remote Debugging Tools</a> (<a href="http://go.microsoft.com/fwlink/?LinkId=313511">x86</a>, <a href="http://go.microsoft.com/fwlink/?LinkId=313512">x64</a>).
<!--more-->

VS 2013 RC includes the Windows 8.1 SDK. As with VS 2012 / Windows 8.0 SDK, this release integrates many aspects of the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee663275.aspx">legacy DirectX SDK</a>. As discussed in <a href="https://walbourn.github.io/where-is-the-directx-sdk-2013-edition/">Where is the DirectX SDK (2013 Edition)?</a>, there's new support for Direct3D 11.2, Direct2D 1.2, DXGI 1.3, HLSL Compiler #47, updates to WIC, and many new 18.0 C++ compiler features (such as ``__vectorcall``). The Windows 8.1 SDK included in VS 2013 RC also includes DirectXMath 3.06 with a few minor changes compared to 3.05 in the Preview (see <a href="https://docs.microsoft.com/en-us/windows/desktop/dxmath/pg-xnamath-whatsnew">Microsoft Docs</a> and this <a href="https://walbourn.github.io/known-issues-directxmath-3-03/">post</a>). For more information on VS 2013 RC, see the <a href="https://blogs.msdn.microsoft.com/vcblog/2013/09/09/visual-studio-2013-rc-now-available/">Visual C++ Team blog</a>, <a href="https://devblogs.microsoft.com/somasegar/announcing-the-visual-studio-2013-release-candidate/">Somasegar's blog</a>, and the <a href="https://devblogs.microsoft.com/visualstudio/visual-studio-2013-rc-available-now/">Visual Studio blog</a>.

For a comparison summary of new C++11 language features in VS 2013, take a look at the tables in the <a href="https://walbourn.github.io/dual-use-coding-techniques-for-games/">Dual-use Coding Techniques for Games</a> post which have been refreshed for the latest toolset.

<strong>Windows 8.1: </strong>In related news, the <a href="https://blogs.msdn.microsoft.com/stevengu/2013/09/08/download-windows-8-1-rtm-visual-studio-2013-rc-and-windows-server-2012-r2-rtm-today/">Windows 8.1 RTM</a> is now available on MSDN/TechNet for subscribers, with GA set for October 18, 2013. If you are developing Win32 desktop games, be sure to review the <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/windows-8-and-windows-server-8-compatibility-cookbook-portal">official appcompat cookbook</a> and this <a href="https://walbourn.github.io/desktop-games-on-windows-8-x">post</a>.

For developers working on Windows Store apps, see <a href="http://go.microsoft.com/fwlink/p/?LinkID=298951">New APIs and features for developers</a> and the <a href="http://go.microsoft.com/fwlink/?LinkID=304117">Migration Guide from Windows 8</a>. If you do not have access to the Windows 8.1 RTM build via a MSDN or TechNet subscription, you should continue to use VS 2013 Preview to develop and test Windows Store apps for Windows 8.1 Preview until GA.

<strong>Related: </strong><a href="https://walbourn.github.io/where-is-the-directx-sdk-2013-edition/">Where is the DirectX SDK (2013 Edition)?</a>, <a href="https://walbourn.github.io/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available/">Visual Studio 2013 and Windows 8.1 SDK RTM are now available</a>
