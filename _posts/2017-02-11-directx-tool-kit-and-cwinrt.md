---
layout: msdnpost
title: DirectX Tool Kit and C++/WinRT
date: 2017-02-11 07:54
author: Chuck Walbourn
comments: true
categories: [uwp, visualc, xbox one]
---
The <strong>February 2017</strong> releases of <em>DirectX Tool Kit</em> for <a href="https://github.com/Microsoft/DirectXTK/releases">DirectX 11</a> and <a href="https://github.com/Microsoft/DirectXTK12/releases">DirectX 12</a> are now available on GitHub. In addition to various bug-fixes and a few minor improvements to the input classes (<a href="https://walbourn.github.io/directx-tool-kit-keyboard-and-mouse-support/">Mouse, Keyboard</a>, and <a href="https://walbourn.github.io/directx-tool-kit-now-with-gamepads/">GamePad</a>), the libraries now also support <strong>C++/WinRT applications</strong> for UWP and Xbox One. C++/WinRT language projections allow you to use Windows Runtime APIs without using the C++/CX language extensions (i.e. the libraries will work with applications built with or without <code>/ZW</code>).
<!--more-->

For more on C++/WinRT, see:

<a href="https://moderncpp.com/">https://moderncpp.com/</a>

<a href="https://msdn.microsoft.com/en-us/magazine/mt745094.aspx">C++ - Introducing C++/WinRT</a> (MSDN Magazine)

<a href="https://github.com/Microsoft/cppwinrt">cppwinrt on GitHub</a>

<a href="https://github.com/Microsoft/cppwinrt/blob/master/Docs/Migrating%20C%2B%2B%20CX%20source%20code%20to%20C%2B%2B%20WinRT.md">Migrating C++/CX source code to C++/WinRT</a>

"<a href="https://www.youtube.com/watch?v=lm4IwfiJ3EU">Embracing Standard C++ for the Windows Runtime</a>" (CppCon 2016)

"<a href="https://www.youtube.com/watch?v=v0SjumbIips">Putting Coroutines to Work with the Windows Runtime</a>" (CppCon 2016)

<strong>VS Templates:</strong> I've added C++/WinRT variants of my Direct3D UWP templates for DirectX 11 and DirectX 12 to <a href="https://github.com/walbourn/directx-vs-templates">directx-vs-templates</a> and the <a href="https://github.com/walbourn/directx-vs-templates/releases">VS 2015 VSIX</a>.

<strong>Samples:</strong> In addition to the samples on the cppwinrt GitHub, there's a C++/WinRT version of some samples on <a href="https://github.com/Microsoft/Xbox-ATG-Samples">Xbox-ATG-Samples</a>.

<strong>NuGet: </strong>You can use  <a href="https://www.nuget.org/packages/cppwinrt/">C++/WinRT on NuGet</a> as an easy way to add the C++/WinRT headers for the <em>Windows 10 Anniversary Update</em> (<a href="https://walbourn.github.io/windows-10-anniversary-update-sdk/">14393</a>) to the templates above or your own project.

<strong>Compiler:</strong> To use C++/WinRT, you must be use using <a href="https://walbourn.github.io/visual-studio-2015-update-3/">Visual Studio 2015 Update 3</a> or Visual Studio 2017 and build with the <a href="https://devblogs.microsoft.com/cppblog/permissive-switch/"><code>/std:c++latest</code></a> switch. The use of <a href="https://devblogs.microsoft.com/cppblog/using-c-coroutines-to-simplify-async-uwp-code/"><code>/await</code></a> is also recommended.

<strong>DirectXMath, DirectXTex, DirectXMesh:</strong> These libraries are also compatible with both C++/WinRT and C++/CX applications.

<strong>Related: </strong><a href="https://walbourn.github.io/directx-tool-kit-for-directx-12/">DirectX Tool Kit for DirectX 12</a>, <a href="https://walbourn.github.io/direct3d-game-visual-studio-templates-redux/">Direct3D Game Visual Studio templates (Redux)</a>
