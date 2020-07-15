---
layout: msdnpost
title: Direct3D 11 Textures and Block Compression
date: 2012-05-04 11:08
author: Chuck Walbourn
comments: true
categories: [dds, direct3d]
---
<h1>Creating and loading textures</h1>

There are a number of previous posts on the state of <code>.DDS</code> files which is the container format for Direct3D resources (see <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3ddds/dx-graphics-dds-pguide">Microsoft Docs</a> for some basics).
<!--more-->

**UPDATE: The latest version of DDSTextureLoader, WICTextureLoader, and ScreenGrab for Direct3D 9, Direct3D 11, and Direct3D 12 can be found on [GitHub](https://github.com/microsoft/DirectXTex/)**

<a href="https://walbourn.github.io/the-dds-file-format-lives/">The DDS File Format Lives</a>

<a href="https://walbourn.github.io/dds-update-and-10-10-10-2-problems/">DDS Update and 10:10:10:2 Problems</a>

<a href="https://walbourn.github.io/ddswithoutd3dx-sample-update/">DDSWithoutD3DX Sample Update</a>

With the retirement of the <a href="https://walbourn.github.io/where-is-the-directx-sdk/">D3DX</a> library, the recommended solutions for working with Direct3D 11 textures and <code>.DDS</code> files are now <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a> and <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK</a>.

<ul>
<li>The <em>DirectXTex</em> library provides the functionality in D3DX for loading bitmaps, resizing and converting them, generating mipmaps, compressing, and then writing them out as <code>.DDS</code> files. This is usually overkill for most applications to do at run-time, and not a particularly good use of end-user's time anyhow, but it's great for writing custom content tool pipelines for texture processing. The DirectXTex package includes a 'sample' which is the venerable <code>texconv</code> command-line tool written to use DirectXTex instead of D3DX.</li>
</ul>

<ul>
<li>The <em>DDSTextureLoader</em> module is intended to handle efficient loading of <code>.DDS</code> files and creating Direct3D 11 resources from them. It does not perform any runtime conversions, so some legacy files with pixel formats that do not directly map to a DXGI format will fail to load and in some cases the DXGI format of the file is not supported by the device and will also fail to load. For these cases, you will want to use <em>DirectXTex</em> to convert them offline to something that you can rely on being able to load on your target machine. This code supports the full range of Direct3D 11 resources including 1D, 2D, 3D, cubemaps, and texture arrays with mipmaps. The <em>DDSTextureLoader </em>module is included in both the <em>DirectXTK</em> <a href="https://github.com/Microsoft/DirectXTK/wiki/DDSTextureLoader">library</a> and in the <em>DirectXTex</em> package.</li>
</ul>

<ul>
<li>For very simple cases, there is also a <em>WICTextureLoader</em> module which can load standard bitmap files, does some runtime conversions and resizing, and then creates a Direct3D 11 texture 2D from it. It can optionally enable the 'auto-gen mipmaps' feature of Direct3D 11 to provide some basic mipmap support as well (standard bitmap files can't store mipmaps with the base image the way a <code>.DDS</code> file can). This makes use of the Windows Imaging Component (WIC), but is much more 'heavyweight' than <em>DDSTextureLoader</em>. This gives you less control over the quality of the filtering (particularly mipmaps), and does not support complex textures like volume maps, cubemaps, or texture arrays. The <em>WICTextureLoader</em> module is also included in both the <em>DirectXTK</em> <a href="https://github.com/Microsoft/DirectXTK/wiki/WICTextureLoader
">library</a> and in the <em>DirectXTex</em>package.</li>
</ul>

<ul>
<li>The <em>ScreenGrab</em> module is intended as a light-weight texture saver for creating 'screen shot' bitmap files from render target textures. The <em>ScreenGrab</em> module is included in the <em>DirectXTK</em> <a href="https://github.com/Microsoft/DirectXTK/wiki/ScreenGrab">library</a> and <em>DirectXTex </em> package.</li>
</ul>

<em>DirectXTK</em> and <em>DirectXTex</em> both support Windows Store apps (a.k.a. Metro style apps) on Windows 8 as well as traditional Win32 desktop applications on Windows 8, Windows 7, and Windows Vista SP2 with the DirectX 11.0 update. There is a version of <em>DDSTextureLoader </em>used by the Windows 8 DirectX samples as well (see the <a href="http://code.msdn.microsoft.com/windowsapps/Direct3D-Resource-Loading-25406148">Direct3D resource loading sample</a>).

<strong>Update: </strong>Both libraries also work on <a href="http://www.shawnhargreaves.com/blog/directx-tool-kit-now-supports-windows-phone-8.html">Windows phone</a>, <a href="http://www.xbox.com/en-us/Developers/id">Xbox One</a>, and Universal Windows Platform apps.

<h1>Block Compression</h1>

One of the advantages of using <code>.DDS</code> files is the ability to make use of Direct3D texture compression. The original <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d9/compressed-texture-resources">Direct3D 9 texture compression</a> schemes (DXT1, DXT2/3, DXT4/5) are still supported (now called BC1, BC2, and BC3) and support is required on all Direct3D 11 API compatible hardware including the 9.1, 9.2, and 9.3 feature levels. These schemes are designed for compressing standard three-channel color data with and without an alpha channel. DirectXTex provides the same software compressor that has been in D3DX for many years, with the addition of a few minor improvements through optional control flags.

Feature Level 10.0, 10.1, 11.0, and 11.1 devices also support <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d10/d3d10-graphics-programming-guide-resources-block-compression">BC4 and BC5 compression</a> schemes. BC4 is also known as 3DC+ ("ATI1"), and BC5 is known as 3Dc ("ATI2") or "DXN", and both are designed for compressing single-channel or tow-channel textures such as normal maps. DirectXTex provides the same software compressor that was in D3DX10 and D3DX11.

Feature Level 11.0 and 11.1 devices support <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/texture-block-compression-in-direct3d-11">BC6H and BC7 compression</a> schemes. BC6H is designed for high-dynamic range (HDR) float16 content, while BC7 is a more robust high-quality alternative to the standard BC1-3 schemes for three-channel color data images. Note that BC6H and BC7 decompression is extremely fast with hardware support, but can be expensive to compress. DirectXTex provides the same software compressor available in D3DX11, but a DirectCompute accelerated version is in the <a href="http://go.microsoft.com/fwlink/?LinkId=254494">BC6HBC7EncoderDecoder </a>sample.

<strong>Update:</strong> The latest <em>DirectXTex</em> supports both the CPU and DirectCompute compressors.

<h1>Porting Notes</h1>

Here's a handy table of equivalents for replacing legacy D3DX texture related functions.

<table border="1">
<tbody>
<tr>
<td><code>D3DX11ComputeNormalMap</code></td>
<td>
<p>DirectXTex library, <code> ComputeNormalMap</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11CreateShaderResourceViewFromFile<br /> D3DX11CreateTextureFromFile</code></td>
<td>
<p>DDSTextureLoader: <code>CreateDDSTextureFromFile</code><br />WICTextureLoader: <code>CreateWICTextureFromFile</code></p>
<p>DirectXTex library (tools), <code>LoadFromXXXFile</code> then <code>CreateShaderResourceView</code> or <code>CreateTexture</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11CreateShaderResourceViewFromMemory<br /> D3DX11CreateTextureFromMemory</code></td>
<td>
<p>DDSTextureLoader: <code>CreateDDSTextureFromMemory</code><br />WICTextureLoader: <code>CreateWICTextureFromMemory</code></p>
<p>DirectXTex library (tools), <code>LoadFromXXXMemory</code> then <code>CreateShaderResourceView</code> or <code>CreateTexture</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11CreateShaderResourceViewFromResource<br /> D3DX11CreateTextureFromResource</code></td>
<td>
<p>No direct equivalent, can use Win32 resource functions and then the 'from memory' APIs above.</p>
</td>
</tr>
<tr>
<td><code>D3DX11FilterTexture</code></td>
<td>
<p>DirectXTex library, <code>GenerateMipMaps</code> and <code>GenerateMipMaps3D</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11GetImageInfoFromFile</code></td>
<td>
<p>DirectXTex library, <code>GetMetadataFromXXXFile</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11GetImageInfoFromMemory</code></td>
<td>
<p>DirectXTex library, <code>GetMetadataFromXXXMemory</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11GetImageInfoFromResource</code></td>
<td>
<p>No direct equivalent, can use Win32 resource functions and then the 'from memory' APIs above.</p>
</td>
</tr>
<tr>
<td><code>D3DX11LoadTextureFromTexture</code></td>
<td>
<p>DirectXTex library, <code>Resize</code>, <code>Convert</code>, <code>Compress</code>, <code>Decompress</code>, and/or <code>CopyRectangle</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11SaveTextureToFile</code></td>
<td>
<p>ScreenGrab: <code>SaveDDSTextureToFile</code> or <code>SaveWICTextureToFile</code></p>
<p>DirectXTex library, <code>CaptureTexture</code> then <code>SaveToXXXFile</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11SaveTextureToMemory</code></td>
<td>
<p>DirectXTex library, <code>CaptureTexture</code> then <code>SaveToXXXMemory</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11SHProjectCubeMap</code></td>
<td>
<p><a href="https://walbourn.github.io/spherical-harmonics-math/">Spherical Harmonics Math</a>, <code>SHProjectCubeMap</code></p>
</td>
</tr>
</tbody>
</table>

<h1>Viewing DDS files</h1>

The legacy DirectX SDK (see <a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a>) includes the DirectX Texture Viewer tool. This only supports older Direct3D 9 <code>.DDS</code> files and will fail to load any file using the 'DX10' extension or BC4, BC5, BC6H, or BC7. <a href="https://walbourn.github.io/visual-studio-2012-release-candidate/">Visual Studio 2012</a> can view modern <code>.DDS</code> files directly via File / Open / File... (the Image Files filter includes <code>.dds</code>). There is also a 'ddsview' sample available in the DirectXTex package.

<b>Windows 8.1:</b> The WIC codec for Windows 8.1 and Windows 10 supports ``DDS`` 2D textures for DXT1-5 (BC1-BC3) formats. No other ``DDS`` file format or texture type is supported by the built-in codec.

<h1>Presentations</h1>

<ul>
<li>Modern Texture Content Pipelines (Gamefest 2011) <a href="https://walbourn.github.io/download/Graphics-Modern-Texture-Content-Pipelines.zip">link</a></li>
<li>Block Compression Smorgasbord (Gamefest 2010) <a href="https://walbourn.github.io/download/Block-Compression-Smorgasbord.zip">link</a></li>
</ul>

<h1>IHV Compressors</h1>

The various video independent hardware vendors (IHVs) have their own texture toolsets as well.

<ul>
<li><a href="http://developer.amd.com/tools-and-sdks/graphics-development/amdcompress/">AMD Compress</a></li>
<li>Intel ISPC compressors: <a href="https://software.intel.com/en-us/articles/fast-ispc-texture-compressor-update">BC6H</a>,  <a href="http://software.intel.com/en-us/articles/fast-ispc-texture-compressor">BC7</a></li>
<li><a href="https://developer.nvidia.com/gpu-accelerated-texture-compression">NVIDIA Texture Tools</a><br /><a href="https://developer.nvidia.com/nvidia-texture-tools-adobe-photoshop">NVIDIA Texture Tools for Adobe Photoshop</a></li>
</ul>

> The NVIDIA tools haven't been updated in some time, and are currently missing support for the <a href="https://walbourn.github.io/the-dds-file-format-lives/">DX10 header extension</a>, BC6H, and BC7.

<strong>Related:</strong> <a href="https://walbourn.github.io/getting-started-with-direct3d-11/">Getting Started with Direct3D 11</a>
