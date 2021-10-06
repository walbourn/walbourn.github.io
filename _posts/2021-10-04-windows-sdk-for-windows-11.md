---
layout: post
title: Windows SDK for Windows 11
date: 2021-10-04 22:08
author: Chuck Walbourn
comments: true
categories: [generl]
---

The Windows SDK for Windows 11 (10.0.22000) is now available for [download](https://aka.ms/windowssdk), and is offered as an optional component in [Visual Studio 2019 16.11.4](https://docs.microsoft.com/en-us/visualstudio/releases/2019/release-notes) and [Visual Studio 2022 Preview](https://visualstudio.microsoft.com/vs/preview/). See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/apps/whats-new/windows-11-build-22000) for an overview of new OS features, as well as these posts on [Windows Blogs](https://blogs.windows.com/windowsdeveloper/2021/10/04/developing-for-windows-11/) and the [Game Stack Blog](https://developer.microsoft.com/en-us/games/blog/game-developers-everywhere-welcome-to-windows-11/).
<!--more-->

**DirectXMath:** This Windows SDK includes version [3.16b](https://walbourn.github.io/directxmath-3.16/) (i.e. 3.16 with hot-fixes for ARM64 issues on clang/LLVM and GCC).

**NuGet**: The Windows SDK is also offered via [NuGet](https://www.nuget.org/profiles/WindowsSDK).

**D3DX12**: There's a new version of the ``D3DX12.H`` header available from [GitHub](https://github.com/microsoft/DirectX-Headers). The primary change is the new [CD3DX12FeatureSupport](https://devblogs.microsoft.com/directx/introducing-a-new-api-for-checking-feature-support-in-direct3d-12/) helper class.

**Windows 11 version checking**: The Windows 11 version is reported as "10.0" with a build number >= 22000. The Windows SDK (22000) ``VersionHelpers.h`` header is missing a **IsWindows11OrGreater** function. This will be fixed in a future Windows SDK, but in the meantime here's some code:

```cpp
#include "VersionHelpers.h"

VERSIONHELPERAPI
IsWindows11OrGreater()
{
    OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0, {0}, 0, 0 };
    DWORDLONG const dwlConditionMask = VerSetConditionMask(
        VerSetConditionMask(
        VerSetConditionMask(
            0, VER_MAJORVERSION, VER_GREATER_EQUAL),
               VER_MINORVERSION, VER_GREATER_EQUAL),
               VER_BUILDNUMBER, VER_GREATER_EQUAL);

    osvi.dwMajorVersion = HIBYTE(_WIN32_WINNT_WIN10);
    osvi.dwMinorVersion = LOBYTE(_WIN32_WINNT_WIN10);
    osvi.dwBuildNumber = 22000;

    return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_BUILDNUMBER, dwlConditionMask) != FALSE;
}
```

Be sure to read [What's in a version number?](https://walbourn.github.io/whats-in-a-version-number/) Also, remember ``VerifyVersionInfoW`` is subject to appcompat behavior unless you have the relevant supportedOS GUID in your EXE manifest as detailed in [Manifest Madness](https://walbourn.github.io/manifest-madness/).

<b>Related:</b> <a href="https://walbourn.github.io/windows-10-sdk-rtm/">Windows 10 SDK RTM</a>, <a href="https://walbourn.github.io/windows-10-sdk-november-2015/">Windows 10 SDK (November 2015)</a>, <a href="https://walbourn.github.io/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK</a>, <a href="https://walbourn.github.io/windows-10-creators-update-sdk/">Windows 10 Creators Update SDK</a>, <a href="https://walbourn.github.io/windows-10-fall-creators-update-sdk/">Windows 10 Fall Creators Update SDK</a>, <a href="https://walbourn.github.io/windows-10-april-2018-update-sdk/">Windows 10 April 2018 Update SDK</a>, <a href="https://walbourn.github.io/windows-10-october-2018-update/">Windows 10 October 2018 Update SDK</a>, <a href="https://walbourn.github.io/windows-10-may-2020-update-sdk/">Windows 10 May 2019 Update SDK</a>
