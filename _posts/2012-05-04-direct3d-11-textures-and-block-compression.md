---
layout: post
title: Direct3D 11 Textures and Block Compression
date: 2012-05-04 11:08
author: walbourn
comments: true
categories: [dds, direct3d, Uncategorized]
---
<h1><strong>Creating and loading textures</strong></h1>
<p>There are a number of previous posts on the state of <code>.DDS</code> files which is the container format for Direct3D resources (see <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb943991.aspx">MSDN</a> for some basics).</p>
<p style="padding-left: 30px;"><a href="http://blogs.msdn.com/b/chuckw/archive/2010/02/05/the-dds-file-format-lives.aspx">The DDS File Format Lives</a></p>
<p style="padding-left: 30px;"><a href="http://blogs.msdn.com/b/chuckw/archive/2010/06/15/dds-update-and-10-10-10-2-problems.aspx">DDS Update and 10:10:10:2 Problems</a></p>
<p style="padding-left: 30px;"><a href="http://blogs.msdn.com/b/chuckw/archive/2010/07/15/ddswithoutd3dx-sample-update.aspx">DDSWithoutD3DX Sample Update</a></p>
<p>With the retirement of the <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">D3DX</a> library, the recommended solutions for working with Direct3D 11 textures and <code>.DDS</code> files are now <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a> and <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK</a>.</p>
<ul>
<li>The&nbsp;<em>DirectXTex</em> library provides the functionality in D3DX for loading bitmaps, resizing and converting them, generating mipmaps, compressing, and then writing them out as <code>.DDS</code> files. This is usually overkill for most applications to do at run-time, and not a particularly good use of end-user's time anyhow, but it's great for writing custom content tool pipelines for texture processing. The DirectXTex package includes a 'sample' which is the venerable <code>texconv</code> command-line tool written to use DirectXTex instead of D3DX.</li>
</ul>
<p>&nbsp;</p>
<ul>
<li>The <em>DDSTextureLoader</em> module is intended to handle efficient loading of <code>.DDS</code> files and creating Direct3D 11 resources from them. It does not perform any runtime conversions, so some legacy files with pixel formats that do not directly map to a DXGI format will fail to load and in some cases the DXGI format of the file is not supported by the device and will also fail to load. For these cases, you will want to use <em>DirectXTex</em> to convert them offline to something that you can rely on being able to load on your target machine. This code supports the full range of Direct3D 11 resources including 1D, 2D, 3D, cubemaps, and texture arrays with mipmaps.&nbsp;The <em>DDSTextureLoader </em>module is included in both the <em>DirectXTK</em> <a href="https://directxtk.codeplex.com/wikipage?title=DDSTextureLoader">library</a> and in the <em>DirectXTex</em> <a href="https://directxtex.codeplex.com/wikipage?title=DDSTextureLoader">package</a>.</li>
</ul>
<p>&nbsp;</p>
<ul>
<li>For very simple cases, there is also a <em>WICTextureLoader</em> module which can load standard bitmap files, does some runtime conversions and resizing, and then creates a Direct3D 11 texture 2D from it. It can optionally enable the 'auto-gen mipmaps' feature of Direct3D 11 to provide some basic mipmap support as well (standard bitmap files can't store mipmaps with the base image the way a <code>.DDS</code> file can). This makes use of the Windows Imaging Component (WIC), but is much more 'heavyweight' than <em>DDSTextureLoader</em>. This gives you less control over the quality of the filtering (particularly mipmaps), and does not support complex textures like volume maps, cubemaps, or texture arrays. The <em>WICTextureLoader</em> module is also included in both the <em>DirectXTK</em> <a href="https://directxtk.codeplex.com/wikipage?title=WICTextureLoader">library</a> and in the <em>DirectXTex</em> <a href="https://directxtex.codeplex.com/wikipage?title=WICTextureLoader">package</a>.</li>
</ul>
<p>&nbsp;</p>
<ul>
<li>The <em>ScreenGrab</em> module is intended as a light-weight texture saver for creating 'screen shot' bitmap files from render target textures. The <em>ScreenGrab</em> module is included in the <em>DirectXTK</em>&nbsp;<a href="https://directxtk.codeplex.com/wikipage?title=ScreenGrab">library</a> and <em>DirectXTex </em><a href="https://directxtex.codeplex.com/wikipage?title=ScreenGrab">package</a>.</li>
</ul>
<p><em>DirectXTK</em> and <em>DirectXTex</em> both support Windows Store apps (a.k.a. Metro style apps) on Windows 8 as well as traditional Win32 desktop applications on Windows 8, Windows 7, and Windows Vista SP2 with the DirectX 11.0 update. There is a version of <em>DDSTextureLoader </em>used by the Windows 8 DirectX samples as well (see the <a href="http://code.msdn.microsoft.com/windowsapps/Direct3D-Resource-Loading-25406148">Direct3D resource loading sample</a>).</p>
<p><strong>Update: </strong>Both libraries also work on <a href="http://blogs.msdn.com/b/shawnhar/archive/2012/10/30/directx-tool-kit-now-supports-windows-phone-8.aspx">Windows phone</a>, <a href="http://www.xbox.com/en-us/Developers/id">Xbox One</a>, and <a href="https://dev.windows.com/develop/Building-universal-Windows-apps">universal Windows apps</a>.</p>
<h1><strong>Block Compression</strong></h1>
<p>One of the advantages of using <code>.DDS</code> files is the abiltiy to make use of Direct3D texture compression. The original <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb204843.aspx">Direct3D 9 texture compression</a> schemes (DXT1, DXT2/3, DXT4/5) are still supported (now called BC1, BC2, and BC3) and support is required on all Direct3D 11 API compatible hardware including the 9.1, 9.2, and 9.3 feature levels. These schemes are designed for compressing standard three-channel color data with and without an alpha channel. DirectXTex provides the same software compressor that has been in D3DX for many years, with the addition of a few minor improvements through optional control flags.</p>
<p>Feature Level 10.0, 10.1, 11.0, and 11.1 devices also support <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb694531.aspx">BC4 and BC5 compression</a> schemes. BC4 is also known as 3DC+ ("ATI1"), and BC5 is known as 3Dc ("ATI2") or "DXN", and both are designed for compressing single-channel or tow-channel textures such as normal maps. DirectXTex provides the same software compressor that was in D3DX10 and D3DX11.</p>
<p>Feature Level 11.0 and 11.1 devices support <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh308955.aspx">BC6H and BC7 compression</a> schemes. BC6H is designed for high-dynamic range (HDR) float16 content, while BC7 is a more robust high-quality alternative to the standard BC1-3 schemes for three-channel color data images. Note that BC6H and BC7 decompression is extremely fast with hardware support, but can be expensive to compress. DirectXTex provides the same software compressor&nbsp;available in D3DX11, but a DirectCompute accelerated version is in the <a href="http://go.microsoft.com/fwlink/?LinkId=254494">BC6HBC7EncoderDecoder </a>sample.</p>
<p><strong>Update:</strong> The latest <em>DirectXTex</em> supports both the CPU and DirectCompute compressors.</p>
<h1>Porting Notes</h1>
<p>Here's a handy table of equivalents for replacing legacy D3DX texture related functions.</p>
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
<p>No direct equivalent, can use Win32 resource functions and then the &lsquo;from memory&rsquo; APIs above.</p>
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
<p>No direct equivalent, can use Win32 resource functions and then the &lsquo;from memory&rsquo; APIs above.</p>
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
<p><a href="http://blogs.msdn.com/b/chuckw/archive/2012/07/28/spherical-harmonics-math.aspx">Spherical Harmonics Math</a>, <code>SHProjectCubeMap</code></p>
</td>
</tr>
</tbody>
</table>
<h1><strong>Viewing DDS files</strong></h1>
<p>The legacy DirectX SDK (see <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">Where is the DirectX SDK?</a>) includes the DirectX Texture Viewer tool. This only supports older Direct3D 9 <code>.DDS</code> files and will fail to load any file using the 'DX10' extension or BC4, BC5, BC6H, or BC7. <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/31/visual-studio-2012-release-candidate.aspx">Visual Studio 2012</a> can view modern <code>.DDS</code> files directly via File / Open / File... (the Image Files filter includes <code>.dds</code>). There is also a 'ddsview' sample available in the DirectXTex package.</p>
<h1><strong>Presentations</strong></h1>
<p><a href="http://www.microsoft.com/download/en/details.aspx?id=27853">Modern Texture Content Pipelines</a> (<em>Gamefest 2011</em>)</p>
<p><a href="http://blogs.msdn.com/b/chuckw/archive/2011/10/28/tiledresources11.aspx">Tiled Resources for Xbox 360 and Direct3D 11</a> (Gamefest 2011)</p>
<p><a href="http://download.microsoft.com/download/D/8/D/D8D077EF-CB8C-4CCA-BC24-F2CDE3F91FAA/Block_Compression_Smorgasbord_US.zip">Block Compression Smorgasbord</a> (<em>Gamefest 2010</em>)&nbsp;</p>
<h1><strong>IHV Compressors&nbsp;</strong></h1>
<p>&nbsp;The various video independent hardware vendors (IHVs) have their own texture toolsets as well.</p>
<ul>
<li><a href="http://developer.amd.com/tools-and-sdks/graphics-development/amdcompress/">AMD Compress</a></li>
<li>Intel ISPC compressors: <a href="https://software.intel.com/en-us/articles/fast-ispc-texture-compressor-update">BC6H</a>,&nbsp; <a href="http://software.intel.com/en-us/articles/fast-ispc-texture-compressor">BC7</a></li>
<li><a href="https://developer.nvidia.com/gpu-accelerated-texture-compression">NVIDIA Texture Tools</a><br /><a href="https://developer.nvidia.com/nvidia-texture-tools-adobe-photoshop">NVIDIA Texture Tools for Adobe Photoshop</a></li>
</ul>
<p><em>Note that the NVIDIA tools haven't been updated in some time, and are currently missing support for the <a href="http://blogs.msdn.com/b/chuckw/archive/2010/02/05/the-dds-file-format-lives.aspx">DX10 header extension</a>, BC6H, and BC7.</em></p>
<p><strong>Related:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2011/07/11/getting-started-with-direct3d-11.aspx">Getting Started with Direct3D 11</a></p>
