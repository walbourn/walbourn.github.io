---
layout: post
title: Living without D3DX
date: 2013-08-20 17:49
author: walbourn
comments: true
categories: [direct3d, dxsdk, Uncategorized]
---
Over the past few years, I've been working on a number of projects in part motivated by the need to replace legacy D3DX functionality. As noted on <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee663275.aspx">MSDN</a>, all versions of D3DX are deprecated and are not shipped with the Windows 8.x SDK. This includes D3DX9, D3DX10, and D3DX11. There are plenty of options for moving existing code over to newer, more supportable solutions most of which are now shared-source.

I've built a number of porting notes tables for each of these topics, and then realized today I don't have a single place to see it all. So here it is, the "D3DX porting mega-table" for Direct3D 11.

<strong>Direct3D 9:</strong> There are not many good replacements for the functionality in D3DX9 if you are still using Direct3D 9. You can make use of D3DCompile APIs directly with the legacy DirectX SDK, but newer versions of the D3DCompile DLL in the Windows 8.x SDK are not compatible with Windows XP for runtime use. You can use DirectXMath/XNAMath for Direct3D 9 instead of D3DXMath. The <a href="http://blogs.msdn.com/b/chuckw/archive/2010/07/15/ddswithoutd3dx-sample-update.aspx">DDSWithoutD3DX</a> sample supports Direct3D 9, and you can use <a href="http://blogs.msdn.com/b/chuckw/archive/2011/10/28/directxtex.aspx">DirectXTex</a> and <a href="http://blogs.msdn.com/b/chuckw/archive/2014/06/27/directxmesh.aspx">DirectXMesh</a> when preparing content for use by Direct3D 9.

<strong>Direct3D 10:</strong> The best option for Direct3D 10.x applications is to update them to use Direct3D 11, and then utilize all the options here to replace legacy D3XD10. Porting the API is very <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff476190.aspx">straightforward</a>, and Direct3D 11 is <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee416644.aspx">available</a> on all supported platforms that have Direct3D 10.

<strong>Direct3D 12: </strong>There is a header that ships in the DirectX 12 samples on <a href="https://github.com/Microsoft/DirectX-Graphics-Samples/tree/master/Libraries/D3DX12">GitHub</a> called <code>d3dx12.h</code>. It is all inline utility header which has no DLL or redistributable dependency, and can be used under the MIT license. It is not included in the Windows SDK. If you are looking for additional functionality, see the <a href="https://blogs.msdn.microsoft.com/chuckw/2016/07/18/directx-tool-kit-for-directx-12/">DirectX Tool Kit for DirectX 12</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2017/02/01/directxtex-and-directxmesh-now-support-direct3d-12/">DirectXTex and DirectXMesh</a>.

<strong>Related:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">Where is the DirectX SDK?</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/07/01/where-is-the-directx-sdk-2013-edition.aspx">Where is the DirectX SDK (2013 Edition)?</a>, <a href="https://blogs.msdn.microsoft.com/chuckw/2015/08/05/where-is-the-directx-sdk-2015-edition/">Where is the DirectX SDK (2015 Edition)?</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/08/22/directx-sdk-s-of-a-certain-age.aspx">DirectX SDKs of a certain age</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/09/14/dxut-for-win32-desktop-update.aspx">DXUT for Win32 Desktop Update</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/09/20/directx-sdk-samples-catalog.aspx">DirectX SDK Samples Catalog</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2014/10/28/directx-sdk-tools-catalog.aspx">DirectX SDK Tools Catalog</a>

<strong>CodePlex: </strong>All CodePlex links below will redirect to the Microsoft organizational section of GitHub as CodePlex has been <a href="https://blogs.msdn.microsoft.com/bharry/2017/03/31/shutting-down-codeplex/">shutdown</a>.
<h1>General Helpers</h1>
The <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/02/directxtk.aspx">DirectX Tool Kit</a> provides a number of helpers that are designed to simplify Direct3D 11 programming in the tradition of the original D3DX library. You can find the library on <a href="http://go.microsoft.com/fwlink/?LinkId=248929">CodePlex</a> and <a href="https://github.com/Microsoft/DirectXTK">GitHub</a>.
<table border="1">
<tbody>
<tr>
<td><code>ID3DX10Sprite</code></td>
<td><code>SpriteBatch</code></td>
</tr>
<tr>
<td><code>ID3DX10Font</code></td>
<td><code>SpriteFont, SpriteBatch</code></td>
</tr>
<tr>
<td><code>ID3DX10Mesh</code></td>
<td><code>Model, ModelMesh, ModelMeshPart</code></td>
</tr>
<tr>
<td><code>D3DXCreateBox
D3DXCreateCylinder
D3DXCreateSphere
D3DXCreateTeapot
D3DXCreateTorus</code></td>
<td><code>GeometricPrimitive</code></td>
</tr>
<tr>
<td><code>D3DX11CreateShaderResourceViewFromFile</code></td>
<td><code>CreateXXXTextureFromFile</code></td>
</tr>
<tr>
<td><code>D3DX11CreateShaderResourceViewFromResource
D3DX11CreateShaderResourceViewFromMemory</code></td>
<td><code>CreateXXXTextureFromMemory</code></td>
</tr>
<tr>
<td><code>D3DX11CreateTextureFromFile</code></td>
<td><code>CreateXXXTextureFromFile</code></td>
</tr>
<tr>
<td><code>D3DX11CreateTextureFromResource
D3DX11CreateTextureFromMemory </code></td>
<td><code>CreateXXXTextureFromMemory</code></td>
</tr>
<tr>
<td><code>D3DX11SaveTextureToFile</code></td>
<td><code>SaveXXXTextureToFile</code></td>
</tr>
</tbody>
</table>
&nbsp;

