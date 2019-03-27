---
layout: msdnpost
title: DirectXMesh
date: 2014-06-27 11:17
author: Chuck Walbourn
comments: true
categories: [codeplex, github]
---
A number of my projects over the past few years have been to provide modern replacements for the full range of functionality provided in the now legacy D3DX library: <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a> in the Windows 8.x SDK, <a href="https://walbourn.github.io/directxtk/">DirectX Tool Kit</a> and the <a href="https://walbourn.github.io/directxtex/">DirectXTex</a> texture processing libraries on CodePlex. To round out that set, I've created <strong>DirectXMesh</strong> for geometry processing functionality such as computing triangle adjacency, computing normals and tangent frames, and vertex cache optimization.
<!--more-->

DirectXMesh is hosted on <a href="http://go.microsoft.com/fwlink/?LinkID=324981">CodePlex</a> and <a href="https://github.com/Microsoft/DirectXMesh">GitHub</a>. The latest version of the library, documentation, notes on future work, release history, and other information is available there.

<strong>Platforms: </strong>The code is designed to build with the Windows 8.x SDK using Visual Studio 2010, 2012, or 2013 and works on Windows Vista, Windows 7, Windows 8.x Win32 desktop, Windows Store apps, and Xbox One.

<strong>Update:</strong> Meshconvert, a sample using DirectXMesh that is a command-line tool replacement for the DirectX SDK sdkmesh conversion utility, is now available on <a href="https://github.com/Microsoft/DirectXMesh/wiki/meshconvert">GitHub</a>.

<h1>Porting Notes</h1>

Here's a handy table of equivalents for D3DX (see <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a> for a complete listing):

<table border="1">
<tbody>
<tr>
<td><code>D3DXCleanMesh</code></td>
<td><code>Clean</code></td>
</tr>
<tr>
<td><code>D3DXComputeNormals</code></td>
<td><code>ComputeNormals</code></td>
</tr>
<tr>
<td><code>D3DXComputeTangent
D3DXComputeTangentFrame
D3DXComputeTangentFrameEx</code></td>
<td><code>ComputeTangentFrame</code></td>
</tr>
<tr>
<td><code>ID3DX10Mesh::GenerateAdjacencyAndPointReps</code></td>
<td><code>GenerateAdjacencyAndPointReps</code></td>
</tr>
<tr>
<td><code>ID3DX10Mesh::GenerateGSAdjacency</code></td>
<td><code>GenerateGSAdjacency</code></td>
</tr>
<tr>
<td><code>ID3DX10Mesh::Optimize</code></td>
<td><code>AttributeSort
OptimizeFacesEx
OptimizeVertices
ReorderIB
FinalizeIB
FinalizeVB</code></td>
</tr>
<tr>
<td><code>D3DXOptimizeFaces</code></td>
<td><code>OptimizeFaces</code></td>
</tr>
<tr>
<td><code>D3DXOptimizeVertices</code></td>
<td><code>OptimizeVertices</code></td>
</tr>
<tr>
<td><code>D3DXValidMesh</code></td>
<td><code>Validate</code></td>
</tr>
<tr>
<td><code>D3DXWeldVertices</code></td>
<td><code>WeldVertices
CompactVB</code></td>
</tr>
</tbody>
</table>
