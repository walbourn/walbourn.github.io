---
layout: post
title: GitHub, NuGet, and VSTS
date: 2018-04-30 11:13
author: Chuck Walbourn
comments: true
categories: [github]
---
There are April 2018 releases on GitHub for DirectX Tool Kit (<a href="https://github.com/Microsoft/DirectXTK/releases">DX11</a> / <a href="https://github.com/Microsoft/DirectXTK12/releases">DX12</a>), <a href="https://github.com/Microsoft/DirectXTex/releases">DirectXTex</a>, <a href="https://github.com/Microsoft/DirectXMesh/releases">DirectXMesh</a>, and <a href="https://github.com/Microsoft/UVAtlas/releases">UVAtlas</a>. These were more minor releases focused on code quality, fixing a few bugs, and cleaning up some <a href="https://devblogs.microsoft.com/cppblog/c-code-analysis-improvements-for-visual-studio-2017-15-7-preview-1/">new /analyze</a> issues based on the <a href="https://github.com/MicrosoftDocs/visualstudio-docs/blob/master/docs/code-quality/using-the-cpp-core-guidelines-checkers.md">C++ Core Checker</a> rules that will be appearing in Visual Studio 2017 (15.7 update) which is currently in preview.
<!--more-->

I'm mentioning these because there are some changes happening with <a href="https://www.nuget.org/">NuGet </a>where I've also been publishing new releases of many of these libraries that has some important implications I wanted to announce.

<h1>The Good</h1>

NuGet packages are getting support for digital signing, which means better security when consuming signed packages in your applications. Packages published by Microsoft now also have more official organizational ownership rather than being published by individual Microsoft developers private Microsoft Accounts.

See <a href="https://blog.nuget.org/20180301/NuGet-Spring-2018-Roadmap.html">this NuGet blog post</a> for more details.

To support digital signing, I'm setting up <a href="https://www.visualstudio.com/vso/">Visual Studio Team Services (VSTS) </a> build support for my libraries so they can be more officially built than just sitting on my machine. Much of Microsoft's internal processes have migrated to using VSO for building including my group's samples work, so this is generally all goodness and it's been a good learning experience making use of the cloud-based build services.

<h1>The Bad</h1>

One consequence of moving to the VSO build solution, however, is that I need to drop support for Visual Studio 2013, Windows Store 8.1, and Windows Phone 8.1. The VSO hosted build services support VS 2015 and VS 2017, so I will continue to support VS 2015 Update 3 & VS 2017 for Win32 desktop applications for Windows 7 SP1 or later, Universal Windows Platform (UWP) apps, and Xbox One XDK development.

As such, the April releases above will be the last to support Visual Studio 2013, Windows Store 8.1, or Windows Phone 8.1. The existing NuGet packages for these platforms are still available (<code>directxtk_desktop_2013</code>, <code>directxtk_windowsstore_8_1</code>, <code>directxtk_windowsphone_8_1</code>, and <code>fx11_desktop_2013</code>), but will no longer receive any updates--much like I had already done for the Windows Phone 8.0 package (<code>directxtk_windowsphone_8</code>) when I dropped VS 2012 support some time ago.

Mine are not the only open source packages from Microsoft so affected, so expect most of them to be dropping these platforms as well.

<em>As an aside, this change is good news for me. This greatly reduces the number of configurations I maintain and let's me focus on the more complete C++14 language and Standard library conformance in VS 2015 or later with a lot of messy conditional compilation. I realize it's a potential hardship on some users of these libraries, but you can continue to use the April 2018 or earlier releases.</em>

Note that Xbox One XDK development never supported VS 2013.

<h1>The Ugly</h1>

Another consequence of the move to the VSO build solution is that I can't make use of the <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">legacy DirectX SDK</a> in those solutions that are published as NuGet packages. For the most part I don't need the legacy DirectX SDK for anything since that's one of the main motivations for doing these libraries in the first place. There is, however, one specific scenario that still require the legacy DirectX SDK: <a href="https://walbourn.github.io/xaudio2-and-windows-8/">XAudio 2.7 support for Windows 7</a>.

