---
layout: post
title: XNA Math Version 2.04
date: 2011-02-22 16:13
author: walbourn
comments: true
categories: [Uncategorized, xnamath]
---
The February 2011 release of the Xbox 360 XDK includes a new version of XNA Math, version 2.04. We are making it available here for Windows developers. The update is subject to the same EULA as the <a title="DirectX SDK" href="http://msdn.microsoft.com/directx/">DirectX SDK</a> (June 2010) release.

<strong>What's New</strong>

XNA Math version 2.04 includes:
<ul>
	<li>Addition of new data types and associated load-store functions:
<ul>
	<li>XMBYTEN2, XMBYTE2, XMUBYTEN2, XMUBYTE2</li>
	<li>XMLoadByteN2, XMLoadByte2, XMLoadUByteN2, XMLoadUByte2</li>
	<li>XMStoreByteN2, XMStoreByte2, XMStoreUByteN2, XMStoreUByte2</li>
	<li>XMINT2, XMUINT2, XMINT3, XMUINT3, XMINT4, XMUINT4</li>
	<li>XMLoadSInt2, XMLoadUInt2, XMLoadSInt3, XMLoadUInt3, XMLoadSInt4, XMLoadUInt4</li>
	<li>XMStoreSInt2, XMStoreUInt2, XMStoreSInt3, XMStoreUInt3, XMStoreSInt4, XMStoreUInt4</li>
</ul>
</li>
	<li>Marked most single-parameter C++ constructors with 'explicit' keyword</li>
	<li>Corrected range <a title="issues" href="http://blogs.msdn.com/b/chuckw/archive/2011/01/20/known-issues-in-xnamath-v2-03.aspx">issues</a> with SSE implementations of <code>XMVectorFloor</code> and <code>XMVectorCeiling</code></li>
	<li>Resolved a boundary issue with <code>XMLoadShort*</code> and <code>XMLoadByte*</code> that previously triggered an assert on values -32768 / -128</li>
</ul>
<strong>Release Notes</strong>
<ul>
	<li>Due to a bug in optimizations done by the Visual Studio 2010 C/C++ compiler, some XNA Math functions will not work properly when used with <code>_XM_NO_INTRINSICS_</code>. This bug only appears at full optimization settings (/Ox) for Windows 32-bit, and may appear at any optimization setting for Windows 64-bit (x64). This issue does not impact the SSE2 intrinsic version of the XNA Math functions. This issue is fixed in <a title="Visual Studio 2010 Service Pack 1" href="http://blogs.msdn.com/b/chuckw/archive/2011/03/16/visual-studio-2010-service-pack-1.aspx">Visual Studio 2010 Service Pack 1</a>.</li>
</ul>
<strong>Update: </strong>There is a newer revision of this math library available as part of the <em>Windows 8.0 SDK </em>and <em>Visual Studio 11 Beta </em>known as "<a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/27/introducing-directxmath.aspx">DirectXMath</a>". You can think of it as "XNAMath version 3.x". It is very similiar although it does have a number of 'breaking' <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh855941.aspx">changes</a> (there's a <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee418730.aspx">migration guide</a> as well), requires Visual Studio 2010 or later, and is not available for the Xbox 360. If you need to maintain compatibility with the Xbox 360 version in the XDK or VS 2008, you should continue to use XNAMath version 2.x.

<strong>GitHub:</strong> Note that DirectXMath is now hosted on <a href="https://github.com/Microsoft/DirectXMath">GitHub</a>.

<a href="https://msdnshared.blob.core.windows.net/media/MSDNBlogsFS/prod.evol.blogs.msdn.com/CommunityServer.Components.PostAttachments/00/10/13/29/00/XNAMath_204.zip">XNAMath_204.zip</a>
