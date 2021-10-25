---
layout: msdnpost
title: Who moved my Windows Media Cheese?
date: 2010-08-13 13:55
author: Chuck Walbourn
comments: true
categories: [win7, win8]
---
Since the release of Windows XP Service Pack 2, support for the Windows Media codec (WMV) has been built into the OS, so developers have come to rely on it being there particularly for DirectShow playback of cutscenes or video textures. On Windows Vista, we introduced the Windows Media Foundation APIs as well. Much like the core of <a href="https://docs.microsoft.com/en-us/windows/desktop/DxTechArts/directx-setup-for-game-developers">DirectX</a> becoming part of the OS, these components being present on all modern versions of Windows simplifies the deployment story for applications.
<!--more-->

Alas, the <a href="https://en.wikipedia.org/wiki/European_Commission">European Commission</a> and the <a href="https://en.wikipedia.org/wiki/Fair_Trade_Commission_(South_Korea)" title="Korea Fair Trade Commission">Korea Fair Trade Commission</a> has made that story a bit more complicated...

For games that make use of the Windows Media codec (WMV), Windows Media Foundation, Windows Media Player, the WMP ActiveX control, or other aspects of the Windows Media Format SDK Runtime, you will need to provide some guideance for users with the <a href="http://windows.microsoft.com/en-US/windows7/products/What-is-Windows-7-N-edition">N</a> or KN editions of Windows.

For Windows 7, there are two options for restoring these components to the system

<ul>
 	<li>The<em> Windows Media Feature Pack</em> (<a href="http://go.microsoft.com/fwlink/?LinkId=199842" title="Knowledge Base Article #968211">KB 968211</a>) installs all the Windows Media components. This is required for applications that make use of the Windows Media Foundation, Windows Media Player, or the WMP ActiveX Control.</li>
</ul>

-or-

<ul>
 	<li>The <em>Windows Media Format Feature Pack</em> (<a href="http://go.microsoft.com/fwlink/?LinkId=199843" title="Knowledge Base Article #968212">KB 968212</a>) installs the Windows Media Format SDK Runtime support for the WMV codec. This is sufficient for applications that use the WMV codec through DirectShow. Note that these components are also included in the KB 968211 update.</li>
</ul>

For Windows Vista or Windows XP N editions, installing <a href="http://go.microsoft.com/fwlink/?LinkId=199844">Windows Media Player</a> is the easiest way to restore this functionality.

<em><strong>Putting a note about these editions in your release notes or on your support website should be sufficient.</strong></em> If, however, you are looking for a way to programmatically detect N or KN editions, you should first use existing techniques for trying to use the feature but gracefully handle it not being available (i.e. try to create the COM object or use explicit linking via <code>LoadLibrary</code>). Only if that fails should you look at generating a message to the user. For Win32 desktop applications, you could then use the <a href="https://docs.microsoft.com/en-us/windows/desktop/api/sysinfoapi/nf-sysinfoapi-getproductinfo"><code>GetProductInfo</code></a> function (KN editions identify as N editions that are localized to the Korean language) when handling the error case to verify that is the likely problem. Note this function is only available on Windows Vista or later, so you should use explicit linking for that API as well if you are trying to maintain code compatibility with Windows XP. While there are in fact Windows XP N Editions, they were sold in very low numbers so you are unlikely to have any significant number of users in this situation.

This reliance on Windows Media components is not limited to just gamers, so it is likely that most users will already have installed one of these updates to enable other applications to function. With fresh installs of the OS, particularly if you are explicitly testing with the N or KN editions of Windows, it is important to apply the appropriate Feature Pack.

<strong>Windows 8.0, Windows 8.1, and Windows 10: </strong>See<strong> </strong><a href="https://support.microsoft.com/en-us/kb/3145500">KB 3145500</a> for which Media Feature Pack to install for your OS.

<strong>Windows 10 / Windows 11:</strong> As of Windows 10 Version 1903 (Build 18362) or later, the "Media Feature Pack" is available as a [Windows optional feature](https://support.microsoft.com/en-au/windows/media-feature-pack-for-windows-n-8622b390-4ce6-43c9-9b42-549e5328e407).

Note that both Window Vista and Windows 7 N and KN editions excluded <code>MFPLAT.DLL</code>, but for Windows 8.x there is handling for systems without the Media Feature Pack installed that returns <code>E_NOTIMPL</code> when you call <code><a href="https://docs.microsoft.com/en-us/windows/desktop/api/mfapi/nf-mfapi-mfstartup">MFStartup</a></code>. This simplifies handling for Windows Store apps and UWP apps which cannot make use of explicit linking to system DLLs. Windows Store apps and UWP apps should therefore make use of delay loading (using dloadhelper.lib) for all Media Foundation DLLs.