The DXERR library is another helper that shipped in the legacy DirectX SDK. In Windows 8.x or later, you can just use <code>FormatMessage</code> to use the built-in error descriptions which support DirectX. Otherwise, the best replacement is to compile your own version of DXERR.
<table border="1">
<tbody>
<tr>
<td><code>DXGetErrorString
DXGetErrorDescription
DXTrace</code></td>
<td>See <a href="https://blogs.msdn.microsoft.com/chuckw/2012/04/24/wheres-dxerr-lib/">Where’s DXERR.LIB?</a></td>
</tr>
</tbody>
</table>
<h1>HLSL Functions</h1>
The HLSL compiler, shader reflection API, and related functionality has been broken out into it's own <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/07/hlsl-fxc-and-d3dcompile.aspx">D3DCompile</a> DLL for some time. D3DCompile is in the Windows 8.x SDK and is included with VS 2012 and VS 2013 Preview.
<table border="1">
<tbody>
<tr>
<td><code>D3DXCompileShaderFromFile
D3DX10CompileFromFile
D3DX11CompileFromFile</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh446872.aspx">D3DCompileFromFile</a></td>
</tr>
<tr>
<td><code>D3DXCompileShader
D3D10CompileShader
D3DX10CompileFromMemory
D3DX11CompileFromMemory</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/dd607324.aspx">D3DCompile</a></td>
</tr>
<tr>
<td><code>D3DXCompileShaderFromResource
D3DX10CompileFromResource
D3DX11CompileFromResource</code></td>
<td>No direct equivalent. Can use resource APIs and then <code>D3DCompile</code> above.</td>
</tr>
<tr>
<td><code>D3DXPreprocessShader
D3DXPreprocessShaderFromFile
D3DXPreprocessShaderFromResource
D3D10PreprocessShader
D3DX10PreprocessShaderFromFile
D3DX10PreprocessShaderFromMemory
D3DX10PreprocessShaderFromResource
D3DX11PreprocessShaderFromFile
D3DX11PreprocessShaderFromMemory
D3DX11PreprocessShaderFromResource</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/dd607332.aspx">D3DPreprocess</a></td>
</tr>
<tr>
<td><code>D3DXDisassembleShader
D3D10DisassembleShader
D3DX10DisassembleShader</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/dd607326.aspx">D3DDisassemble</a></td>
</tr>
<tr>
<td><code>D3D10ReflectShader
D3DX10ReflectShader</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/dd607334.aspx">D3DReflect</a>
<a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff728670.aspx">D3D11Reflect</a></td>
</tr>
<tr>
<td><code>ID3DXBuffer
ID3D10Blob</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff728743.aspx">ID3DBlob</a></td>
</tr>
<tr>
<td><code>D3DXCreateBuffer
D3D10CreateBlob</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff728672.aspx">D3DCreateBlob</a></td>
</tr>
<tr>
<td><code>D3D10GetInputSignatureBlob
D3D10GetOutputSignatureBlob
D3D10GetInputAndOutputSignatureBlob
D3D10GetShaderDebugInfo</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff728674.aspx">D3DGetBlobPart</a></td>
</tr>
</tbody>
</table>
<h1>Texture Functions</h1>
The <a href="http://blogs.msdn.com/b/chuckw/archive/2011/10/28/directxtex.aspx">DirectXTex</a> library is primarily intended for <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/04/direct3d-11-textures-and-block-compression.aspx">texture processing</a> offline with tools, although it can also be used at runtime for doing texture block compression, mipmap generation, or handling more general image processing needs. <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/02/directxtk.aspx">DirectXTK</a> is intended for use at runtime with light-weight helpers and image loaders, but does not provide support for general runtime texture format conversion. You can find both libraries on <a href="http://go.microsoft.com/fwlink/?LinkId=248926">CodePlex</a> and <a href="https://github.com/Microsoft/DirectXTex">GitHub</a>.
<table border="1">
<tbody>
<tr>
<td><code>D3DX11ComputeNormalMap</code></td>
<td>DirectXTex library, <code> ComputeNormalMap</code></td>
</tr>
<tr>
<td><code>D3DX11CreateShaderResourceViewFromFile
D3DX11CreateTextureFromFile</code></td>
<td>DDSTextureLoader: <code>CreateDDSTextureFromFile</code>
WICTextureLoader: <code>CreateWICTextureFromFile</code>DirectXTex library (tools), <code>LoadFromXXXFile</code> then <code>CreateShaderResourceView</code> or <code>CreateTexture</code></td>
</tr>
<tr>
<td><code>D3DX11CreateShaderResourceViewFromMemory
D3DX11CreateTextureFromMemory</code></td>
<td>DDSTextureLoader: <code>CreateDDSTextureFromMemory</code>
WICTextureLoader: <code>CreateWICTextureFromMemory</code>DirectXTex library (tools), <code>LoadFromXXXMemory</code> then <code>CreateShaderResourceView</code> or <code>CreateTexture</code></td>
</tr>
<tr>
<td><code>D3DX11CreateShaderResourceViewFromResource
D3DX11CreateTextureFromResource</code></td>
<td>No direct equivalent, can use Win32 resource functions and then the ‘from memory’ APIs above.</td>
</tr>
<tr>
<td><code>D3DX11FilterTexture</code></td>
<td>DirectXTex library, <code>GenerateMipMaps</code> and <code>GenerateMipMaps3D</code></td>
</tr>
<tr>
<td><code>D3DX11GetImageInfoFromFile</code></td>
<td>DirectXTex library, <code>GetMetadataFromXXXFile</code></td>
</tr>
<tr>
<td><code>D3DX11GetImageInfoFromMemory</code></td>
<td>DirectXTex library, <code>GetMetadataFromXXXMemory</code></td>
</tr>
<tr>
<td><code>D3DX11GetImageInfoFromResource</code></td>
<td>No direct equivalent, can use Win32 resource functions and then the ‘from memory’ APIs above.</td>
</tr>
<tr>
<td><code>D3DX11LoadTextureFromTexture</code></td>
<td>DirectXTex library, <code>Resize</code>, <code>Convert</code>, <code>Compress</code>, <code>Decompress</code>, and/or <code>CopyRectangle</code></td>
</tr>
<tr>
<td><code>D3DX11SaveTextureToFile</code></td>
<td>ScreenGrab: <code>SaveDDSTextureToFile</code> or <code>SaveWICTextureToFile</code>

