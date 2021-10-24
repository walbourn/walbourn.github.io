---
layout: post
title: DirectX Tool Kit Vertex Skinning Update
date: 2021-10-23 21:51
author: Chuck Walbourn
comments: true
categories: [github]
---

Back when I first implemented the **Model** class for *DirectX Tool Kit*, I was focused on having some basic mesh rendering for samples and demos. As such, while I supported creating ``SkinnedEffect`` materials for models with vertex bone information, I didn't have much else there to support implementing vertex skinning animation, or even rigid-body animation. I have been meaning to get back finishing that work for 5+ years.

October is *Hackathon* time for Microsoft, so I went back and dusted off a bunch of prototype work over the years and finally got it implemented.
<!--more-->

The current releases of *DirectX Tool Kit* for [DX11](https://github.com/microsoft/DirectXTK/releases) / [DX12](https://github.com/microsoft/DirectXTK12/releases) now include:

* ``ModelBone`` loading from ``CMO`` and ``SDKMESH`` geometry formats

* Rigid-body animation (supported by ``SDKMESH``)

* Vertex-skinned animation (supported by ``CMO`` and ``SDKMESH``)

* In addition to the original ``SkinnedEffect`` (i.e. XNA Game Studio 4 ``BasicEffect`` with vertex skinning), there is now ``SkinnedNormalMapEffect`` and ``SkinnedPBREffect``.

* For the DirectX 11 version of *DirectX Tool Kit*, the skinning support in ``DGSLEffect`` was moved to a ``SkinnedDGSLEffect``.

Tutorials are available for [DirectX 11](https://github.com/microsoft/DirectXTK/wiki/Animating-using-model-bones) and [DirectX 12](https://github.com/microsoft/DirectXTK12/wiki/Animating-using-model-bones) on the GitHub wikis.

As with *XNA Game Studio*, the tool kit doesn't include a specific animation system but I've got sample ones available as utility code for both **CMO** and **SDKMESH** animation data.

<strong>Related:</strong> <a href="https://walbourn.github.io/latest-news-on-directx-tool-kit/">September 2021</a>
