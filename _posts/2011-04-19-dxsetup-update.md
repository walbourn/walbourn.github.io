---
layout: msdnpost
title: DXSETUP Update
date: 2011-04-19 10:49
author: Chuck Walbourn
comments: true
categories: [directx, dxsdk]
---
As I noted in my post on a <a href="https://walbourn.github.io/dxwebsetup-update/">DXWSETUP</a> back in November 2010, we have addressed a number of bugs in DirectSetup after the release of the DirectX SDK (June 2010). These bugs include some localization display issues with the EULA and various non-Codepage 1252 languages, plus resolving a problem with .NET 4.0's strong deprecation of <code>GetCORVersion</code> function used to detect which version of .NET (if any) is present on the system. Even without the legacy Managed DirectX 1.1 CABs present, this check triggers a non-fatal error pop-up on systems with only the .NET 4.0 Runtime installed. As noted before, this does not impact Windows Vista, Windows 7, Windows Server 2008, or Windows Server 2008 R2 machines which always include the .NET 2.0, 3.0, or 3.5 runtime. It doesn't impact most existing Windows XP systems since most have either no .NET runtime installed or some version of .NET 2.0, 3.0, or 3.5. This also includes the change for an improved error message when run on Windows XP RTM, Windows XP SP1, or Windows Server 2003 RTM machines (which are not supported scenarios, but the original June 2010 release of DirectSetup generates an obscure error message in this case).
<!--more-->

Since most usage of DXSETUP (the DirectX SDK REDIST folder) is with the <code>/silent</code>  switch, the localization fixes do not impact most publishers using DirectSetup to deploy their optional DirectX SDK side-by-side dependencies (D3DX9, D3DX10, D3DX11, D3DCSX, D3DCompiler, XINPUT, XAUDIO2, XACTENGINE, and/or X3DAUDIO). With the strong deprecation of <code>GetCORVersion</code> with .NET 4.0, we are seeing some publishers concerned about the error pop-up that occurs on "fresh" Windows XP deployments with only the .NET 4.0 runtime installed even with <code>/silent</code>. To address those concerns we have refreshed the <a href="http://go.microsoft.com/fwlink/?LinkID=194352" title="DirectX End-User Runtimes (June 2010) [MS Downloads]">DirectX End-User Runtimes (June 2010)</a> stand-alone installer (which now has a published date of 4/18/2011), which is essentially just a ZIP'd version of the DirectX SDK REDIST folder. <em>None of the REDIST CABs or the DLLs it deploys have changed from their June 2010 versions. This only modifies the DirectSetup files themselves, notably <code>dsetup.dll</code>, <code>dsetup32.dll</code>, <code>dxdllreg_x86.cab</code>, <code>dxsetup.exe</code>, and <code>dxupdate.cab</code> </em>. These refreshed files are subject to the same EULA as present in the DirectX SDK (June 2010) release, and can therefore be redistributed with your application if desired.

Anyone working with DirectSetup or DirectX application deployment should be sure to review my <a href="https://walbourn.github.io/not-so-direct-setup/">blog post</a> on the subject, as well as the various linked articles.

> **NOTE**: For game developers looking to repackage older games, consider using the [Microsoft.DXSDK.D3DX](https://www.nuget.org/packages/Microsoft.DXSDK.D3DX) NuGet package which provides a side-by-side shippable version of ``D3DX9_43.DLL``, ``D3DX10_43.DLL``, ``D3DX11_43.DLL``, and ``D3DCompiler_43.dll`` under a new license per [this blog post](https://walbourn.github.io/legacy-d3dx-on-nuget/). For XAudio2 on Windows 7 SP1 or later, consider updating your audio code using the  [Microsoft.XAudio2.Redist](https://www.nuget.org/packages/Microsoft.XAudio2.Redist/) NuGet package as detailed on [Microsoft Docs](https://aka.ms/XAudio2Redist). These packages do *not* make use of legacy DirectSetup and are shipped 'application local'.

In addition to a refresh of the stand-alone installer, we have again updated the <a href="http://go.microsoft.com/fwlink/p/?LinkId=159853" title="DirectX End-User Runtime Web Installer [MS Downloads]">DirectX End-User Runtime Web Installer</a> (which now has a published date of 4/18/2011) for the Bing Bar version 7 release. There are no other changes to the web installer beyond those described in my previous <a href="https://walbourn.github.io/dxwebsetup-update/" title="DXWEBSETUP Update">blog post</a>. <strong><em>The Bing Bar offer is limited to only the Web Installer. The stand-alone installer does not offer nor does it install the Bing Bar</em>.</strong>

<strong>Update:</strong> Note that Windows 8.x and Windows 10 include the .NET 4.5 Runtime. The .NET 3.5 Runtime can be optionally enabled, but is not present by default. Therefore, these Windows 8.x and Windows 10 systems trigger a "Windows Feature" request dialog if it has not already been enabled. This refreshed version of DXSETUP and DXWSETUP both resolve this issue for the Windows 8.x and Windows 10 as well.

There are no plans to update this package for newer releases of D3DCSX or D3DCompiler. These are only available in the Windows 8.0 SDK, Windows 8.1 SDK, and/or Windows 10 SDK.

<strong>SHA-512:</strong> The best way to validate that you have an uncorrupted copy of this package it to run:

```
certutil -hashfile directx_jun2010_redist.exe SHA512
```

The valid SHA-512 hash for the original SHA-1 signed exe is:

```
4325f649f56f2773b3bea2ca00639878caaa272f801be3931835a58ef313c397aa39e5b164e4006127b9061492e9350501c2756c6514e99f4612bba4fa663b0e
```

The valid SHA-512 has for the SHA-256 signed exe is:

```
04c6347e6db6cff037a1292a88bf062c3e4042fb265a665afdbe7616aed7936f4955a35637a86c30332731762e0052b6f5c721f9fe7682d147e0965a7fb77a63
```

<strong>Desktop Bridge</strong>: [Desktop Bridge](https://developer.microsoft.com/en-us/windows/bridges/desktop/) applications that use D3DX9, D3DX10, D3DX11, XAudio 2.7, XInput 1.3, or XACT must use the [Microsoft.DirectX.x86](https://aka.ms/directx_x86_appx) / [Microsoft.DirectX.x64](https://aka.ms/directx_x64_appx) framework to deploy these legacy DirectX SDK side-by-side components. Alternatively, developers can remove all such dependencies—see https://aka.ms/Kfsdiu, https://aka.ms/XAudio2Redist, https://aka.ms/Mu9kn7.
