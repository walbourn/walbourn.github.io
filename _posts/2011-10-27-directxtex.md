---
layout: msdnpost
title: DirectXTex
date: 2011-10-27 17:15
author: Chuck Walbourn
comments: true
categories: [codeplex, conference, dds]
---
As part of my <strong>Gamefest 2011</strong> presentation <em>Modern Texture Content Pipelines </em> (<a href="https://walbourn.github.io/download/Graphics-Modern-Texture-Content-Pipelines.zip">link</a>), I demonstrated the "DirectXTex" library which is a shared source implementation of DDS file I/O (including the "DX10" header extension), texture content processing operations (resize, format conversion, mip-map-generation), software block compression (BC1 - BC7), height-map to normal-map conversion, and a simple .TGA file reader and writer.
<!--more-->

The attached package includes:

<ul>
<li>The <strong>DirectXTex</strong> library</li>
<li><strong>Texconv</strong>, a sample using DirectXTex that is a command-line tool replacement for the DirectX SDK Texture Conversion Tool (Extended)</li>
<li><strong>DDSView</strong>, a simple DDS viewer sample using DirectXTex</li>
<li><strong>DDSTextureLoader</strong>, a light-weight DDS loader for DirectX 11 applications</li>
<li><strong>WICTextureLoader</strong>, a WIC-based image loader for creating simple 2D textures with auto-gen mipmaps for DirectX 11 applications</li>
<li><strong>ScreenGrab</strong>, a light-weight screen shot saver for DirectX 11 applications</li>
<li><strike>A copy of <a href="https://walbourn.github.io/xna-math-version-2-04/">XNAMath 2.04</a>, which is required to build the DirectXTex library with VS 2010</strike></li>
</ul>

See the ReadMe file in the package for more details.

<strong>Platforms: </strong>The code is designed to build with the Windows 8.x SDK using Visual Studio 2010, 2012, or 2013 and works on Windows Vista, Windows 7, Windows 8.x Win32 desktop, Windows Store apps, Windows phone 8.1, and Xbox One.

<strong>Note:</strong> DDSTextureLoader, WICTextureLoader, and ScreenGrab are also provided in the _DirectX Tool Kit_ for [DX11](https://walbourn.github.io/directxtk/) / [DX12](https://walbourn.github.io/directx-tool-kit-for-directx-12/)

# Porting Notes

<p>Here's a handy table of equivalents for D3DX (see <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a> for a complete listing):</p>
<table border="1">
<tbody>
<tr>
<td><code>D3DX11ComputeNormalMap</code></td>
<td>
<p><code>ComputeNormalMap</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11CreateShaderResourceViewFromFile</code></td>
<td>
<p><code>LoadFromXXXFile, CreateShaderResourceView</code></p>
<p>-or-</p>
<p><code>CreateXXXTextureFromFile</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11CreateShaderResourceViewFromResource<br />D3DX11CreateShaderResourceViewFromMemory</code></td>
<td>
<p><code>LoadFromXXXMemory, CreateShaderResourceView</code></p>
<p>-or-</p>
<p><code>CreateXXXTextureFromMemory</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11CreateTextureFromFile</code></td>
<td>
<p><code>LoadFromXXXFile, CreateTexture</code></p>
<p>-or-</p>
<p><code>CreateXXXTextureFromFile</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11CreateTextureFromResource<br />D3DX11CreateTextureFromMemory </code></td>
<td>
<p><code>LoadFromXXXMemory, CreateTexture</code></p>
<p>-or-</p>
<p><code>CreateXXXTextureFromMemory</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11FilterTexture</code></td>
<td>
<p><code>GenerateMipMaps, GenerateMipMaps3D</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11GetImageInfoFromFile</code></td>
<td>
<p><code>GetMetadataFromXXXFile</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11GetImageInfoFromResource<br />D3DX11GetImageInfoFromMemory</code></td>
<td>
<p><code>GetMetadataFromXXXMemory</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11LoadTextureFromTexture</code></td>
<td>
<p><code>Resize</code>, <code>Convert</code>, <code>Compress</code>, <code>Decompress</code>, and/or <code>CopyRectangle</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11SaveTextureToFile</code></td>
<td>
<p><code>CaptureTexture, SaveToXXXFile</code></p>
<p>-or-</p>
<p><code>SaveXXXTextureToFile</code></p>
</td>
</tr>
<tr>
<td><code>D3DX11SaveTextureToMemory</code></td>
<td>
<p><code>CaptureTexture, SaveToXXXMemory </code></p>
</td>
</tr>
</tbody>
</table>

Where XXX is "DDS" for working with .DDS files, "WIC" for working with WIC-supported bitmap image formats such as .BMP, .JPG, .PNG, etc. or "TGA" for working with Targa Truvision files. Note that ``.TGA`` is supported by legacy D3DX and by DirectXTex, but not by WICTextureLoader or DirectXTK.

**UPDATE**: DirectXTex now also supports ``.HDR`` files. See [this post](https://walbourn.github.io/hdr-lighting-and-displays/). The XXX above would be "HDR".

# Note

There is another version of the Texconv sample with the DirectXTex library that uses <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a> with <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3ddxgi/dxgi-1-2-improvements">DXGI 1.2</a> support available on the<a href="http://code.msdn.microsoft.com/windowsdesktop/DirectX-11-Texture-fecd4824"> Windows SDK Samples Code Gallery</a>. It can be built using either <a href="https://walbourn.github.io/visual-studio-2012-release-candidate/">Visual Studio 2012</a> or VS 2010 with the <a href="https://developer.microsoft.com/en-us/windows/downloads/sdk-archive">new Windows SDK</a>. There is also a Windows Store app (a.k.a. Metro style app) version of the DDSTextureLoader <a href="http://code.msdn.microsoft.com/windowsapps/Direct3D-Resource-Loading-25406148">there</a> as well. The <em>Windows SDK Samples Code Gallery</em> version of DirectXTex can be made to run on Windows Vista and Windows 7 by adding ``_WIN32_WINNT=0x0600`` to the Preprocessor Definitions.

<strong>Update:</strong> DirectXTex is now hosted on <strike><a href="http://directxtex.codeplex.com/">CodePlex</a></strike><a href="https://github.com/Microsoft/DirectXTex">GitHub</a>. The latest version of the library, documentation, notes on future work, release history, and other information is now available there.

<strong>vcpkg</strong>: The vcpkg C++ Package Manager has a [directxtex](https://github.com/microsoft/vcpkg/tree/master/ports/directxtex) port available.

<strong>Related:</strong> <a href="https://walbourn.github.io/directxtk/">DirectX Tool Kit for DX11</a>, <a href="https://walbourn.github.io/directxmesh/">DirectXMesh</a>, <a href="https://walbourn.github.io/directx-tool-kit-for-directx-12/">DirectX Tool Kit for DX12</a>
