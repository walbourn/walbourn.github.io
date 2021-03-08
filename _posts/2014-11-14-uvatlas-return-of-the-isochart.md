---
layout: msdnpost
title: UVAtlas - Return of the Isochart
date: 2014-11-14 02:00
author: Chuck Walbourn
comments: true
categories: [codeplex, github]
---
Thanks to help from the original Microsoft developer, Xin Huang, the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d9/using-uvatlas">UVAtlas isochart technology</a> that previously was only available in the deprecated D3DX9 library is now available on <strike><a href="http://go.microsoft.com/fwlink/?LinkID=512686">CodePlex</a></strike><a href="https://github.com/Microsoft/UVAtlas">GitHub</a>. It is standalone and builds with the usual assortment of platform tools: Visual Studio 2013, Visual Studio 2012, Visual Studio 2010 with the Windows 8.1 SDK. It has no dependencies on the legacy DirectX SDK, D3DX, or DirectSetup. While not required, you will find <a href="https://walbourn.github.io/directxmesh/">DirectXMesh</a> useful for generating the triangle adjacencies required for the isochart creation, and <a href="https://walbourn.github.io/directxtex/">DirectXTex</a> useful for loading/converting image data when generating IMTs from textures.
<!--more-->

The package includes a new version of the <em>UVAtlas command-line tool sample</em> which also requires the latest DirectXMesh and DirectXTex packages to build--this sample is based on the <em>meshconvert </em>command-line tool sample for DirectXMesh.

<h1>Porting Notes</h1>

Here's a handy table of equivalents for D3DX (see <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a> for a complete listing):

<table border="1">
<tbody>
<tr>
<td><code>D3DXUVAtlasCreate</code></td>
<td><code>UVAtlasCreate</code></td>
</tr>
<tr>
<td><code>D3DXUVAtlasPartition</code></td>
<td><code>UVAtlasPartition</code></td>
</tr>
<tr>
<td><code>D3DXUVAtlasPack</code></td>
<td><code>UVAtlasPack</code></td>
</tr>
<tr>
<td><code>D3DXComputeIMTFromPerVertexSignal</code></td>
<td><code>UVAtlasComputeIMTFromPerVertexSignal</code></td>
</tr>
<tr>
<td><code>D3DXComputeIMTFromPerTexelSignal</code></td>
<td><code>UVAtlasComputeIMTFromPerTexelSignal</code></td>
</tr>
<tr>
<td><code>D3DXComputeIMTFromSignal </code></td>
<td><code>UVAtlasComputeIMTFromSignal</code></td>
</tr>
<tr>
<td><code>D3DXComputeIMTFromTexture </code></td>
<td><code>UVAtlasComputeIMTFromTexture</code></td>
</tr>
</tbody>
</table>

<strong>Update: </strong>In related news, I've also posted an update of <a href="http://go.microsoft.com/fwlink/?LinkID=324981">DirectXMesh</a> with a sample tool <em>meshconvert</em>.

<strong>vcpkg</strong>: The vcpkg C++ Package Manager has a [uvatlas](https://github.com/microsoft/vcpkg/tree/master/ports/uvatlas) port available.
