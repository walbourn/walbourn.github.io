---
layout: post
title: Direct3D Game Visual Studio templates (VCPKG edition)
date: 2025-07-23 17:01
author: Chuck Walbourn
comments: true
categories: [direct3d, visualc, vcpkg]
---

Over the past few years, I've been working more with the [vcpkg Package Manager](https://vcpkg.io/), including support for all my GitHub projects, development of [xbox community triplets](https://walbourn.github.io/vcpkg-now-supports-targeting-xbox/), and adopting VCPKG for a number of game develompent workflows. In doing so, I've found the "vcpkg manifest mode" feature greatly simplifies integration for projects. I have therefore released a number of new Visual Studio Project templates.

<!--more-->

The [directx-vs-templates](https://github.com/walbourn/directx-vs-templates) project hosts most of my templates with two new templates in the latest release: **d3d11game_vcpkg** and **d3d12game_vcpkg**. The [VSIX](https://github.com/walbourn/directx-vs-templates/raw/main/VSIX/Direct3DUWPGame.vsix) package there lets you create MSBuild projects, and there are PowerShell scripts and files available for generating CMake versions. For more information, see [the wiki](https://github.com/walbourn/directx-vs-templates/wiki).

In addition, there is now an official *Microsoft GDK* template that uses vcpkg available on [Visual Studio Marketplace](https://aka.ms/gdktemplates). This includes both a MSBuild and a CMake version using the [ms-gdk](https://github.com/microsoft/vcpkg/tree/master/ports/ms-gdk) vcpkg port so you don't need to install the *Microsoft GDK* to build against it. The `README.md` includes a quick tutorial on adding the *directxtk12* port to the project and some basic drawing with *Directx Tool Kit for DX12*.

> I'm working on some new samples to demonstrate building a single project with both the public *Microsoft GDK* and the NDA *Microsoft GDK with Xbox Extensions* using VCPKG for various dependancies. I'll update this blog post with links when they are available later this summer.

See [Direct3D Win32 Game Visual Studio template](https://walbourn.github.io/direct3d-win32-game-visual-studio-template/) and [Direct3D Game Visual Studio templates (Redux)](https://walbourn.github.io/direct3d-game-visual-studio-templates-redux/)
