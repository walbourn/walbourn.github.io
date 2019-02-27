---
layout: post
title: Windows 10 SDK RTM
date: 2015-07-30 13:57
author: walbourn
comments: true
categories: [Uncategorized, uwp, win10, windowssdk]
---
Last week saw the release of the final version of <a href="http://blogs.msdn.com/b/chuckw/archive/2015/07/24/visual-studio-2015-rtm.aspx">VS 2015</a>, and yesterday was the release of the Windows 10 SDK (10.0.10240). The Windows 10 SDK is installed via <a href="http://blogs.msdn.com/b/somasegar/archive/2015/07/29/building-apps-for-windows-10-with-visual-studio-2015.aspx">VS 2015 Custom install options</a> or as a <a href="https://go.microsoft.com/fwlink/p/?LinkId=619296">standalone installer</a>. This includes <a href="http://blogs.msdn.com/b/chuckw/archive/2015/04/29/directxmath-3-07.aspx">DirectXMath 3.07</a>, <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/dn914596.aspx">Direct3D 11.3</a>, <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/dn903821.aspx">Direct3D 12.0</a>, DXGI 1.4, Direct2D/DirectWrite 1.3, and <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/ee415802.aspx">XAudio 2.9</a>.

<strong>VS 2015 Users: </strong>Be sure to read <a href="http://blogs.msdn.com/b/vcblog/archive/2015/07/29/developing-for-windows-10-with-visual-c-2015.aspx">this blog post</a> about configuring your VS 2015 projects to use the 10240 build of the Windows 10 SDK--remember that Windows desktop applications with VS 2015 default to building with the Windows 8.1 SDK Spring 2015 release.

<strong>GitHub:</strong> All of my open source project have new releases to support VS 2015 and Windows 10 SDK RTM: <a href="https://github.com/Microsoft/DirectXTK">DirectXTK</a>, <a href="https://github.com/Microsoft/DirectXTex">DirectXTex</a>, <a href="https://github.com/Microsoft/DirectXMesh">DirectXMesh</a>, <a href="https://github.com/Microsoft/UVAtlas">UVAtlas</a>, <a href="https://github.com/Microsoft/FX11">Effects11</a>, and <a href="https://github.com/Microsoft/DXUT">DXUT11</a>.

<strong>Direct3D 12:</strong> The samples for Windows desktop development using Direct3D 12 are on <a href="https://github.com/Microsoft/DirectX-Graphics-Samples/">GitHub</a>. Note that WARP12 is part of the <a href="http://blogs.msdn.com/b/vcblog/archive/2015/03/31/visual-studio-2015-and-graphics-tools-for-windows-10.aspx">Graphics Tools optional feature</a> as it's currently intended only for use by developers.

<strong>XInput:</strong> For UWP, you can continue to use the XInput 1.4 API but need to change from linking to <code>xinput.lib</code> to <code>xinputuap.lib</code>. Alternatively, you can make use of the <a href="http://blogs.msdn.com/b/chuckw/archive/2014/09/05/directx-tool-kit-now-with-gamepads.aspx">GamePad</a> class in <a href="https://github.com/Microsoft/DirectXTK">DirectX Tool Kit</a> which uses the new <code><a href="https://msdn.microsoft.com/en-us/library/windows/apps/windows.gaming.input">Windows.Gaming.Input</a></code> API. See <a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/26/xinput-and-windows-8-consumer-preview.aspx">XInput and Windows 8</a>.

<strong>XAudio:</strong> With the Windows 10 SDK, if you are linking with <code>xaudio2.lib</code> you are linking against XAudio 2.9 and should build your application using <code>_WIN32_WINNT=0x0A00</code>. If you want to use XAudio 2.8 with the Windows 10 SDK, you need to set <code>_WIN32_WINNT=0x0602</code> or <code>_WIN32_WINNT=0x0603</code> and link against <code>xaudio2_8.lib</code>. See <a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/02/xaudio2-and-windows-8-consumer-preview.aspx">XAudio2 and Windows 8</a> for more details.

<strong>VS 2013 Users: </strong>As with the past few releases, the Windows 10 SDK only integrates with the latest Visual Studio, VS 2015. You can use the Windows 10 SDK with VS 2013 by using the props attached per this <a href="http://blogs.msdn.com/b/vcblog/archive/2012/11/23/using-the-windows-8-sdk-with-visual-studio-2010-configuring-multiple-projects.aspx">Visual C+ Team Blog</a>.

<strong>Samples:</strong> Official Windows samples are hosted on GitHub: <a href="https://github.com/Microsoft/Windows-universal-samples">Windows-universal-samples</a>, <a href="https://github.com/Microsoft/Windows-classic-samples">Windows-classic-samples</a>, <a href="https://github.com/Microsoft/Windows-driver-samples">Windows-driver-samples</a>. See also <a href="http://blogs.msdn.com/b/chuckw/archive/2013/09/20/directx-sdk-samples-catalog.aspx">DirectX SDK Samples Catalog</a>.

<strong>Related:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2015/11/30/windows-10-sdk-november-2015.aspx">Windows 10 SDK (November 2015),</a> <a href="https://blogs.msdn.microsoft.com/chuckw/2016/08/02/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK</a>

<a href="https://msdnshared.blob.core.windows.net/media/MSDNBlogsFS/prod.evol.blogs.msdn.com/CommunityServer.Components.PostAttachments/00/10/63/19/48/Windows10SDKVS13.zip">Windows10SDKVS13.zip</a>
