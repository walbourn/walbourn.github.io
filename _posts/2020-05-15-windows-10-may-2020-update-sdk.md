---
layout: post
title: Windows 10 May 2020 Update SDK
date: 2020-05-15 23:54
author: Chuck Walbourn
comments: true
categories: [windowssdk]
---

The Windows 10 May 2020 Update (a.k.a. Version 2004) is now [available](https://blogs.windows.com/windowsexperience/2020/05/27/how-to-get-the-windows-10-may-2020-update/), and the Windows 10 May 2020 Update SDK (19041) has been [released](https://blogs.windows.com/windowsdeveloper/2020/05/12/start-developing-on-windows-10-version-2004-today/). The new SDK is available for download [standalone](https://developer.microsoft.com/en-US/windows/downloads/windows-10-sdk/) as well as an optional component with VS 2019 ([16.5](https://walbourn.github.io/vs-2019-update-5/)) or later. See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/uwp/whats-new/windows-10-build-19041) for an overview of the new OS features.
<!--more-->

**DirectX 12**: The latest version of DirectX 12 supports new [mesh & amplification shaders](https://devblogs.microsoft.com/directx/coming-to-directx-12-mesh-shaders-and-amplification-shaders-reinventing-the-geometry-pipeline/), [DirectX Raytracing 1.1](https://devblogs.microsoft.com/directx/dxr-1-1/), [Sampler Feedback](https://devblogs.microsoft.com/directx/coming-to-directx-12-sampler-feedback-some-useful-once-hidden-data-unlocked/). See [this blog post](https://devblogs.microsoft.com/directx/dev-preview-of-new-directx-12-features/) for a more complete overview of new features, and *DirectX Developer Day 2020* on [YouTube](https://www.youtube.com/watch?v=CFXKTXtil34).

**DirectXMath**: DirectMath 3.14 is included in this release. See [this blog post](https://walbourn.github.io/directxmath-3.14/).

**DxCapsViewer**: For this SDK release, I fixed a long-standing bug in the Shader Model 6 and Root Signature 1.1 detection logic used by this developer tool. In older versions it was always showing Shader Model 5.1 and Root Signature 1.0 even when higher models were supported. For more detail on the proper way to do this detection in code, see the [DirectX Tool Kit for DX12 wiki](https://github.com/microsoft/DirectXTK12/wiki/Shader-Model-6).

**GitHub**: The [directx-vs-templates](https://github.com/walbourn/directx-vs-templates/releases) has been updated including the latest [D3DX12](https://github.com/microsoft/DirectX-Graphics-Samples/tree/master/Libraries/D3DX12) header.

<b>Related:</b> <a href="https://walbourn.github.io/windows-10-sdk-rtm/">Windows 10 SDK RTM</a>, <a href="https://walbourn.github.io/windows-10-sdk-november-2015/">Windows 10 SDK (November 2015)</a>, <a href="https://walbourn.github.io/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK</a>, <a href="https://walbourn.github.io/windows-10-creators-update-sdk/">Windows 10 Creators Update SDK</a>, <a href="https://walbourn.github.io/windows-10-fall-creators-update-sdk/">Windows 10 Fall Creators Update SDK</a>, <a href="https://walbourn.github.io/windows-10-april-2018-update-sdk/">Windows 10 April 2018 Update SDK</a>, <a href="https://walbourn.github.io/windows-10-october-2018-update/">Windows 10 October 2018 Update SDK</a>, <a href="https://walbourn.github.io/windows-10-may-2019-update/">Windows 10 May 2019 Update SDK</a>
