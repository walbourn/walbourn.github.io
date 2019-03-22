---
layout: post
title: CodePlex VS 2013 Refresh
date: 2013-10-29 12:07
author: Chuck Walbourn
comments: true
categories: [codeplex]
---
Now that VS 2013 has shipped, Windows 8.1 SDK is finished, and Windows 8.1 has hit GA--see this <a href="https://walbourn.github.io/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available/">post</a> for details--, I've made new releases of my <strike>CodePlex</strike>GitHub projects. Here is a summary of the changes since the last time I blogged about these projects.
<!--more-->

All these updates includes the <code>.props</code> files needed to use the Windows 8.1 SDK with VS 2010 and VS 2012, as well as projects for VS 2013.

<h1>DirectX Tool Kit</h1>

<a href="http://go.microsoft.com/fwlink/?LinkId=248929">http://go.microsoft.com/fwlink/?LinkId=248929</a>

The October 2013 release includes support for the Visual Studio 2012 and 2013 Shader Designer (DGSL) via the new <strong>DGSLEffect</strong>, which can be used with both ``.CMO`` and ``.SDKMESH`` models via the <strong>DGSLEffectFactory</strong>. This includes support for both rigid models and skinned models. Also, the <strong>EffectFactory</strong> for BasicEffect has been updated to use SkinnedEffect for skinned models loaded from either ``.CMO`` or ``.SDKMESH``. This update also fixes some problems with UV texture coordinates from .CMO models which were ignoring the materials UV transform matrix.

Details on DGSLEffect and other changes are covered in the project documentation <a href="https://github.com/Microsoft/DirectXTK/wiki/DirectXTK">wiki</a>.

<em><strong>Note:</strong> Support for playing back ``.CMO`` keyframe animations and ``.SDKMESH_ANIM`` files is not yet implemented.</em>

Over the summer a number of smaller improvements have been made to DirectXTK including use of sRGB metadata when loading JPEG, PNG, and TIFF files; support for setting custom encoder properties for the WIC version of <strong>ScreenGrab</strong>; and more <strong>GeometricPrimitive</strong> shapes including Cone, Tetrahedron, Octahedron, Dodecahedron, and Icosahedron. <strong>SimpleMath</strong> was added back in February as 'training wheels' for using DirectXMath and to simplify porting code from XNA Game Studio math.

The five versions of DirectXTK Simple Sample have been updated on MSDN Code Gallery for the October 2013 release.

<ul>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Win32-23db418a">SimpleSample</a> - A Win32 desktop sample</li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Sample-608bc274">SimpleSample</a> - A Windows Store app sample for Windows 8</li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Sample-a0b6de36">SimpelSample</a> - A Windows Store app sample for Windows 8.1</li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Windows-80e6b591">SimpleSample</a> - A Windows phone 8 sample</li>
<li><a href="http://code.msdn.microsoft.com/DXUTDirectXTK-Simple-Win32-9cf797e9">SimpleSample</a> - A Win32 desktop sample that demonstrates DirectXTK in combination with <a href="https://walbourn.github.io/dxut-for-win32-desktop-update/">DXUT</a>.</li>
</ul>

<strong>Update: </strong>DirectX Tool Kit is also hosted on <a href="https://github.com/Microsoft/DirectXTK">GitHub</a>

<strong>Related:</strong> <a href="https://walbourn.github.io/directxtk/">DirectXTK (March 2012)</a>, <a href="https://walbourn.github.io/directxtk-update/">DirectXTK Update (Jan 2013)</a>

<h1>DirectXTex</h1>

<a href="http://go.microsoft.com/fwlink/?LinkId=248926">http://go.microsoft.com/fwlink/?LinkId=248926</a>

The October 2013 release includes updates to take advantage of <a href="https://walbourn.github.io/directxmath-3-06/">DirectXMath 3.06</a>, as well as some fixes for sRGB handling with premultiplied alpha and with the BC7 DirectCompute compressor.

<strong>Update:</strong> DirectXTex is also hosted on <a href="https://github.com/Microsoft/DirectXTex">GitHub</a>

<strong>Related:</strong> <a href="https://walbourn.github.io/directxtex/">DirectXTex (October 2011)</a>, <a href="https://walbourn.github.io/directxtex-update/">DirectXTex Update (June 2013)</a>, <a href="https://walbourn.github.io/directxtex-and-effects-11-update/">DirectXTex and Effects 11 Update (August 2013)</a>

<h1>Effects for Direct3D 11</h1>

<a href="http://go.microsoft.com/fwlink/p/?LinkId=271568">http://go.microsoft.com/fwlink/p/?LinkId=271568</a>

The October 2013 release (11.08) is a minor update for the new VS 2013 toolset and Windows 8.1 SDK.

<strong>Update: </strong>Effects 11 is also hosted on <a href="https://github.com/Microsoft/FX11">GitHub</a>

<strong>Related:</strong> <a href="https://walbourn.github.io/effects-for-direct3d-11-update/">Effects for Direct3D 11 Update (October 2012)</a>, <a href="https://walbourn.github.io/directxtex-and-effects-11-update/">DirectXTex and Effects 11 Update (August 2013)</a>

<h1>DXUT for Direct3D 11</h1>

<a href="http://go.microsoft.com/fwlink/?LinkId=320437">http://go.microsoft.com/fwlink/?LinkId=320437</a>

The October 2013 release (11.04) is a minor update for the new VS 2013 toolset and Windows 8.1 SDK.

<strong>Update:</strong> DXUT11 is also hosted on <a href="https://github.com/Microsoft/DXUT">GitHub</a>

<strong>Related</strong>: <a href="https://walbourn.github.io/dxut-for-win32-desktop-update/">DXUT for Win32 Desktop Update (September 2013)</a>
