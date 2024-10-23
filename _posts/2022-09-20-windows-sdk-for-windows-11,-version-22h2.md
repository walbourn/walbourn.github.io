---
layout: post
title: Windows SDK for Windows 11, Version 22H2
date: 2022-09-20 14:47
author: Chuck Walbourn
comments: true
categories: [windowssdk]
---

*Windows 11 "2022 Update"* (Version 22H2, Build 22621) was released today per the [Windows Experience Blog](https://blogs.windows.com/windowsexperience/2022/09/20/available-today-the-windows-11-2022-update/). The Windows SDK for Windows 11, Version 22H2 (10.0.22621) is available for [download](https://aka.ms/windowssdk), and is offered as an optional component in [Visual Studio 2022](https://visualstudio.microsoft.com/vs/).
<!--more-->

**DirectXMath:** This Windows SDK includes version [3.17](https://walbourn.github.io/directxmath-3.17/).

**NuGet**: The Windows SDK is also offered via [NuGet](https://www.nuget.org/profiles/WindowsSDK).

**Direct3D 12**: New features supported in this Windows 11 update include [Shader Model 6.7](https://devblogs.microsoft.com/directx/shader-model-6-7/), [Alpha Blend Factor, and a few other new optional features](https://devblogs.microsoft.com/directx/agility-sdk-1-602-0/). See  ``D3D12_FEATURE_D3D12_OPTIONS12``, and ``D3D12_FEATURE_D3D12_OPTIONS13``. These are also supported on recent builds of Windows 10 via the [DirectX SDK Agility SDK](https://aka.ms/directx12agility). Support for these new optional features require appropriate drivers are installed for your hardware.

> Note that the [Enhanced Barriers](https://devblogs.microsoft.com/directx/preview-agility-sdk-1-706-3-preview-sm-6-7-enhanced-barriers-and-more/) feature is still in preview in the Windows 11, Version 22H2 release. You must use the *DirectX Agility SDK* 1.700 or later to access this feature including the ``ID3D12Device10``, ``ID3D12GraphicsCommandList7``, and ``ID3D12Debug6`` interfaces.

> In other words, ``D3D12_FEATURE_D3D12_OPTIONS12.EnhancedBarriersSupported`` and ``.RelaxedFormatCastingSupported`` are always ``FALSE`` on 'stock' Windows 11, Version 22H2. This also means Shader Model 6.7's "Advanced Texture Operations" all require the *DirectX Agility SDK* since those use newer optional features.

**D3DX12**: The latest version on [DirectX-Headers](https://github.com/microsoft/DirectX-Headers) assumes you are using the [DirectX SDK Agility SDK](https://aka.ms/directx12agility) and/or the rest of the DirectX-Headers content which already includes some post *Windows 11, Version 22H2* SDK content. For the latest version of D3DX12 that supports the new Direct3D 12 types in 22621, but not anything newer, see [GitHub](https://github.com/walbourn/directx-vs-templates/blob/main/d3d12game_win32_dr/d3dx12.h).

**clang/LLVM**: Note that there are a few libraries in the latest Windows SDK that contain "eXtended Flow Guard" (XFG) debug information. These sections are new, and clang/LLVM's ``lld-link`` emits harmless warnings when these are encountered prior to [LLVM 15.0.0](https://releases.llvm.org/15.0.0/tools/clang/docs/ReleaseNotes.html).

```
lld-link: warning/error: ignoring unknown debug$S subsection kind 0xFF in file libucrt.lib
```

See [this issue](https://reviews.llvm.org/D129378) for more details.

> The [Visual Studio 2022 17.4 Update](https://walbourn.github.io/vs-2022-update-4/) includes clang 15.0.1 to address this issue.

<b>Related:</b> <a href="https://walbourn.github.io/windows-sdk-for-windows-11/">Windows SDK for Windows 11</a>
