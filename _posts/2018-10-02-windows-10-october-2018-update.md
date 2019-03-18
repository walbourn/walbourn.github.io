---
layout: post
title: Windows 10 October 2018 Update
date: 2018-10-02 16:20
author: Chuck Walbourn
comments: true
categories: [uwp, visualc, win10, windowssdk]
---
The <a href="https://blogs.windows.com/windowsexperience/2018/10/02/how-to-get-the-windows-10-october-2018-update/">Windows 10 October 2018 Update</a> (a.k.a. Version 1809) is now available along with the <a href="https://blogs.windows.com/buildingapps/2018/10/02/start-developing-on-windows-10-october-2018-update-today">Windows 10 SDK</a> (10.0.17763). The new SDK can be installed via VS 2017 (15.8.6 update or later) as an optional component under the UWP workload, as an individual component, or as a <a href="https://developer.microsoft.com/en-US/windows/downloads/windows-10-sdk">standalone installer</a>. This release includes some updates to DirectX 12, DirectWrite, DXGI, and <a href="https://walbourn.github.io/directxmath-3-13/">DirectXMath</a>. See <a href="https://docs.microsoft.com/en-us/windows/uwp/whats-new/windows-10-build-17763">What's New in Windows 10 for developers, build 17763</a>.
<!--more-->

<strong>DirectX Raytracing: </strong>This release of the OS and SDK includes DirectX Raytracing. For more details, see <a href="https://blogs.msdn.microsoft.com/directx/2018/10/02/directx-raytracing-and-the-windows-10-october-2018-update/">this blog post</a>.

<b>VS 2015 Users: </b>The Windows 10 SDK (15063, 16299, 17134, 17763) is officially only supported for VS 2017.

<strong>C++/WinRT:</strong> The C++/WinRT headers included in this release of the Windows 10 SDK have a number of updates and improvements, with a few breaking changes. For details, see the <a href="https://docs.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/news">docs</a>.

<strong>Samples:</strong> The following GitHub repos have been updated to use the Windows 10 SDK (17763) release: <a href="https://github.com/Microsoft/DirectXTex/releases">DirectXTex</a>, <a href="https://github.com/Microsoft/DirectXMesh/releases">DirectXMesh</a>, DirectX Tool Kit (<a href="https://github.com/Microsoft/DirectXTK/releases">DX11</a> / <a href="https://github.com/Microsoft/DirectXTK12/releases">DX12</a>), <a href="https://github.com/Microsoft/UVAtlas/releases">UVAtlas</a>, <a href="https://github.com/Microsoft/DirectX-Graphics-Samples/releases/tag/v10.0.17763.0">DirectX-Graphics-Samples</a>, <a href="https://github.com/Microsoft/Windows-universal-samples">Windows-universal-samples</a>

<b>Related:</b> <a href="https://walbourn.github.io/windows-10-sdk-rtm/">Windows 10 SDK RTM</a>, <a href="https://walbourn.github.io/windows-10-sdk-november-2015/">Windows 10 SDK (November 2015)</a>, <a href="https://walbourn.github.io/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK</a>, <a href="https://walbourn.github.io/windows-10-creators-update-sdk/">Windows 10 Creators Update SDK</a>, <a href="https://walbourn.github.io/windows-10-fall-creators-update-sdk/">Windows 10 Fall Creators Update SDK</a>, <a href="https://walbourn.github.io/windows-10-april-2018-update-sdk/">Windows 10 April 2018 Update SDK</a>
