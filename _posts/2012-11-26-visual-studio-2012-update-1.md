---
layout: post
title: Visual Studio 2012 Update 1
date: 2012-11-26 14:44
author: walbourn
comments: true
categories: [dxsdk, Uncategorized, visualc]
---
An update to Visual Studio 2012 is now available for <a href="http://www.microsoft.com/visualstudio/eng/downloads#d-visual-studio-2012-update">download</a>. For full details, see the following blog posts: <a href="http://blogs.msdn.com/b/visualstudio/archive/2012/11/26/visual-studio-2012-update-1-is-here.aspx">Visual Studio team blog</a>, <span class="breadcrumb-item2"><a href="http://blogs.msdn.com/b/somasegar/archive/2012/11/26/visual-studio-2012-update-1-now-available.aspx">Somasegar's blog</a>, and </span><a href="http://blogs.msdn.com/b/visualstudioalm/archive/2012/11/26/visual-studio-and-team-foundation-server-2012-update-1-now-available.aspx">Visual Studio ALM + Team Foundation Server blog</a>.

This update includes support for targeting Windows XP with the Visual C++ 2012 toolset and CRT. This provides C++11 Language and Standard Library support for Win32 desktop applications compatible with the <a href="http://blogs.msdn.com/b/chuckw/archive/2010/10/22/goodbye-to-an-old-friend.aspx">legacy Windows XP platform</a>. This is accomplished through using the Platform Toolset "v110_xp". Details on this were announced for the <a href="http://blogs.msdn.com/b/vcblog/archive/2012/10/08/10357555.aspx">CTP</a>.

See <a href="http://support.microsoft.com/kb/2797915">KB 2797915</a>
<h1>Compiler and CRT</h1>
<em>VS 2012 Update 1</em> includes a new version of the compiler (17.00.51106) and C/C++ Runtime (11.0.51106).

