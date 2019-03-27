---
layout: msdnpost
title: Known Issue - D3D11InstallHelper sample
date: 2010-11-10 13:33
author: Chuck Walbourn
comments: true
categories: [directx]
---
I recently found a minor problem with the existing <strong>D3D11InstallHelper</strong> sample that shipped in August 2009, February 2010, and June 2010 versions of the DirectX SDK. The supplied version of <code>D3D11Install.exe</code> is correct, but if you compile it using the Visual Studio project yourself, it does not properly inject a reference to the Windows Common Controls version 6.0 into the manifest file. The result of this is that the dialogs (which all contain hyperlinks using the SysLink common control) do not initialize and fail to display.
<!--more-->

The fix is fairly easy. In the <code>D3D11Install.cpp</code> file, just add a ``#pragma`` statement:

```cpp
//-----------------------------------------------------------------------------
// File: D3D11Install.cpp
//
// Desc: Windows code that calls D3D11InstallHelper sample DLL and displays
//       the recommended UI prompts and messages.
//
// (C) Copyright Microsoft Corp.  All rights reserved.
//-----------------------------------------------------------------------------
#define _WIN32_DCOM
#define _CRT_SECURE_NO_DEPRECATE

#include "D3D11InstallHelper.h"
#include "resource.h"

#include <stdio.h>
#include <shlobj.h>
#include <process.h>
#include <shellapi.h>

#define MSG_SIZE    1024
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
```
<strong>Update</strong>: Note the most current version of this sample is available on <a href="https://github.com/walbourn/directx-sdk-samples/tree/master/InstallHelpers/D3D11InstallHelper">GitHub</a>.
