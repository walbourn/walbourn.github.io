---
layout: post
title: BC6HBC7EncoderDecoder Sample Update
date: 2011-06-02 11:33
author: walbourn
comments: true
categories: [dds, dxsdk, Uncategorized]
---
Direct3D 11 class hardware through the Direct3D 11 API supports two new texture compression formats: BC6H and BC7. These new Block Compressed formats provide excellent compression for High-Dynamic Range (HDR) images and higher-fidelity traditional content. The D3DX11 library includes a software implementation of the encoder, but the new BC formats are extremely asymmetric meaning the encoding algorithm has a very large search space to determine the optimal compression for each 4x4 block. This makes a great candidate for a GPGPU DirectCompute implementation of the compression algorithm. The <strong>BC6HBC7EncoderDecoder11</strong> sample in the DirectX SDK provides such an implementation using DirectCompute 4.0.

Attached to this post is a ZIP containing an updated copy of the C++ source files and the two HLSL shaders for encoding which you can drop into the <strong>BC6HBC7EncoderDecoder11</strong> sample code in the DirectX SDK (June 2010). This update enables support for HD Photo source images which makes a great source for HDR content (D3DX11 supports the HD Photo file format, but COM must be explicitly initialized for it to work properly), as well as a work-around for an HLSL compiler bug with the June 2010 release that affected encoding in some cases. There are also a few minor cleanups and a diagnostic message to highlight that the source image <em>must</em> have dimensions that are a multiple of 4 for the encoder to succeed (this is a requirement for all the BC formats).

For more information on BC6H and BC7 texture compression, see the Gamefest 2010 talk <em>Block Compression Smorgasbord</em> (<a href="http://download.microsoft.com/download/D/8/D/D8D077EF-CB8C-4CCA-BC24-F2CDE3F91FAA/Block_Compression_Smorgasbord_US.zip" title="MS Downloads">US</a>). Remember that DDS files containing BC6H and BC7 content are stored using the <a href="http://blogs.msdn.com/b/chuckw/archive/2010/02/05/the-dds-file-format-lives.aspx" title="Games for Windows and the DirectX SDK Blog">'DX10'</a> header extension, which is not widely supported by existing tools

<strong>Update</strong>: Note that full documentation on the BC6H and BC7 formats is now available on <a href="http://msdn.microsoft.com/en-us/library/hh308955.aspx" title="Texture Block Compression in Direct3D 11">MSDN</a>. The source to the D3DX11 software compressor and decompressor has been incorporated into the <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a> library as well.

<strong>Note:</strong> The latest version of this code is now available on <a href="https://github.com/walbourn/directx-sdk-samples/tree/master/BC6HBC7EncoderCS">GitHub</a>.

<strong>DirectXTex</strong>: The DirectCompute BC6H and BC7 compressors are now integrated into <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a>.
