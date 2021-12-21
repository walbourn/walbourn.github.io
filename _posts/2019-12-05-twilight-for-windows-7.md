---
layout: post
title: Twilight for Windows 7
date: 2019-12-05 17:49
author: Chuck Walbourn
comments: true
categories: [general]
---

As a reminder, [Windows 7 end-of-life](https://www.microsoft.com/en-us/windows/windows-7-end-of-life-support-information) for consumer is fast approaching on January 14, 2020. There are enterprises that will have on-going support contracts, but officially for consumers that's the end of the road. There are of course a number of gamers still running Windows 7--thankfully according to the [Valve Steam Hardware Survey](https://store.steampowered.com/hwsurvey) they are almost all running 64-bit--, and it will remain important in some markets for some time to come. So, here are a few tips for developers still needing to support Windows 7.
<!--more-->

First, [Windows 7 Service Pack 1](https://walbourn.github.io/windows-7-service-pack-1/) is really your minimum. Officially Windows 7 RTM isn't supported anymore even by the Visual C++ Runtime. There are also assumptions made for most consumer software that the system is updated with the latest changes from Windows Update. For a history of the roll-up releases, see [KB4009469](https://support.microsoft.com/en-us/help/4009469).

Second, keep in mind that SHA-2 support is an essential update for a Windows 7 machine. See [KB4472027](https://support.microsoft.com/en-us/help/4472027/2019-sha-2-code-signing-support-requirement-for-windows-and-wsus) and [Windows Enforcement of SHA1 Certificates](https://social.technet.microsoft.com/wiki/contents/articles/32288.windows-enforcement-of-sha1-certificates.aspx).

# DirectX

Windows 7 SP1 supports all the DirectX 11.1 software features with [KB2670838](https://support.microsoft.com/en-us/help/2670838/platform-update-for-windows-7-sp1-and-windows-server-2008-r2-sp1), but it does not support ``D3D_FEATURE_LEVEL_11_1`` or the various 'optional hardware features' that require updated drivers. Note the 11.1 Runtime makes it a lot easier to interop Direct2D/DirectWrite with Direct3D 11. See [this blog post](https://walbourn.github.io/directx-11-1-and-windows-7-update/) and [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/direct3darticles/platform-update-for-windows-7) for the technical details.

A limited form of Direct3D 12 is also available for Windows 7 SP1. This includes the DirectX Raytracing API. It requires some careful coding, and existing Windows 10 DirectX 12 applications are probably making a number of other system assumptions that need to be revisited, but it's a useful option for unifying your rendering. For details see [Porting DirectX 12 games to Windows 7](https://devblogs.microsoft.com/directx/porting-directx-12-games-to-windows-7/). For developers, this is supported through a [NuGet](https://www.nuget.org/packages/Microsoft.Direct3D.D3D12On7) package.

> Debugging support and tooling in these scenarios is  limited, so you should plan to do most of your development work on Windows 10.

> Also be aware that the D3D12onWin7 solution does not support Windows 8.0 or Windows 8.1 per the [specification](https://microsoft.github.io/DirectX-Specs/d3d/D3D12onWin7.html#q-what-about-windows-8-or-windows-81). If you look at the numbers on [hardware survey](https://store.steampowered.com/hwsurvey) you'll see why this was excluded.

# XAudio 2

In my many blog posts about the retiring of the [legacy DirectX SDK](https://aka.ms/dxsdk), one key area that keeps it [alive](https://walbourn.github.io/the-zombie-directx-sdk/) is the fact that XAudio 2.7 was the last  release to support Windows 7. This made it difficult for games to use XAudio 2.8/2.9 features built into the OS for Win32 desktop applications on [later versions of Windows](https://walbourn.github.io/xaudio2-and-windows-8/).

The great news here is that much like the DirectX 12 story, there is a version of XAudio 2.9 that supports Windows 7 SP1, Windows 8.0, Windows 8.1, and still takes advantage of the Windows 10 built-in version. See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/xaudio2/xaudio2-redistributable) for all the details. The developer story utilizes a [NuGet](https://www.nuget.org/packages/Microsoft.XAudio2.Redist/) package as well.

> The XAudio2 samples on [GitHub](https://github.com/walbourn/directx-sdk-samples/tree/main/XAudio2) have been updated to support using the new XAudio 2.9 REDIST version instead of the DirectX SDK.

# HLSL

The ``D3DCompiler_47.dll`` in the Windows 10 SDK is compatible with Windows 7 and can be redistributed with your application. See [HLSL, FXC, and D3DCompile](https://walbourn.github.io/hlsl-fxc-and-d3dcompile/).

The DXIL Shader Model 6 ``dxcompiler.dll`` from the Windows 10 (18362 or earlier) SDK is not compatible with Windows 7. The most recent release from [GitHub](https://github.com/microsoft/DirectXShaderCompiler/releases) does support being used on Windows 7.

# UTF-8

Windows has long made use of Unicode for localization support, but this has been through ``wchar_t`` 16-bit wide characters. There are proponents that strongly suggest using UTF-8 instead since they are more portable, take less memory, etc. See the [UTF-8 Everywhere](https://utf8everywhere.org/) manifesto for details and some recommended best practices for Windows development.

> There's been some good work to get the most recent versions of Windows 10 to better support UTF-8, but it will be a long time before you can just switch to using narrow-string Unicode to call the Win32 APIs.

You can and should use the manifesto practices on Windows 7 as well, but there's one issue I've run into you should note. When you use ``MultiByteToWideChar`` with ``CP_UTF8``, if you pass the flag ``MB_PRECOMPOSED`` it works fine with Windows 10. It will, however, fail on Windows 7. This is because officially the only valid flags are 0 or ``MB_ERR_INVALID_CHARS``. Windows 10 ignores the commonly used ``MB_PRECOMPOSED`` flag for this case to simplify porting, but older systems don't tolerate it.

# Additional notes

* The ``LOAD_LIBRARY_SEARCH_SYSTEM32`` flag is a useful security feature when explicitly loading a system DLL. Keep in mind that it's not supported on Windows 7 SP1 without [KB2533623](https://support.microsoft.com/en-us/help/2533623/microsoft-security-advisory-insecure-library-loading-could-allow-remot) installed.

* With Windows 7 or later, Win32 desktop applications should include embedded manifests. See [Manifest Madness](https://walbourn.github.io/manifest-madness/).

* If you are wanting to integrate with the Game Explorer, the most recent version of the GDFMaker tool can be found in Windows 10 SDK. You can find [GDFTrace](https://github.com/walbourn/directx-sdk-samples/tree/main/GDFTrace) and [GamesuxInstallHelper](https://github.com/walbourn/directx-sdk-samples/tree/main/InstallHelpers/GameuxInstallHelper) on GitHub.

<b>Related:</b> <a href="https://walbourn.github.io/a-look-back-windows-vista/">Windows Vista</a>, <a href="https://walbourn.github.io/goodbye-to-an-old-friend/">Windows XP</a>
