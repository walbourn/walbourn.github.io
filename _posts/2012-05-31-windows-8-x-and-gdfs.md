---
layout: msdnpost
title: Windows 8.x and GDFs
date: 2012-05-31 15:42
author: Chuck Walbourn
comments: true
categories: [directx, dxsdk, win8]
---
Windows 8 includes numerous improvements as discussed on the <em>Building Windows 8 blog</em>, the DirectX 11.1 Runtime (including <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3darticles/directx-warp">WARP</a> support for feature levels 11.1 and 11.0), and for game developers and publishers it includes some important updates to the <em>Windows Family Safety / Parental Controls</em> system for game ratings.
<!--more-->

Includes support for four new ratings systems:

<ul>
 	<li><a href="http://go.microsoft.com/fwlink/?LinkId=241628">COB-AU</a> - Classification Operations Board (Australia)</li>
 	<li><a href="http://go.microsoft.com/fwlink/?LinkId=241631">DJCTQ</a> - Department of Justice (Brazil)</li>
 	<li><a href="http://go.microsoft.com/fwlink/?LinkId=241627">FPB</a> - Film and Publication Board (South Africa)</li>
 	<li><a href="http://go.microsoft.com/fwlink/?LinkId=241629">OFLC-NZ</a> Office of Film and Literature Classification (New Zealand)</li>
</ul>

<ul>
 	<li>The artwork for <a href="http://go.microsoft.com/fwlink/?LinkId=62076">PEGI</a> has been updated and two new descriptors ("Online" and "Gambling") have been added.</li>
 	<li>Support for PEGI (Finland) and OFLC (Australia) rating systems have been removed as these rating systems are now deprecated. Finland now uses PEGI (rather than their own variant), and Australia uses COB-AU.</li>
 	<li>The artwork for <a href="http://go.microsoft.com/fwlink/?LinkID=132708&&clcid=0x409">CSRR</a> has been updated, the "PG" rating is deprecated, "PG12" and "PG15" rating levels have been added, and there are now 10 content descriptors.</li>
</ul>

<strong>Windows 7:</strong> These updates to the rating systems apply to Windows 7 as well when <a href="http://support.microsoft.com/kb/2773072">KB2773072</a> has been installed. PEGI (Finland) and OFLC (Australia) are present after the update, but are marked deprecated in the UI as end-users are encouraged to switch to the newer systems.

<strong>Windows 8.1:</strong> This release includes two changes to the rating systems:
<ul>
 	<li><a href="http://go.microsoft.com/fwlink/?LinkId=282715">PCBP</a> - Russian Age Rating System (Russia) is now supported.</li>
 	<li>PEGI/BBFC is no longer supported (UK uses standard PEGI)</li>
</ul>
<strong>Windows 8:</strong> <a href="http://support.microsoft.com/kb/2838466">KB 2838466</a> updates Windows 8 with support for PCBP (Russian Age Rating System)

<strong>Windows 10:</strong> For Win32 desktop applications, the GDF data is still used to obtain ratings information for Windows Parental Controls.

<h1>Game Definition File (GDF) Tools</h1>

The DirectX SDK has historically been the shipping vehicle for the various Game Explorer tools. With the transition to the Windows SDK (see <a href="https://aka.ms/dxsdk">Where is the DirectX SDK?</a>), these tools now have new homes:

<h2>Game Definition File Editor</h2>

<code>GDFMaker.EXE</code> is in the Windows 8.x SDK (included with Visual Studio 2012 and available <a href="https://developer.microsoft.com/en-us/windows/downloads/sdk-archive">standalone</a>). It is located in the <code>x86</code> directory under the <code>bin</code> folder. This version of the tool uses the ratings systems descriptions available on the version of Windows it is run on, rather than including a local copy as the older DirectX SDK version did. This means you should run it on Windows 8 be able to populate all the latest ratings information, although the tool can be run on Windows 7 as well only showing the rating systems available for Windows 7. The Windows SDK version requires .NET 4.x as well. This tool is used to author GDF files for both Win32 desktop and Windows Store apps.

<strong>Windows 8.1 SDK: </strong>There's an updated version of <code>GDFMaker.EXE</code> (included with VS 2013 and available <a href="http://go.microsoft.com/fwlink/?LinkID=323507">standalone</a>) that resolves a problem when run on English but not EN-US systems.

<h2>Game Definition File Validator</h2>

<code>GDFTrace.EXE</code> is available on <a href="http://code.msdn.microsoft.com/GDF-Trace-5389d1b4">MSDN Code Gallery</a> and has been updated for these latest rating systems changes and can build without requiring the DirectX SDK  using Visual Studio 2010 or Visual Studio 2012.

<h2>Gameux Install Helper</h2>

<code>GameuxInstallHelper.DLL</code> is available on <a href="http://code.msdn.microsoft.com/GameuxInstallHelper-6a9335ca">MSDN Code Gallery</a>. It has been updated from the DirectX SDK (June 2010) version and can build without requiring the DirectX SDK using Visual Studio 2010 or Visual Studio 2012. This utility is used for deploying Win32 desktop applications.

<strong>Update: </strong>These tools are also included in the DirectX SDK samples repo on <a href="https://github.com/walbourn/directx-sdk-samples">GitHub</a>.

<h1>Application Compatibility</h1>

For publishers and developers of games on Windows 7, be sure to read <a href="https://walbourn.github.io/desktop-games-on-windows-8-x">Desktop Games for Windows 8 Consumer Preview</a> for recommendations on compatibility for existing Win32 desktop style applications as well as the official <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/windows-8-and-windows-server-8-compatibility-cookbook-portal">Compatibility Cookbook</a>.
