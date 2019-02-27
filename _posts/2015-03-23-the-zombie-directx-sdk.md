---
layout: post
title: The Zombie DirectX SDK
date: 2015-03-23 14:58
author: walbourn
comments: true
categories: [dxsdk, Uncategorized]
---
<p>Over the past five years, I've devoted significant time and effort to explaining the state of affairs with&nbsp;the <a href="http://blogs.msdn.com/b/chuckw/archive/2013/07/01/where-is-the-directx-sdk-2013-edition.aspx">legacy DirectX SDK</a>. Developers can of course continue to use the legacy DirectX SDK (once they apply the <a href="http://blogs.msdn.com/b/chuckw/archive/2013/09/24/10246203.aspx">workaround</a> for the existing installation problems) with the Windows 8.0 SDK or later which comes with VS 2012 / 2013 / 2015 per the instructions on <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/ee663275.aspx">MSDN</a>. This allows existing projects that still use deprecated D3DX9/D3DX10/D3DX11, XAudio 2.7, XInput 1.3, or XACT to build but still gain access to the latest Windows headers/libraries. You should in general rely on other methods for obtaining the latest <a href="http://blogs.msdn.com/b/chuckw/archive/2012/11/30/direct3d-sdk-debug-layer-tricks.aspx">debug device layer</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2014/10/28/directx-sdk-tools-catalog.aspx">tools</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/08/21/living-without-d3dx.aspx">utility libraries</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/09/20/directx-sdk-samples-catalog.aspx">samples</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/10/24/effects-for-direct3d-11-update.aspx">Effects 11</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/09/14/dxut-for-win32-desktop-update.aspx">DXUT11</a>, and <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/07/hlsl-fxc-and-d3dcompile.aspx">HLSL Compiler</a>.</p>
<p>There is, however, one case that I've not addressed to date: <strong>A number of developers actually "checked in" the legacy DirectX SDK headers and libraries into their source control</strong>. While this behavior is a bit of a grey area in terms of the DirectX SDK EULA, it is none-the-less a widespread practice in the industry including several major game engines. In this case, the various recommendations I mentioned above are difficult to properly apply since typically headers/libs in your source control tree are going to take precedence over the platform headers/libs in the Windows SDK. Therefore, this article suggest how to modify these legacy DirectX SDK "mirrors" to get proper build behavior.</p>
<p><em>If you do not already have the legacy DirectX SDK headers/libraries submitted into your source control, I do not recommend doing so. This post is for people who already have and can't simply delete it all without breaking supported scenarios. This is explicitly not an endorsement of the practice and I make no claims about whether or not this use is actually allowed by the terms of the DirectX SDK EULA.</em></p>
<h1>Delete</h1>
<p>The first step in this process is to delete the following legacy DirectX SDK&nbsp;headers &amp; libraries completely. These are already provided by the Windows 8.x SDK when using the standard "v110", "v120", or "v140" Platform Toolsets, and are also provided by the Windows 7.1A SDK that is used when building with the "v110_xp", "v120_xp", or "v140_xp" Platform Toolsets that allow you to target Windows XP systems (see&nbsp;<a href="http://blogs.msdn.com/b/chuckw/archive/2012/11/26/visual-studio-2012-update-1.aspx">this post</a> for more details). <em>You do not need a private copy of these and the legacy DirectX SDK versions are out of date.</em></p>
<table border="1">
<tbody>
<tr>
<td><code>dxsdk\include\</code></td>
<td><code>D2D1.h<br /> D2D1Helper.h<br /> D2DBaseTypes.h<br /> D2Derr.h<br /> d3d9.h<br /> d3d9caps.h<br /> d3d9types.h<br /> Dcommon.h<br /> dinput.h<br /> dinputd.h<br /> dsconf.h<br /> dsound.h<br /> DWrite.h<br /> DXGI.h<br /> DXGIFormat.h<br /> DXGIType.h<br /> gameux.h<br /> rpcsal.h</code></td>
</tr>
<tr>
<td><code>dxsdk\lib\x86\</code></td>
<td><code>d2d1.lib<br /> d3d10.lib<br /> d3d10_1.lib<br /> d3d11.lib<br /> d3d9.lib<br /> dinput8.lib<br /> dsound.lib<br /> dwrite.lib<br /> dxgi.lib</code></td>
</tr>
<tr>
<td><code>dxsdk\lib\x64\</code></td>
<td><code>d2d1.lib<br /> d3d10.lib<br /> d3d10_1.lib<br /> d3d11.lib<br /> d3d9.lib<br /> dinput8.lib<br /> dsound.lib<br /> dwrite.lib<br /> dxgi.lib</code></td>
</tr>
</tbody>
</table>
<h1>Keep</h1>
<p>The next set of headers/libs are those that are unique to the legacy DirectX SDK and do not conflict with any of the headers/libs in the Windows 8.x SDK or Windows 7.1A SDK. <em>You can safely keep these until you completely eliminate all use of legacy DirectX SDK content from your project.</em> Also remember that you should <span style="text-decoration: underline;">not</span> use any of these headers/libs for Windows Store apps, Windows phone apps, Xbox One apps, or universal Windows apps.</p>
<table border="1">
<tbody>
<tr>
<td><code>dxsdk\include\</code></td>
<td><code>audiodefs.h<br /> comdecl.h<br /> D3DX10.h<br /> d3dx10async.h<br /> D3DX10core.h<br /> D3DX10math.h<br /> D3DX10math.inl<br /> D3DX10mesh.h<br /> D3DX10tex.h<br /> D3DX11.h<br /> D3DX11async.h<br /> D3DX11core.h<br /> D3DX11tex.h<br /> d3dx9.h<br /> d3dx9anim.h<br /> d3dx9core.h<br /> d3dx9effect.h<br /> d3dx9math.h<br /> d3dx9math.inl<br /> d3dx9mesh.h<br /> d3dx9shader.h<br /> d3dx9shape.h<br /> d3dx9tex.h<br /> d3dx9xof.h<br /> dsetup.h<br /> dxdiag.h<br /> DxErr.h*<br /> dxfile.h<br /> dxsdkver.h<br /> PIXPlugin.h<br /> rmxfguid.h<br /> rmxftmpl.h<br /> xact3.h<br /> xact3d3.h<br /> xact3wb.h<br /> XDSP.h<br /> xma2defs.h</code></td>
</tr>
<tr>
<td><code>dxsdk\lib\x86\</code></td>
<td><code>d3dx10.lib<br /> d3dx10d.lib<br /> d3dx11.lib<br /> d3dx11d.lib<br /> d3dx9.lib<br /> d3dx9d.lib<br /> d3dxof.lib<br /> dsetup.lib<br /> DxErr.lib*</code></td>
</tr>
<tr>
<td><code>dxsdk\lib\x64\</code></td>
<td><code>d3dx10.lib<br /> d3dx10d.lib<br /> d3dx11.lib<br /> d3dx11d.lib<br /> d3dx9.lib<br /> d3dx9d.lib<br /> d3dxof.lib<br /> DxErr.lib*</code></td>
</tr>
</tbody>
</table>
<h1>Windows 7</h1>
<p>This next set of headers/libraries are only needed when targeting Windows 7 or earlier if you are using XAudio or more functionality for XInput than is provided in the basic 9.1.0 version of the API which is already present on Windows. This provides XAudio 2.7 (see <a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/02/xaudio2-and-windows-8-consumer-preview.aspx">this post</a>) and XInput 1.3 (see <a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/26/xinput-and-windows-8-consumer-preview.aspx">this post</a>). These headers/libs directly conflict with headers/libs in the Windows 8.x SDK, are not present in the Windows 7.1A SDK, and should be moved into a subfolder.</p>
<table border="1">
<tbody>
<tr>
<td><code>dxsdk\include\win7\</code></td>
<td><code>X3DAudio.h<br /> XAPO.h<br /> XAPOBase.h<br /> XAPOFX.h<br /> XAudio2.h<br /> XAudio2fx.h<br /> XInput.h</code></td>
</tr>
<tr>
<td><code>dxsdk\lib\win7\x86\</code></td>
<td><code>X3DAudio.lib<br /> xapobase.lib<br /> xapobased.lib<br /> XAPOFX.lib<br /> XInput.lib</code></td>
</tr>
<tr>
<td><code>dxsdk\lib\win7\x64\</code></td>
<td><code>X3DAudio.lib<br /> xapobase.lib<br /> xapobased.lib<br /> XAPOFX.lib<br /> XInput.lib</code></td>
</tr>
</tbody>
</table>
<p><strong>Note:</strong> The Windows 8.x SDK copy of <code>xinput.h</code> will use XInput 9.1.0 instead of XInput 1.4 if <code>_WIN32_WINNT</code> is set below 0x0602 (Windows 8.0). The legacy DirectX SDK <code>xinput.h</code> will use XInput 9.1.0 instead of XInput 1.3. if <code>XINPUT_USE_9_1_0</code> is defined. The Windows 7.1 SDK copy of <code>xinput.h</code> only uses XInput 9.1.0.</p>
<h1>Windows XP</h1>
<p>Lastly, this set of headers/libraries are only needed when targeting Windows XP (i.e. building a EXE that can run on Windows XP as obviously Direct3D 10.x and Direct3D 11 are not supported on Windows XP). These headers/libs all conflict with the Windows 8.x SDK except XNAMath, are out of date compared to the Windows 8.x SDK, and should be moved into a subfolder. Some of these are not present in the Windows 7.1A SDK, while&nbsp;others are newer versions.</p>
<table border="1">
<tbody>
<tr>
<td><code>dxsdk\include\xp\</code></td>
<td><code>D3D10.h<br /> D3D10effect.h<br /> d3d10misc.h<br /> d3d10sdklayers.h<br /> D3D10shader.h<br /> D3D10_1.h<br /> D3D10_1shader.h<br /> D3D11.h<br /> D3D11SDKLayers.h<br /> D3D11Shader.h<br /> D3Dcommon.h<br /> D3Dcompiler.h<br /> D3DCSX.h<br /> D3DX_DXGIFormatConvert.inl<br /> xnamath.h<br /> xnamathconvert.inl<br /> xnamathmatrix.inl<br /> xnamathmisc.inl<br /> xnamathvector.inl</code></td>
</tr>
<tr>
<td><code>dxsdk\lib\xp\x86\</code></td>
<td><code>d3dcompiler.lib<br /> D3DCSX.lib<br /> D3DCSXd.lib<br /> dxguid.lib</code></td>
</tr>
<tr>
<td><code>dxsdk\lib\xp\x64\</code></td>
<td><code>d3dcompiler.lib<br /> D3DCSX.lib<br /> D3DCSXd.lib<br /> dxguid.lib</code></td>
</tr>
</tbody>
</table>
<p><strong>Note:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/27/introducing-directxmath.aspx">DirectXMath</a> will work on Windows XP, but there's no official include path configuration that would support this scenario. You could in theory delete <code>xnamath*.*</code> and instead put a copy of <code>DirectXMath*.*</code>, <code>DirectXCollision.*</code>, <code>DirectXColors.h</code>, and <code>DirectXPackedVector.*</code> in this folder instead for Windows XP use.<em> I make no claim that this is or is not allowed by the terms of the Windows SDK EULA.</em></p>
<h1>Project Configuration</h1>
<p>Assuming you had a <code>dxsdk</code> subtree configured as described above, then you should use the following as <em>Additional Include Paths</em> and <em>Additional Library Paths</em> in your project settings depending on your target platform if you have legacy DirectX SDK dependencies. <em>Ideally you should minimize and work to eliminate all use of the legacy DirectX SDK in favor of the standard Windows SDK content.</em></p>
<ul>
<li>For Windows Store apps, universal Windows apps, Windows phone apps, and Xbox One apps you should <span style="text-decoration: underline;">not use any</span> of these paths in your build.</li>
</ul>
<ul>
<li>For Windows desktop applications built using the standard "v110", "v120", or "v140" Platform Toolsets--which will use the Windows 8.x SDK--and have <code>_WIN32_WINNT </code>set to 0x0600 (Windows Vista) or 0x0601 (Windows 7), then use:
<ul>
<li>Include: <code>dxsdk\include;dxsdk\include\win7;%(AdditionalIncludeDirectories)</code></li>
<li>Libraries for "Win32" configurations: <code>dxsdk\lib\x86;dxsdk\lib\win7\x86;%(AdditionalDependencies)</code></li>
<li>Libraries for "x64" configurations: <code>dxsdk\lib\x64;dxsdk\lib\win7\x64;%(AdditionalDependencies)</code></li>
</ul>
</li>
</ul>
<ul>
<li>For Windows desktop applications that do not make use of XACT; are built using the standard "v110", "v120", or "v140"&nbsp;Platform Toolsets; and have <code>_WIN32_WINNT </code>set to 0x0602 (Windows 8) or higher, then use:
<ul>
<li>Include: <code>dxsdk\include;%(AdditionalIncludeDirectories)</code></li>
<li>Libraries for "Win32" configurations: <code>dxsdk\lib\x86;%(AdditionalDependencies)</code></li>
<li>Libraries for "x64" configurations: <code>dxsdk\lib\x64;%(AdditionalDependencies)</code></li>
</ul>
</li>
</ul>
<ul>
<li>For a Windows desktop application that is compatible with Windows XP built using the "v110_xp", "v120_xp" or "v140_xp" Platform Toolset--which will use the Windows 7.1A SDK--and has <code>_WIN32_WINNT </code>set to 0x0501 (Windows XP), then use:
<ul>
<li>Include: <code>dxsdk\include;dxsdk\include\win7;dxsdk\include\xp;%(AdditionalIncludeDirectories)</code></li>
<li>Libraries for "Win32" configurations: <code>dxsdk\lib\x86;dxsdk\lib\win7\x86;dxsdk\lib\xp\x86;%(AdditionalDependencies)</code></li>
<li>Libraries for "x64" configurations: <code>dxsdk\lib\x64;dxsdk\lib\win7\x64;dxsdk\lib\xp\x64;%(AdditionalDependencies)</code></li>
</ul>
</li>
</ul>
<h1>Deployment</h1>
<p>If you make use of these legacy DirectX SDK libraries, then you continue to depend on the legacy DirectSetup deployment mechanism to install these DLLs on end-user systems. See <a href="http://blogs.msdn.com/b/chuckw/archive/2010/09/08/not-so-direct-setup.aspx">Not So DirectSetup</a> and <a href="http://blogs.msdn.com/b/chuckw/archive/2011/04/19/dxsetup-update.aspx">DXSETUP Update</a> for more background on the proper use of this legacy deployment mechanism, and work to minimize your use of it.</p>
<ul>
<li>Use of <code>dxsdk\include</code> for <code>D3DX9_43.DLL</code>, <code>D3DX10_43.DLL</code>, <code>D3DX11_43.DLL</code>, or <code>XACTEngine3_7.DLL</code></li>
<li>Use of <code>dxsdk\include\win7</code> for <code>XInput1_3.DLL</code>, <code>XAudio2_7.DLL</code>, <code>XAPOFX1_5.DLL</code>, or <code>X3DAudio1_7.dll</code></li>
<li>Use of <code>dxsdk\include\xp</code> for <code>D3DCompiler_43.DLL</code> or <code>D3DCSX_43.DLL</code></li>
</ul>
<p><strong>VS 2015 Users:&nbsp; </strong>Note that <code>DXERR.LIB</code> in the legacy DirectX SDK is not compatible with the C Runtime used by VS 2015. You must use <a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/24/where-s-dxerr-lib.aspx">this version</a> of DXERR instead.</p>
