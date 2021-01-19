---
layout: msdnpost
title: DirectX and .NET
date: 2010-12-09 11:49
author: Chuck Walbourn
comments: true
categories: [directx]
---
With the DirectX SDK (June 2010) release and the addition of support for Visual Studio 2010, I've been seeing a lot of questions of the form:

> How do I create a DirectX .NET application in Visual Studio 2010? I can't find Microsoft.DirectX to add to my project but I have the DirectX SDK (June 2010) release installed.</em>

As with many seemingly simple questions on a technical topic, this one is actually quite complex.
<!--more-->

Back in the days of DirectX 7 and DirectX 8, there was support included for using DirectX from Visual Basic. While most developers used DirectX APIs via C and C++, there was intense interest in the hobbyist community to access this technology. Thus the focus on enabling Visual Basic developers. When working on DirectX 9, Visual Basic had become unified with the .NET family of languages and thus <em>Managed DirectX 1.1</em> was created (with a great deal of individual passion and effort from <a href="http://millermansworld.com/">Tom Miller</a> and others on the DirectX team at the time). It was designed for the .NET 1.1 Runtime, and include managed wrappers for the whole family of DirectX technology: Direct3D 9, D3DX9, DXDIAG, DirectDraw, DirectInput, DirectPlay, DirectSound, and a simple wrapper for DirectShow. The focus shifted from the Visual Basic language to C#, although VB .NET could still be used.

<strong>Note:</strong> The DirectX 7 and 8 Visual Basic 6.0 support I mention here is no longer available as of Windows Vista. It was part of DirectX 9.0c and was included with Windows XP Service Pack 2&3, Windows Server 2003 Service Pack 1 & 2, and Windows XP Professional x64 Edition.

With the release of .NET 2.0, there was an effort to update Managed DirectX to use the new constructs and in 2005 there was a Managed DirectX 2.0 Beta included as part of the DirectX SDK. As this effort was underway, a major reorganization at Microsoft took place and when the dust settled, the relatively small team that had been working on this technology suddenly found themselves as the seed of an entirely new effort around .NET gaming development: *XNA Game Studio*. The Managed DirectX 2.0 project was shelved, and all the effort focused on this new more comprehensive end-to-end solution for the indie game developers targeting Windows, Xbox 360, Zune, and eventually Windows Phone 7.

Managed DirectX 1.1 as it stands today is deprecated. It was last updated in April 2006 to match that version of D3DX9, while the Managed DirectX 1.1 documentation was last updated in August 2005. The last DirectX SDK to include the samples and documentation for Managed DirectX 1.1 was August 2006. Since that time, we've continued to include the Managed DirectX 1.1 assemblies in the DirectX SDK Developer Runtime, the DirectSetup REDIST folder, the DirectX End-User Runtime package, and the DirectX End-User Runtime Web Installer to simplify legacy deployment and support existing applications that relied on it. This last support for Managed DirectX 1.1 deployment is likely to be removed in a future DirectX SDK update.

At this point, Managed DirectX 1.1 is really beginning to show it's age.

* Since the last version of D3DX9 supported by Managed DirectX 1.1 is April 2006, it makes use of a very outdated version of the HLSL compiler. <em>The D3DX9 library itself and the DirectX SDK are also legacy at this point</em>.

* The Managed DirectX 1.1 assemblies are 32-bit only, so you cannot use them from an x64 native .NET application (``/platform:anycpu`` on a Windows x64 system). You must build with ``/platform:x86`` and stay within the limits of the 2 GB memory space of 32-bit applications.

* The assemblies only support the legacy DirectX API set, with no support for Direct3D9Ex, Direct3D 10.x, Direct3D 11, Direct3D 12, Direct2D, DirectWrite, DXGI, D3DX10, D3DX11, XAUDIO2, XACT, XINPUT, etc.

* Since Managed DirectX 2.0 was never released in production form, the Managed DirectX 1.1 assemblies still reflect .NET 1.1 design principles and does not support or make use of .NET 2.0 constructs.
* Managed DirectX 1.1 while compatible with .NET 2.0 (and the .NET 3.0 and .NET 3.5 extensions of the 2.0 runtime), is not compatible with .NET 4.0

