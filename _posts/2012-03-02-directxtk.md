---
layout: post
title: DirectXTK
date: 2012-03-02 13:11
author: walbourn
comments: true
categories: [codeplex, direct3d, Uncategorized, winphone]
---
The <a href="http://blogs.msdn.com/b/chuckw/archive/2011/10/28/directxtex.aspx">DirectXTex</a> library does an excellent job of providing all the 'texture content processing' functionality from the venerable D3DX library (see "<a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">Where is the DirectX SDK?</a>"), and <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/27/introducing-directxmath.aspx">DirectXMath</a> (or the older <a href="http://blogs.msdn.com/b/chuckw/archive/2011/02/23/xna-math-version-2-04.aspx">XNAMath</a>) takes over for D3DXMath. <a href="http://blogs.msdn.com/b/shawnhar/">Shawn Hargreaves</a> and I have been putting together another utility library, dubbed "DirectX Tool Kit" or "DirectXTK", to address some additional runtime needs for Direct3D 11 applications.

DirectXTK includes the following components:
<ul>
 	<li><strong>SpriteBatch</strong> - a 2D sprite rendering class (a C++ version of the <a href="http://msdn.microsoft.com/en-us/library/bb199034.aspx">SpriteBatch</a> used for <em>XNA Game Studio</em>)</li>
 	<li><strong>SpriteFont</strong> - a bitmap based text rendering (a C++ version of the <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.spritefont.aspx">SpriteFont</a> used for <em>XNA Game Studio</em>)</li>
 	<li><strong>Effects</strong> - a collection of ready-to-use common shaders (C++ versions of the <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.basiceffect.aspx">BasicEffect</a>, <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.alphatesteffect.aspx">AlphaTestEffect</a>, <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.dualtextureeffect.aspx">DualTextureEffect</a>, <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.environmentmapeffect.aspx">EnvironmentMapEffect</a>, and <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.skinnedeffect.aspx">SkinnedEffect</a> used for <em>XNA Game Studio</em>)</li>
 	<li><strong>PrimtiveBatch</strong> - simple and efficient way to draw user primitives which replicates the simplicity of the Direct3D 9 era DrawUP APIs</li>
 	<li><strong>GeometricPrimitives</strong> - geometry helpers for common shapes (Cube, Sphere, GeoSphere, Cylinder, Torus, Teapot, Tetrahedron, Octahedron, Dodecahedron, and Isosahedron)</li>
 	<li><strong>Model</strong> - draws simple meshes loaded from .CMO or .SDKMESH files</li>
 	<li><strong>CommonStates</strong> - Factory for common combinations of rendering states as Direct3D 11 state objects (C++ versions modelled after the 'public fields' of <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.blendstate_fields.aspx">BlendState</a>, <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.depthstencilstate_fields.aspx">DepthStencilState</a>, <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.rasterizerstate_fields.aspx">RasterizerState</a>, and <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.samplerstate_fields.aspx">SampleState</a> classes used for <em>XNA Game Studio</em>)</li>
 	<li><strong>VertexTypes</strong> -  collection of commonly used vertex buffer data structures with a input layout descriptions (C++ versions of <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.vertexpositioncolor.aspx">VertexPositionColor</a>, <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.vertexpositiontexture.aspx">VertexPositionTexture</a>, <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.vertexpositioncolortexture.aspx">VertexPositionColorTexture</a>, and <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.graphics.vertexpositionnormaltexture.aspx">VertexPositionNormalTexture</a> structures used for <em>XNA Game Studio</em>)</li>
 	<li>It also includes <strong>DDSTextureLoader,</strong>  <strong>WICTextureLoader,</strong> and <strong>ScreenGrab</strong> from the DirectXTex package.</li>
 	<li><strong>SimpleMath</strong> - a wrapper for DirectXMath that makes it easier to write basic math operations without as many restrictions as the SIMD-friendly base library</li>
 	<li>And the <strong>MakeSpriteFont</strong> utility for generating <code>.spritefont</code> files (based on the <a href="http://create.msdn.com/en-US/education/catalog/utility/bitmap_font_maker">Bitmap Font Maker Tool</a> for <em>XNA Game Studio</em>)</li>
</ul>
<strong>Platforms: </strong>The code is designed to build with the Windows 8.x SDK using Visual Studio 2010, 2012, or 2013 and works on Windows Vista, Windows 7, Windows 8.x Win32 desktop, Windows Store apps, Windows phone 8.1, and Xbox One.

The README.TXT in the ZIP package contains additional information, and see Shawn's posts <a href="http://blogs.msdn.com/b/shawnhar/archive/2012/03/02/spritebatch-and-basiceffect-for-c-direct3d-11.aspx">here</a> and <a href="http://blogs.msdn.com/b/shawnhar/archive/2012/05/02/directxtk-now-includes-spritefont.aspx">here</a> with some code snippets for usage.
<h1>Porting Notes</h1>
Here's a handy table of equivalents for D3DX (see <a href="http://blogs.msdn.com/b/chuckw/archive/2013/08/21/living-without-d3dx.aspx">Living without D3DX</a> for a complete listing):
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
Where XXX is "DDS" for working with .DDS files, or "WIC" for working with WIC-supported bitmap image formats such as .BMP, .JPG, .PNG, etc. Note that .TGA is supported by legacy D3DX and by DirectXTex, but not by DirectXTK.
<h1>Note</h1>
<strong>Update:</strong> DirectXTK is now hosted on <a href="https://github.com/Microsoft/DirectXTK">GitHub</a>.The latest version of the library, documentation, notes on future work, release history, and other information is now available there. The library now includes <a href="http://blogs.msdn.com/b/shawnhar/archive/2012/10/12/directxtk-primitivebatch-helper-makes-it-easy-to-draw-user-primitives-with-d3d11.aspx">PrimitiveBatch</a>, <a href="http://blogs.msdn.com/b/shawnhar/archive/2013/01/25/directxtk-now-supports-loading-and-drawing-3d-models.aspx">Model</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2014/09/05/directx-tool-kit-now-with-gamepads.aspx">GamePad</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2015/08/06/directx-tool-kit-keyboard-and-mouse-support/">Keyboard/Mouse</a>, <a href="https://blogs.msdn.microsoft.com/shawnhar/2013/01/08/simplemath-a-simplified-wrapper-for-directxmath/">SimpleMath</a>, and <a href="http://blogs.msdn.com/b/chuckw/archive/2013/12/24/directx-tool-kit-for-audio.aspx">DirectXTK for Audio</a> as well.

<strong>Windows phone 8:</strong> DirectXTK supports Windows phone 8 apps using the <a href="http://go.microsoft.com/fwlink/?LinkID=261873">Windows phone SDK 8.0</a>. See ShawnHar's <a href="http://blogs.msdn.com/b/shawnhar/archive/2012/10/30/directx-tool-kit-now-supports-windows-phone-8.aspx">post</a>. It also supports <a href="http://blogs.msdn.com/b/shawnhar/archive/2014/04/03/windows-phone-8-1.aspx">Windows phone 8.1</a> using VS 2013 Update 2 or later.

<strong>DirectX 12</strong>: If you are already an expert in using DirectX 11 and would like to use DirectX 12 instead, see <a href="https://blogs.msdn.microsoft.com/chuckw/2016/07/18/directx-tool-kit-for-directx-12/">DirectX Tool Kit for DirectX 12</a>

<strong>Related:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2014/06/27/directxmesh.aspx">DirectXMesh</a>
