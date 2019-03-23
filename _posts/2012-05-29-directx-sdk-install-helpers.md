---
layout: post
title: DirectX SDK Install Helpers
date: 2012-05-29 15:11
author: Chuck Walbourn
comments: true
categories: [dxsdk, gfwtr]
---
With the transition of the DirectX SDK to the Windows SDK (see <a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a>), and the Windows SDK samples now being hosted online on <a href="http://code.msdn.microsoft.com/">MSDN's Code Gallery</a>, I've begun the process of cleaning up older DirectX SDK samples and posting them directly online.
<!--more-->

Three very important samples are actually helper modules for deployment solutions, and these are now availalble online. These samples do not require the DirectX SDK to build.

<ul>
<li><a href="http://code.msdn.microsoft.com/GameuxInstallHelper-6a9335ca">GameuxInstallHelper</a> - See <a href="https://docs.microsoft.com/en-us/windows/desktop/DxTechArts/windows-game-explorer-integration">Windows Game Explorer for Game Developers</a></li>
<li><a href="http://code.msdn.microsoft.com/Direct3D-11-Install-Helper-3044575e">D3D11InstallHelper</a> - See <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3darticles/direct3d11-deployment">Direct3D 11 Deployment for Game Developers</a></li>
<li><a href="http://code.msdn.microsoft.com/Windows-Firewall-Install-c87391b9">FirewallInstallHelper</a> - See <a href="https://docs.microsoft.com/en-us/windows/desktop/DxTechArts/games-and-firewalls">Windows Firewall for Game Developers</a></li>
</ul>

> These only apply to Win32 desktop applications, not Windows Store apps (a.k.a. Metro style apps) which have their own deployment solution.

These are all Visual Studio 2010 solutions, but can be easily upgraded to build with <a href="https://walbourn.github.io/visual-studio-2012-release-candidate/">Visual Studio 2012</a> (non-Express edition since these are Win32 desktop projects). Be sure to add the preprocessor definition ``_WIN32_WINNT=0x0600`` when upgrading to ensure the resulting binaries are compatible "down-level".

**Update:** These are now available on [GitHub](https://github.com/walbourn/directx-sdk-samples/tree/master/InstallHelpers)
