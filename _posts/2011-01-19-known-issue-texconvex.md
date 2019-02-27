---
layout: post
title: Known Issue: TexconvEx
date: 2011-01-19 14:58
author: walbourn
comments: true
categories: [dds, dxsdk, Uncategorized]
---
<p>Doing some work on the <a title="Texture Conversion Tool Extended (MSDN)" href="http://msdn.microsoft.com/en-us/library/ee422506.aspx"><strong>texconvex</strong> </a>tool (the Direct3D 10.x/11 version of the Texture Conversion Tool), I discovered that my use of the NULL render device resulted in garbage output from this tool in some scenarios. This is easily remedied using the WARP or REFERENCE device.</p>
<p>Since this is just a simple shell around D3DX functionality, the source code is fairly trivial. Here is the source to the current tool as shipped in the DirectX SDK (June 2010) with the above fix, as well as support for the <a title="Bill Crow's Digital Imaging &amp; Photography Blog" href="http://blogs.msdn.com/b/billcrow/archive/2006/11/17/introducing-hd-photo.aspx">Windows Media Photo / HD Photo</a> format (i.e. D3DX11_IFF_WMP). As the primary high-dynamic range image format supported by D3DX, it is an important format to support particularly when generating BC6H compressed images.</p>
<p><strong>Update:</strong> It is recommended you make use of the <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a> version of texconv instead of this version using the legacy D3DX library.</p>
<p>&nbsp;</p>
<p><a href="https://msdnshared.blob.core.windows.net/media/MSDNBlogsFS/prod.evol.blogs.msdn.com/CommunityServer.Components.PostAttachments/00/10/11/78/94/texconvex.zip" original-url="http://blogs.msdn.com/cfs-file.ashx/__key/communityserver-components-postattachments/00-10-11-78-94/texconvex.zip">texconvex.zip</a></p>
