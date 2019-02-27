---
layout: post
title: Getting Started with Direct3D 12
date: 2016-09-15 19:41
author: walbourn
comments: true
categories: [direct3d, Uncategorized]
---
The first thing to do is get up to speed on Direct3D 11 (see <a href="https://blogs.msdn.microsoft.com/chuckw/2011/07/11/getting-started-with-direct3d-11/">Getting Started with Direct3D 11</a>), especially if you are coming from a background of knowing Direct3D 9. Jumping feet-first into Direct3D 12 without a solid grounding in what a <a href="https://blogs.msdn.microsoft.com/chuckw/2012/06/20/direct3d-feature-levels/">Direct3D feature level</a> means, DXGI device-and-swapchain creation, the modern <a href="https://blogs.msdn.microsoft.com/chuckw/2012/05/07/hlsl-fxc-and-d3dcompile/">HLSL compiler </a>story, the fate of the <a href="https://blogs.msdn.microsoft.com/chuckw/2015/08/05/where-is-the-directx-sdk-2015-edition/">legacy DirectX SDK</a>, and the Direct3D 10/Direct3D 11 state model and graphics pipeline design is a recipe for confusion and frustration.

DirectX 12 is an expert API which builds on knowing the ins &amp; outs of DirectX 11. DirectX 12 is an extremely low-level API designed for graphic experts who have a solid understanding of the architecture of modern GPU hardware, and can essentially write the DirectX 11 Runtime from scratch. Both DirectX 11 and DirectX 12 provide access to the same hardware features on Windows 10, but drive the hardware in different ways which can allow a well-optimized DirectX 12 engine to achieve much lower CPU overhead than in DirectX 11.

With that preamble out of the way, you should familiarize yourself with the documentation on <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/dn899121.aspx">MSDN</a>. Then install <a href="https://blogs.msdn.microsoft.com/vcblog/2015/07/29/developing-for-windows-10-with-visual-c-2015/">Visual Studio 2015</a> or <a href="https://blogs.msdn.microsoft.com/chuckw/2017/03/07/visual-studio-2017/">Visual Studio 2017</a> with the latest <a href="https://blogs.msdn.microsoft.com/chuckw/2017/10/11/windows-10-fall-creators-update-sdk/">Windows 10 SDK</a>.

<strong>Samples: </strong>The official samples are on <strong><a href="https://github.com/Microsoft/DirectX-Graphics-Samples/">GitHub</a>. </strong>For introductory samples, take a look at <em>D3D12HelloWorld</em> (<a href="https://github.com/Microsoft/DirectX-Graphics-Samples/tree/master/Samples/Desktop/D3D12HelloWorld">PC desktop </a>and <a href="https://github.com/Microsoft/DirectX-Graphics-Samples/tree/master/Samples/UWP/D3D12HelloWorld">UWP</a>), as well as the <a href="https://github.com/Microsoft/Xbox-ATG-Samples#introductory-graphics">Xbox ATG Graphics </a><em>Introductory Graphics</em> samples. <em>DirectX Tool Kit for DirectX 12</em> includes some <a href="https://github.com/Microsoft/DirectXTK12/wiki/Getting-Started">tutorials</a> as well.

<strong>Presentations:</strong> There've been a number of public presentations on Direct3D 12.

<em>DirectX: Evolving Microsoft's Graphics Platform</em> (GDC 2014): <a href="https://channel9.msdn.com/Blogs/DirectX-Developer-Blog/DirectX-Evolving-Microsoft-s-Graphics-Platform">link</a>

<em>Direct3D 12 API Preview</em> (BUILD 2014): <a href="https://channel9.msdn.com/Events/Build/2014/3-564">link</a>

<em>Better Power, Better Performance: Your Game on DirectX12</em> (GDC 2015): <a href="https://channel9.msdn.com/Events/GDC/GDC-2015/Better-Power-Better-Performance-Your-Game-on-DirectX12">link</a>

<em>Advanced DirectX12 Graphics and Performance</em> (GDC 2015/BUILD 2015): <a href="https://channel9.msdn.com/Events/GDC/GDC-2015/Advanced-DirectX12-Graphics-and-Performance">link</a>

<em>Direct3D Update: </em>(GDC 2016): <a href="https://www.youtube.com/watch?v=dcDDvoauaz0">link</a>

<em>AMD, Intel, and NVidia also have additional materials available online.</em>

<strong>Videos: </strong>There is a series of <a href="https://www.youtube.com/channel/UCiaX2B8XiXR70jaN7NK-FpA">YouTube videos</a> on various aspects of Direct3D 12 you should take a look at as well.

<strong>Debugging:</strong> The debug device (aka the Developer Runtime) on Windows 10 is not installed by any SDK. It is enabled as a Windows Optional Feature called "Graphics Tools". See <a href="https://blogs.msdn.microsoft.com/vcblog/2015/03/31/visual-studio-2015-and-graphics-tools-for-windows-10/">this post</a> for details. You should also familiarize yourself with <a href="https://blogs.msdn.microsoft.com/chuckw/2015/07/27/dxgi-debug-device/">DXGI debugging features</a>. Note that the WARP12 device is only available when the "Graphics Tools" feature is enabled.

<strong>Drivers:</strong> Keep in mind that not all video hardware have DirectX 12 capable (WDDM 2.0) drivers available. You should make sure you have the latest drivers installed and verify that your video card supports DirectX 12. Otherwise, you'll have to limit yourself to using the WARP12 software device.

<strong>Utilities: </strong>The various Direct3D 12 templates make use of a simple header-only helper <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/dn708058.aspx">D3DX12</a>. This does not have nearly the scope of the <a href="https://blogs.msdn.microsoft.com/chuckw/2013/08/20/living-without-d3dx/">deprecated D3DX libraries</a>, but is useful in taking care of many of the more mundane aspects of creating the required structures. For support in loading textures, rendering fonts &amp; sprites, loading models, etc. see <a href="https://blogs.msdn.microsoft.com/chuckw/2016/07/18/directx-tool-kit-for-directx-12/">DirectX Tool Kit for DirectX 12</a>. For graphics math, see <a href="https://blogs.msdn.microsoft.com/chuckw/2012/03/26/introducing-directxmath/">DirectXMath</a>. You should use <a href="https://blogs.msdn.microsoft.com/chuckw/2017/02/01/directxtex-and-directxmesh-now-support-direct3d-12/">DirectXTex, DirectXMesh</a>, and <a href="https://blogs.msdn.microsoft.com/chuckw/2014/11/14/uvatlas-return-of-the-isochart/">UVAtlas</a> for content processing as well.

<strong><em></em>Multi-GPU:</strong> See <a href="https://blogs.msdn.microsoft.com/directx/2016/07/13/explicit-directx-12-multigpu-the-affinity-layer-helper-library-and-your-game/">this blog post</a>.

<strong>Books:</strong> So far the only book I'm aware of that's been published is Frank Luna's <em>Introduction to 3D Game Programming with DirectX 12</em> (2016).

<strong>Related:</strong> <a href="https://blogs.msdn.microsoft.com/chuckw/2016/08/16/anatomy-of-direct3d-12-create-device/">Anatomy of Direct3D 12 Create Device</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2015/12/17/direct3d-game-visual-studio-templates-redux/">Direct3D Game Visual Studio templates (Redux)</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2016/08/02/windows-10-anniversary-update-sdk/">Windows 10 Anniversary Update SDK</a>