DirectXTex library, <code>CaptureTexture</code> then <code>SaveToXXXFile</code></td>
</tr>
<tr>
<td><code>D3DX11SaveTextureToMemory</code></td>
<td>DirectXTex library, <code>CaptureTexture</code> then <code>SaveToXXXMemory</code></td>
</tr>
</tbody>
</table>
<h1>Geometry Functions</h1>
The <a href="http://blogs.msdn.com/b/chuckw/archive/2014/06/27/directxmesh.aspx">DirectXMesh</a> library is intended for geometry processing offline with tools, although it can be used at runtime. You can find the library on <a href="http://go.microsoft.com/fwlink/?LinkID=324981">CodePlex</a> and <a href="https://github.com/Microsoft/DirectXMesh">GitHub</a>.
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
<h1>Math</h1>
The legacy D3DXMath library has been replaced by <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/27/introducing-directxmath.aspx">DirectXMath</a>. The library is in the Windows 8.x SDK or later, as well as being available on <a href="https://github.com/Microsoft/DirectXMath">GitHub</a>. You may also want to take a look at the <a href="https://github.com/Microsoft/DirectXTK/wiki/SimpleMath">SimpleMath </a>wrapper.
<table border="1">
<tbody>
<tr>
<td><code>D3DXFLOAT16</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.types.__macro_half.aspx">HALF</a></td>
</tr>
<tr>
<td><code>D3DXMATRIXA16</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xmmatrix.aspx">XMMATRIX</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xmfloat4x4a.aspx">XMFLOAT4X4A</a></td>
</tr>
<tr>
<td><code>D3DXMATRIX</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xmfloat4x4.aspx">XMFLOAT4X4</a></td>
</tr>
<tr>
<td><code>D3DXQUATERNION</code>

<code>D3DXPLANE</code>

<code>D3DXCOLOR</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee420742.aspx">XMVECTOR</a> is used rather than having unique types, so you will likely need to use an <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xmfloat4.aspx">XMFLOAT4</a></td>
</tr>
<tr>
<td><code>D3DXVECTOR2</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xmfloat2.aspx">XMFLOAT2</a></td>
</tr>
<tr>
<td><code>D3DXVECTOR2_16F</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xmhalf2.aspx">XMHALF2</a></td>
</tr>
<tr>
<td><code>D3DXVECTOR3</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xmfloat3.aspx">XMFLOAT3</a></td>
</tr>
<tr>
<td><code>D3DXVECTOR4</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xmfloat4.aspx">XMFLOAT4</a>

