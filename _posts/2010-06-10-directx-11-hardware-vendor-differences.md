---
layout: post
title: DirectX 11 Hardware Vendor Differences
date: 2010-06-10 13:03
author: walbourn
comments: true
categories: [direct3d]
---
With the June 2010 DirectX SDK, one of our work items was to try out the various DirectX 11 samples against the NVIDIA DirectX 11 graphics parts (NVIDIA GeForce GTX <a href="http://www.nvidia.com/object/product_geforce_gtx_470_us.html" title="470">470</a>/<a href="http://www.nvidia.com/object/product_geforce_gtx_480_us.html" title="480">480</a>) now that they are available. For the August 2009 and February 2010 releases, we only had the AMD/ATI DirectX 11 graphics cards available (ATI Radeon HD <a href="http://www.amd.com/us/products/desktop/graphics/ati-radeon-hd-5000/Pages/ati-radeon-hd-5000.aspx" title="5000">5000 </a>Series). Video cards have traditionally competed on a mix of features, performance, and price. These days they are increasingly also competing on power consumption--while this has always been true in the mobile & laptop space, it is becoming increasingly important even in desktops.
<!--more-->

There has been a lot of focus in Direct3D 10, 10.1, and 11 to try to minimize the 'feature fragmentation' problem in the Direct3D API (best demonstrated by the "sea of caps" in the Direct3D 9 Card Capabilities spreadsheet we ship in the DirectX SDK) to help simplify the programmer's job of efficiently use these APIs. This effort really started with Direct3D 9 Shader Model 3.0 trying to tighten down the specificiation a bit more. This is also a lot of what the [Feature Level](https://docs.microsoft.com/en-us/windows/desktop/direct3d11/overviews-direct3d-11-devices-downlevel-intro) concept introduced in Direct3D 10.1 and the '10level9' feature levels of DirectX 11 is trying to address in a more manageable way. Performance differences can still vary a great deal between vendors and will vary a lot even between the same vendor's cards at different price-points, but we hope it at least helps constrain the degrees of freedom the programmer has to concern themselves with.

Our work with the NVIDIA hardware for this release has provided insight into some areas that programmers need to pay attention to with respect to different vendor's cards. The biggest difference I noticed was that number of MSAA quality levels exposed by AMD vs. NVIDIA. This information is obtained via the [CheckMultisampleQualityLevels](https://docs.microsoft.com/en-us/windows/desktop/api/d3d11/nf-d3d11-id3d11device-checkmultisamplequalitylevels) method in Direct3D 10.x and 11. The <em>ATI Radeon HD 5000 </em>Series only provides one quality level per sample count, while the <em>NVIDIA GeForce GTX 400 </em>Series exposes a number of fine-grain quality levels per sample count. This highlighted a few UI bugs in some of the samples as well as DXUT/DXUT11 that were corrected in the June 2010 release--the UI bugs had been there for some time, but nobody had really noticed. <strong>Be sure to test the behavior of any MSAA settings and quality levels in your DX10.x and DX11 programs on both vendor's hardware. </strong>Another area to pay close attention to is DirectCompute synchronization and timing behavior. <strong>DirectCompute as a low-level exposure of the GPU behavior is more subject to architectural differences, so  be sure to test any use of DirectCompute on hardware from multiple vendors.</strong>

One other difference of note is only some (typically higher-end) cards support the driver optional feature <strong>Double Precision Shaders.</strong> The <em>NVIDIA GeForce 470/480, ATI Radeon HD 5830/5850/5870, </em>and <em>ATI Radeon HD 5970 </em>report support this feature. This feature only applies to Shader Model 5.0 shader programs written to convert data to and from double-precision, and then to perform computations in double-precision, but it can be a useful feature for advanced DirectCompute 5.0 programs. Support for this feature is detected via the [CheckFeatureSupport](https://docs.microsoft.com/en-us/windows/desktop/api/d3d11/nf-d3d11-id3d11device-checkfeaturesupport) method in Direct3D 11 using <code>D3D11_FEATURE_DOUBLES</code>. Note that the REFERENCE software device also supports Double Precision Shaders. You can play around with double precision shaders using the [BasicCompute11](https://github.com/walbourn/directx-sdk-samples/tree/master/BasicCompute11) sample in the <em>DirectX SDK (June 2010)</em> release by editing <code>BasicCompute11.cpp</code> and uncommenting the #define in the following line:

```
// If defined, then the hardware/driver must report support for
// double-precision CS 5.0 shaders or the sample fails to run
//#define TEST_DOUBLE
```

This will also cause the HLSL shader program to be compiled with the same define.
