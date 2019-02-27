---
layout: post
title: Windows 10 Technical Preview
date: 2014-10-03 11:00
author: walbourn
comments: true
categories: [Uncategorized, win10]
---
<p>The next version of Windows is now available as a Technical Preview for developers via the <a href="http://preview.windows.com/">Windows Insiders</a> program and for MSDN Subscribers. For more details, see <a href="http://blogs.windows.com/bloggingwindows/2014/09/30/announcing-windows-10/">Announcing Windows 10</a>.</p>
<p><strong>DirectX SDK Debug Layer: </strong>For Windows 10 Technical Preview (<a href="http://blogs.windows.com/bloggingwindows/2015/01/23/january-build-now-available-to-the-windows-insider-program/">9926</a> or later), you need to&nbsp;enable the debug layer as a Windows optional&nbsp;feature to successfully use <code>D3D11_CREATE_DEBUG_DEVICE</code> or the Visual Studio 2013 Graphics Diagnostics tools: Start -&gt; Settings -&gt; System -&gt; Optional features -&gt; Add a feature; select "Graphics Tools". See <a href="http://blogs.msdn.com/b/vcblog/archive/2015/03/31/visual-studio-2015-and-graphics-tools-for-windows-10.aspx">this post</a> for details.</p>
<p><strong>Win32 desktop games:</strong> The existing guidance for quality Win32 desktop games running on Windows 7, Windows 8.0, and Windows 8.1 all applies to Windows 10 as well (see <a href="http://blogs.msdn.com/b/chuckw/archive/2014/08/07/10287042.aspx">Desktop Games on Windows 8.x</a>). Note that there is a new <code>&lt;compatibility&gt;</code> manifest section GUID for Windows 10 (see <a href="http://blogs.msdn.com/b/chuckw/archive/2013/09/10/manifest-madness.aspx">Manifest Madness</a>), and <code>VerifyVersionInfo</code> is now subject to the same manifest-based behavior as <code>GetVersion(Ex)</code>.</p>
<p><strong>DirectX 12:</strong> If you are looking to try out DirectX 12, you should read the <a href="http://blogs.msdn.com/b/directx/archive/2014/10/01/directx-12-and-windows-10.aspx">DirectX Developer Blog</a> post and sign up for the DirectX 12 <a href="http://1drv.ms/1dgelm6">Early Access</a> program.</p>
<p><strong>Enterprise:</strong> If you are curious about the business version of Windows 10, see this <a href="http://blogs.windows.com/business/2014/09/30/introducing-windows-10-for-business/">post</a>.</p>
<p><strong>Web developers:</strong> The Technical Preview includes IE11, but there are a few <a href="http://blogs.msdn.com/b/ie/archive/2014/10/01/internet-explorer-and-the-windows-10-technical-preview.aspx">improvements</a> for Windows 10.</p>
<p><strong>Windows Store and Windows phone developers:</strong> See this <a href="http://blogs.windows.com/buildingapps/2014/09/30/universal-windows-apps-get-better-with-windows-10/">post</a>.</p>
<p><strong>Command Prompt:</strong> There's some fun features added for Windows 10's command prompt. See this <a href="http://blogs.msdn.com/b/winsdk/archive/2014/10/02/windows-10-threshold-changes-to-the-windows-command-prompt.aspx">post</a>.</p>
