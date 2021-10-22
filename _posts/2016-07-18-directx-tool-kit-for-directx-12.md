---
layout: msdnpost
title: DirectX Tool Kit for DirectX 12
date: 2016-07-18 23:54
author: Chuck Walbourn
comments: true
categories: [direct3d, github]
---
Since the release of <a href="https://walbourn.github.io/directxtk/">DirectX Tool Kit</a> four years ago, it has proven to be a very useful library for samples, indie and hobbyist projects, people moving from XNA Game Studio to C++, learning Direct3D 11, and for developers looking for supported replacements for the <a href="https://walbourn.github.io/living-without-d3dx/">legacy D3DX</a> library and the retiring of the <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">legacy DirectX SDK</a>.
<!--more-->

Today I'm announcing the <em>DirectX Tool Kit for DirectX 12</em>, which is hosted as it's own <a href="https://github.com/Microsoft/DirectXTK12">GitHub </a>site. After much discussion and debate, we realized that both tool kits are really independent projects. While they share a lot of code (all the non-graphics stuff is 100% identical), the Direct3D 12 API is significantly different than Direct3D 11 so the graphics components 'feel' the same but in practice are used very differently.

<em>DirectXTK for DirectX 12</em> includes the following components:

<ul>
  <li><strong>CommonStates</strong> – Factory for common combinations of rendering states (C++ versions modelled after the 'public fields' of BlendState, DepthStencilState, RasterizerState, and SampleState classes used for XNA Game Studio)</li>
  <li><strong>DDSTextureLoader</strong> - light-weight DDS file texture loader</li>
  <li><strong>DirectXHelpers</strong> - misc C++ helpers for D3D programming</li>
  <li><strong>Effects</strong> – a collection of ready-to-use common shaders (C++ versions of the BasicEffect, AlphaTestEffect, DualTextureEffect, EnvironmentMapEffect, and SkinnedEffect used for XNA Game Studio)</li>
  <li><strong>GeometricPrimitives</strong> – geometry helpers for common shapes (Cube, Sphere, GeoSphere, Cylinder, Torus, Teapot, Tetrahedron, Octahedron, Dodecahedron, and Isosahedron)</li>
  <li><strong>GraphicsMemory</strong> - helper for managing graphics memory allocation</li>
  <li><strong>Model</strong> – draws simple meshes loaded from <code>.SDKMESH</code> or <code>.VBO</code> files</li>
  <li><strong>PostProcess</strong> - set of built-in shaders for common post-processing operations</li>
  <li><strong>PrimitiveBatch</strong> – simple and efficient way to draw user primitives which replicates the simplicity of the Direct3D 9 era DrawUP APIs</li>
  <li><strong>ScreenGrab</strong> - light-weight screen shot saver</li>
  <li><strong>SpriteBatch</strong> – a 2D sprite rendering class (a C++ version of the SpriteBatch used for XNA Game Studio)</li>
  <li><strong>SpriteFont</strong> – a bitmap based text rendering (a C++ version of the SpriteFont used for XNA Game Studio)</li>
  <li><strong>VertexTypes</strong> –  collection of commonly used vertex buffer data structures with a input layout descriptions (C++ versions of VertexPositionColor, VertexPositionTexture, VertexPositionColorTexture, and VertexPositionNormalTexture structures used for XNA Game Studio)</li>
  <li><strong>WICTextureLoader</strong> - WIC-based image file texture loader</li>
</ul>

DirectX Tool Kit for DirectX 12 also includes <a href="https://walbourn.github.io/directx-tool-kit-for-audio/">DirectX Tool Kit for Audio</a>, <a href="https://walbourn.github.io/directx-tool-kit-now-with-gamepads/">GamePad</a>, <a href="https://walbourn.github.io/directx-tool-kit-keyboard-and-mouse-support/">Keyboard, Mouse</a>, and <a href="https://blogs.msdn.microsoft.com/shawnhar/2013/01/08/simplemath-a-simplified-wrapper-for-directxmath/">SimpleMath</a>.  The **MakeSpriteFont** and **XWBTool** tools are identical so they are hosted on the DirectX Tool Kit for DirectX 11 <a href="https://github.com/Microsoft/DirectXTK/">GitHub</a>.

There are a few key differences compared to the DirectX 11 version:

<ul>
  <li>No support for <strike>loading <code>.CMO</code> models or</strike> DGSL effect shaders (i.e. DGSLEffect)</li>
  <li>VertexTypes does not include <code>VertexPositionNormalTangentColorTexture</code> or
<code>VertexPositionNormalTangentColorTextureSkinning</code></li>
  <li>DirectX Tool Kit for DirectX 11 supports Feature Level 9.3, while DirectX 12 requires Direct3D Feature Level 11.0. There are no expected DirectX 12 drivers for  any lower feature level devices.</li>
  <li>The library assumes it is building for Windows 10 (aka <code>_WIN32_WINNT=0x0A00</code>) so it makes use of XAudio 2.9 and WIC2 as well as DirectX 12.</li>
</ul>

<em>A word of caution:</em> DirectX 12 is an API designed for graphics experts. If you are not already an expert in using Direct3D 11, I'd recommend sticking with the Direct3D 11 API until you find yourself in need of the additional control. Direct3D 12 provides a great deal of control over memory allocation, synchronization, state management which can result in reduced CPU overhead for rendering compared to older versions of Direct3D, but that control means the API is quite unforgiving. If you are new to Direct3D entirely, definitely start with <a href="https://github.com/Microsoft/DirectXTK/wiki/Getting-Started">Direct3D 11 first</a>.

<em>DirectX Tool Kit for DirectX 12</em> is documented on the <a href="https://github.com/Microsoft/DirectXTK12/wiki/">GitHub wiki </a>and there are <a href="https://github.com/Microsoft/DirectXTK12/wiki/Getting-Started">basic tutorials</a> on it's usage. It's also host on NuGet for <a href="https://www.nuget.org/packages/directxtk12_uwp/">Windows Universal Platform (UWP) apps</a> and <a href="https://www.nuget.org/packages/directxtk12_desktop_2015/">Win32 desktop apps on Windows 10</a>.

Both version so the *DirectX Tool* Kit now include support for NormalMapEffect and per-pixel lighting support for EnvironmentMapEffect.

<strong>vcpkg</strong>: The vcpkg C++ Package Manager has a [directxtk12](https://github.com/microsoft/vcpkg/tree/master/ports/directxtk12) port available.

<strong>CMO:</strong>: Originally *DirectX Tool Kit for DX12* did not support loading Visual Studio Content Pipeline (CMO) models. This is now supported with the September 2021 release. DGSL shaders are still not supported.

<strong>Related:</strong> <a href="https://walbourn.github.io/anatomy-of-direct3d-12-create-device/">Anatomy of Direct3D 12 Create Device</a>, <a href="https://walbourn.github.io/getting-started-with-direct3d-12/">Getting Started with Direct3D 12</a>, <a href="https://walbourn.github.io/directxtex-and-directxmesh-now-support-direct3d-12/">DirectXTex and DirectXMesh now support Direct3D 12</a>
