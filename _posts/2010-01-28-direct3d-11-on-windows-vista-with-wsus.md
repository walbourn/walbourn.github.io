---
layout: post
title: Direct3D 11 on Windows Vista with WSUS
date: 2010-01-28 18:59
author: Chuck Walbourn
comments: true
categories: [direct3d]
---
<p>The DirectX SDK (August 2009) release was our "RTM" release for DirectX 11 and includes the final versions of headers, link libraries, deployment details, and samples for shipping DirectX 11 applications. The [Direct3D 11 Deployment for Game Developers](https://docs.microsoft.com/en-us/windows/desktop/direct3darticles/direct3d11-deployment) article details most everything you need to know to handle the DirectX 11 dependency for your application. Windows 7 and Windows Server 2008 R2 already include the runtime, although if you make use of HLSL at runtime or D3DX, you'll still need to use DirectSetup to deploy those components as they are not included in the OS--be sure to see [DirectX Installation for Game Developers](https://docs.microsoft.com/en-us/windows/desktop/DxTechArts/directx-setup-for-game-developers). DirectX 11 is available on Windows Vista and Windows Server 2008 through [KB 971644](http://go.microsoft.com/fwlink/?LinkId=160189) as explained in detail in the article.</p>
<!--more-->

<p>This pretty much buttoned up the consumer experience, but there was one small catch. Many developers at large publishers are actually working within locally managed Windows Server Update Service (WSUS) environments. For these developers, KB 971644 is not available. Instead, corporate network users need to refer to [KB 971512](http://support.microsoft.com/kb/971512/). This is covered in the DirectX SDK (February 2010) version of the deployment article.</p>