(or if you can guarantee the data is 16-byte aligned, <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee420742.aspx">XMVECTOR</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xmfloat4a.aspx">XMFLOAT4A</a> )</td>
</tr>
<tr>
<td><code>D3DXVECTOR4_16F</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.reference.xmhalf4.aspx">XMHALF4</a></td>
</tr>
<tr>
<td><code>D3DX_PI</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee415576.aspx">XM_PI</a></td>
</tr>
<tr>
<td><code>D3DX_1BYPI</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee415576.aspx">XM_1DIVPI</a></td>
</tr>
<tr>
<td><code>D3DXToRadian</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.conversion.xmconverttoradians.aspx">XMConvertToRadians</a></td>
</tr>
<tr>
<td><code>D3DXToDegree</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.conversion.xmconverttodegrees.aspx">XMConvertToDegrees</a></td>
</tr>
<tr>
<td><code>D3DXBoxBoundProbe</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh437817.aspx">BoundingBox::Intersects(XMVECTOR, XMVECTOR, float&amp;)</a></td>
</tr>
<tr>
<td><code>D3DXComputeBoundingBox</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh437802.aspx">BoundingBox::CreateFromPoints</a></td>
</tr>
<tr>
<td><code>D3DXComputeBoundingSphere</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.directxcollision.boundingsphere.createfrompoints.aspx">BoundingSphere::CreateFromPoints</a></td>
</tr>
<tr>
<td><code>D3DXSphereBoundProbe</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh437818.aspx">BoundingSphere::Intersects(XMVECTOR, XMVECTOR, float&amp;)</a></td>
</tr>
<tr>
<td><code>D3DXIntersectTriFunction</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh855857.aspx">TriangleTests::Intersects</a></td>
</tr>
<tr>
<td><code>D3DXFloat32To16Array</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh437913.aspx">XMConvertFloatToHalfStream</a></td>
</tr>
<tr>
<td><code>D3DXFloat16To32Array</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh437922.aspx">XMConvertHalfToFloatStream</a></td>
</tr>
<tr>
<td><code>D3DXVec2Length</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector2length.aspx">XMVector2Length</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector2lengthest.aspx">XMVector2LengthEst</a></td>
</tr>
<tr>
<td><code>D3DXVec2LengthSq</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector2lengthsq.aspx">XMVector2LengthSq</a></td>
</tr>
<tr>
<td><code>D3DXVec2Dot</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector2dot.aspx">XMVector2Dot</a></td>
</tr>
<tr>
<td><code>D3DXVec2CCW</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector2cross.aspx">XMVector2Cross</a></td>
</tr>
<tr>
<td><code>D3DXVec2Add</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectoradd.aspx">XMVectorAdd</a></td>
</tr>
<tr>
<td><code>D3DXVec2Subtract</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectorsubtract.aspx">XMVectorSubtract</a></td>
</tr>
<tr>
<td><code>D3DXVec2Minimize</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectormin.aspx">XMVectorMin</a></td>
</tr>
<tr>
<td><code>D3DXVec2Maximize</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectormax.aspx">XMVectorMax</a></td>
</tr>
<tr>
<td><code>D3DXVec2Scale</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectorscale.aspx">XMVectorScale</a></td>
</tr>
<tr>
<td><code>D3DXVec2Lerp</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerp.aspx">XMVectorLerp</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerpv.aspx">XMVectorLerpV</a></td>
</tr>
<tr>
<td><code>D3DXVec2Normalize</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector2normalize.aspx">XMVector2Normalize</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector2normalizeest.aspx">XMVector2NormalizeEst</a></td>
</tr>
<tr>
<td><code>D3DXVec2Hermite</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorhermite.aspx">XMVectorHermite</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorhermitev.aspx">XMVectorHermiteV</a></td>
</tr>
<tr>
<td><code>D3DXVec2CatmullRom</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorcatmullrom.aspx">XMVectorCatmullRom</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorcatmullromv.aspx">XMVectorCatmullRomV</a></td>
</tr>
<tr>
<td><code>D3DXVec2BaryCentric</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorbarycentric.aspx">XMVectorBaryCentric</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorbarycentricv.aspx">XMVectorBaryCentricV</a></td>
</tr>
<tr>
<td><code>D3DXVec2Transform</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.transformation.xmvector2transform.aspx">XMVector2Transform</a></td>
</tr>
<tr>
<td><code>D3DXVec2TransformCoord</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.transformation.xmvector2transformcoord.aspx">XMVector2TransformCoord</a></td>
</tr>
<tr>
<td><code>D3DXVec2TransformNormal</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.transformation.xmvector2transformnormal.aspx">XMVector2TransformNormal</a></td>
</tr>
<tr>
<td><code>D3DXVec2TransformArray</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh404775.aspx">XMVector2TransformStream</a></td>
</tr>
<tr>
<td><code>D3DXVec2TransformCoordArray</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh404773.aspx">XMVector2TransformCoordStream</a></td>
</tr>
<tr>
<td><code>D3DXVec2TransformNormalArray</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh404774.aspx">XMVector2TransformNormalStream</a></td>
</tr>
<tr>
<td><code>D3DXVec3Length</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector3length.aspx">XMVector3Length</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector3lengthest.aspx">XMVector3LengthEst</a></td>
</tr>
<tr>
<td><code>D3DXVec3LengthSq</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector3lengthsq.aspx">XMVector3LengthSq</a></td>
</tr>
<tr>
<td><code>D3DXVec3Dot</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector3dot.aspx">XMVector3Dot</a></td>
</tr>
<tr>
<td><code>D3DXVec3Cross</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector3cross.aspx">XMVector3Cross</a></td>
</tr>
<tr>
<td><code>D3DXVec3Add</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectoradd.aspx">XMVectorAdd</a></td>
</tr>
<tr>
<td><code>D3DXVec3Subtract</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectorsubtract.aspx">XMVectorSubtract</a></td>
</tr>
<tr>
<td><code>D3DXVec3Minimize</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectormin.aspx">XMVectorMin</a></td>
</tr>
<tr>
<td><code>D3DXVec3Maximize</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectormax.aspx">XMVectorMax</a></td>
</tr>
<tr>
<td><code>D3DXVec3Scale</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectorscale.aspx">XMVectorScale</a></td>
</tr>
<tr>
<td><code>D3DXVec3Lerp</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerp.aspx">XMVectorLerp</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerpv.aspx">XMVectorLerpV</a></td>
</tr>
<tr>
<td><code>D3DXVec3Normalize</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector3normalize.aspx">XMVector3Normalize</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector3normalizeest.aspx">XMVector3NormalizeEst</a></td>
</tr>
<tr>
<td><code>D3DXVec3Hermite</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorhermite.aspx">XMVectorHermite</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorhermitev.aspx">XMVectorHermiteV</a></td>
</tr>
<tr>
<td><code>D3DXVec3CatmullRom</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorcatmullrom.aspx">XMVectorCatmullRom</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorcatmullromv.aspx">XMVectorCatmullRomV</a></td>
</tr>
<tr>
<td><code>D3DXVec3BaryCentric</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorbarycentric.aspx">XMVectorBaryCentric</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorbarycentricv.aspx">XMVectorBaryCentricV</a></td>
</tr>
<tr>
<td><code>D3DXVec3Transform</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.transformation.xmvector3transform.aspx">XMVector3Transform</a></td>
</tr>
<tr>
<td><code>D3DXVec3TransformCoord</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.transformation.xmvector3transformcoord.aspx">XMVector3TransformCoord</a></td>
</tr>
<tr>
<td><code>D3DXVec3TransformNormal</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.transformation.xmvector3transformnormal.aspx">XMVector3TransformNormal</a></td>
</tr>
<tr>
<td><code>D3DXVec3TransformArray</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh404780.aspx">XMVector3TransformStream</a></td>
</tr>
<tr>
<td><code>D3DXVec3TransformCoordArray</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh404778.aspx">XMVector3TransformCoordStream</a></td>
</tr>
<tr>
<td><code>D3DXVec3TransformNormalArray</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh404779.aspx">XMVector3TransformNormalStream</a></td>
</tr>
<tr>
<td><code>D3DXVec3Project</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.transformation.xmvector3project.aspx">XMVector3Project</a></td>
</tr>
<tr>
<td><code>D3DXVec3Unproject</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.transformation.xmvector3unproject.aspx">XMVector3Unproject</a></td>
</tr>
<tr>
<td><code>D3DXVec3ProjectArray</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh404776.aspx">XMVector3ProjectStream</a></td>
</tr>
<tr>
<td><code>D3DXVec3UnprojectArray</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh404782.aspx">XMVector3UnprojectStream</a></td>
</tr>
<tr>
<td><code>D3DXVec4Length</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector4length.aspx">XMVector4Length</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector4lengthest.aspx">XMVector4LengthEst</a></td>
</tr>
<tr>
<td><code>D3DXVec4LengthSq</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector4lengthsq.aspx">XMVector4LengthSq</a></td>
</tr>
<tr>
<td><code>D3DXVec4Dot</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector4dot.aspx">XMVector4Dot</a></td>
</tr>
<tr>
<td><code>D3DXVec4Add</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectoradd.aspx">XMVectorAdd</a></td>
</tr>
<tr>
<td><code>D3DXVec4Subtract</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectorsubtract.aspx">XMVectorSubtract</a></td>
</tr>
<tr>
<td><code>D3DXVec4Minimize</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectormin.aspx">XMVectorMin</a></td>
</tr>
<tr>
<td><code>D3DXVec4Maximize</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectormax.aspx">XMVectorMax</a></td>
</tr>
<tr>
<td><code>D3DXVec4Scale</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectorscale.aspx">XMVectorScale</a></td>
</tr>
<tr>
<td><code>D3DXVec4Lerp</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerp.aspx">XMVectorLerp</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerpv.aspx">XMVectorLerpV</a></td>
</tr>
<tr>
<td><code>D3DXVec4Cross</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector4cross.aspx">XMVector4Cross</a></td>
</tr>
<tr>
<td><code>D3DXVec4Normalize</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector4normalize.aspx">XMVector4Normalize</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvector4normalizeest.aspx">XMVector4NormalizeEst</a></td>
</tr>
<tr>
<td><code>D3DXVec4Hermite</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorhermite.aspx">XMVectorHermite</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorhermitev.aspx">XMVectorHermiteV</a></td>
</tr>
<tr>
<td><code>D3DXVec4CatmullRom</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorcatmullrom.aspx">XMVectorCatmullRom</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorcatmullromv.aspx">XMVectorCatmullRomV</a></td>
</tr>
<tr>
<td><code>D3DXVec4BaryCentric</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorbarycentric.aspx">XMVectorBaryCentric</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorbarycentricv.aspx">XMVectorBaryCentricV</a></td>
</tr>
<tr>
<td><code>D3DXVec4Transform</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.transformation.xmvector4transform.aspx">XMVector4Transform</a></td>
</tr>
<tr>
<td><code>D3DXVec4TransformArray</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh404783.aspx">XMVector4TransformStream</a></td>
</tr>
<tr>
<td><code>D3DXMatrixIdentity</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixidentity.aspx">XMMatrixIdentity</a></td>
</tr>
<tr>
<td><code>D3DXMatrixDeterminant</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixdeterminant.aspx">XMMatrixDeterminant</a></td>
</tr>
<tr>
<td><code>D3DXMatrixDecompose</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixdecompose.aspx">XMMatrixDecompose</a></td>
</tr>
<tr>
<td><code>D3DXMatrixTranspose</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixtranspose.aspx">XMMatrixTranspose</a></td>
</tr>
<tr>
<td><code>D3DXMatrixMultiply</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixmultiply.aspx">XMMatrixMultiply</a></td>
</tr>
<tr>
<td><code>D3DXMatrixMultiplyTranspose</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixmultiplytranspose.aspx">XMMatrixMultiplyTranspose</a></td>
</tr>
<tr>
<td><code>D3DXMatrixInverse</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixinverse.aspx">XMMatrixInverse</a></td>
</tr>
<tr>
<td><code>D3DXMatrixScaling</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixscaling.aspx">XMMatrixScaling</a></td>
</tr>
<tr>
<td><code>D3DXMatrixTranslation</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixtranslation.aspx">XMMatrixTranslation</a></td>
</tr>
<tr>
<td><code>D3DXMatrixRotationX</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixrotationx.aspx">XMMatrixRotationX</a></td>
</tr>
<tr>
<td><code>D3DXMatrixRotationY</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixrotationy.aspx">XMMatrixRotationY</a></td>
</tr>
<tr>
<td><code>D3DXMatrixRotationZ</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixrotationz.aspx">XMMatrixRotationZ</a></td>
</tr>
<tr>
<td><code>D3DXMatrixRotationAxis</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixrotationaxis.aspx">XMMatrixRotationAxis</a></td>
</tr>
<tr>
<td><code>D3DXMatrixRotationQuaternion</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixrotationquaternion.aspx">XMMatrixRotationQuaternion</a></td>
</tr>
<tr>
<td><code>D3DXMatrixRotationYawPitchRoll</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixrotationrollpitchyaw.aspx">XMMatrixRotationRollPitchYaw</a>
(Note the order of parameters is different:
D3DXMath takes yaw, pitch, roll,
DirectXMath takes pitch, yaw, roll)</td>
</tr>
<tr>
<td><code>D3DXMatrixTransformation</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixtransformation.aspx">XMMatrixTransformation</a></td>
</tr>
<tr>
<td><code>D3DXMatrixTransformation2D</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixtransformation2d.aspx">XMMatrixTransformation2D</a></td>
</tr>
<tr>
<td><code>D3DXMatrixAffineTransformation</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixaffinetransformation.aspx">XMMatrixAffineTransformation</a></td>
</tr>
<tr>
<td><code>D3DXMatrixAffineTransformation2D</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixaffinetransformation2d.aspx">XMMatrixAffineTransformation2D</a></td>
</tr>
<tr>
<td><code>D3DXMatrixLookAtRH</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixlookatrh.aspx">XMMatrixLookAtRH</a></td>
</tr>
<tr>
<td><code>D3DXMatrixLookAtLH</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixlookatlh.aspx">XMMatrixLookAtLH</a></td>
</tr>
<tr>
<td><code>D3DXMatrixPerspectiveRH</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixperspectiverh.aspx">XMMatrixPerspectiveRH</a></td>
</tr>
<tr>
<td><code>D3DXMatrixPerspectiveLH</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixperspectivelh.aspx">XMMatrixPerspectiveLH</a></td>
</tr>
<tr>
<td><code>D3DXMatrixPerspectiveFovRH</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixperspectivefovrh.aspx">XMMatrixPerspectiveFovRH</a></td>
</tr>
<tr>
<td><code>D3DXMatrixPerspectiveFovLH</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixperspectivefovlh.aspx">XMMatrixPerspectiveFovLH</a></td>
</tr>
<tr>
<td><code>D3DXMatrixPerspectiveOffCenterRH</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixperspectiveoffcenterrh.aspx">XMMatrixPerspectiveOffCenterRH</a></td>
</tr>
<tr>
<td><code>D3DXMatrixPerspectiveOffCenterLH</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixperspectiveoffcenterlh.aspx">XMMatrixPerspectiveOffCenterLH</a></td>
</tr>
<tr>
<td><code>D3DXMatrixOrthoRH</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixorthographicrh.aspx">XMMatrixOrthographicRH</a></td>
</tr>
<tr>
<td><code>D3DXMatrixOrthoLH</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixorthographiclh.aspx">XMMatrixOrthographicLH</a></td>
</tr>
<tr>
<td><code>D3DXMatrixOrthoOffCenterRH</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixorthographicoffcenterrh.aspx">XMMatrixOrthographicOffCenterRH</a></td>
</tr>
<tr>
<td><code>D3DXMatrixOrthoOffCenterLH</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixorthographicoffcenterlh.aspx">XMMatrixOrthographicOffCenterLH</a></td>
</tr>
<tr>
<td><code>D3DXMatrixShadow</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixshadow.aspx">XMMatrixShadow</a></td>
</tr>
<tr>
<td><code>D3DXMatrixReflect</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.matrix.xmmatrixreflect.aspx">XMMatrixReflect</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionLength</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionlength.aspx">XMQuaternionLength</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionLengthSq</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionlengthsq.aspx">XMQuaternionLengthSq</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionDot</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaterniondot.aspx">XMQuaternionDot</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionIdentity</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionidentity.aspx">XMQuaternionIdentity</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionIsIdentity</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionisidentity.aspx">XMQuaternionIsIdentity</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionConjugate</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionconjugate.aspx">XMQuaternionConjugate</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionToAxisAngle</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaterniontoaxisangle.aspx">XMQuaternionToAxisAngle</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionRotationMatrix</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionrotationmatrix.aspx">XMQuaternionRotationMatrix</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionRotationAxis</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionrotationaxis.aspx">XMQuaternionRotationAxis</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionRotationYawPitchRoll</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionrotationrollpitchyaw.aspx">XMQuaternionRotationRollPitchYaw</a>
(Note the order of parameters is different:
D3DXMath takes yaw, pitch, roll,
DirectXMath takes pitch, yaw, roll)</td>
</tr>
<tr>
<td><code>D3DXQuaternionMultiply</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionmultiply.aspx">XMQuaternionMultiply</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionNormalize</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionnormalize.aspx">XMQuaternionNormalize</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionnormalizeest.aspx">XMQuaternionNormalizeEst</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionInverse</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternioninverse.aspx">XMQuaternionInverse</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionLn</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionln.aspx">XMQuaternionLn</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionExp</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionexp.aspx">XMQuaternionExp</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionSlerp</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionslerp.aspx">XMQuaternionSlerp</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionslerpv.aspx">XMQuaternionSlerpV</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionSquad</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionsquad.aspx">XMQuaternionSquad</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionsquadv.aspx">XMQuaternionSquadV</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionSquadSetup</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionsquadsetup.aspx">XMQuaternionSquadSetup</a></td>
</tr>
<tr>
<td><code>D3DXQuaternionBaryCentric</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionbarycentric.aspx">XMQuaternionBaryCentric</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.quaternion.xmquaternionbarycentricv.aspx">XMQuaternionBaryCentricV</a></td>
</tr>
<tr>
<td><code>D3DXPlaneDot</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanedot.aspx">XMPlaneDot</a></td>
</tr>
<tr>
<td><code>D3DXPlaneDotCoord</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanedotcoord.aspx">XMPlaneDotCoord</a></td>
</tr>
<tr>
<td><code>D3DXPlaneDotNormal</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanedotnormal.aspx">XMPlaneDotNormal</a></td>
</tr>
<tr>
<td><code>D3DXPlaneScale</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectorscale.aspx">XMVectorScale</a></td>
</tr>
<tr>
<td><code>D3DXPlaneNormalize</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanenormalize.aspx">XMPlaneNormalize</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanenormalizeest.aspx">XMPlaneNormalizeEst</a></td>
</tr>
<tr>
<td><code>D3DXPlaneIntersectLine</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplaneintersectline.aspx">XMPlaneIntersectLine</a></td>
</tr>
<tr>
<td><code>D3DXPlaneFromPointNormal</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanefrompointnormal.aspx">XMPlaneFromPointNormal</a></td>
</tr>
<tr>
<td><code>D3DXPlaneFromPoints</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanefrompoints.aspx">XMPlaneFromPoints</a></td>
</tr>
<tr>
<td><code>D3DXPlaneTransform</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.plane.xmplanetransform.aspx">XMPlaneTransform</a></td>
</tr>
<tr>
<td><code>D3DXPlaneTransformArray</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh404689.aspx">XMPlaneTransformStream</a></td>
</tr>
<tr>
<td><code>D3DXColorNegative</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.color.xmcolornegative.aspx">XMColorNegative</a></td>
</tr>
<tr>
<td><code>D3DXColorAdd</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectoradd.aspx">XMVectorAdd</a></td>
</tr>
<tr>
<td><code>D3DXColorSubtract</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectorsubtract.aspx">XMVectorSubtract</a></td>
</tr>
<tr>
<td><code>D3DXColorScale</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.arithmetic.xmvectorscale.aspx">XMVectorScale</a></td>
</tr>
<tr>
<td><code>D3DXColorModulate</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.color.xmcolormodulate.aspx">XMColorModulate</a></td>
</tr>
<tr>
<td><code>D3DXColorLerp</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerp.aspx">XMVectorLerp</a> or <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.geometric.xmvectorlerpv.aspx">XMVectorLerpV</a></td>
</tr>
<tr>
<td><code>D3DXColorAdjustSaturation</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.color.xmcoloradjustsaturation.aspx">XMColorAdjustSaturation</a></td>
</tr>
<tr>
<td><code>D3DXColorAdjustContrast</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.color.xmcoloradjustcontrast.aspx">XMColorAdjustContrast</a></td>
</tr>
<tr>
<td><code>D3DXFresnelTerm</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.utilities.xmfresnelterm.aspx">XMFresnelTerm</a></td>
</tr>
</tbody>
</table>
<h1>Spherical Harmonics Math</h1>
The <a href="http://blogs.msdn.com/b/chuckw/archive/2012/07/28/spherical-harmonics-math.aspx">SHmath</a> library is available as an add-on for DirectXMath.
<table border="1">
<tbody>
<tr>
<td><code>XMSHEvalDirection</code></td>
<td>Evaluates the Spherical Harmonic basis functions. Equivalent to <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb205448.aspx">D3DXSHEvalDirection</a> function.</td>
</tr>
<tr>
<td><code>XMSHRotate</code></td>
<td>Rotates SH vector by a rotation matrix. Equivalent to the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb204992.aspx">D3DXSHRotate</a> function.</td>
</tr>
<tr>
<td><code>XMSHRotateZ</code></td>
<td>Rotates the SH vector in the Z axis by an angle. Equivalent to the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb205461.aspx">D3DXSHRotateZ</a> function.</td>
</tr>
<tr>
<td><code>XMSHAdd</code></td>
<td>Adds two SH vectors. Equivalent to the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb205438.aspx">D3DXSHAdd</a> function.</td>
</tr>
<tr>
<td><code>XMSHScale</code></td>
<td>Scales a SH vector. Equivalent to the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb204994.aspx">D3DXSHScale</a> function.</td>
</tr>
<tr>
<td><code>XMSHDot</code></td>
<td>Computes the dot product of two SH vectors. Equivalent to the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb205446.aspx">D3DXSHDot</a> function.</td>
</tr>
<tr>
<td><code><code>XMSHMultiply
</code></code><code>XMSHMultiply2
XMSHMultiply3
XMSHMultiply4
XMSHMultiply5
XMSHMultiply6</code></td>
<td>Computes the product of two functions represented using SH. Equivalent to <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb205454.aspx">D3DXSHMultiply2</a>, <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb232906.aspx">D3DXSHMultiply3</a>, <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb232907.aspx">D3DXSHMultiply4</a>, <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb232908.aspx">D3DXSHMultiply5</a>, and <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb232909.aspx">D3DXSHMultiply6</a>.</td>
</tr>
<tr>
<td><code>XMSHEvalDirectionalLight</code></td>
<td>Evaluates a directional light and returns spectral SH data. Equivalent to the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb204988.aspx">D3DXSHEvalDirectionalLight</a> function.</td>
</tr>
<tr>
<td><code>XMSHEvalSphericalLight</code></td>
<td>Evaluates a spherical light and returns spectral SH data. Equivalent to the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb205451.aspx">D3DXEvalSphericalLight</a> function.</td>
</tr>
<tr>
<td><code>XMSHEvalConeLight</code></td>
<td>Evaluates a light that is a cone of constant intensity and returns spectral SH data. Equivalent to the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb204986.aspx">D3DXSHEvalConeLight</a> function.</td>
</tr>
<tr>
<td><code>XMSHEvalHemisphereLight</code></td>
<td>Evaluates a light that is a linear interpolant between two colors over the sphere. Equivalent to the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/bb204989.aspx">D3DXSHEvalHemisphereLight</a> function.</td>
</tr>
<tr>
<td><code>SHProjectCubeMap</code></td>
<td>Projects a function represented in a cube map into spherical harmonics. Equivalent to the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff476300.aspx">D3DX11SHProjectCubeMap</a> function.</td>
</tr>
</tbody>
</table>
<h1>Effects (FX)</h1>
The <a href="http://blogs.msdn.com/b/chuckw/archive/2012/10/24/effects-for-direct3d-11-update.aspx">Effects system for Direct3D 11</a> is primarily provided as a porting aid for older code. The library is available on <a href="http://go.microsoft.com/fwlink/p/?LinkId=271568">CodePlex</a> and <a href="https://github.com/Microsoft/FX11">GitHub</a>.
<table border="1">
<tbody>
<tr>
<td><code>D3DXCreateEffect
D3DXCreateEffectEx
D3DXCreateEffectFromResource
D3DXCreateEffectFromResourceEx
D3D10CompileEffectFromMemory</code></td>
<td><code>D3DX11CompileEffectFromMemory</code></td>
</tr>
<tr>
<td><code>D3DXCreateEffectFromFile
D3DXCreateEffectFromFileEx</code></td>
<td><code>D3DX11CompileEffectFromFile</code></td>
</tr>
<tr>
<td><code>D3D10CreateEffectFromMemory</code></td>
<td><code>D3DX11CreateEffectFromMemory</code></td>
</tr>
<tr>
<td><code>D3DXCreateEffectPool
D3D10CreateEffectPoolFromMemory</code></td>
<td>Effects 11 does not support 'effect pools'
or <code>D3DCOMPILE_EFFECT_CHILD_EFFECT</code>. Effect <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ff476120.aspx">groups</a> provide a more efficient solution for common scenarios previously addressed with 'effect pools'</td>
</tr>
<tr>
<td><code>D3DXDisassembleEffect
D3D10DisassembleEffect</code></td>
<td><code>D3DDisassemble</code>
<code>D3DDisassemble10Effect</code> in D3DCompile</td>
</tr>
</tbody>
</table>
<h1>Performance/Profiling</h1>
D3DX9 included the entry-points intercepted by PIX for Windows for performance profiling. This is now handled by the DirectX runtime directly and is monitored by the Visual Studio Graphics Diagnostics tool.
<table border="1">
<tbody>
<tr>
<td><code>D3DPERF_BeginEvent
D3DPERF_EndEvent
D3DPERF_SetMarker
D3DPERF_SetRegion
D3DPERF_QueryRepeatFrame
D3DPERF_SetOptions
D3DPERF_GetStatus</code></td>
<td><a href="http://msdn.microsoft.com/en-us/library/hh446881.aspx">ID3DUserDefinedAnnotation</a> which is supported by the DirectX 11.1 runtime on Windows 8.x and Windows 7 Service Pack 1 + <a href="http://blogs.msdn.com/b/chuckw/archive/2013/02/26/directx-11-1-and-windows-7-update.aspx">KB2670838</a>

