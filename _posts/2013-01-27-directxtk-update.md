---
layout: post
title: DirectXTK Update
date: 2013-01-27 13:32
author: Chuck Walbourn
comments: true
categories: [codeplex, direct3d]
---
The <em>DirectX Toolkit (</em>aka<em> DirectXTK)</em> for Direct3D 11 <a href="https://walbourn.github.io/directxtk/">introduced</a> last year and made an official CodePlex project has continued to improve. The DirectXTK project provides 'runtime' utility shared-source C++ code to replace the <a href="https://walbourn.github.io/where-is-the-directx-sdk/">deprecated D3DX</a> library for Win32 desktop applications using Direct3D 11 (Windows 8, Windows 7, Windows Vista SP2+KB971644, and the Server equivalents) as well as Windows Store apps on Windows 8. This complements <a href="https://walbourn.github.io/directxtex/">DirectXTex</a> which provides shared-source C++ code for 'build time' texture processing that used to ship in D3DX, <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a> and <a href="https://walbourn.github.io/spherical-harmonics-math/">Spherical Harmonics math</a> which replace D3DXMath, and the <a href="https://walbourn.github.io/hlsl-fxc-and-d3dcompile/">D3DCompile</a> API which replaced the once integrated HLSL compiler. For Win32 desktop applications, there's also an <a href="http://go.microsoft.com/fwlink/p/?LinkId=271568">Effects 11</a> to replace the FX library from D3DX9.
<!--more-->

The original toolkit consisted of some key functionality based on the XNA Game Studio design: <a href="http://www.shawnhargreaves.com/blog/spritebatch-and-basiceffect-for-c-direct3d-11.html">SpriteBatch, Effects, GeometricPrimitive</a> along with some helper code (CommonStates, VertexTypes) and runtime texture loaders (DDSTextureLoader and WICTextureLoader). Shawn then added <a href="http://www.shawnhargreaves.com/blog/directxtk-now-includes-spritefont.html">SpriteFont</a> and support for <a href="http://www.shawnhargreaves.com/blog/directx-tool-kit-now-supports-windows-phone-8.html">Windows phone 8</a>, and I added the <strong>ScreenGrab</strong> module to support the runtime creation of 'screenshots' from render targets. A fellow Microsoftie also contributed code for a <a href="http://www.shawnhargreaves.com/blog/directxtk-october-2012-release.html">geodesic sphere</a> <strong>GeometricPrimitive</strong> as an alternative to the traditional UV-sphere.

The most recent additions to the library include

<ul>
<li><a href="http://www.shawnhargreaves.com/blog/directxtk-primitivebatch-helper-makes-it-easy-to-draw-user-primitives-with-d3d11.html">PrimitiveBatch </a>- simple and efficient way to draw dynamic geometry as a replacement for the Direct3D 9 "DrawUP" and "DrawIndexedUP" functions, ideal for debug geometry or on-the-fly procedural geometry generation.</li>
<li>Improved <strong>GeometricPrimitive</strong> with support for proper winding order for both right-handed coordinates (the assumed default based on the XNA Game Studio conventions) and left-handed coordinates (typically used by DirectX C++ applications), as well as support for drawing them with custom effects.</li>
<li><a href="https://github.com/Microsoft/DirectXTK/wiki/Model">Model</a> - This draws simple meshes loaded from Visual Studio 2012's built in Autodesk FBX exporter <code>.CMO</code> files or the legacy DirectX SDK <a href="https://walbourn.github.io/samples-content-exporter-update/">Samples Content Exporter</a> <code>.SDKMESH</code> files. This is currently limited to rigid models but we'll be working to add skinning support.</li>
</ul>
<p>The <strike>CodePlex</strike>GitHub site hosts the latest version of the library, <a href="https://github.com/Microsoft/DirectXTK/wiki">documentation</a>, discussion forums, bug reports, and feature requests. Developers can use Visual Studio 2012 or use Visual Studio 2010 with the standalone Windows 8.0 SDK.</p>
<a href="https://github.com/Microsoft/DirectXTK">https://github.com/Microsoft/DirectXTK</a>

We are also getting some samples using DirectXTK available on <a href="https://github.com/walbourn/directxtk-samples">GitHub</a>.

<ul>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Win32-23db418a">SimpleSample</a> - A Win32 desktop sample that demonstrates DirectXTK.</li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Sample-608bc274">SimpleSample</a> - A Windows store app sample that demonstrates DirectXTK</li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Windows-80e6b591">SimpleSample</a> - A Windows phone 8 sample that demonstrates DirectXTK</li>
<li><a href="http://code.msdn.microsoft.com/DXUTDirectXTK-Simple-Win32-9cf797e9">SimpleSample</a> - A Win32 desktop sample that demonstrates DirectXTK in combination with <a href="https://walbourn.github.io/dxut-for-win32-desktop-update/">DXUT</a>.</li>
<li>The Windows phone 8 version of <a href="http://code.msdn.microsoft.com/Marble-Maze-sample-for-c9f3706b">MarbleMaze</a> also makes use of DirectXTK</li>
</ul>

<strong>Update: </strong>DirectX Tool Kit is also hosted on <a href="https://github.com/Microsoft/DirectXTK">GitHub</a>.
