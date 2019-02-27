---
layout: post
title: DirectXTex and DirectXMesh now support Direct3D 12
date: 2017-02-01 06:55
author: walbourn
comments: true
categories: [direct3d, github, Uncategorized]
---
As part of my multi-year personal project of providing <a href="https://blogs.msdn.microsoft.com/chuckw/2013/08/20/living-without-d3dx/">open source replacements</a> for the deprecated D3DX library once found in the <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/ee663275.aspx">legacy DirectX SDK</a>, two libraries are focused on content creation tools and build pipelines. <em>DirectXTex</em> handles loading image files, texture processing including format conversion, mipmap generation, block-compression, and writing out 'fully cooked' textures into DDS files. <em>DirectXMesh</em> provides geometry support such as computing normals and tangent-frames, transparent vertex cache optimization, and provides utilities for extracting/inserting vertex data in vertex buffers.

These libraries were originally written for DirectX 11, and it seems likely that most tools should continue to use DirectX 11 for the simplicity and ease of developer productivity. There are, however, cases where you want to use some of this functionality 'in-engine', so the January 2017 releases include DirectX 12 API support as well.

DirectXTex January 2017 release on <a href="https://github.com/Microsoft/DirectXTex/releases/">GitHub</a>

DirectXMesh January 2017 release on <a href="https://github.com/Microsoft/DirectXMesh/releases/">GitHub</a>

To simplify supporting all the various platforms and Windows SDK combinations, the library continues to default to using DirectX 11. If you want to use DirectX 12, you need to explicitly include the required headers before including the library header:

<code>#include &lt;d3d12.h&gt;
#include "DirectXTex.h"</code>

You also need to link with the <code>DirectXTex_Desktop_2015_Win10.vcxproj</code>, <code>DirectXTex_Windows10.vcxproj</code>, or <code>DirectXTex_XboxOneXDK_2015.vcxproj</code> projects which build with both DirectX 11 and DirectX 12 support.

If you want to use both DirectX 11 and DirectX 12 in the same compilation module, then you need to explicitly include both:

<code>#include &lt;d3d11_1.h&gt;
#include &lt;d3d12.h&gt;
#include "DirectXTex.h"</code>

The story is similar for DirectXMesh, although in this case it's just to let you use <code>D3D12_</code> input layouts enums and structures instead of <code>D3D11_</code>--the data itself is identical.

In case you missed it, DirectXTex was updated to support the <a href="https://en.wikipedia.org/wiki/RGBE_image_format">HDR (RGBE)</a> file format as a source for floating-point HDR texture data, as well as having 'opt-in' support for <a href="https://en.wikipedia.org/wiki/OpenEXR">OpenEXR</a>. For more details on how to enable OpenEXR, see <a href="https://github.com/Microsoft/DirectXTex/wiki/Adding-OpenEXR">this page</a>.

<strong>Related: </strong><a href="https://blogs.msdn.microsoft.com/chuckw/2016/07/18/directx-tool-kit-for-directx-12/">DirectX Tool Kit for DirectX 12</a>
