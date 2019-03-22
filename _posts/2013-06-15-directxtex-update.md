---
layout: post
title: DirectXTex Update
date: 2013-06-15 12:55
author: Chuck Walbourn
comments: true
categories: [codeplex, direct3d]
---
The DirectX Texture library (aka DirectXTex) for Direct3D 11 (originally released on this <a href="https://walbourn.github.io/directxtex/">blog</a> and made an official CodePlex project) has continued to improve. It's been a busy month of work, but with this release I've hit a milestone of sorts so I'm declaring this DirectXTex "Version 1.1". This release includes custom filtering implementations to fully finish out the feature set, and as of this release all the functionality that was in D3DX11 for texture processing is now available in DirectXTex. Resizing and mipmap generation has been updated to avoid a number of known issues with the Windows Imaging Component (WIC) including proper HDR/XR format handling, sRGB gamma correct filtering and conversion behavior, mirror/wrap texture address mode filtering semantics, and implements the finite low-pass triangle filter that was available in D3DX. Volume map mipmap generation now supports all filtering modes and supports non-power-of-2 volume maps.
<!--more-->

The DirectXTex package also include a new command-line utility for creating volume maps, cube maps, and texture arrays (<code>texassemble</code>). It loads each of the image files provided, performs any required resizing and format conversion to get them all to match, and outputs a .DDS files containing the new complex resource. This tool does not perform texture compression or mipmap generation, but the .DDS output file is suitable for use with <code>texconv</code> to do these operations. For convenience it will expand texture compressed .DDS files used as input files, but will exit with an error if given a complex .DDS file as input.

The latest release is available on <a href="https://directxtex.codeplex.com/">CodePlex</a> and <a href="https://github.com/Microsoft/DirectXTex">GitHub</a>. The documentation on <a href="https://github.com/Microsoft/DirectXTex/wiki">GitHub</a> has also been updated.

<h1>June 15, 2013</h1>

<ul>
<li>Custom filtering implementation for Resize & GenerateMipMaps(3D) - Point, Box, Linear, Cubic, and Triangle</li>
<ul>
<li>``TEX_FILTER_TRIANGLE`` finite low-pass triangle filter</li>
<li>``TEX_FILTER_WRAP``, ``TEX_FILTER_MIRROR`` texture semantics for custom filtering</li>
<li>``TEX_FILTER_BOX`` alias for ``TEX_FILTER_FANT`` WIC</li>
</ul>
<li>Ordered and error diffusion dithering for non-WIC conversion</li>
<li>sRGB gamma correct custom filtering and conversion</li>
<li>``DDS_FLAGS_EXPAND_LUMINANCE`` - Reader conversion option for L8, L16, and A8L8 legacy DDS files</li>
<li>Added use of WIC metadata for sRGB pixel formats</li>
<li>Added BitsPerColor utility function</li>
<li>Fixed Convert threshold parameter usage</li>
<li>Non-power-of-2 volume map support, fixed bug with non-square volume maps</li>
<li><code>Texconv</code> utility update with -xlum, -wrap, and -mirror options; reworked -if options for improved dithering</li>
<li><code>Texassemble</code> utility for creating cubemaps, volume maps, and texture arrays</li>
<li>DDSTextureLoader and WICTextureLoader sync'd with DirectXTK versions</li>
</ul>
