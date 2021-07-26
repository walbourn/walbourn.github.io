---
layout: msdnpost
title: DirectX SDK Tools Catalog
date: 2014-10-28 16:47
author: Chuck Walbourn
comments: true
categories: [dxsdk]
---
In the same vein as my post on where you can find many of the <a href="https://walbourn.github.io/directx-sdk-samples-catalog/">samples</a> from the <a href="https://docs.microsoft.com/en-us/windows/win32/directx-sdk--august-2009-">legacy DirectX SDK</a>, where you can find all the various <a href="https://walbourn.github.io/living-without-d3dx/">replacements for D3DX</a>, and the status of various <a href="https://walbourn.github.io/directx-sdks-of-a-certain-age/">DirectX components</a>; this post is a catalog of where you can find the latest version of various tools that shipped with the legacy DirectX SDK. Lacking that, it at least provides a status or alternative for the tool.
<!--more-->

<table border="1">
<tbody>
<tr>
<td>
<p>DirectX Control Panel (<code>DxCpl.exe</code>)</p>
<p>Game Definition File Editor (<code>GDFMaker.exe</code>)</p>
<p>HLSL Compiler (<code>fxc.exe</code>)</p>
<p><code>AdpcmEncode.exe</code></p></td>
<td><a href="https://walbourn.github.io/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available/">Windows 8.1 SDK / Visual Studio 2013</a> or later</td>
</tr>
<tr>
<td>DirectX Capabilities Viewer (<code>DxCapsViewer.exe</code>)</td>
<td>See <a href="https://walbourn.github.io/directx-caps-viewer-update/">DirectX Caps Viewer Update</a> and <a href="https://github.com/microsoft/DxCapsViewer">GitHub</a>.</td>
</tr>
<tr>
<td>DirectX Error Lookup Tool (<code>DXErr.exe</code>)</td>
<td>The Visual Studio<em> Error Lookup</em> (under Tools) should help with many HRESULT values, particularly for development on Windows 8.x or later.<br />
<br />
For notes on the DxErr library that the <code>DXErr.exe</code> tool used, see <a href="https://walbourn.github.io/wheres-dxerr-lib/">this post</a>.</td>
</tr>
<tr>
<td>Game Definition File Validator (<code>gdftrace.exe</code>)</td>
<td><a href="https://github.com/walbourn/directx-sdk-samples/tree/master/GDFTrace">GitHub</a></td>
</tr>
<tr>
<td>Texture Conversion Tool (<code>Texconv.exe</code>)
<code>Texconvex.exe</code></td>
<td><a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a></td>
</tr>
<tr>
<td><code>Meshconvert.exe</code></td>
<td><a href="http://go.microsoft.com/fwlink/?LinkID=324981">DirectXMesh</a><br />
<br />
See also the <a href="https://aka.ms/dxsdkcontentexporter">Samples Content Exporter</a>.</td>
</tr>
<tr>
<td>DirectX Texture Editor (<code>DxTex.exe</code>)</td>
<td>This legacy DirectX SDK tool does not support DDS files with the <a href="https://walbourn.github.io/the-dds-file-format-lives/">'DX10' header extension</a>.<br />
<br />
VS 2012 or later can view all DDS files supported by DirectXTex.</td>
</tr>
<tr>
<td><code>TxView.DLL</code></td>
<td><a href="https://docs.microsoft.com/en-us/windows/desktop/wic/what-s-new-in-wic-for-windows-8-1">Windows 8.1 WIC</a> or later supports DDS format files for BC1-BC3/DXT1-5 so these show up as thumbnails and can be opened with Photo Viewer.</td>
</tr>
<tr>
<td><p><code>AudConsole3.exe</code></p>
<p><code>Xact3.exe</code></p>
<p><code>XactBld3.exe</code></p>
<p><code>XaudConsole3.exe</code></p></td>
<td>XACT is deprecated and is only available in the legacy DirectX SDK.

The <code>xwbtool</code> in <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectX Tool Kit </a> can build XACT3-style <code>.xwb</code> wave banks for bulk loading of <code>.wav</code> files as well as streaming using <em>DirectX Tool Kit for Audio</em>.</td>
</tr>
<tr>
<td><code>xWMAEncode.exe</code></td>
<td><p>xWMA compression is supported by XAudio 2.7 and the Xbox One version of XAudio, but not by <a href="https://walbourn.github.io/xaudio2-and-windows-8/">XAudio 2.8 in Windows 8.x</a>.</p>
<p><b>UPDATE:</b> XAudio 2.9 in Windows 10 and the <a href="https://aka.ms/xaudio2redist">XAudio2Redist</a> support xWMA content.</p>
<p>This tool currently only ships in the legacy DirectX SDK and in the Xbox One development kit.</p></td>
</tr>
<tr>
<td>Microsoft XNA Test Case Tool</td>
<td><strike>The latest version of this tool is on Microsoft Downloads</strike>. <em>For the latest game-specific best practices for Windows, see <a href="https://walbourn.github.io/desktop-games-on-windows-8-x">this post</a>.</em>

Certification for Windows logo usage for Win32 desktop application is managed through <a href="https://docs.microsoft.com/en-us/windows/desktop/win_cert/certification-requirements-for-windows-desktop-apps">Windows App Certification Kit (WACK).</a>.</td>
</tr>
<tr>
<td>PIX for Windows</td>
<td><p>Legacy PIX for Windows is not compatible with the DirectX 11.1 or later runtime on Windows 8.x or Windows 7 SP1 with <a href="http://support.microsoft.com/kb/2670838">KB2670838</a>. It's not compatible with Windows 10. See <a href="https://walbourn.github.io/directx-11-1-and-windows-7-update/">this post</a> for details.</p>
<p><a href="https://docs.microsoft.com/en-us/visualstudio/debugger/overview-of-visual-studio-graphics-diagnostics">Visual Studio Graphics Diagnostics</a> in VS 2012 Pro+, VS 2013 Express for Windows, VS 2013 Pro+, or VS 2013 Community, or later.</p>
<p></p>
<p>Graphics vendor tools from Intel (<a href="http://www.intel.com/software/gpa">GPA</a>), AMD (<a href="http://developer.amd.com/tools-and-sdks/graphics-development/gpu-perfstudio/">GPU PerfStudio</a>), or NVidia (<a href="https://developer.nvidia.com/nvidia-nsight-visual-studio-edition">Nsight</a>).</p>
<p><b>UPDATE:</b> For DirectX 12 development, see <a href="https://devblogs.microsoft.com/pix/">PIX on Windows</a>.</p></td>
</tr>
<tr>
<td>UVAtlas Tool</td>
<td>In the legacy DirectX SDK the <code>uvatlas.exe</code> was a Direct3D 9 sample. You can find the latest version on <a href="https://github.com/Microsoft/UVAtlas">GitHub</a>.</td>
</tr>
</tbody>
</table>
