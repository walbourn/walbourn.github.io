---
layout: post
title: UVAtlas: Return of the Isochart
date: 2014-11-14 02:00
author: walbourn
comments: true
categories: [Uncategorized]
---
<p>Thanks to help from the original Microsoft developer, Xin Huang, the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb206321.aspx">UVAtlas isochart technology</a> that previously was only available in the deprecated D3DX9 library is now available on <a href="http://go.microsoft.com/fwlink/?LinkID=512686">CodePlex</a>. It is standalone and builds with the usual assortment of platform tools: Visual Studio 2013, Visual Studio 2012, Visual Studio 2010 with the Windows 8.1 SDK. It has no dependencies on the legacy DirectX SDK, D3DX, or DirectSetup. While not required, you will find <a href="http://blogs.msdn.com/b/chuckw/archive/2014/06/27/directxmesh.aspx">DirectXMesh</a> useful for generating the triangle adjacencies required for the isochart creation, and <a href="http://blogs.msdn.com/b/chuckw/archive/2011/10/28/directxtex.aspx">DirectXTex</a> useful for loading/converting image data when generating IMTs from textures.</p>
<p>The CodePlex package includes a new version of the <em>UVAtlas command-line tool sample</em> which also requires the latest DirectXMesh and DirectXTex packages to build--this sample is based on the <em>meshconvert </em>command-line tool sample for DirectXMesh.</p>
<h1>Porting Notes</h1>
<p>Here's a handy table of equivalents for D3DX (see <a href="http://blogs.msdn.com/b/chuckw/archive/2013/08/21/living-without-d3dx.aspx">Living without D3DX</a> for a complete listing):</p>
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
<p>&nbsp;</p>
<p><strong>Update: </strong>In related news, I&rsquo;ve also posted an update of <a href="http://go.microsoft.com/fwlink/?LinkID=324981">DirectXMesh</a> with a sample tool <em>meshconvert</em>.</p>
<p>In addition to <a href="https://uvatlas.codeplex.com/">CodePlex</a>, this project is also hosted on <a href="https://github.com/Microsoft/UVAtlas">GitHub</a>.</p>
