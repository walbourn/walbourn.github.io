---
layout: post
title: Windows 10 Fall Creators Update SDK
date: 2017-10-11 13:19
author: walbourn
comments: true
categories: [Uncategorized, uwp, visualc, win10, windowssdk]
---
The <em>Windows 10 Fall Creators Update</em> (a.k.a. Version 1710) <span style="text-decoration: line-through">will be released <a href="https://blogs.windows.com/windowsexperience/2017/09/01/create-and-play-this-holiday-with-the-windows-10-fall-creators-update-coming-oct-17/">October 17</a></span> is now <a href="https://blogs.windows.com/windowsexperience/2017/10/17/whats-new-windows-10-fall-creators-update/">available</a>. The <em>Windows 10 Fall Creators Update SDK</em> (10.0.16299) is <a href="https://blogs.windows.com/buildingapps/2017/10/10/windows-developer-day-london-windows-10-fall-creators-update-sdk-availability/">now available</a> and can be installed via VS 2017 (<a href="https://blogs.msdn.microsoft.com/visualstudio/2017/10/10/visual-studio-2017-version-15-4-released/">15.4</a>) or as <a href="https://go.microsoft.com/fwlink/?linkid=859886">a standalone installer</a>. This includes <a href="https://blogs.msdn.microsoft.com/chuckw/2017/06/28/directxmath-3-11/">DirectXMath 3.11</a>, updated <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/mt748631.aspx">DirectX 12</a>, and updated <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/hh802478.aspx">Direct2D</a>/<a href="https://msdn.microsoft.com/en-us/library/windows/desktop/hh802480.aspx">DirectWrite</a>. See <a href="https://docs.microsoft.com/en-us/windows/uwp/whats-new/windows-10-build-16299">What's New in Windows 10 for developers, build 16299</a>.

The <em>Windows 10 Fall Creators Update SDK</em> resolves a number of conformance errors in Windows system headers enabling the use of the <code>/permissive-</code> switch with the latest <a href="https://blogs.msdn.microsoft.com/vcblog/2017/09/11/two-phase-name-lookup-support-comes-to-msvc/">two-phase name lookup</a> (thus allowing you to avoid the need to use <code>/Zc:twoPhase-</code>).

Note: See <a href="https://support.microsoft.com/en-us/help/4034825/features-that-are-removed-or-deprecated-in-windows-10-fall-creators-up">KB4034825</a> for some deprecation notes for the <em>Windows 10 Fall Creators Update</em>

<strong>C/C++ Compiler:</strong> The VS 2017 (15.4) compiler contains a few servicing updates since the previous update (version 19.11.25547).

<strong>VS 2015 Users:</strong> The Windows 10 SDK (15063, 16299) is officially only supported for VS 2017.

<strong>C++/WinRT:</strong> New C++/WinRT headers for this Windows 10 SDK are now available on <a href="https://github.com/Microsoft/cppwinrt/releases/tag/fall_2017_creators_update_for_vs_15.3">GitHub</a> and <a href="https://www.nuget.org/packages/cppwinrt/2017.10.13.1">NuGet</a>.

<strong>UWP: </strong>Prior to the VS 2017 (15.4 update) you had to install older Windows 10 SDKs to be able to set an older "Minimum version" in the UWP project properties. This has been fixed so that you only need the Windows 10 SDK (16299) and can select all older releases (15063, 14393, 15086, 10240) as the minimum if needed.

<strong>FXC:</strong> With the Windows 10 SDK (15063/16299), the FXC compiler and the <code>D3DCompiler_47.DLL</code> were made side-by-side. From the Developer Command Prompt for VS 2017, using FXC will use the Windows 10 Anniversary Update (14393) version. You need to explicitly select the side-by-side version if you want to use a newer one from the command-line: <code>"%WindowsSdkBinPath%%WindowsSDKVersion%\x86\fxc.exe"</code>

<strong>GitHub:</strong> I've made new releases of my various libraries that now build with the Windows 10 SDK (16299): DirectX Tool Kit (<a href="https://github.com/Microsoft/DirectXTK/releases">DX11</a>, <a href="https://github.com/Microsoft/DirectXTK12/releases">DX12</a>), <a href="https://github.com/Microsoft/DirectXTex/releases">DirectXTex</a>, <a href="https://github.com/Microsoft/DirectXMesh/releases">DirectXMesh</a>, and <a href="https://github.com/Microsoft/UVAtlas/releases">UVAtlas</a>.

<strong>Samples: </strong><a href="https://github.com/Microsoft/Windows-universal-samples">Windows-universal-samples</a>, <a href="https://github.com/Microsoft/DirectX-Graphics-Samples">DirectX-Graphics-Samples</a>, <a href="https://github.com/Microsoft/Xbox-ATG-Samples/releases">Xbox-ATG-Samples</a>, and <a href="https://github.com/walbourn/directx-sdk-samples">directx-sdk-samples</a> have been updated to use the new Windows 10 SDK (16299). There is also a new version of <code>D3DX12.H</code> updated for the updated Direct3D 12 headers (now included in <a href="https://github.com/walbourn/directx-vs-templates">directx-vs-templates</a>)

<strong>Related:</strong> <a href="https://blogs.msdn.microsoft.com/chuckw/2015/07/30/windows-10-sdk-rtm/">Windows 10 SDK RTM</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2015/11/30/windows-10-sdk-november-2015/">Windows 10 SDK (November 2015)</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2016/08/02/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2017/04/06/windows-10-creators-update-sdk/">Windows 10 Creators Update SDK</a>
