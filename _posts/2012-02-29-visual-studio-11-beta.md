---
layout: msdnpost
title: Visual Studio 11 Beta
date: 2012-02-29 11:56
author: Chuck Walbourn
comments: true
categories: [visualc]
---
The <a href="http://www.microsoft.com/visualstudio/11/en-us/downloads">Visual Studio 11 Beta</a> release is now live. For an overview of the new product, take a moment to read this <a href="">Visual Studio blog</a> entry as well as an entry on the <a href="https://devblogs.microsoft.com/cppblog/whats-new-in-visual-studio-11-beta-for-c-developers/">Visual C++ blog</a>. This Beta release includes the full range of SKUs including <a href="http://www.microsoft.com/download/en/details.aspx?id=28974">Express</a>, <a href="http://www.microsoft.com/download/en/details.aspx?id=28992">Professional</a>, <a href="http://www.microsoft.com/download/en/details.aspx?id=28985">Premium</a>, and <a href="http://www.microsoft.com/download/en/details.aspx?id=28975">Ultimate</a>. As with the <a href="https://walbourn.github.io/visual-studio-11-developer-preview/">Developer Preview</a>, this release includes a new C++ compiler and Standard Library with additional <a href="https://devblogs.microsoft.com/cppblog/c11-features-in-visual-c-11/">C++11</a> support, an integrated <em>PIX for Windows</em> replacement called <a href="https://devblogs.microsoft.com/cppblog/game-debugging-in-visual-studio-11/"><em>Visual Studio Graphics Diagnostics</em> </a>including HLSL debugging, the latest HLSL compiler, and a DDS image viewer (both legacy and 'DX10' extension variants).
<!--more-->

The VS 11 Beta includes a Beta version of the next <a href="https://developer.microsoft.com/en-us/windows/downloads/sdk-archive">Windows SDK</a> integrated into the release. This new SDK has a number of DirectX SDK components built in, including the Developer Runtime components (REF, D3D10 SDK Layers, D3D11 SDK Layers) for Windows 7 and Windows 8 Consumer Preview. Building the DirectX SDK samples using the new Windows SDK requires some build settings changes. See "<a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK</a>" for further details.

> If you are looking to move applications written using the Developer Preview release to the new Beta, you should keep a link to this <a href="http://go.microsoft.com/fwlink/?LinkID=242888">migration guide</a> handy.

<strong>Update:</strong> See this <a href="http://blogs.amd.com/developer/2012/03/01/amd-and-the-visual-studio-11-beta/">AMD</a> post for some details about new intrinsics support in the VS 11 Beta. There is also support for Intel's <a href="http://software.intel.com/en-us/blogs/2011/06/13/haswell-new-instruction-descriptions-now-available/">FMA3 and AVX2</a> instruction intrinsics. FMA4 and AVX intrinsics were aready added in <a href="https://devblogs.microsoft.com/cppblog/visual-studio-2010-service-pack-1-general-availability/">Visual Studio 2010 SP1</a>.

And this post on how to <a href="https://devblogs.microsoft.com/cppblog/target-windows-xp-in-visual-studio-11-beta-using-the-visual-studio-2010-compiler-and-libraries/">mix Visual Studio 11 with the VS 2010 toolsets</a> to build for Windows XP.
