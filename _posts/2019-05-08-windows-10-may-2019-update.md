---
layout: post
title: Windows 10 May 2019 Update
date: 2019-05-08 12:12
author: Chuck Walbourn
comments: true
categories: [uwp, win10, windowssdk]
---

The Windows 10 May 2019 Update (a.k.a. Version 1903) has been deployed to insiders and <strike>will be deployed publicly [in late May](https://blogs.windows.com/windowsexperience/2019/04/04/improving-the-windows-10-update-experience-with-control-quality-and-transparency/)</strike> is being deployed publicly on [May 21st](https://blogs.windows.com/windowsexperience/2019/05/21/how-to-get-the-windows-10-may-2019-update/), but in the meantime the matching Windows 10 SDK (10.0.18362) is available now. See [this blog post](https://blogs.windows.com/buildingapps/2019/04/18/start-developing-on-windows-10-may-2019-update-today) for details on the 'go-live' plan.
<!--more-->

If you are using VS 2019 you can install the latest Windows 10 SDK by selecting it from the Visual Studio installer as an 'optional component' in some workloads, or in the 'individual components' tab. If you are using VS 2017, then you can install the [standalone](https://developer.microsoft.com/en-US/windows/downloads/windows-10-sdk) SDK. This release includes some updates to DirectX 12 including the release of [HLSL Shader Model 6.4](https://docs.microsoft.com/en-us/windows/desktop/direct3dhlsl/hlsl-shader-model-6-4-features-for-direct3d-12). See [What's New in Windows 10 for developers, build 18362](https://docs.microsoft.com/en-us/windows/uwp/whats-new/windows-10-build-18362).

**DirectML:** This release of the OS and SDK includes the _Direct Machine Learning_ (DirectML) API. See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/desktop/direct3d12/dml). You can find samples on [GitHub](https://github.com/Microsoft/DirectML-Samples).

**VS 2015 Users:** The Windows 10 SDK (15063 or later) is not supported for VS 2015; please upgrade to VS 2017 or VS 2019.

**VS 2019 Users:** This version of Visual Studio offers a new option for which Windows 10 SDK to use to build: "*10.0 (latest installed version)*"

In ``.vcxproj`` files this option appears as:

```xml
<WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>
```

**Known Issue:** Note that the *Error List* in VS 2017 (15.9) and VS 2019 (16.0) will indicate an error in a  Windows 10 SDK header ``winnt.h`` that does not actually show up in the build window. This is a bug with the IntelliSense compiler and does not impact the C/C++ compiler at all. It will be fixed in a future update of Visual Studio.

**C++/WinRT:** The C++/WinRT headers included in this release of the Windows 10 SDK includes the new C++/WinRT 2.0. See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/news) for details.

**GitHub:** The samples in [Windows-universal-samples](https://github.com/microsoft/Windows-universal-samples/) have been updated to use the new Windows 10 SDK. For my GitHub projects, the VS 2017 projects still use 10.0.17763 by default, but the VS 2019 projects are configured with the "latest installed SDK" setting.

**Python:** Note that the May 2019 release of Windows 10 includes improved [Python integration](https://devblogs.microsoft.com/python/python-in-the-windows-10-may-2019-update/).

<b>Related:</b> <a href="https://walbourn.github.io/windows-10-sdk-rtm/">Windows 10 SDK RTM</a>, <a href="https://walbourn.github.io/windows-10-sdk-november-2015/">Windows 10 SDK (November 2015)</a>, <a href="https://walbourn.github.io/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK</a>, <a href="https://walbourn.github.io/windows-10-creators-update-sdk/">Windows 10 Creators Update SDK</a>, <a href="https://walbourn.github.io/windows-10-fall-creators-update-sdk/">Windows 10 Fall Creators Update SDK</a>, <a href="https://walbourn.github.io/windows-10-april-2018-update-sdk/">Windows 10 April 2018 Update SDK</a>, <a href="https://walbourn.github.io/windows-10-october-2018-update/">Windows 10 October 2018 Update SDK</a>
