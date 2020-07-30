---
layout: post
title: DirectX Caps Viewer Update
date: 2020-07-29 20:05
author: Chuck Walbourn
comments: true
categories: [github]
---

The *DirectX Capabilities Viewer* utility dates back to the DirectX 5 era, which was written to help developers review the myriad "caps bits", resolutions, and devices supported by DirectX components. It shipped in the legacy [DirectX SDK](https://docs.microsoft.com/en-us/windows/win32/directx-sdk--august-2009-), and then moved to the Windows 8.0 SDK, Windows 8.1 SDK, and ships in the Windows 10 SDK today.

<!--more-->

# DirectX SDK Version

The 'classic' version of this tool enumerates devices/caps for Direct3D, DirectDraw, DirectSound, DirectInput, DirectPlay, and DirectMusic. Both DirectPlay and DirectMusic were deprecated a while back--the [DirectMusic](https://walbourn.github.io/directx-sdks-of-a-certain-age/) story is actually a bit more complicated than just deprecated--so support for these were removed from the DirectX SDK after August 2008.

![DxCapsViewer DXSDK](https://raw.githubusercontent.com/walbourn/walbourn.github.io/master/images/dxcapsviewerclassic.png)

With the introduction of Direct3D 10, one of the main design points was to greatly simplify the 'sea of caps bits' problem for Direct3D, so the DxCapsViewer tool was considered uninteresting and left as legacy functionality. Direct3D 10 devices all did the same thing, so there was little point.

The Direct3D 10.1 story add a small wrinkle and introduced the notion of [Direct3D hardware feature levels](https://walbourn.github.io/direct3d-feature-levels/). There was ``D3D10_FEATURE_LEVEL_10_0`` which was defined to be exactly what Direct3D 10.0 supported, and ``D3D10_FEATURE_LEVEL_10_1`` was a strict superset with a few more features that worked on Direct3D 10.1 cards.

Then along came Direct3D 11 which not only introduced ``D3D_FEATURE_LEVEL_11_0``, but also a few optional features like double-precision shaders. There was some optional support for DirectCompute 4.x on feature level 10.x hardware. It also came with new '10level9' feature levels for Shader Model 2.0/3.0 era hardware. There was also the evolving story of [WARP](https://docs.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp). With each hardware feature level, there were various rules about which formats were required and which were optional.

While this did not bring back the 'sea of caps bits' that was Direct3D 9 and prior, I was finding it a bit of a struggle to fully understand and document all this, and explain it succinctly in a talk I was working on in 2009. It was then I found myself picking this old, dusty, long-forgotten tool up and I added the "DXGI" device node.

# Windows 8.x SDK Version

The DirectX SDK (June 2010) release turned out to be the end-of-life release for the venerable product, and I was tasked with going through the inventory of what was there and finding new homes for them where applicable. One of the things I moved over to the Windows SDK was the DxCapsViewer tool. At the time the only real change was to remove the DirectInput and DirectSound functionality. I also added a few tweaks for Direct3D 11.1, ``D3D_FEATURE_LEVEL_11_1``, and Direct3D 11.2.

# Windows 10 SDK Version

Since then, I've sporadically updated the tool, initially for Direct3D 12 then Direct3D 12.1, DirectX 11.4, and DXGI 1.5.

![DxCapsViewer DXSDK](https://raw.githubusercontent.com/walbourn/walbourn.github.io/master/images/dxcapsviewermodern.png)

Over the past few releases of Windows 10, the tool had again aged a bit so I recently updated the tool for numerous optional Direct3D 12 features such as Pipeline libraries, Variable Rate Shading, DirectX Raytracing, and Amplification/Mesh Shaders.

The latest source for this tool is now available on [GitHub](https://github.com/microsoft/DxCapsViewer). The latest functionality can be seen in the [Windows 10 SDK Insider Preview](https://www.microsoft.com/en-us/software-download/windowsinsiderpreviewSDK) or, of course, you can build it yourself from source.