Up through the April 2018 release, the NuGet <code>directxtk_desktop_2015</code> package includes <code>DirectXTKAudioDX.lib</code> which uses XAudio 2.7 to support Windows 7, but I will now have to make it include the <code>DirectXTKAudioWin8.lib</code> instead for the May 2018 and later versions of the NuGet package. That means if you using a project that is set up to use DirectX Tool Kit for Audio with Windows 7 (``_WIN32_WINNT`` set to 0x0600 or 0x0601), you'll now get a build failure including <code>"Audio.h"</code> or trying to link. The newer Win32 desktop NuGet packages will work fine if you are building for Windows 8 or later (``_WIN32_WINNT`` set to 0x0602, 0x0603, or 0x0A00).

Use of the <code>DirectXTKAudioDX.lib</code> already required some gymnastics with the legacy DirectX SDK and imposed specific deployment requirements using legacy DirectSetup. If you need DirectX Tool Kit for Audio support on Windows 7, I recommend you move to using <a href="https://github.com/Microsoft/DirectXTK/wiki/DirectXTK#using-project-to-project-references">project-to-project references</a> instead of the NuGet package.

The Win32 desktop NuGet package will still be built for Windows 7 SP1 support for the graphics, input, and math functionality so this only affects you if you are using <a href="https://github.com/Microsoft/DirectXTK/wiki/Audio">DirectX Tool Kit for Audio</a>. There are also no issues when using the UWP packages since XAudio 2.8 or later is always available on those platforms.

<strong>C++/WinRT:</strong> Note that I'm also no longer updating the <code>cppwinrt</code> NuGet package. As of the Windows 10 SDK (17343), the C++/WinRT headers are include in the Windows SDK per <a href="https://devblogs.microsoft.com/cppblog/cppwinrt-is-now-included-the-windows-sdk/">this blog post</a>. Therefore, the 2017.10.13 NuGet package which supported the Windows 10 Fall Creators Update SDK (16299) is the last one, and the related <a href="https://github.com/Microsoft/cppwinrt">GitHub project</a> is now archived.

<strong>Update:</strong> See <a href="https://blog.nuget.org/20180522/Introducing-signed-package-submissions.html">this blog post</a> for the latest information on NuGet signing support. The following NuGet packages are now available digitally signed: DirectXMesh (<a href="https://www.nuget.org/packages/directxmesh_desktop_2015/2018.6.1.2">directxmesh_desktop_2015</a>, <a href="https://www.nuget.org/packages/directxmesh_uwp/2018.6.1.2">directxmesh_uwp</a>), DirectXTex (<a href="https://www.nuget.org/packages/directxtex_desktop_2015/2018.6.1.2">directxtex_desktop_2015</a>, <a href="https://www.nuget.org/packages/directxtex_uwp/2018.6.1.2">directxtex_uwp</a>), DirectX Tool Kit for DX 11 (<a href="https://www.nuget.org/packages/directxtk_desktop_2015/2018.6.1.2">directxtk_desktop_2015</a>, <a href="https://www.nuget.org/packages/directxtk_uwp/2018.6.1.2">directxtk_uwp</a>), DirectX Tool Kit for DX12 (<a href="https://www.nuget.org/packages/directxtk12_desktop_2015/2018.6.1.2">directxtk12_desktop_2015</a>, <a href="https://www.nuget.org/packages/directxtk12_uwp/2018.6.1.2">directxtk12_uwp</a>), DirectXMath (<a href="https://www.nuget.org/packages/directxmath/2018.7.23.2">directxmath</a>), and Effects for Direct3D 11 (<a href="https://www.nuget.org/packages/fx11_desktop_2015/2018.9.7.1">fx11_desktop_2015</a>).
