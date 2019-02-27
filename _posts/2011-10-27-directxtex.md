---
layout: post
title: DirectXTex
date: 2011-10-27 17:15
author: walbourn
comments: true
categories: [codeplex, conference, dds, Uncategorized]
---
<p>As part of my <strong>Gamefest 2011</strong> presentation <em>Modern Texture Content Pipelines </em>(<a href="http://www.microsoft.com/download/en/details.aspx?id=27853">US</a> / <a href="http://www.microsoft.com/download/en/details.aspx?id=27852">UK</a>), I demonstrated the "DirectXTex" library which is a shared source implementation of DDS file I/O (including the "DX10" header extension), texture content processing operations (resize, format conversion, mip-map-generation), software block compression (BC1 - BC7), height-map to normal-map conversion, and a simple .TGA file reader and writer.</p>
<p>The attached package includes:</p>
<ul>
<li>The <strong>DirectXTex</strong> library</li>
<li><strong>Texconv</strong>, a sample using DirectXTex that is a command-line tool replacement for the DirectX SDK Texture Conversion Tool (Extended)</li>
<li><strong>DDSView</strong>, a simple DDS viewer sample using DirectXTex</li>
<li><strong>DDSTextureLoader</strong>, a light-weight DDS loader for DirectX 11 applications</li>
<li><strong>WICTextureLoader</strong>, a WIC-based image loader for creating simple 2D textures with auto-gen mipmaps for DirectX 11 applications</li>
<li><strong>ScreenGrab</strong>, a light-weight screen shot saver for DirectX 11 applications</li>
<li>A copy of <a title="Games for Windows and the DirectX SDK Blog" href="http://blogs.msdn.com/b/chuckw/archive/2011/02/23/xna-math-version-2-04.aspx">XNAMath 2.04</a>, which is required to build the DirectXTex library with VS 2010</li>
</ul>
<p>See the ReadMe.txt file in the package for more details.</p>
<p><strong>Platforms: </strong>The code is designed to build with the Windows 8.x SDK using Visual Studio 2010, 2012, or 2013 and works on Windows Vista, Windows 7, Windows 8.x Win32 desktop, Windows Store apps, Windows phone 8.1,&nbsp;and Xbox One.</p>
<p><strong>Note:</strong> DDSTextureLoader, WICTextureLoader, and ScreenGrab are also provided in the <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/02/directxtk.aspx">DirectX Tool Kit</a></p>
<h1>Porting Notes</h1>
<p>Here's a handy table of equivalents for D3DX (see <a href="http://blogs.msdn.com/b/chuckw/archive/2013/08/21/living-without-d3dx.aspx">Living without D3DX</a> for a complete listing):</p>
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
<p>Where XXX is "DDS" for working with .DDS files, "WIC" for working with WIC-supported bitmap image formats such as .BMP, .JPG, .PNG, etc. or "TGA" for working with Targa Truvision files. Note that .TGA is supported by legacy D3DX and by DirectXTex, but not by WICTextureLoader or DirectXTK.</p>
<h1>Note</h1>
<p>There is&nbsp;another version of the Texconv sample with the DirectXTex library that uses <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/27/introducing-directxmath.aspx">DirectXMath</a> with <a title="MSDN Library" href="http://msdn.microsoft.com/en-us/library/hh404490.aspx">DXGI 1.2</a> support available on the<a href="http://code.msdn.microsoft.com/windowsdesktop/DirectX-11-Texture-fecd4824"> Windows SDK Samples Code Gallery</a>. It can be built using either <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/31/visual-studio-2012-release-candidate.aspx">Visual Studio 2012</a> or VS 2010 with the <a href="http://msdn.microsoft.com/en-us/windows/hardware/hh852363">new Windows SDK</a>. There is also a Windows Store app (a.k.a. Metro style app) version of the DDSTextureLoader <a title="Windows SDK Samples Code Gallery" href="http://code.msdn.microsoft.com/windowsapps/Direct3D-Resource-Loading-25406148">there</a> as well. The <em>Windows SDK Samples Code Gallery</em> version of DirectXTex can be made to run on Windows Vista and WIndows 7 by adding <code>_WIN32_WINNT=0x0600</code> to the Preprocessor Definitions.</p>
<p><strong>Update:</strong> DirectXTex is now hosted on <a href="http://directxtex.codeplex.com/">CodePlex</a>&nbsp;and <a href="https://github.com/Microsoft/DirectXTex">GitHub</a>. The latest version of the library, documentation, notes on future work, release history, and other information is now available there.</p>
<p><strong>Related:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/02/directxtk.aspx">DirectX Tool Kit</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2014/06/27/directxmesh.aspx">DirectXMesh</a></p>
