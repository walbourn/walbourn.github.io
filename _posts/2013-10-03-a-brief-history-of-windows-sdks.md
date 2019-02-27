---
layout: post
title: A Brief History of Windows SDKs
date: 2013-10-03 11:13
author: walbourn
comments: true
categories: [Uncategorized, windowssdk]
---
A common source of confusion for Windows development is the Windows SDK naming scheme. For example: Can someone use the "Windows SDK for Windows Server 2008 and .NET Framework 3.5" to target Windows XP?

The recommendation is for developers to use the latest version of the Windows SDK they can for access to the latest technologies and APIs, given the restrictions of your projects development platform, target platforms, and toolset. Figuring out this matrix of choices is a bit challenging, so this blog post spells out some key differences.

For a more complete version history, you might want to check out <a href="http://en.wikipedia.org/wiki/Microsoft_Windows_SDK">Wikipedia</a>.
<h1>Q: What SDK am I using currently?</h1>
Most developers get a copy of the Windows SDK or Platform SDK with their Visual Studio installation.
<table border="1">
<tbody>
<tr>
<td>Visual Studio 2017</td>
<td>Windows 10 SDK (14393, 15063, or 16299)

Windows 8.1 SDK Spring 2015 [optional]

Windows 7.1A SDK for "v14_xp" Platform Toolset</td>
</tr>
<tr>
<td>Visual Studio 2015</td>
<td>Windows 8.1 SDK Spring 2015

Windows 10 SDK (10240, 10586, or 14393) [optional]

Windows 7.1A SDK for "v140_xp" Platform Toolset</td>
</tr>
<tr>
<td>Visual Studio 2013</td>
<td>Windows 8.1 SDK (VS 2013 Update 3 and Update 5 contain newer versions)

Windows 7.1A SDK for "v120_xp" Platform Toolset

VS 2013 Express for Windows only includes a subset of the full Windows 8.1 SDK</td>
</tr>
<tr>
<td>Visual Studio 2012</td>
<td>Windows 8.0 SDK

Windows 7.1A SDK for "v110_xp" Platform Toolset (added in Update 1)

VS 2012 Express for Windows only includes a subset of the full Windows 8.0 SDK</td>
</tr>
<tr>
<td>Visual Studio 2010</td>
<td>Windows SDK 7.0A

Similar to <em>Windows SDK for Windows 7 and .NET Framework 3.5 SP1</em> (August 2009)</td>
</tr>
<tr>
<td>Visual Studio 2008</td>
<td>Windows SDK 6.0A

Similar to <em>Windows SDK for Windows Vista Update and .NET Framework 3.0</em> (February 2007)</td>
</tr>
<tr>
<td>Visual Studio 2005</td>
<td>Similar to <em>Windows Server 2003 SP1 Platform SDK</em> (April 2005)

VS 2005 Express did not include the Platform SDK</td>
</tr>
</tbody>
</table>
<h1>Q: What platform does a given Windows SDK target?</h1>
Given the naming scheme for the Window SDKs, this is probably the most confusing aspect of choosing a Windows SDK. The easiest way to describe it is to list the last releases which allowed you to target a given OS.
<ul>
 	<li>Windows SDK 7.1 (aka <em>Windows SDK for Windows 7 and .NET Framework 4.0</em>) was the last release to support targeting Windows XP and Windows Server 2003.</li>
 	<li><em>Windows Server 2003 SP1 Platform SDK (April 2005)</em> was the last release to support targeting Windows 2000.</li>
</ul>
<h1>Q: What platform does a given Window SDK support for development?</h1>
Another aspect is that the Windows SDK often supports a smaller set of platforms for development (i.e. it can be installed on) compared to those it can target (i.e. deploy applications to).
<ul>
 	<li>Windows 10 SDK requires Windows 7 SP1, Windows 8, Windows 8.1, or Windows 10</li>
 	<li>Windows 8.1 SDK requires Windows 7 SP1, Windows 8, or Windows 8.1</li>
 	<li>Windows 8.0 SDK requires Windows 7 or Windows 8.x</li>
</ul>
<h1>Q: What compiler toolset does a given Windows SDK support?</h1>
Not all Windows SDKs can be used with all versions of Visual Studio. Changes in language features, /analyze SAL annotation, and other aspects of the compiler toolset are assumed as the baseline for a given Visual Studio release--usually that version that comes with a given Visual Studio release is the 'oldest' one it supports.
<ul>
 	<li>Windows 10 SDK supports Visual Studio 2015</li>
 	<li>Windows 8.1 SDK supports Visual Studio 2010 or later. To use with VS 2010 or VS 2012 requires manual integration per this <a href="http://blogs.msdn.com/b/vcblog/archive/2012/11/23/using-the-windows-8-sdk-with-visual-studio-2010-configuring-multiple-projects.aspx">blog</a> post.</li>
 	<li>Windows 8.0 SDK supports Visual Studio 2010 or later. To use with VS 2010 requires manual integration per this <a href="http://blogs.msdn.com/b/vcblog/archive/2012/11/23/using-the-windows-8-sdk-with-visual-studio-2010-configuring-multiple-projects.aspx">blog</a> post.</li>
 	<li>Windows 7.1 SDK supports Visual Studio 2005 or later.</li>
 	<li>Platform SDK (February 2003) was the last release to support Visual Studio 6.</li>
</ul>
<h1>Q: How do I use a newer SDK to target an older version of Windows?</h1>
The standard way of doing this is to set a Preprocessor Define _WIN32_WINNT to the appropriate value for the 'oldest' version of Windows you are targeting (see <a href="http://msdn.microsoft.com/en-us/library/aa383745.aspx">Using the Windows Headers</a>). This causes the headers to work in such a way that newer APIs are not available at build time. This can get a bit complicated for "Platform Updates" that put portions of newer OS features onto older version of Windows, but otherwise _WIN32_WINNT is usually sufficient to get the expected behavior. Otherwise, you can set a 'higher' value to give you access to newer APIs, but the programmer must take care to handle detection or fallback as needed for partially supported or unsupported APIs on down-level versions of Windows (i.e. <a href="http://blogs.msdn.com/b/chuckw/archive/2012/11/19/windows-imaging-component-and-windows-8.aspx">WIC2</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2014/02/05/anatomy-of-direct3d-11-create-device.aspx">Direct3D 11</a>)

Note that unlike previous Windows SDKs, the Windows 8.x SDKs use a default value of _WIN32_WINNT that is the 'newest' rather than the 'oldest' version of the OS.

<strong>Related: </strong><a href="http://blogs.msdn.com/b/chuckw/archive/2012/08/22/directx-sdk-s-of-a-certain-age.aspx">DirectX SDKs of a certain age</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2010/06/15/windows-sdk-7-1.aspx">Windows 7.1 SDK</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/08/15/visual-studio-2012-and-windows-8-0-sdk-rtm-are-now-available.aspx">Windows 8.0 SDK</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/10/18/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available.aspx">Windows 8.1 SDK</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2015/03/30/visual-studio-tools-for-windows-10-preview.aspx">Windows 10 SDK</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/11/26/visual-studio-2012-update-1.aspx">VS 2012 Update 1</a>