If using DirectX 11.2+, you can use <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/dn280498.aspx">ID3D11DeviceContext2</a> directly for BeginEventInt, SetMarkerInt, and EndEvent.</td>
</tr>
</tbody>
</table>
<h1>UVAtlas Functions</h1>
The <a href="http://blogs.msdn.com/b/chuckw/archive/2014/11/14/uvatlas-return-of-the-isochart.aspx">UVAtlas</a> library is intended for isochart creation offline with tools, although it can be used at runtime. You can find the library on <a href="http://go.microsoft.com/fwlink/?LinkID=512686">CodePlex</a> and <a href="https://github.com/Microsoft/UVAtlas">GitHub</a>.
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
<h1>Note</h1>
Careful readers will note that there are a few omissions from this table.
<ul>
 	<li>The <code>ID3DXMatrixStack</code> from D3DXMath doesn't have a new version, but it's actually pretty easy to implement your own. If someone has a burning need for this, please comment below.</li>
 	<li>The Precomputed Radiance Transfer (PRT) simulator is only available in closed-source form in legacy D3DX9. There are a number of papers that cover this technology in the literature, and the most generally useful parts of this functionality are the <a href="http://blogs.msdn.com/b/chuckw/archive/2012/07/28/spherical-harmonics-math.aspx">SHmath</a> functions which are available.</li>
</ul>
<h1>Background</h1>
A few folks have asked why the D3DX libraries were deprecated in the first place in the transition to the Windows 8.x SDK. D3DX has been a useful set of utility code for Direct3D applications since Direct3D 7, but has a presented a number of challenges over the years. The primary one is that as a 'closed-source' utility library; it was difficult to debug, resolve performance issues, or apply hot-fixes without taking a dependency on a newer release of the DirectX SDK. Second, with the security requirements that came with the adoption of the <a href="http://www.microsoft.com/security/sdl/default.aspx">Secure Development Lifecycle</a> (SDL) at Microsoft, the transition to a DLL rather than a static library created a redistribution requirement that<a href="http://blogs.msdn.com/b/chuckw/archive/2010/09/08/not-so-direct-setup.aspx"> complicated setup</a> for many developers--note that static libraries have their own problems such as being specific to a particular release of the compiler including service pack level. D3DX9 itself became a bit bloated which resulted in a DLL larger than many EXEs that used it. Finally, the actual usable content of subsequent generations of D3DX left D3DX11 with not much in it. The need for useful utility code is still there, but it is now being solved with various 'shared-source' solutions rather than a monolithic closed-source DLL like D3DX.
