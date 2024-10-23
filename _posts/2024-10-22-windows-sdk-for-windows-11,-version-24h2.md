---
layout: post
title: Windows SDK for Windows 11, Version 24H2
date: 2024-10-22 21:50
author: Chuck Walbourn
comments: true
categories: [windowssdk]
---

*Windows 11 "2024 Update"* (Version 24H2, Build 26100) was widely released this month. The Windows SDK for Windows 11, Version 24H2 (10.0.26100) is available for [download](https://aka.ms/windowssdk), and is offered as an optional component in [Visual Studio 2022](https://visualstudio.microsoft.com/vs/).

<!--more-->

**DirectX 12:** This Windows SDK has version 1.612 of the headers which is between the *DirectX Agility SDK* 1.611 and 1.613 releases. This includes up to `ID3D12Device14`, `ID3D12GraphicsCommandList10`, and `D3D12_FEATURE_D3D12_OPTIONS21`. These headers also define `D3D_SHADER_MODEL_6_8`, `D3D_SHADER_MODEL_6_9`, `D3D_ROOT_SIGNATURE_VERSION_1_2`, `D3D12_HEAP_TYPE_GPU_UPLOAD`, `D3D_FEATURE_LEVEL_1_0_GENERIC`, and `D3D_PRIMITIVE_TOPOLOGY_TRIANGLEFAN`.

**DirectXMath:** This Windows SDK includes version [3.19](https://github.com/microsoft/DirectXMath/releases) which has some minor updates for MinGW, Clang/LLVM, and GNUC compatibility.

**NuGet**: The Windows SDK is also offered via [NuGet](https://www.nuget.org/profiles/WindowsSDK).

**ARM64/AArch64**: The Windows SDK (26100) does not support VS 2019 for Win32 on ARM64/AArch64 development as of 10.0.26100.1882, and VS 2022 is highly recommended for all Windows on ARM64 development. Note that ARM32/AArch32 is [deprecated](https://learn.microsoft.com/windows/arm/arm32-to-arm64).

<b>Related:</b> <a href="https://walbourn.github.io/windows-sdk-for-windows-11/">Windows SDK for Windows 11</a>, <a href="https://walbourn.github.io/windows-sdk-for-windows-11,-version-22h2/">Windows SDK for Windows 11, Version 22H2</a>
