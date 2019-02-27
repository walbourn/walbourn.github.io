---
layout: post
title: Game Rating Systems and Windows 7
date: 2013-01-20 23:35
author: walbourn
comments: true
categories: [Uncategorized, win7]
---
<p>Windows 8 includes a number of changes to the parental control ratings systems supported by Windows Family Safety (aka Windows Parental Controls) for Win32 desktop games. These changes are now available on Windows 7 via <a href="http://support.microsoft.com/kb/2773072">KB2773072</a>. It is recommended that all game publishers populate their GDFs using the latest <em>Game Definition File Editor</em> (<code>GDFMaker.EXE</code>) in the Windows 8.0 SDK rather than using the legacy DirectX SDK version which does not support these ratings changes.</p>
<p>For full details on these changes to the ratings systems and GDF-related tools, see the <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/31/windows-8-release-preview-and-gdfs.aspx">Windows 8 and GDFs</a> blog post.</p>
<p>Note: The latest version of the <em>Game Definition File Validator</em> (<code>GDFTrace.EXE</code>) on <a href="http://code.msdn.microsoft.com/GDF-Trace-5389d1b4">MSDN Code Gallery</a> has been updated for all the latest ratings system changes.</p>
<p><strong>Update:</strong> The latest version of <a href="http://blogs.msdn.com/b/chuckw/archive/2013/10/18/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available.aspx">GDFMaker</a> is in the Windows 8.1 SDK.</p>
<p>&nbsp;</p>
