---
layout: msdnpost
title: Getting Started with Direct3D 12
date: 2016-09-15 19:41
author: Chuck Walbourn
comments: true
categories: [direct3d]
---
The first thing to do is get up to speed on Direct3D 11 (see <a href="https://walbourn.github.io/getting-started-with-direct3d-11/">Getting Started with Direct3D 11</a>), especially if you are coming from a background of knowing Direct3D 9. Jumping feet-first into Direct3D 12 without a solid grounding in what a <a href="https://walbourn.github.io/direct3d-feature-levels/">Direct3D feature level</a> means, <a href="https://walbourn.github.io/care-and-feeding-of-modern-swapchains/">DXGI device-and-swapchain creation</a>, the modern <a href="https://walbourn.github.io/hlsl-fxc-and-d3dcompile/">HLSL compiler </a>story, the fate of the <a href="https://walbourn.github.io/where-is-the-directx-sdk-2015-edition/">legacy DirectX SDK</a>, and the Direct3D 10/Direct3D 11 state model and graphics pipeline design is a recipe for confusion and frustration.
<!--more-->

DirectX 12 is an expert API which builds on knowing the ins & outs of DirectX 11. DirectX 12 is an extremely low-level API designed for graphic experts who have a solid understanding of the architecture of modern GPU hardware, and can essentially write the DirectX 11 Runtime from scratch. Both DirectX 11 and DirectX 12 provide access to the same hardware features on Windows 10, but drive the hardware in different ways which can allow a well-optimized DirectX 12 engine to achieve much lower CPU overhead than in DirectX 11.

With that preamble out of the way, you should familiarize yourself with the documentation on <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d12/directx-12-programming-guide">Microsoft Docs</a>. Then install <a href="https://devblogs.microsoft.com/cppblog/developing-for-windows-10-with-visual-c-2015/">Visual Studio 2015</a> or <a href="https://walbourn.github.io/visual-studio-2017/">Visual Studio 2017</a> with the latest <a href="https://walbourn.github.io/windows-10-fall-creators-update-sdk/">Windows 10 SDK</a>.

<strong>Samples: </strong>The official samples are on <a href="https://github.com/Microsoft/DirectX-Graphics-Samples/">GitHub</a>. For introductory samples, take a look at <em>D3D12HelloWorld</em> (<a href="https://github.com/Microsoft/DirectX-Graphics-Samples/tree/master/Samples/Desktop/D3D12HelloWorld">PC desktop </a>and <a href="https://github.com/Microsoft/DirectX-Graphics-Samples/tree/master/Samples/UWP/D3D12HelloWorld">UWP</a>), as well as the <a href="https://github.com/Microsoft/Xbox-ATG-Samples#introductory-graphics">Xbox ATG Graphics </a><em>Introductory Graphics</em> samples. <em>DirectX Tool Kit for DirectX 12</em> includes some <a href="https://github.com/Microsoft/DirectXTK12/wiki/Getting-Started">tutorials</a> as well.

<strong>Presentations:</strong> There've been a number of public presentations on Direct3D 12.

<em>DirectX: Evolving Microsoft's Graphics Platform</em> (GDC 2014): <a href="https://channel9.msdn.com/Blogs/DirectX-Developer-Blog/DirectX-Evolving-Microsoft-s-Graphics-Platform">link</a>

<em>Direct3D 12 API Preview</em> (BUILD 2014): <a href="https://channel9.msdn.com/Events/Build/2014/3-564">link</a>

<em>Better Power, Better Performance: Your Game on DirectX12</em> (GDC 2015): <a href="https://channel9.msdn.com/Events/GDC/GDC-2015/Better-Power-Better-Performance-Your-Game-on-DirectX12">link</a>

<em>Advanced DirectX12 Graphics and Performance</em> (GDC 2015/BUILD 2015): <a href="https://channel9.msdn.com/Events/GDC/GDC-2015/Advanced-DirectX12-Graphics-and-Performance">link</a>

<em>Direct3D Update: </em>(GDC 2016): <a href="https://www.youtube.com/watch?v=dcDDvoauaz0">link</a>

<em>AMD, Intel, and NVidia also have additional materials available online.</em>

<strong>Videos: </strong>There is a series of <a href="https://www.youtube.com/channel/UCiaX2B8XiXR70jaN7NK-FpA">YouTube videos</a> on various aspects of Direct3D 12 you should take a look at as well.

<strong>Debugging:</strong> The debug device (aka the Developer Runtime) on Windows 10 is not installed by any SDK. It is enabled as a Windows Optional Feature called "Graphics Tools". See <a href="https://devblogs.microsoft.com/cppblog/visual-studio-2015-and-graphics-tools-for-windows-10/">this post</a> for details. You should also familiarize yourself with <a href="https://walbourn.github.io/dxgi-debug-device/">DXGI debugging features</a>. <strike>Note that the WARP12 device is only available when the "Graphics Tools" feature is enabled.</strike>. WARP for DirectX 12 is supported on Windows 10 (Version 1709, Build 16299) or later.

<strong>Drivers:</strong> Keep in mind that not all video hardware have DirectX 12 capable (WDDM 2.0) drivers available. You should make sure you have the latest drivers installed and verify that your video card supports DirectX 12. Otherwise, you'll have to limit yourself to using the WARP12 software device.

<strong>Utilities: </strong>The various Direct3D 12 templates make use of a simple header-only helper <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d12/helper-structures-and-functions-for-d3d12">D3DX12</a>. This does not have nearly the scope of the <a href="https://walbourn.github.io/living-without-d3dx/">deprecated D3DX libraries</a>, but is useful in taking care of many of the more mundane aspects of creating the required structures. For support in loading textures, rendering fonts & sprites, loading models, etc. see <a href="https://walbourn.github.io/directx-tool-kit-for-directx-12/">DirectX Tool Kit for DirectX 12</a>. For graphics math, see <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a>. You should use <a href="https://walbourn.github.io/directxtex-and-directxmesh-now-support-direct3d-12/">DirectXTex, DirectXMesh</a>, and <a href="https://walbourn.github.io/uvatlas-return-of-the-isochart/">UVAtlas</a> for content processing as well.

<strong>Multi-GPU:</strong> See <a href="https://devblogs.microsoft.com/directx/explicit-directx-12-multigpu-the-affinity-layer-helper-library-and-your-game/">this blog post</a>.

<strong>Books:</strong> So far the only book I'm aware of that's been published is Frank Luna's <em>Introduction to 3D Game Programming with DirectX 12</em> (2016).

<strong>Related:</strong> <a href="https://walbourn.github.io/anatomy-of-direct3d-12-create-device/">Anatomy of Direct3D 12 Create Device</a>, <a href="https://walbourn.github.io/direct3d-game-visual-studio-templates-redux/">Direct3D Game Visual Studio templates (Redux)</a>, <a href="https://walbourn.github.io/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK</a>
