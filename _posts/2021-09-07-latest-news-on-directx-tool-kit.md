---
layout: post
title: Latest news on DirectX Tool Kit
date: 2021-09-07 11:00
author: Chuck Walbourn
comments: true
categories: [direct3d, github, xbox]
---

Last year, in the early days of quarantine, I updated *DirectX Tool Kit for Audio* with streaming support per [this blog post](https://walbourn.github.io/directx-tool-kit-for-audio-updates-and-a-direct3d-9-footnote/), and in the winter holidays I added [CMake and vcpkg support](https://walbourn.github.io/directxtex-directxmesh-and-uvatlas-now-support-linux/) to all my GitHub projects. Over this past summer we took a long-overdue family trip, but I also had some time to work on my *Issues* backlog for *DirectX Tool Kit* [DX11](https://github.com/microsoft/DirectXTK) / [DX12](https://github.com/microsoft/DirectXTK12).

<!--more-->

Since my last major [post](https://walbourn.github.io/directx-tool-kit-for-directx-12/) on the state of *DirectX Tool Kit*, I've added:

* <b>BufferHelpers</b> provides functions for creating static vertex buffers/index buffers, plus for *DirectX 11* includes the *ConstantBuffer* helper moved to the public header space.
* <b>Effects</b> now includes *NormalMapEffect*, *PBREffect*, and *DebugEffect*. These are all Shadel Model 4+ shader effects, and now support GPU hardware instancing. The normal-map implementation includes ``BC5_UNORM`` handling, and all effects support optional '2x biased normals' for compressed vertex normal DXGI formats.
* <b>GeometricPrimitive</b> and <b>Model</b> have ``DrawInstanced`` methods to support GPU hardware instancing usage.
* <b>PostProcess</b> ``ToneMapPostProcess`` now has a color-rotation matrix property for HDR10 output signal prep. using alternative color-spaces like DCI-P3-D65.
* <b>WICTextureLoader</b> supports additional loader flags ``FORCE_RGBA32``, ``FIT_POW2``, and ``MAKE_SQUARE``.
* Publicly available [Microsoft GDK](https://github.com/microsoft/GDK) support for the ``Gaming.*.x64`` platforms.
* Windows ARM64 platform support.
* Introduction of [SDKMESH](https://github.com/microsoft/DirectXMesh/wiki/Geometry-formats#sdkmesh) v2 format and *PBREffectFactory*.

The focus the past few weeks has been in catching up on the documentation backlog.

* Both the [DirectX 11](https://github.com/microsoft/DirectXTK/wiki/Getting-Started) and [DirectX 12](https://github.com/microsoft/DirectXTK12/wiki/Getting-Started) tutorials have been refreshed to focus on the *DeviceResources* variant of my [templates](https://walbourn.github.io/direct3d-game-visual-studio-templates-redux/).
* The tutorials now cover *Multistream rendering and instancing*, *Authoring an Effect*, and *Physically-based rendering*. I also added a DirectX 12 version of *Writing custom shaders* on using custom shaders with ``SpriteBatch``.
* Post-processing content in the *wiki* [DX11](https://github.com/microsoft/DirectXTK/wiki) / [DX12](https://github.com/microsoft/DirectXTK12/wiki) now includes examples.
* The *utilities* [DX11](https://github.com/microsoft/DirectXTK/wiki/Utilities) / [DX12](https://github.com/microsoft/DirectXTK12/wiki/Utilities) page now includes a *MSAAHelper* and *SkyboxEffect* as well as a *Compressing assets* topic.

# Work in progress

I'm finally making progress on a [ModelBone](https://github.com/microsoft/DirectXTK/issues/280) implementation for both ``SDKMESH`` and ``CMO``, with the associated Draw methods for hierarchical bone drawing and skinned models. I'm also adding [CMO model loading](https://github.com/microsoft/DirectXTK12/pull/105) support to the *DirectX Tool Kit for DX12*, although I have no plans to support the DGSL effect system for DirectX 12 since it is strongly tied to HLSL Shader Model 4.

**Update**: This functionality has shipped in the September 2021 releases.

Much like *XNA Game Studio*, I don't have a specific animation system implementation, but I do have some example code for both SDKMESH and CMO animations. I'm currently working on tutorials for rigid-body animation, skinned animation, and skinning support for the normalmap effect.
