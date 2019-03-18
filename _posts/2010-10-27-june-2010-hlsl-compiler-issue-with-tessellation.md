---
layout: post
title: June 2010 HLSL Compiler Issue with Tessellation
date: 2010-10-27 11:16
author: Chuck Walbourn
comments: true
categories: [direct3d, directx, hlsl]
---
One of our areas of focus for the DirectX SDK (June 2010) release was to make sure our samples supported Direct3D 11 <a href="https://walbourn.github.io/directx-11-hardware-vendor-differences/" title="DirectX 11 Hardware Vendor Differences">hardware from NVIDIA</a>, as we had previously only had AMD/ATI Direct3D 11 hardware to work with. There were a few issues that arose right around the release with the <em>SubD11</em> and <em>PNTriangles</em>11<em> </em>samples. At the time we thought it was related to the driver, but in fact it turned out to be due to tessellation shader related optimization issues in the June 2010 version of the HLSL complier.
<!--more-->

A work-around is available and is described in the Microsoft Knowledge Base article #<a href="https://support.microsoft.com/en-us/help/2448404/visual-artifacts-may-occur-when-running-some-tessellation-shaders-comp" title="2448404">2448404</a>.

```cpp
//---------------------------------------------------------------------------
// File: SubD11.hlsl
//
// This file contains functions to convert from a Catmull-Clark subdivision
// representation to a bicubic patch representation.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------

//Work-around for an optimization rule problem in the June 2010 HLSL Compiler
// (9.29.952.3111)
// see http://support.microsoft.com/kb/2448404
#if D3DX_VERSION == 0xa2b
#pragma ruledisable 0x0802405f
#endif
```

```cpp
//---------------------------------------------------------------------------
// File: PNTriangles11.hlsl
//
// These shaders implement the PN-Triangles tessellation technique
//
// Contributed by the AMD Developer Relations Team
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//---------------------------------------------------------------------------

#include "AdaptiveTessellation.hlsl"

//Work-around for an optimization rule problem in the June 2010 HLSL Compiler
// (9.29.952.3111)
// see http://support.microsoft.com/kb/2448404
#if D3DX_VERSION == 0xa2b
#pragma ruledisable 0x0802405f
#endif
```

<a href="https://walbourn.github.io/download/HLSLWithWorkaround.zip">HLSLWithWorkaround.zip</a>
