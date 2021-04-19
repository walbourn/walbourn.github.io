---
layout: post
title: DirectXTK for Audio updates and a Direct3D 9 footnote
date: 2020-05-10 14:20
author: Chuck Walbourn
comments: true
categories: [github]
---

The May 2020 releases of [DirectXTex](https://github.com/microsoft/DirectXTex/releases/tag/may2020), [DirectXMesh](https://github.com/microsoft/DirectXMesh/releases/tag/may2020), *DirectX Tool Kit* [DX11](https://github.com/microsoft/DirectXTK/releases/tag/may2020) / [DX12](https://github.com/microsoft/DirectXTK12/releases/tag/may2020), and [UVAltas](https://github.com/microsoft/UVAtlas/releases/tag/may2020) are now available on GitHub and NuGet. Two notable features in these releases as well as a bonus tool kit feature for DirectX 12 are covered in this post.
<!--more-->

# DirectX Tool Kit for Audio updates

The [DirectX Tool Kit for Audio](https://walbourn.github.io/directx-tool-kit-for-audio/) provides a simple "XNA Game Studio like" wrapper for the XAudio2 and X3DAudio libraries, complete with 'one-shots' and voice management. When I implemented it back in 2013, I also included support for playing sounds from XACT-style in-memory wave banks. The [xwbtool](https://github.com/Microsoft/DirectXTK/wiki/XWBTool) command-line tool supports creating both *in-memory* and *streaming* wave banks, but the only code that used the streaming flavor was the [XAudio2AsyncStream](https://github.com/walbourn/directx-sdk-samples/tree/master/XAudio2/XAudio2AsyncStream) sample.

The primary value of the XACT-style streaming wavebank is that the data is laid out for non-buffered asynchronous I/O "sector" alignment requirements, which is the ideal mode for efficient sound streaming from disk. The **XAudio2AsyncStream** sample implemented this for PCM audio, which is pretty simple because the block size, packet size, and sector size all align. Getting MS-ADPCM, xWMA, or XMA2 to work was not quite as easy.

In any case, thanks in part to the global pandemic, I finally had the time and motivation to implement the [SoundStreamInstance](https://github.com/microsoft/DirectXTK/wiki/SoundStreamInstance) class. It supports streaming for PCM, MS-ADPCM, xWMA (XAudio 2.7 or XAudio 2.9 required), and XMA2 (Xbox) from XACT-style streaming wavebanks.

The main functional limitation compared to XACT's streaming implementation is that I don't yet support loop-points for streaming or loop-counts. I do support basic looping and the "exit loop" behavior of the ``Stop`` method.

> Note that the May 2020 release of *DirectX Tool Kit for Audio* will be the last one to support XAudio 2.7 with the legacy DirectX SDK. The [XAudio2Redist](https://aka.ms/xaudio2redist) solution provides much improved and more robust support for Windows 7 SP1, as well as providing xWMA support on XAudio 2.8 if needed.

# Legacy Direct3D 9 texture support

It's been 18 years since the release of DirectX 9, and I've been focused on providing excellent developer support for DirectX 11 and DirectX 12 for most of that time. That said, I did have a recent request for help with the basics of loading DDS textures from disk for Direct3D 9 without having to use the deprecated D3DX9 library from the [legacy DirectX SDK](https://docs.microsoft.com/en-us/windows/win32/directx-sdk--august-2009-). Unfortuantely, the [DDSWithoutD3DX](https://walbourn.github.io/ddswithoutd3dx-sample-update/) sample was realy showing it's age, and was conjoined with Direct3D 10.

I now have Direct3D 9, Direct3D 11, and Direct3D 12 versions of the [DDSTextureLoader](https://github.com/microsoft/DirectXTex/tree/master/DDSTextureLoader), [WICTextureLoader](https://github.com/microsoft/DirectXTex/tree/master/WICTextureLoader), and [ScreenGrab](https://github.com/microsoft/DirectXTex/tree/master/ScreenGrab) 'standalone' modules. For all versions of the WICTextureLoader, I added three new loader flags: one to force the texture resize target to a power of 2, another to force the texture resize target to be square, and a third flag to force the resulting texture to always be in RGBA32 pixel format. The first two are most useful when dealing with some limitations of older Direct3D 9 era video cards.

> Note that the WICTextureLoader for Direct3D 9 actually strongly prefers "BGR" color order instead of the more common "RGB" color order used by most DXGI formats. This is because many of these older Direct3D 9 implementations only support "BGR" pixel formats--and the new "force RGBA32" flag for Direct3D 9 is technically a "force BGRA32".

The Direct3D 9 version of DDSTextureLoader only loads "legacy style" DDS files (i.e. not those that use the 'DX10' header extension for ``DXGI_FORMAT``). While the ``texconv`` command-line tool already preferred the "legacy style" unless you used the ``-dx10`` switch, there are a few cases where it will write using the 'DX10' header extension anyhow (specifically when writing 10:10:10:2 formats per [this blog post](https://walbourn.github.io/dds-update-and-1010102-problems/) and for sRGB formats). There is a new ``-dx9`` switch which will cause the tool to always output "legacy style" DDS files. If it is unable to represent it as such, it will fail (such as for texture 2D arrays or cubemap arrays which always require the 'DX10' extension header).

I can't justify putting time into creating a complete Direct3D 9 tool kit at this point, but I hope these routines and the ``-dx9`` switch are useful to the community.

> For the May 2020 release of *DirectX Tool Kit*, I removed the hard requirement for the [SimpleMath](https://github.com/microsoft/DirectXTK/wiki/SimpleMath) header to include either d3d11.h or d3d12.h before including SimpleMath (a DirectXMath wrapper library). You can use it with d3d9.h instead, but it won't have any Direct3D Viewport structure implicit conversion operators.

# DirectX 12 resource loading

The [ResourceUploadBatch](https://github.com/microsoft/DirectXTK12/wiki/ResourceUploadBatch) class is used in *DirectX Tool Kit for DX12* to manage uploading of texture data, static vertex buffers, and static index buffers to video memory. The class also implements  auto-generation of mipmaps if requested. The original implementation focused on using ``D3D12_COMMAND_LIST_TYPE_DIRECT`` command queues (i.e. the DirectX 12 equivalent of the DX 11 'immediate device context').

One of the design advantages to DirectX 12, is that you can simultaneously access 'copy engines' and 'compute engines' on the GPU while performing rendering commands. Therefore, the May 2020 release of the tool kit now supports using ``D3D12_COMMAND_LIST_TYPE_COMPUTE`` and ``D3D12_COMMAND_LIST_TYPE_COPY`` command queues which can be used from loading threads. The compute queue offers support for both uploading and auto-generation of mipmaps. The copy version is sufficient for all texture loading if you don't need auto-generation of mips.

Since there are limitations on valid resource states when using these alternative command queues, there are new ``Transition`` helper methods for [GeometricPrimitive](https://github.com/microsoft/DirectXTK12/wiki/GeometricPrimitive) and [Model](https://github.com/microsoft/DirectXTK12/wiki/Model) when loading static VBs/IBs for compute/copy command queues. These can be used to put those resources into the proper state for rendering after the upload has completed.
