---
layout: msdnpost
title: DirectXTK
date: 2012-03-02 13:11
author: Chuck Walbourn
comments: true
categories: [codeplex, direct3d, winphone]
---
The <a href="https://walbourn.github.io/directxtex/">DirectXTex</a> library does an excellent job of providing all the 'texture content processing' functionality from the venerable D3DX library (see "<a href="https://aka.ms/dxsdk">Where is the DirectX SDK?</a>"), and <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a> (or the older <a href="https://walbourn.github.io/xna-math-version-2-04/">XNAMath</a>) takes over for D3DXMath. <a href="https://www.shawnhargreaves.com/">Shawn Hargreaves</a> and I have been putting together another utility library, dubbed "DirectX Tool Kit" or "DirectXTK", to address some additional runtime needs for Direct3D 11 applications.
<!--more-->

DirectXTK includes the following components:

<ul>
 	<li><strong>SpriteBatch</strong> - a 2D sprite rendering class (a C++ version of the SpriteBatch used for <em>XNA Game Studio</em>)</li>
 	<li><strong>SpriteFont</strong> - a bitmap based text rendering (a C++ version of the SpriteFont used for <em>XNA Game Studio</em>)</li>
 	<li><strong>Effects</strong> - a collection of ready-to-use common shaders (C++ versions of the BasicEffect, AlphaTestEffect, DualTextureEffect, EnvironmentMapEffect, and SkinnedEffect used for <em>XNA Game Studio</em>)</li>
 	<li><strong>PrimtiveBatch</strong> - simple and efficient way to draw user primitives which replicates the simplicity of the Direct3D 9 era DrawUP APIs</li>
 	<li><strong>GeometricPrimitives</strong> - geometry helpers for common shapes (Cube, Sphere, GeoSphere, Cylinder, Torus, Teapot, Tetrahedron, Octahedron, Dodecahedron, and Isosahedron)</li>
 	<li><strong>Model</strong> - draws simple meshes loaded from .CMO or .SDKMESH files</li>
 	<li><strong>CommonStates</strong> - Factory for common combinations of rendering states as Direct3D 11 state objects (C++ versions modelled after the 'public fields' of BlendState, DepthStencilState, RasterizerState, and SampleState classes used for <em>XNA Game Studio</em>)</li>
 	<li><strong>VertexTypes</strong> -  collection of commonly used vertex buffer data structures with a input layout descriptions (C++ versions of VertexPositionColor, VertexPositionTexture, VertexPositionColorTexture, and VertexPositionNormalTexture structures used for <em>XNA Game Studio</em>)</li>
 	<li>It also includes <strong>DDSTextureLoader,</strong>  <strong>WICTextureLoader,</strong> and <strong>ScreenGrab</strong> from the DirectXTex package.</li>
 	<li><strong>SimpleMath</strong> - a wrapper for DirectXMath that makes it easier to write basic math operations without as many restrictions as the SIMD-friendly base library</li>
 	<li>And the <strong>MakeSpriteFont</strong> utility for generating <code>.spritefont</code> files (based on the <a href="https://github.com/SimonDarksideJ/XNAGameStudio/wiki/Bitmap-Font-Maker">Bitmap Font Maker Tool</a> for <em>XNA Game Studio</em>)</li>
</ul>

<strong>Platforms: </strong>The code is designed to build with the Windows 8.x SDK using Visual Studio 2010, 2012, or 2013 and works on Windows Vista, Windows 7, Windows 8.x Win32 desktop, Windows Store apps, Windows phone 8.1, and Xbox One.

The README.TXT in the ZIP package contains additional information, and see Shawn's posts <a href="http://www.shawnhargreaves.com/blog/spritebatch-and-basiceffect-for-c-direct3d-11.html">here</a> and <a href="http://www.shawnhargreaves.com/blog/directxtk-now-includes-spritefont.html">here</a> with some code snippets for usage.

<h1>Porting Notes</h1>

Here's a handy table of equivalents for D3DX (see <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a> for a complete listing):

<table border="1">
<tbody>
<tr>
<td><code>ID3DX10Sprite</code></td>
<td><code>SpriteBatch</code></td>
</tr>
<tr>
<td><code>ID3DX10Font</code></td>
<td><code>SpriteFont, SpriteBatch</code></td>
</tr>
<tr>
<td><code>ID3DX10Mesh</code></td>
<td><code>Model, ModelMesh, ModelMeshPart</code></td>
</tr>
<tr>
<td><code>D3DXCreateBox
D3DXCreateCylinder
D3DXCreateSphere
D3DXCreateTeapot
D3DXCreateTorus</code></td>
<td><code>GeometricPrimitive</code></td>
</tr>
<tr>
<td><code>D3DX11CreateShaderResourceViewFromFile</code></td>
<td><code>CreateXXXTextureFromFile</code></td>
</tr>
<tr>
<td><code>D3DX11CreateShaderResourceViewFromResource
D3DX11CreateShaderResourceViewFromMemory</code></td>
<td><code>CreateXXXTextureFromMemory</code></td>
</tr>
<tr>
<td><code>D3DX11CreateTextureFromFile</code></td>
<td><code>CreateXXXTextureFromFile</code></td>
</tr>
<tr>
<td><code>D3DX11CreateTextureFromResource
D3DX11CreateTextureFromMemory </code></td>
<td><code>CreateXXXTextureFromMemory</code></td>
</tr>
<tr>
<td><code>D3DX11SaveTextureToFile</code></td>
<td><code>SaveXXXTextureToFile</code></td>
</tr>
</tbody>
</table>

Where XXX is "DDS" for working with ``.DDS`` files, or "WIC" for working with WIC-supported bitmap image formats such as ``.BMP``, ``.JPG``, ``.PNG``, etc. Note that ``.TGA`` is supported by legacy D3DX and by DirectXTex, but not by DirectXTK.

<h1>Note</h1>

<strong>Update:</strong> DirectXTK is now hosted on <a href="https://github.com/Microsoft/DirectXTK">GitHub</a>.The latest version of the library, documentation, notes on future work, release history, and other information is now available there. The library now includes <a href="http://www.shawnhargreaves.com/blog/directxtk-primitivebatch-helper-makes-it-easy-to-draw-user-primitives-with-d3d11.html">PrimitiveBatch</a>, <a href="http://www.shawnhargreaves.com/blog/directxtk-now-supports-loading-and-drawing-3d-models.html">Model</a>, <a href="https://walbourn.github.io/directx-tool-kit-now-with-gamepads/">GamePad</a>, <a href="https://walbourn.github.io/directx-tool-kit-keyboard-and-mouse-support/">Keyboard/Mouse</a>, <a href="http://www.shawnhargreaves.com/blog/simplemath-a-simplified-wrapper-for-directxmath.html">SimpleMath</a>, and <a href="https://walbourn.github.io/directx-tool-kit-for-audio/">DirectXTK for Audio</a> as well.

<strong>Windows phone 8:</strong> DirectXTK supports Windows phone 8 apps using the <a href="http://go.microsoft.com/fwlink/?LinkID=261873">Windows phone SDK 8.0</a>. See ShawnHar's <a href="http://www.shawnhargreaves.com/blog/directx-tool-kit-now-supports-windows-phone-8.html">post</a>. It also supports <a href="http://www.shawnhargreaves.com/blog/windows-phone-8-1.html">Windows phone 8.1</a> using VS 2013 Update 2 or later.

<strong>DirectX 12</strong>: If you are already an expert in using DirectX 11 and would like to use DirectX 12 instead, see <a href="https://walbourn.github.io/directx-tool-kit-for-directx-12/">DirectX Tool Kit for DirectX 12</a>

<strong>vcpkg</strong>: The vcpkg C++ Package Manager has a [directxtk](https://github.com/microsoft/vcpkg/tree/master/ports/directxtk) port available.

<strong>Related:</strong> <a href="https://walbourn.github.io/directxmesh/">DirectXMesh</a>
