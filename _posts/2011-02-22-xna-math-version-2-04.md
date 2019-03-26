---
layout: post
title: XNA Math Version 2.04
date: 2011-02-22 16:13
author: Chuck Walbourn
comments: true
categories: [xnamath, directxmath]
---
The February 2011 release of the Xbox 360 XDK includes a new version of XNA Math, version 2.04. We are making it available here for Windows developers. The update is subject to the same EULA as the DirectX SDK (June 2010) release.
<!--more-->

<h1>What's New</h1>

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
	<li>Corrected range <a href="https://walbourn.github.io/known-issues-in-xnamath-v2-03/">issues</a> with SSE implementations of <code>XMVectorFloor</code> and <code>XMVectorCeiling</code></li>
	<li>Resolved a boundary issue with <code>XMLoadShort*</code> and <code>XMLoadByte*</code> that previously triggered an assert on values -32768 / -128</li>
</ul>

<h1>Release Notes</h1>

<ul>
	<li>Due to a bug in optimizations done by the Visual Studio 2010 C/C++ compiler, some XNA Math functions will not work properly when used with <code>_XM_NO_INTRINSICS_</code>. This bug only appears at full optimization settings (/Ox) for Windows 32-bit, and may appear at any optimization setting for Windows 64-bit (x64). This issue does not impact the SSE2 intrinsic version of the XNA Math functions. This issue is fixed in <a href="https://walbourn.github.io/visual-studio-2010-service-pack-1/">Visual Studio 2010 Service Pack 1</a>.</li>
</ul>

<strong>Update: </strong>There is a newer revision of this math library available as part of the <em>Windows 8.0 SDK </em>and <em>Visual Studio 11 Beta </em>known as "<a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a>". You can think of it as "XNAMath version 3.x". It is very similiar although it does have a number of 'breaking' <a href="https://docs.microsoft.com/en-us/windows/desktop/dxmath/pg-xnamath-whatsnew">changes</a> (there's a <a href="https://docs.microsoft.com/en-us/windows/desktop/dxmath/pg-xnamath-migration">migration guide</a> as well), requires Visual Studio 2010 or later, and is not available for the Xbox 360. If you need to maintain compatibility with the Xbox 360 version in the XDK or VS 2008, you should continue to use XNAMath version 2.x.

<strong>GitHub:</strong> Note that DirectXMath is now hosted on <a href="https://github.com/Microsoft/DirectXMath">GitHub</a> under the [MIT license](https://opensource.org/licenses/MIT)

<a href="https://walbourn.github.io/download/XNAMath_204.zip">XNAMath_204.zip</a>
