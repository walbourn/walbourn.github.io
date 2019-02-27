---
layout: post
title: DirectX SDK Install Helpers
date: 2012-05-29 15:11
author: walbourn
comments: true
categories: [dxsdk, gfwtr, Uncategorized]
---
<p>With the transition of the DirectX SDK to the Windows SDK (see <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">Where is the DirectX SDK?</a>), and the Windows SDK samples now being hosted online&nbsp;on <a href="http://code.msdn.microsoft.com/">MSDN's Code Gallery</a>, I've begun the process of cleaning up older DirectX SDK samples and posting them directly online.</p>
<p>Three very important samples are actually helper modules for deployment solutions, and these are now availalble online. These samples do not require the DirectX SDK to build.</p>
<ul>
<li><a href="http://code.msdn.microsoft.com/GameuxInstallHelper-6a9335ca">GameuxInstallHelper</a>&nbsp;- See <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee419047.aspx">Windows Game Explorer for Game Developers</a></li>
<li><a href="http://code.msdn.microsoft.com/Direct3D-11-Install-Helper-3044575e">D3D11InstallHelper</a>&nbsp;- See <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee416644.aspx">Direct3D 11 Deployment for Game Developers</a></li>
<li><a href="http://code.msdn.microsoft.com/Windows-Firewall-Install-c87391b9">FirewallInstallHelper</a>&nbsp;- See <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee417690.aspx">Windows Firewall for Game Developers</a></li>
</ul>
<p>Note that these only apply to Win32 desktop applications, not Windows Store apps (a.k.a. Metro style apps) which have their own <a href="http://msdn.microsoft.com/en-us/library/windows/apps/hh464929.aspx">deployment solution</a>.</p>
<p>These are all Visual Studio 2010 solutions, but can be easily upgraded to build with <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/31/visual-studio-2012-release-candidate.aspx">Visual Studio 2012</a> (non-Express edition since these are Win32 desktop projects). Be sure to add the preprocessor definition <code>_WIN32_WINNT=0x0600</code> when upgrading to ensure the resulting binaries are compatible "down-level".</p>
