---
layout: post
title: Visual Studio 2017 (15.3) update
date: 2017-08-14 12:52
author: walbourn
comments: true
categories: [Uncategorized, visualc]
---
Since the release of Visual Studio 2017 in March, there have been two minor updates (<a href="https://blogs.msdn.microsoft.com/visualstudio/2017/04/05/visual-studio-2017-update/">15.1</a> and <a href="https://blogs.msdn.microsoft.com/visualstudio/2017/05/10/update-to-visual-studio-2017-and-next-preview/">15.2</a>) per the new <a href="https://www.visualstudio.com/en-us/productinfo/vs2017-release-rhythm">release rhythm</a>. The first update (15.1) integrated the <a href="https://blogs.msdn.microsoft.com/chuckw/2017/04/06/windows-10-creators-update-sdk/">Windows 10 Creators Update SDK</a> (15063), and the second update (15.2) included fixes for the IDE and tools. Neither of these updates included significant changes to the C/C++ compiler beyond a few specific hotfixes. The first major revision to the Visual C++ 19.1 compiler and libraries is now available with the latest update: <a href="https://blogs.msdn.microsoft.com/visualstudio/2017/08/14/visual-studio-2017-version-15-3-released/">Visual Studio 2017 (15.3)</a>.

If you already have VS 2017 installed, run the "Visual Studio Installer" application on your system to apply the update. If you don't yet have VS 2017 installed, you can download the latest installer from <a href="https://www.visualstudio.com/downloads/">here</a>.

The latest VS 2017 Redistribution packages are available (<a href="https://go.microsoft.com/fwlink/?LinkId=746571">x86</a>, <a href="https://go.microsoft.com/fwlink/?LinkId=746572">x64</a>), as well as the Remote Debugging Tools (<a href="https://go.microsoft.com/fwlink/?LinkId=746569">x86</a>, <a href="https://go.microsoft.com/fwlink/?LinkId=746570">x64</a>). For more on the Visual Studio 2017 (15.3) update, see the <a href="https://www.visualstudio.com/en-us/news/releasenotes/vs2017-relnotes">release notes</a>.

<strong>Note: </strong> The <a href="https://blogs.msdn.microsoft.com/vcblog/2016/10/05/faster-c-solution-load-with-vs-15/">Lightweight Solution Load option</a> that does a partial load of projects for large C++ solutions is included in this update.
<h1>Compiler and CRT</h1>
VS 2017 (15.3) inclues a new version of the C/C++ compiler (19.11.25506). See <a href="https://blogs.msdn.microsoft.com/vcblog/2017/08/11/c17-features-and-stl-fixes-in-vs-2017-15-3/">this blog post</a> for details on the latest Standard conformance and language/library fixes. There are a few new warnings--a few of which are currently off-by-default but quite useful for portability--detailed in <a href="https://blogs.msdn.microsoft.com/vcblog/2017/07/21/diagnostic-improvements-in-vs2017-15-3-0/">this blog post</a>. The latest update also includes support for <a href="https://blogs.msdn.microsoft.com/vcblog/2017/07/11/microsoft-visual-studio-2017-supports-intel-avx-512/">AVX-512 intrinsics</a>. There's also some new behavior for <code>/permissive-</code> with <a href="https://blogs.msdn.microsoft.com/vcblog/2017/09/11/two-phase-name-lookup-support-comes-to-msvc/">two-phase name lookup</a>.

The <code>/std</code> switch can be specified with a new VC++ project element <code>&lt;LanguageStandard&gt;</code> instead of having to use <code>&lt;AdditionalOptions&gt;</code> starting with the 15.3 update.

<strong>Note:</strong> Per <a href="https://blogs.msdn.microsoft.com/vcblog/2016/10/05/visual-c-compiler-version/">this blog post</a>, the <code>_MSC_VER</code> value is now 1911 instead of 1910.

The C/C++ Runtime (14.11.25325) is included in this update. Remember that VS 2015 and VS 2017 share the same runtime redistributable binaries and that VS 2015 Update 3 is binary compatible with VS 2017--code or static library built with one can be linked to the other--, so this is the latest version for both.

The C++ Core Guidelines checker has also been updated. See <a href="https://blogs.msdn.microsoft.com/vcblog/2017/08/11/c-core-guidelines-checker-in-visual-studio-2017/">this blog post</a> as well as <a href="https://blogs.msdn.microsoft.com/vcblog/2017/08/14/managing-warnings-in-the-c-core-guidelines-checker/">this one</a>.

<strong>directx-vs-templates:</strong> The VS 2017 (15.3) includes a fix with my <a href="https://github.com/walbourn/directx-vs-templates/wiki">Direct3D game templates</a> if using them on a system without VS 2015 installed side-by-side.

<strong>GitHub:</strong> I've done new releases of DirecX Tool Kit (<a href="https://github.com/Microsoft/DirectXTK">DX11</a> / <a href="https://github.com/Microsoft/DirectXTK12">DX12</a>), <a href="https://github.com/Microsoft/DirectXTex">DirectXTex</a>, <a href="https://github.com/Microsoft/DirectXMesh">DirectXMesh</a>, and <a href="https://github.com/Microsoft/UVAtlas">UVAtlas</a> which have been updated to build correctly with VS 2017 when using the 15.3 update--I make use of <code>/permissive-</code> for these projects.

<strong>Related:</strong> <a href="https://blogs.msdn.microsoft.com/chuckw/2017/03/07/visual-studio-2017/">Visual Studio 2017 RTM</a>
