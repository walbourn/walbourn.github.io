---
layout: post
title: Known Issue: D3D11InstallHelper sample
date: 2010-11-10 13:33
author: walbourn
comments: true
categories: [directx, Uncategorized]
---
<p>I recently found a minor problem with the existing <strong>D3D11InstallHelper</strong> sample that shipped in August 2009, February 2010, and June 2010 versions of the DirectX SDK. The supplied version of <code>D3D11Install.exe</code> is correct, but if you compile it using the Visual Studio project yourself, it does not properly inject a reference to the Windows Common Controls version 6.0 into the manifest file. The result of this is that the dialogs (which all contain hyperlinks using the SysLink common control) do not initialize and fail to display.</p>
<p>The fix is fairly easy. In the <code>D3D11Install.cpp</code> file, just add a #pragma statement:</p>
<p>//-----------------------------------------------------------------------------<br />// File: D3D11Install.cpp<br />//<br />// Desc: Windows code that calls D3D11InstallHelper sample DLL and displays<br />//&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; the recommended UI prompts and messages.<br />//<br />// (C) Copyright Microsoft Corp.&nbsp; All rights reserved.<br />//-----------------------------------------------------------------------------<br />#define _WIN32_DCOM<br />#define _CRT_SECURE_NO_DEPRECATE<br />#include "D3D11InstallHelper.h"<br />#include "resource.h"</p>
<p>#include &lt;stdio.h&gt;<br />#include &lt;shlobj.h&gt;<br />#include &lt;process.h&gt;<br />#include &lt;shellapi.h&gt;</p>
<p>#define MSG_SIZE&nbsp;&nbsp;&nbsp; 1024</p>
<p><span style="background-color: #ffff99;">#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")</span></p>
<p>&nbsp;<strong>Update</strong>: Note the most current version of this sample is available on <a href="http://code.msdn.microsoft.com/Direct3D-11-Install-Helper-3044575e">MSDN Code Gallery</a>.</p>
