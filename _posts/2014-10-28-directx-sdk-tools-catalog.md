---
layout: post
title: DirectX SDK Tools Catalog
date: 2014-10-28 16:47
author: walbourn
comments: true
categories: [dxsdk, Uncategorized]
---
In the same vein as my post on where you can find many of the <a href="http://blogs.msdn.com/b/chuckw/archive/2013/09/20/directx-sdk-samples-catalog.aspx">samples</a> from the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee663275.aspx">legacy DirectX SDK</a>, where you can find all the various <a href="http://blogs.msdn.com/b/chuckw/archive/2013/08/21/living-without-d3dx.aspx">replacements for D3DX</a>, and the status of various <a href="http://blogs.msdn.com/b/chuckw/archive/2012/08/22/directx-sdk-s-of-a-certain-age.aspx">DirectX components</a>; this post is a catalog of where you can find the latest version of various tools that shipped with the legacy DirectX SDK. Lacking that, it at least provides a status or alternative for the tool.
<table border="1">
<tbody>
<tr>
<td>DirectX Capabilities Viewer (<code>DxCapsViewer.exe</code>)
DirectX Control Panel (<code>DxCpl.exe</code>)
Game Definition File Editor (<code>GDFMaker.exe</code>)
HLSL Compiler (<code>fxc.exe</code>)
<code>AdpcmEncode.exe</code></td>
<td><a href="http://blogs.msdn.com/b/chuckw/archive/2013/10/18/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available.aspx">Windows 8.1 SDK / Visual Studio 2013</a> or later</td>
</tr>
<tr>
<td>DirectX Error Lookup Tool (<code>DXErr.exe</code>)</td>
<td>The Visual Studio<em> Error Lookup</em> (under Tools) should help with many HRESULT values, particularly for development on Windows 8.x or later.

For notes on the DxErr library that the <code>DXErr.exe</code> tool used, see <a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/24/where-s-dxerr-lib.aspx">this post</a>.</td>
</tr>
<tr>
<td>Game Definition File Validator (<code>gdftrace.exe</code>)</td>
<td><a href="https://code.msdn.microsoft.com/GDF-Trace-5389d1b4">MSDN Code Gallery</a> or <a href="https://github.com/walbourn/directx-sdk-samples/tree/master/GDFTrace">GitHub</a></td>
</tr>
<tr>
<td>Texture Conversion Tool (<code>Texconv.exe</code>)
<code>Texconvex.exe</code></td>
<td><a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a></td>
</tr>
<tr>
<td><code>Meshconvert.exe</code></td>
<td><a href="http://go.microsoft.com/fwlink/?LinkID=324981">DirectXMesh</a>

See also the <a href="http://go.microsoft.com/fwlink/?LinkId=226208">Samples Content Exporter</a>.</td>
</tr>
<tr>
<td>DirectX Texture Editor (<code>DxTex.exe</code>)</td>
<td>This legacy DirectX SDK tool does not support DDS files with the <a href="http://blogs.msdn.com/b/chuckw/archive/2010/02/05/the-dds-file-format-lives.aspx">'DX10' header extension</a>.

VS 2012 or later can view all DDS files supported by DirectXTex.</td>
</tr>
<tr>
<td><code>TxView.DLL</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/dn280986.aspx">Windows 8.1 WIC</a> supports DDS format files for BC1-BC3/DXT1-5 so these show up as thumbnails and can be opened with Photo Viewer.</td>
</tr>
<tr>
<td><code>AudConsole3.exe
Xact3.exe
XactBld3.exe
XaudConsole3.exe</code></td>
<td>XACT is deprecated and is only available in the legacy DirectX SDK.

The <code>xwbtool</code> in <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectX Tool Kit </a> can build XACT3-style .xwb wave banks for bulk loading of .wav files using <em>DirectX Tool Kit for Audio</em>.</td>
</tr>
<tr>
<td><code>xWMAEncode.exe</code></td>
<td>xWMA compression is supported by XAudio 2.7 and the Xbox One version of XAudio, but not by <a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/02/xaudio2-and-windows-8-consumer-preview.aspx">XAudio 2.8 in Windows 8.x</a>.

Therefore this tool only ships in the legacy DirectX SDK and in the Xbox One XDK.</td>
</tr>
<tr>
<td>Microsoft XNA Test Case Tool</td>
<td>The latest version of this tool is on <a href="http://www.microsoft.com/en-us/download/details.aspx?id=13884">Microsoft Downloads</a>. <em>For the latest game-specific best practices for Windows, see <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/23/desktop-games-on-windows-8-consumer-preview.aspx">this post</a>.</em>

Certification for Windows logo usage for Win32 desktop application is managed through <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh749939">Windows App Certification Kit (WACK).</a>.</td>
</tr>
<tr>
<td>PIX for Windows</td>
<td>PIX for Windows is not compatible with the DirectX 11.1 or later runtime on Windows 8.x or Windows 7 SP1 with <a href="http://support.microsoft.com/kb/2670838">KB2670838</a>. See <a href="http://blogs.msdn.com/b/chuckw/archive/2013/02/26/directx-11-1-and-windows-7-update.aspx">this post</a> for details.

<a href="http://msdn.microsoft.com/en-us/library/hh873207.aspx">Visual Studio Graphics Diagnostics</a> in VS 2012 Pro+, VS 2013 Express for Windows, VS 2013 Pro+, or VS 2013 Community.

Graphics vendor tools from Intel (<a href="http://www.intel.com/software/gpa">GPA</a>), AMD (<a href="http://developer.amd.com/tools-and-sdks/graphics-development/gpu-perfstudio/">GPU PerfStudio</a>), or NVidia (<a href="https://developer.nvidia.com/nvidia-nsight-visual-studio-edition">Nsight</a>).</td>
</tr>
</tbody>
</table>
