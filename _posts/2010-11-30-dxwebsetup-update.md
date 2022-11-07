---
layout: msdnpost
title: DXWEBSETUP Update
date: 2010-11-30 15:26
author: Chuck Walbourn
comments: true
categories: [directx]
---
We've republished the June 2010 <a href="http://go.microsoft.com/fwlink/p/?LinkId=159853">DirectX End-User Runtime Web Installer</a>, which now shows a release date of <strike>"11/30/2010"</strike> "4/18/2011". This deploys all the same binaries as the June 2010 version, but the setup itself has been updated to resolve a few key issues.
<!--more-->

**IMPORTANT: The *DirectX End-User Runtime* has been updated in 2021 to address SHA-1 deprecation. Be sure to read [this blog post](https://walbourn.github.io/where-is-the-directx-sdk-2021-edition/) and [this one](https://walbourn.github.io/legacy-d3dx-on-nuget/).**

For the June 2010 DirectX SDK release, we switched over to the Visual C++ 2010 compiler toolset which generates binaries that are not compatible with Windows XP RTM, Windows XP Service Pack 1, or Windows Server 2003 RTM. Attempts to run the installer on these older versions of Windows resulted in a strange error about a missing <code>EncodePointer()</code> entry-point in KERNEL32.DLL. This updated installer will now display an error about that version not being supported. <em>Windows XP RTM, Windows XP Service Pack 1, and Windows Server 2003 RTM along with Windows 2000, Windows 98, and Windows ME are not supported by the current DirectX End-User Runtime Installers.</em> See "<a href="https://walbourn.github.io/not-so-direct-setup/">Not So DirectSetup</a>" for more information about the state of DirectSetup.

> **NOTE**: For game developers looking to repackage older games, consider using the [Microsoft.DXSDK.D3DX](https://www.nuget.org/packages/Microsoft.DXSDK.D3DX) NuGet package which provides a side-by-side shippable version of ``D3DX9_43.DLL``, ``D3DX10_43.DLL``, ``D3DX11_43.DLL``, and ``D3DCompiler_43.dll`` under a new license per [this blog post](https://walbourn.github.io/legacy-d3dx-on-nuget/). For XAudio2 on Windows 7 SP1 or later, consider updating your audio code using the  [Microsoft.XAudio2.Redist](https://www.nuget.org/packages/Microsoft.XAudio2.Redist/) NuGet package as detailed on [Microsoft Docs](https://aka.ms/XAudio2Redist). These packages do *not* make use of legacy DirectSetup and are shipped 'application local'.

There've been several long-standing international font display issues in the End-User Runtime installer, particularly for languages that do not make use of Codepage 1252 (Simplified Chinese, Traditional Chinese, Czech, Japanese, Korean, Polish, and Russian). This has been corrected for most of the dialogs and prompts, although some problems persist in the status strings due to limitations of the underlying install technology. This ensures the EULA and the dialog UI is displayed correctly on all supported languages on Windows XP, Windows Vista, and Windows 7 with the appropriate <a href="http://windows.microsoft.com/en-US/windows/downloads/languages">language pack</a> installed.

The .NET 4.0 Runtime has deprecated the <code>GetCORVersion()</code> entry-point, and the Managed DirectX 1.1 installation would trigger an error message if the system had .NET 4.0 but did not also have the .NET 1.1 or 2.0 Runtime available. This case was limited to Windows XP machines as Windows Vista and Windows 7 both include .NET 2.0. With this update, the error message is no longer triggered. Note that Managed DirectX 1.1 is not compatible with .NET 4.0, so it will not get installed on systems that only have the .NET 4.0 Runtime available.

<strike>We are currently evaluating when we might update the <a href="http://www.microsoft.com/downloads/en/details.aspx?displaylang=en&FamilyID=3b170b25-abab-4bc3-ae91-50ceb6d8fa8d">DirectX End-User Runtimes</a> (stand-alone) with these fixes.</strike> These fixes were also made to the <a href="https://walbourn.github.io/dxsetup-update/">DirectX End-User Runtimes</a> (stand-alone)

In addition to correcting these issues, the <strong>DirectX End-User Runtime Web Installer</strong> will offer users the option to install the Bing&trade; Bar for non-Server versions of Windows if it is not already installed.

<strong>Update</strong>: As noted in this newer blog <a href="https://walbourn.github.io/dxsetup-update/">post</a>, we have updated the DirectX End-user Runtimes (June 2010) stand-alone with these fixes. The latest DirectX End-User Runtime Web Installer now has a publish date of 4/18/2011.
