---
layout: msdnpost
title: Game Rating Systems and Windows 7
date: 2013-01-20 23:35
author: Chuck Walbourn
comments: true
categories: [win7]
---
Windows 8 includes a number of changes to the parental control ratings systems supported by Windows Family Safety (aka Windows Parental Controls) for Win32 desktop games. These changes are now available on Windows 7 via <a href="http://support.microsoft.com/kb/2773072">KB2773072</a>. It is recommended that all game publishers populate their GDFs using the latest <em>Game Definition File Editor</em> (<code>GDFMaker.EXE</code>) in the Windows 8.0 SDK rather than using the legacy DirectX SDK version which does not support these ratings changes.
<!--more-->

For full details on these changes to the ratings systems and GDF-related tools, see the <a href="https://walbourn.github.io/windows-8-release-preview-and-gdfs/">Windows 8 and GDFs</a> blog post.

> The latest version of the <em>Game Definition File Validator</em> (<code>GDFTrace.EXE</code>) on <a href="https://github.com/walbourn/directx-sdk-samples/tree/main/GDFTrace">GitHub</a> has been updated for all the latest ratings system changes.

<strong>Update:</strong> The latest version of <a href="https://walbourn.github.io/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available/">GDFMaker</a> is in the Windows 8.1 SDK.