<a href="http://www.microsoft.com/en-us/download/details.aspx?id=30679">MSDN downloads</a> has the updated retail redistribution packages which are now compatible with Windows XP Service Pack 3.
<h1>Windows SDK and Windows XP</h1>
First be sure to read this <a href="http://blogs.msdn.com/b/vcblog/archive/2012/10/08/windows-xp-targeting-with-c-in-visual-studio-2012.aspx">blog post</a> by the Visual Studio team. When building applications that support the legacy Windows XP platform, you are using a platform header and library set similar to those that shipped in the <a href="http://blogs.msdn.com/b/chuckw/archive/2010/06/15/windows-sdk-7-1.aspx">Windows 7.1 SDK</a> rather than the <em>Windows 8.x SDK</em> with the integrated <em>DirectX SDK</em> content (see <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">Where is the DirectX SDK?</a>). Many of the "DirectX" headers and libraries are included with these Windows XP compatible platform headers (see <a href="http://blogs.msdn.com/b/chuckw/archive/2012/08/22/directx-sdk-s-of-a-certain-age.aspx">DirectX SDKs of a certain age</a>) such as Direct3D 9, DirectSound, and DirectInput. You will, however, need to continue to use the legacy <em>DirectX SDK</em> for Windows XP compatible versions of the D3DCompile API (#43), legacy D3DX9, XAUDIO2, XINPUT, and <em>PIX for Windows</em> tool (the Visual Studio 2012 Graphics Debugger does not support Direct3D 9 applications).

<em>Windows SDK 7.1A</em> is installed as part of VS 2012 Update 1 for use with the "v110_xp" Platform Toolset, which contains the headers, libraries, and a subset of the tools that originally shipped in the <em>Windows SDK 7.1</em>. There are older Direct3D 10 and Direct3D 11 headers as part of this 7.1 era toolset which are outdated compared to the Windows 8.x SDK versions using the standard "v110" Platform Toolset, particularly the SDK Debug Layers installed by the Windows 8.0 SDK on Windows 7 and Windows 8. The Platform Toolset "v110_xp" is therefore not recommended for developing DirectX 11 applications, but it can technically be done with some caution. <em>Windows SDK 7.1A</em> does not contain a <code>dxguid.lib</code> so must either locally define the required GUIDs in your project by using <code>#define INITGUID</code> in one of your .cpp files, or use the legacy <em>DirectX SDK </em>version.

This also means that the 'search path order' guidance for "v110_xp" is different than the Windows 8.x SDK recommendations on <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee663275.aspx">MSDN</a>. For "v110_xp" you should use the legacy order:

<p style="padding-left: 30px"><code>$(DXSDK_DIR)Include;$(IncludePath)
$(DXSDK_DIR)Lib\x86;$(LibraryPath)</code>

For "v110" if you are using legacy DirectX SDK components for an EXE that does not support Windows XP:

<p style="padding-left: 30px"><code>$(IncludePath);$(DXSDK_DIR)Include
$(LibraryPath);$(DXSDK_DIR)Lib\x86</code> or <code>x64</code>

<strong>_WIN32_WINNT:</strong> When building an application that is 'down-level' when using headers in the Windows 8.x SDK, be sure to explicitly select the correct 'minimum' _WIN32_WINNT value. For Windows 8, that is 0x0602 (which is the default when building code with Visual Studio 2012 and for all Windows Store apps). For Windows 7 use 0x0601, and for Windows Vista use 0x0600. When using "v110_xp" set it to <code>0x0502</code> (the Visual C++ REDIST requires Windows XP Service Pack 3). Typically this is done as part of the project configuration via Preprocessor Definitions. See <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745.aspx">Using the Windows Headers</a> for more information.

<strong>Note:</strong> The Direct3D 9 Developer Runtime is only available on Windows 7 or older versions of the OS using the legacy DirectX SDK. Direct3D 9 debugging is not supported for Windows 8.x or Windows 10.

<strong>Windows Server:</strong> Targeting Window Server 2003 or Windows Server 2003 R2 also requires the use of "v110_xp".

<strong>VS 2013:</strong> This information also applies to Visual C++ 2013's "v120_xp" platform target.

<strong>VS 2015: </strong>This information also applies to Visual C++ 2015's "v140_xp" platform target. Note that a number of warnings are generated in system headers when using the older SDK with the newer compiler. You will need to select the optional component <em>Windows XP Support for C++ </em>in the <a href="https://blogs.msdn.microsoft.com/vcblog/2015/07/24/setup-changes-in-visual-studio-2015-affecting-c-developers/">custom install</a>.

<strong>VS 2017: </strong>This information also applies to Visual C++ 2017's "v141_xp" platform target. Note that a number of warnings are generated in system headers when using the older SDK with the newer compiler, and you won't be able to make use of <code>/permissive-</code>.  You will need to install additional optional component <em>Windows XP Support for C++</em> (<code>Microsoft.VisualStudio.Component.WinXP</code> and <code>Microsoft.VisualStudio.ComponentGroup.NativeDesktop.WinXP</code>) in the <a href="https://blogs.msdn.microsoft.com/vcblog/2016/08/22/the-lightweight-visual-studio-15-installer/">installer</a>.
<h1>DirectXMath and Windows XP</h1>
<a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/27/introducing-directxmath.aspx">DirectXMath</a> in the Windows 8.x SDK is compatible with Windows XP, but the "v110_xp" Platform Toolset include paths will not find it. You can make use <a href="http://blogs.msdn.com/b/chuckw/archive/2012/06/22/xna-math-version-2-05-smoothing-the-transition-to-directxmath.aspx">XNAMath 2.05</a> for your Windows XP configurations, or you can make a copy of the DirectXMath headers in the project for Windows XP configurations--DirectXMath can also obtained directly from <a href="https://github.com/Microsoft/DirectXMath">GitHub</a>.
<h1>Microsoft::WRL::ComPtr and Windows XP</h1>
A similar issue to the one with DirectXMath arises when using the <a href="https://msdn.microsoft.com/en-us/library/br244983.aspx">ComPtr</a> smart-pointer: the "v110_xp" Platform Toolset include paths will not find <code>wrl.h</code> or <code>wrl\client.h</code>. You can use ATL's <a href="https://msdn.microsoft.com/en-us/library/ezzw7k98.aspx">CComPtr</a> instead when targeting Windows XP, but remember that <code>operator&amp;</code> with ATL's <code>CComPtr</code> maps to <code>GetAddressOf()</code> while the same operator with <code>Microsoft::WRL::ComPtr</code> maps to <code>ReleaseAndGetAddressOf()</code>.
<h1>Code Analysis</h1>
This update includes Code Analysis <code>/analyze</code> support for Windows phone 8 applications (i.e. when using the Platform Toolset "v110_wp80")

Note that the Platform Toolset "v110_xp" does not support Code Analysis <code>/analyze</code> which is disabled due to incompatibilities with the <em>Windows SDK 7.1A</em> headers.

<strong>Related:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2013/04/08/visual-studio-2012-update-2.aspx">Visual Studio 2012 Update 2</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/06/26/visual-studio-2012-update-3.aspx">Visual Studio 2012 Update 3</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/11/14/visual-studio-2012-update-4.aspx">Visual Studio 2012 Update 4</a>
