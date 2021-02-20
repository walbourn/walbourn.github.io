---
layout: msdnpost
title: Known Issue - DirectX SDK (June 2010) Setup and the S1023 error
date: 2011-12-09 12:48
author: Chuck Walbourn
comments: true
categories: [directx, dxsdk, visualc]
---
<strong>Note that the DirectX SDK is deprecated. See "<a href="https://walbourn.github.io/where-is-the-directx-sdk-2021-edition/">Where is the DirectX SDK (2021 Edition)?</a>" for details.</strong>

Over the past few month we've been getting reports of problems with the <strong>DirectX SDK (June 2010)</strong> setup failing for customers displaying an installation error when it gets to point of installing the "redistributable packages". This particular problem has been traced to an issue with the <em>Visual C++ 2010 Redistributable Package</em> version 10.0.30319 (RTM). When the 10.0.40219 (Service Pack 1) version is already present on the system, the 10.0.30319 (RTM) version returns a failure instead of a success as was expected.
<!--more-->

The work-around for this issue is straight-forward:

(1) Remove the <em>Visual C++ 2010 Redistributable Package</em> version 10.0.40219 (Service Pack 1) from the system (both x86 and x64 if applicable). This can be easily done via a command-line with administrator rights:

```
MsiExec.exe /passive /X{F0C3E5D1-1ADE-321E-8167-68EF0DE699A5}
MsiExec.exe /passive /X{1D8E6291-B0D5-35EC-8441-6616F567A0F7}
```

(2) Install the DirectX SDK (June 2010)

(3) Reinstall the <em>Visual C++ 2010 Redistributable Package</em> version 10.0.40219 (Service Pack 1). On an x64 system, you should install both the x86 and x64 versions of the C++ REDIST. Be sure to install the most <a href="http://www.microsoft.com/download/en/details.aspx?displaylang=en&id=26999">current version available</a>, which at this point is the <a href="http://support.microsoft.com/kb/2565063">KB 2565063</a> with a security fix.

<em>This issue is also covered by <a href="http://support.microsoft.com/kb/2728613">KB 2717426</a></em>

<strong>Note:</strong> This issue does not affect earlier version of the DirectX SDK which deploy the VS 2005 / VS 2008 CRT REDIST and do not deploy the VS 2010 CRT REDIST. This issue does <em>not</em> affect the <em>DirectX End-User Runtime</em> web or stand-alone installer as those packages do not deploy any version of the VC++ CRT.

<strong>Windows SDK:</strong> The <a href="https://walbourn.github.io/windows-sdk-7-1/">Windows SDK 7.1</a> has exactly the same issue as noted in <a href="http://support.microsoft.com/kb/2717426">KB 2717426</a>.

<strong>Windows 7 Service Pack 1 / Windows 8 users:</strong> The Direct3D 10.x/Direct3D 11.x SDK Debug Layers installed by the DirectX SDK (June 2010) are not compatible with Windows 8 or Windows 7 SP1 + <a href="http://support.microsoft.com/kb/2670838">KB 2670838</a>. See this <a href="https://walbourn.github.io/directx-11-1-and-windows-7-update/">post</a> for details on installing the correct version.

<strong>Setup writers:</strong> If you are creating a deployment for your application and you are using VS 2010, it is recommended you use the <a href="https://walbourn.github.io/visual-studio-2010-service-pack-1/">Service Pack 1</a> version and not the RTM version to avoid this issue. You should also consider picking up the updated version of the <a href="https://walbourn.github.io/dxsetup-update/">DirectX End-User Runtime Package</a> if you are deploying DirectX SDK components with your application, and of course fully understand the issues detailed in this earlier blog <a href="https://walbourn.github.io/not-so-direct-setup/">post</a>.


<strong>SHA-512:</strong> This of course assumes you actually have an uncorrupted copy of the DirectX SDK setup package. The best way to validate this it to run:

```
certutil -hashfile DXSDK_Jun10.exe SHA512
```

The valid SHA-512 hash for the original SHA-1 signed exe is:

```
4869ac947a35cd0d6949fbda17547256ea806fef36f48474dda63651f751583e9902641087250b6e8ccabaab85e51effccd9235dc6cdf64e21ec2b298227fe19
```

The valid SHA-512 has for the SHA-256 signed exe is:

```
24e1e9bda319b780124b865f4640822cfc44e4d18fbdcc8456d48fe54081652ce4ddb63d3bd8596351057cbae50fc824b8297e99f0f7c97547153162562ba73f
```
