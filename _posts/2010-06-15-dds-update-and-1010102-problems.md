---
layout: msdnpost
title: DDS Update and 10:10:10:2 Problems
date: 2010-06-15 14:53
author: Chuck Walbourn
comments: true
categories: [dds]
---
The <em>DirectX SDK (June 2010)</em> release includes the fixes to the <em>DDSWithoutD3DX</em> and <em>DDSWithoutD3DX11</em> samples I mentioned in earlier posts. The <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3ddds/dx-graphics-dds-pguide" title="Programmer's Guide for DDS">Programmer's Guide for DDS</a> in the Windows DirectX Graphics documentation was also updated to reflect the latest format details.
<!--more-->

There is a footnote at the end of the documentation chart that I wanted to expand on, and this is a consequence of D3DX having a long-standing bug in the way it reads and writes 10:10:10:2 format ``DDS`` data files.

D3DX9 writes out ``D3DFMT_A2B10G10R10`` format texture data using an RGB surface with the following color masks:

    R: 3ff00000, G: 000ffc00, B: 000003ff, A: c0000000

For a ``D3DFMT_A2R10G10B10`` format, it creates an RGB surface with:

    R: 000003ff, G: 000ffc00, B: 3ff00000, A: c0000000

The problem is that the RED and BLUE masks are <em>backwards </em>from the actual data ordering. The reader makes the same mistake, so this is not an issue if you only use D3DX to read and write your ``DDS`` files, but if you try to parse them yourself or make use of 3rd party ``DDS`` texture tools you may end up with RED and BLUE swapped. This bug still exists in the June 2010 version of D3DX9, and affects texconv, DxTex, and any other tool that uses D3DX9 to read or write 10:10:10:2 format ``DDS`` files. You can see this by creating a 10:10:10:2 format texture file with one of these tools and loading it with the <em>DDSWithoutD3DX</em> sample--the code there expects the 'correct' mask order.

D3DX10 and D3DX11 have their own version of this same bug. When writing out ``DXGI_FORMAT_R10G10B10A2_UNORM`` format texture data, it creates an RGB surface with color masks

    R: 3ff00000, G: 000ffc00, B: 000003ff, A: c0000000

This DXGI format is equivalent to ``D3DFMT_A2B10G10R10``, and the RED/BLUE masks are again <em>backwards </em>from the true bit ordering in the format. Again, the reader and writer have the same bug, and since it is basically the same as the bug in D3DX9, this never shows up unless you are writing your own ``DDS`` file parser or using a 3rd party DDS tool. This bug also continues to exist in the June 2010 version of D3DX10 and D3DX11, and affects the texconvex tool.

The good news is there is a robust way to resolve the issue for your own ``DDS`` reader & writer. Instead of using RGB surface masks to describe the 10:10:10:2 format, use the 'DX10' extension header instead (see my post <a href="https://walbourn.github.io/the-dds-file-format-lives/" title="The DDS File Format Lives">The DDS File Format Lives</a> for details). This will work unambiguously for D3DX10 or D3DX11 reading the file, and side-steps the compat issue generally for DXGI-aware versions of the ``DDS`` file parser. Unfortunately, the D3DX9 library does not support the 'DX10' header extension so this is not a solution for Direct3D 9 era ``DDS`` files. However, if you have your own ``DDS`` file parser you can have it support the 'DX10' header extension and the subset of DXGI formats that correspond directly to Direct3D 9 formats to handle this case. For back-compat purposes, you may want your reader to duplicate this buggy mask usage but have any ``DDS`` files you generate use the 'DX10' header to avoid generating more incorrect ``DDS`` files for these texture formats.

It is unlikely that we'll change this behavior for D3DX9 as there is no good robust solution that would not invalidate existing 10:10:10:2 texture format ``DDS`` files. Developers writing their own ``DDS`` file parsers will need to be aware of this bug, and should prefer using the 'DX10' extension header whenever possible. See the <strong>Programmer's Guide for DDS</strong> page for recommendations on how best to describe each format.<strong></strong>

<strong>DirectXTex and DirectXTK:</strong>Due to this ambiguity, <a href="https://github.com/Microsoft/DirectXTex">DirectXTex</a>'s DDS writer, [DirectX Tool Kit for DX11](https://github.com/Microsoft/DirectXTK) ScreenGrab, and [DirectX Tool Kit for DX12](https://github.com/Microsoft/DirectXTK12) ScreenGrab always encode <code>DXGI_FORMAT_R10G10B10A2_UNORM</code> using the 'DX10' header extension. The DDS readers in both libraries will assume any legacy 10:10:10:2 DDS header is 'flipped' as D3DX would have written it.
