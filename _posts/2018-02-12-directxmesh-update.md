---
layout: post
title: DirectXMesh Update
date: 2018-02-12 10:48
author: walbourn
comments: true
categories: [github]
---
The February 2018 release of DirectXMesh is available on <a href="https://github.com/Microsoft/DirectXMesh/releases">GitHub</a>. I wanted to call attention to this release in particular because I discovered an important and long-standing bug in the library that is now fixed.
<!--more-->

First, the good news: I have implemented a vertex welding algorithm similar to the legacy function <code>D3DXWeldVertices</code>, and I've added support for Tom Forsyth's <a href="https://tomforsyth1000.github.io/papers/fast_vert_cache_opt.html"><em>Linear-speed Vertex Cache Optimisation </em></a>algorithm as an alternative to the Hugh Hoppe <a href="http://hhoppe.com/proj/tvc/"><em>Transparent Vertex Cache</em><em> Optimization</em></a> algorithm that was originally ported from the <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">deprecated D3DX9 library</a>. The <code>meshconvert</code> tool was updated with a new <code>-oplru</code> switch to use the Forsyth algorithm, and the <a href="https://github.com/walbourn/contentexporter/releases">DirectX SDK Samples Content Exporter</a> now supports an <code>-optimization</code> switch to control the algorithm selection as well (see the <a href="https://github.com/walbourn/contentexporter/wiki/Options">wiki</a> for details).

To support vertex welding (which results in a number of 'unused' vertices), I also added a new helper function <code>CompactVB</code>. In the course of that work I realized that <code>FinalizeVB</code>, <code>FinalizeVB</code>, and <code>FinalizeVBAndPointReps</code> were all applying the vertex remap <em>backwards</em>. The original D3DX9 codebase used both kinds of vertex maps: <code>oldLoc = vertexRemap[newLoc]</code> and <code>newLoc = vertexRemap[oldLoc]</code>. The D3DX9 library and DirectXMesh are intended to expose only the first version maps to the client code (which is the most useful for copying around related attributes), but internally there are a number of places you need to use the inverse. It turns out I was returning the correct vertex remaps from <code>OptimizeVertices</code>, but then applied them incorrectly with my remap functions--but they were consistent so it still rendered correctly. Unfortunately this means it was always making the vertex buffer less efficient. Ooops. My bad. I've improved my <a href="https://github.com/walbourn/directxmeshtest">test suite</a> and the <a href="https://github.com/Microsoft/DirectXMesh/wiki">documentation</a> here as well as fixing the remap functions.

<strong>Wavefront OBJ: </strong>In the December 2017 release I fixed the <code>WaveFrontReader.h</code> helper to support 'relative' indices which were missing from the original sample implementation I used to create the header, and in February 2018 I made a few more robustness improvements. The February 2018 versions of <a href="https://github.com/Microsoft/DirectXMesh/wiki/Meshconvert">meshconvert</a> and the <a href="https://github.com/Microsoft/UVAtlas/wiki/UVAtlasTool">uvatlas tool</a> now use this improved version.

<strong>NuGet:</strong> The DirectXMesh library is now available on NuGet as well. I provide a <a href="https://www.nuget.org/packages/directxmesh_desktop_2015/">Win32 desktop package</a> suitable for use with VS 2015 Update 3 or VS 2017, as well as a <a href="https://www.nuget.org/packages/directxmesh_uwp/">UWP version</a>.

<strong>Related:</strong> <a href="https://walbourn.github.io/directxmesh/">DirectXMesh</a>, <a href="https://walbourn.github.io/directxtex-and-directxmesh-now-support-direct3d-12/">DirectXTex and DirectXMesh now support Direct3D 12</a>
