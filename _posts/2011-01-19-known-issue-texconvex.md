---
layout: msdnpost
title: Known Issue - TexconvEx
date: 2011-01-19 14:58
author: Chuck Walbourn
comments: true
categories: [dds, dxsdk]
---
Doing some work on the ``texconvex`` tool (the Direct3D 10.x/11 version of the Texture Conversion Tool ``texconv``), I discovered that my use of the NULL render device resulted in garbage output from this tool in some scenarios. This is easily remedied using the WARP or REFERENCE device.
<!--more-->

Since this is just a simple shell around D3DX functionality, the source code is fairly trivial. Here is the source to the current tool as shipped in the DirectX SDK (June 2010) with the above fix, as well as support for the *Windows Media Photo / HD Photo* format (i.e. ``D3DX11_IFF_WMP``). As the primary high-dynamic range image format supported by D3DX, it is an important format to support particularly when generating BC6H compressed images.

<strong>Update:</strong> It is recommended you make use of the <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a> version of ``texconv`` instead of either version using the legacy D3DX library.

<p><a href="https://walbourn.github.io/download/texconvex.zip">texconvex.zip</a>
