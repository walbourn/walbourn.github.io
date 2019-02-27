---
layout: post
title: Known Issue: DirectX SDK (June 2010) Setup and the S1023 error
date: 2011-12-09 12:48
author: walbourn
comments: true
categories: [directx, dxsdk, Uncategorized, visualc]
---
<span style="font-size: large"><strong>Note that the DirectX SDK is deprecated. See "<a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">Where is the DirectX SDK?</a>", "<a href="http://blogs.msdn.com/b/chuckw/archive/2013/07/01/where-is-the-directx-sdk-2013-edition.aspx">Where is the DirectX SDK (2013 Edition)?</a>", and "<a href="http://blogs.msdn.com/b/chuckw/archive/2015/08/05/where-is-the-directx-sdk-2015-edition.aspx">Where is the DirectX SDK (2015 Edition)?</a>" for details.</strong></span>

Over the past few month we've been getting reports of problems with the <strong>DirectX SDK (June 2010)</strong> setup failing for customers displaying an installation error when it gets to point of installing the "redistributable packages". This particular problem has been traced to an issue with the <em>Visual C++ 2010 Redistributable Package</em> version 10.0.30319 (RTM). When the 10.0.40219 (Service Pack 1) version is already present on the system, the 10.0.30319 (RTM) version returns a failure instead of a success as was expected.

The work-around for this issue is straight-forward:

(1) Remove the <em>Visual C++ 2010 Redistributable Package</em> version 10.0.40219 (Service Pack 1) from the system (both x86 and x64 if applicable). This can be easily done via a command-line with administrator rights:

<span style="font-family: courier new,courier">MsiExec.exe /passive /X{F0C3E5D1-1ADE-321E-8167-68EF0DE699A5}
MsiExec.exe /passive /X{1D8E6291-B0D5-35EC-8441-6616F567A0F7}</span>

(2) Install the DirectX SDK (June 2010)

(3) Reinstall the <em>Visual C++ 2010 Redistributable Package</em> version 10.0.40219 (Service Pack 1). On an x64 system, you should install both the x86 and x64 versions of the C++ REDIST. Be sure to install the most <a href="http://www.microsoft.com/download/en/details.aspx?displaylang=en&amp;id=26999">current version available</a>, which at this point is the <a href="http://support.microsoft.com/kb/2565063">KB 2565063</a> with a security fix.

<em>This issue is also covered by <a href="http://support.microsoft.com/kb/2728613">KB 2717426</a></em>

<strong>Note:</strong> This issue does not affect earlier version of the DirectX SDK which deploy the VS 2005 / VS 2008 CRT REDIST and do not deploy the VS 2010 CRT REDIST. This issue does <em>not</em> affect the <em>DirectX End-User Runtime</em> web or stand-alone installer as those packages do not deploy any version of the VC++ CRT.

<strong>Windows SDK:</strong> The <a href="http://blogs.msdn.com/b/chuckw/archive/2010/06/15/windows-sdk-7-1.aspx">Windows SDK 7.1</a> has exactly the same issue as noted in <a href="http://support.microsoft.com/kb/2717426">KB 2717426</a>.

<strong>Windows 7 Service Pack 1 / Windows 8 users:</strong> The Direct3D 10.x/Direct3D 11.x SDK Debug Layers installed by the DirectX SDK (June 2010) are not compatible with Windows 8 or Windows 7 SP1 + <a href="http://support.microsoft.com/kb/2670838">KB 2670838</a>. See this <a href="http://blogs.msdn.com/b/chuckw/archive/2013/02/26/directx-11-1-and-windows-7-update.aspx">post</a> for details on installing the correct version.

<strong>Setup writers:</strong> If you are creating a deployment for your application and you are using VS 2010, it is recommended you use the <a title="Games for Windows and the DirectX SDK Blog" href="http://blogs.msdn.com/b/chuckw/archive/2011/03/16/visual-studio-2010-service-pack-1.aspx">Service Pack 1</a> version and not the RTM version to avoid this issue. You should also consider picking up the updated version of the <a href="http://blogs.msdn.com/b/chuckw/archive/2011/04/19/dxsetup-update.aspx">DirectX End-User Runtime Package</a> if you are deploying DirectX SDK components with your application, and of course fully understand the issues detailed in this earlier blog <a title="Games for Windows and the DirectX SDK Blog" href="http://blogs.msdn.com/b/chuckw/archive/2010/09/08/not-so-direct-setup.aspx">post</a>.

<strong>FCIV:</strong> This of course assumes you actually have an uncorrupted copy of the DirectX SDK setup package. The best way to validate this it to run <code><a href="http://support.microsoft.com/kb/841290">fciv</a> -sha1 DXSDK_Jun10.exe</code> and verify you get <code>8fe98c00fde0f524760bb9021f438bd7d9304a69 dxsdk_jun10.exe</code>