The last bullet here is the heart of the issue I started out with in this post. The Visual Studio 2010 toolset only supports developing .NET 4.0 applications, and therefore Managed DirectX 1.1 as a .NET 1.1 technology is not supported by Visual Studio 2010. BTW, it is possible to use the Visual Studio 2010 IDE to build .NET 2.0 applications using older toolsets through <a href="http://weblogs.asp.net/scottgu/archive/2009/08/27/multi-targeting-support-vs-2010-and-net-4-series.aspx">multi-targeting</a>, but this is really using legacy tools which do work with .NET 1.1 era assemblies.

> One more challenge of trying to use the legacy Managed DirectX 1.1 assemblies is that they are only deployed by the legacy [DirectSetup](https://walbourn.github.io/not-so-direct-setup/) package. If you continue to use it, be sure to use the [refreshed](https://walbourn.github.io/dxsetup-update/) version of DXSETUP.

The modern version of the DirectX SDK is designed for C/C++ native developers. If you are looking for .NET solutions for using DirectX technology, there are many options available although the choice of solution depends on your specific needs:

* <em>XNA Game Studio</em> is the solution aimed directly at indie game developers looking to create Direct3D games on Windows, Xbox 360, Zune, and Windows Phone 7. It has some limitations (requires ``/platform:x86``, no support for DirectX 10.x or DirectX 11, more focused DirectX API support, no support for Windows Store or Windows phone, content pipeline only works with VS 2010), but includes numerous tools and a vibrant developer community. Those original hobbyist developers Tom Miller wanted to help are very well served by this product, as is the professional and indie game developer looking for a complete solution for writing .NET games. <em><a href="http://www.monogame.net/">Monogame</a> is also an open-source alternative to XNA Game Studio, and <a href="http://unity3d.com/">Unity3D</a> is a commercial alternative.</em>

* ~~For a developer using the Windows Presentation Foundation but wants to use the new DirectX 11 APIs, the Windows API Code Pack provides managed assemblies for Direct3D 10.1, Direct3D 11, Direct2D, DirectWrite, DXGI, and the Windows Imaging Library (WIC) along with many other Windows 7 features. The latest version supports .NET 4.0, and x64 native "anycpu" applications. Note you still need to install the DirectX SDK to get the HLSL compiler (``FXC.EXE``) tool~~.

* For developers who are invested in Managed DirectX 1.1 but are looking for updates to address the limitations I note above for Win32 desktop applications, the open source <a href="https://github.com/SlimDX/slimdx">SlimDX</a> library is designed to mimic Managed DirectX 1.1 for just this purpose. It includes support for x64 native "anycpu" applications, includes DirectX 11 support, and is compatible with the .NET 4.0 runtime. <em>SlimDX is no longer maintained and was last released around ~2012. The source is openly available so it's still a good option when looking for a 'drop-in' replacement for legacy Managed DX 1.1</em>.

* <a href="https://github.com/sharpdx/SharpDX">SharpDX</a> another option for C# and is currently the preferred solution for 'modern' Microsoft platforms including Windows Store and Windows phone 8. <em>SharpDX is no longer maintained as of 2019, but is available as open source</em>.

* If you are a media developer using DirectShow and want a more complete solution than the simple Managed DirectX 1.1 wrapper, the open source <a href="http://directshownet.sourceforge.net/"><em>directshow.net</em> </a>library may be useful to you, although it hasn't been updated since ~2010.

If these solutions don't work for you, you can always write your own managed wrapper using standard native interop constructs or use Managed C++/CLI to write the DirectX portion of your application in C/C++ using the DirectX SDK. The Windows Presentation Foundation <a href="https://docs.microsoft.com/en-us/dotnet/api/system.windows.interop.d3dimage">D3DImage </a>class can be a useful way to do this interop, although the use of Direct3D9Ex on Windows Vista and Windows 7 can cause some problems with components like D3DX9 which you should watch out for.

> You should also look at [GitHub](https://github.com/Microsoft/WPFDXInterop)

<strong>.NET 1.1 Framework:</strong> Note that the .NET 1.1 Framework is <a href="http://support.microsoft.com/kb/2489698">not supported</a> on either Windows 7, Windows 8.x, or Windows 10.

<strong>Win2D: </strong>Another option to consider is ShawnHar's <a href="https://github.com/Microsoft/Win2D">latest project</a> for using Direct2D/DirectWrite from C# or C++/CX. This is a Windows Runtime API projection for UWP, and includes WIC integration.
