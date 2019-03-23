---
layout: post
title: XNA Math Version 2.05 - Smoothing the transition to DirectXMath
date: 2012-06-22 11:45
author: Chuck Walbourn
comments: true
categories: [directxmath]
---
The July 2012 release of the Xbox 360 XDK includes a new version of XNA Math, version 2.05. We are making it available here for Windows developers. The update is subject to the <span style="text-decoration: line-through">same EULA as the <a href="http://www.microsoft.com/en-us/download/details.aspx?id=6812">DirectX SDK</a> (June 2010) release</span> <a href="https://opensource.org/licenses/MIT">MIT</a> license.
<!--more-->

<strong>What's New</strong>

XNA Math version 2.05 includes:

<ul>
 	<li>Template forms have been added for <code>XMVectorSwizzle</code>, <code>XMVectorPermute</code>, <code>XMVectorShiftLeft</code>, <code>XMVectorRotateLeft</code>, <code>XMVectorRotateRight</code>, and <code>XMVectorInsert</code>.</li>
 	<li>The <code>XM_STRICT_XMMATRIX</code> compilation define has been added for opaque <code>XMMATRIX</code>.</li>
 	<li>Stream stride and count arguments have been changed to <code>size_t</code>.</li>
 	<li>The <em>pDeterminant</em> parameter of <code>XMMatrixInverse</code> is now optional.</li>
 	<li>Additional operator= overloads for <code>XMBYTEN4</code>, <code>XMBYTE4</code>, <code>XMUBYTEN4</code>, and <code>XMUBYTE4</code> types are now available.</li>
</ul>

See <a href="https://walbourn.github.io/xna-math-version-2-04/">XNA Math version 2.04</a> for details on what changed previously compared to XNA Math version 2.03 in the DirectX SDK (June 2010) release.

<strong>Why update XNA Math?</strong>

The <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a> library that ships as part of the <em>Windows 8.0 </em>SDK and <em>Visual Studio 2012 RC</em> is the recommended latest version of "XNA Math". You can think of it as "XNAMath version 3.x". It is very similar although it does have a number of 'breaking' <a href="https://docs.microsoft.com/en-us/windows/desktop/dxmath/pg-xnamath-whatsnew">changes</a> (there's a <a href="https://docs.microsoft.com/en-us/windows/desktop/dxmath/pg-xnamath-migration">migration guide</a> as well), requires Visual Studio 2010 or later, and is not available for the Xbox 360.

The primary purpose for the XNA Math version 2.05 update is for developers who need to maintain compatibility with the Xbox 360 version in the XDK or VS 2008, but want to prepare for migration to DirectXMath or support compiling with either math library.

<strong>XNAMath / DirectXMath Portability Recommendations</strong>

For an example of how to use this, see <a href="https://github.com/Microsoft/DirectXTex">DirectXTex</a> which builds with either DirectXMath or using the <code>USE_XNAMATH</code> define with XNA Math version 2.05. Here are some guidelines for achieving this:

<ul>
 	<li>Set preprocessor defines <code>XM_STRICT_VECTOR4</code> and <code>XM_STRICT_MATRIX</code> in your build to ensure you are using <code>XMVECTOR</code> and <code>XMMATRIX</code> as opaque types.</li>
 	<li>Where possible, prefer the template forms to function forms. Note that for template forms, you should use simple indices (0-7) rather than the <code>XM_PERMUTE_?</code> values which have different definitions in the two library versions or <code>XM_SWIZZLE_?</code> which is not defined for XNA Math.</li>
 	<li>Make use of <code>typedef</code> or <code>using namespace</code> statements to cope with the lack of namespaces in XNA Math</li>
</ul>

<strong>Note:</strong> DirectXMath is now hosted on <a href="https://github.com/Microsoft/DirectXMath/releases/tag/jul2012">GitHub</a>.

<a href="https://walbourn.github.io/download/GXNAMath_205.zip">XNAMath_205.zip</a>
