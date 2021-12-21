---
layout: msdnpost
title: DDSWithoutD3DX Sample Update
date: 2010-07-15 14:50
author: Chuck Walbourn
comments: true
categories: [dds]
---
Over the past few releases of the DirectX SDK, I've been working on updating our documentation for the ``DDS`` file format. The <strong>DDSWithoutD3DX</strong> and <strong>DDSWithoutD3DX11</strong> samples in the <em>DirectX SDK (June 2010)</em> release demonstrate the details of interpreting the DDS file format for basic 2D textures and 2D texture arrays for Direct3D 9, Direct3D 10.x, and Direct3D 11. Since the June release, I've been expanding the sample to support cubemaps, volume textures, and 1D textures. In the process I also found a number of minor issues with the DDSTextureLoader code and the ``DDS.H`` header.
<!--more-->

**UPDATE: The latest version of DDSTextureLoader for Direct3D 9, Direct3D 11, and Direct3D 12 can be found on [GitHub](https://github.com/microsoft/DirectXTex/tree/main/DDSTextureLoader)**

> Attached to this post is a ZIP containing an updated DDS.H, DDSTextureLoader.cpp, and DDSTextureLoader.h which you can drop into the <strong>DDSWithoutD3DX11</strong> sample code in the DirectX SDK (June 2010). Note that the <strong>DDSWithoutD3DX</strong> sample is very similar if you are looking to use it with Direct3D 10.x instead of Direct3D 11, although there are some additional complexities when dealing with cubemap arrays which are supported by the Direct3D 10.1 API with ``D3D10_FEATURE_LEVEL_10_1`` hardware, but not the Direct3D 10.0 API or ``D3D10_FEATURE_LEVEL_10_0`` hardware.

<strong>Update</strong>: A recent inquiry about the ``DDS`` file format has brought up an area of common confusion when parsing these files w.r.t. to the pitch alignment of uncompressed pixel data (there are different rules for computing the sizes of block compressed DXT/BC formats and the packed R8G8_B8G8/G8R8_G8B8 pixel formats). The DDS file format always uses ``byte`` alignment for the pitch of uncompressed data, but the original <em>DrawDraw</em> structures used to define the format document that the pitch should be ``DWORD`` aligned. With many common texture formats and sizes, these computations yield the same results but for 16-bit and 24-bit per pixel formats, these results do not agree.  This is further complicated by the fact that many DDS writers (including D3DX) do not set a PITCH value in the header, so DDS readers have to compute one from assumptions.

The recommendation is to use byte-alignment (which is what the <strong>DDSWithoutD3DX</strong> samples do), but you may want to support a legacy compatibility flag on your DDS reader that will compute DWORD aligned pitch values should you encounter content that uses the incorrect "DWORD" alignment. You can also side-step this issue by preferring the use of block compressed (DXT/BC) or 32-bit per pixel formats--16-bit and 24-bit per pixel formats are not supported by Direct3D 10.x or 11 in any case. It is also important than when copying the data from the DDS structure into a Direct3D resource that you do not assume the pitch values will match, so you must support copying line-by-line (or use initData for Direct3D 10.x & 11 which is what the <strong>DDSWithoutD3DX</strong> sample demonstrates).

<strong>Update 2:</strong> I found a minor problem with legacy cubemap DDS files. I was over-validating legacy volume map DDS files for having the 'right' flags set in dwCaps2, which are often missing.

<strong>Update 3:</strong> Minor issue, but BC4 formats should be 4 BitsPerPixel. Doesn't affect the functionality because GetSurfaceInfo has special handling for BC4 formats already, but in the interest of avoiding future cut & paste issues I've fixed it in another refresh of the source.

See also <a href="https://walbourn.github.io/the-dds-file-format-lives/">The DDS File Format Lives</a> and <a href="https://walbourn.github.io/dds-update-and-10-10-10-2-problems/">DDS Update and 10:10:10:2 problems</a>

<strong>Update 4:</strong> For Direct3D 11 only applications, consider using the DDSTextureLoader included in <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectX Tool Kit for DX11</a> instead. There is also a DDSTextureLoader for DirectX 12 included in <a href="http://go.microsoft.com/fwlink/?LinkID=615561">DirectX Tool Kit for DX12</a>.

<a href="https://walbourn.github.io/download/DDSTextureLoader-Updates-August-2011.zip">DDSTextureLoader Updates August 2011.zip</a>
