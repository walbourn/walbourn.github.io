---
layout: msdnpost
title: Windows 10 April 2018 Update SDK
date: 2018-05-02 22:52
author: Chuck Walbourn
comments: true
categories: [uwp, win10, windowssdk]
---
The <em>Windows 10 April 2018 Update</em> (a.k.a. Version 1803) is <a href="https://blogs.windows.com/buildingapps/2018/04/30/start-developing-on-windows-10-april-2018-update-today/">now available</a> along with the Windows 10 SDK (10.0.17134). The new SDK can be installed via VS 2017 (<a href="https://walbourn.github.io/vs-2017-15-7-update/">15.7 update</a>) or as a <a href="https://go.microsoft.com/fwlink/?linkid=870807">standalone installer</a>. This release includes some updates to DirectX 12, DirectWrite, and DXGI. See <a href="https://docs.microsoft.com/en-us/windows/uwp/whats-new/windows-10-build-17134">What's New in Windows 10 for developers, build 17134</a>.
<!--more-->

<strong>VS 2015 Users:</strong> The Windows 10 SDK (15063, 16299, 17134) is officially only supported for VS 2017.

<strong>C++/WinRT:</strong> The new C++/WinRT headers for this Windows SDK are included. You no longer need to make use of the GitHub project (which is now archived) or the NuGet package when using C++/WinRT projections for the latest Windows 10 SDK. See <a href="https://devblogs.microsoft.com/cppblog/cppwinrt-is-now-included-the-windows-sdk/">this blog post</a>.

<strong>Samples:</strong> The <a href="https://github.com/Microsoft/DirectX-Graphics-Samples/">DirectX-Graphics-Samples</a> repository of DirectX 12 samples has been updated to use the Windows 10 SDK (17134). This includes samples for the recently announced <a href="https://devblogs.microsoft.com/directx/announcing-microsoft-directx-raytracing/">DirectX Raytracing</a> API as well. <a href="https://github.com/Microsoft/Windows-universal-samples">Windows-universal-samples</a> and <a href="https://github.com/Microsoft/Xbox-ATG-Samples">Xbox-ATG-Samples</a> also now use the Windows 10 SDK (17134)

<strong>GitHub: </strong>There are May 31, 2018 releases for DirectX Tool Kit (<a href="https://github.com/Microsoft/DirectXTK/releases">DX11</a> / <a href="https://github.com/Microsoft/DirectXTK12/releases">DX12</a>), <a href="https://github.com/Microsoft/DirectXTex/releases">DirectXTex</a>, <a href="https://github.com/Microsoft/DirectXMesh/releases">DirectXMesh</a>, <a href="https://github.com/Microsoft/UVAtlas/releases">UVAtlas</a>, <a href="https://github.com/Microsoft/FX11/releases">FX11</a>, and <a href="https://github.com/Microsoft/DXUT/releases">DXUT</a> that all use the Windows 10 SDK (17314) when building with VS 2017.

<b>Related:</b> <a href="https://walbourn.github.io/windows-10-sdk-rtm/">Windows 10 SDK RTM</a>, <a href="https://walbourn.github.io/windows-10-sdk-november-2015/">Windows 10 SDK (November 2015)</a>, <a href="https://walbourn.github.io/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK</a>, <a href="https://walbourn.github.io/windows-10-creators-update-sdk/">Windows 10 Creators Update SDK</a>, <a href="https://walbourn.github.io/windows-10-fall-creators-update-sdk/">Windows 10 Fall Creators Update SDK</a>, <a href="https://walbourn.github.io/windows-10-october-2018-update/">Windows 10 October 2018 Update SDK</a>, <a href="https://walbourn.github.io/windows-10-may-2019-update/">Windows 10 May 2019 Update SDK</a>
