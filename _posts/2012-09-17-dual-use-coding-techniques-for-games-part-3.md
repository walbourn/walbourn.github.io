---
layout: msdnpost
title: Dual-use Coding Techniques for Games, part 3
date: 2012-09-17 17:37
author: Chuck Walbourn
comments: true
categories: [win10, win8, winphone, xbox]
---
<em>Writing shared code for Windows Store, Xbox One, Universal Windows Platform (UWP) apps, and Win32 desktop apps</em>

(continued from <a href="https://walbourn.github.io/dual-use-coding-techniques-for-games-part-1/">part 1</a> and <a href="https://walbourn.github.io/dual-use-coding-techniques-for-games-part-2/">part 2</a>)

<h1>Windows Runtime (WinRT) APIs</h1>

There are a number of areas of the system where you must use WinRT APIs to access the required functionality for Windows Store apps, and there is no Win32 equivalent included in the Windows Store apps API family. This code is not a good candidate for dual-use scenarios, but there are times when it makes sense to house both the WinRT and Win32 implementation in the same module. Generally you should prefer to have the client application handle this platform-specific functionality and provide the information needed to your dual-use shared code as parameters, but this is not always convenient or practical.
<!--more-->

This scenario is one where you have to make use of the <code>WINAPI_FAMILY</code> macro to determine if you are building for Windows Store apps or Win32 desktop apps. There are a number of ways to do this, and most of them are subtly incorrect. The system headers make extensive use of the <code>WINAPI_FAMILY_PARTITION</code> macro available in ``<winapifamily.h>``, however, as the exact make-up of partitions is subject to change with the introduction of new families over time, the recommendation is to only take dependencies on the FAMILY macros.

```cpp
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
// This code is for Win32 desktop apps
#else
// This code is for Windows Store or Windows phone apps
#endif
```

In some cases when writing code for Windows phone apps, you may need to handle a difference from Windows Store apps. In this case, you can use this guard.

```cpp
#if defined(WINAPI_FAMILY) && (WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP)
// This code is for Windows phone apps only
#endif
```

Alternatively, you may want to support contexts without the Windows 8.0 SDK such as using the Windows 7.1 SDK for Windows XP support. In this case requiring an explicit build configuration (such as <code>/DBUILDING_FOR_DESKTOP</code> in the project settings for Win32 desktop usage) is the easiest and cleanest solution.

```cpp
#ifdef BUILDING_FOR_DESKTOP
// This code is for Win32 desktop apps
#else
// This code is for Windows Store apps
#endif
```

> For Xbox One, you should make use of the ``_XBOX_ONE`` and ``_TITLE`` defines (both are defined the Xbox One XDK, just ``_XBOX_ONE`` is defined for the Xbox One ADK).

The ``__cplusplus_winrt`` control define can be a useful way to isolate C++/CX language extensions as well, and this define is active whenever building with <code>/ZW</code> (the default for Windows Store app projects). It is, however, possible to be building for a Windows Store app without the <code>/ZW</code> switch (such as in a static library), so the ``#ifndef __cplusplus_winrt`` case can still be for a Windows Store app. Thus it is not a substitute for the logic above with the <code>WINAPI_FAMILY</code> control define for determining when building for the Windows Store vs. Win32 desktop.

```cpp
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
// This code is for Win32 desktop apps
#elif !defined (__cplusplus_winrt)
#error This module requires WinRT C++/CX language support (/ZW)
// This code is for WinRT Windows Store apps
#endif
```

For example, here is some utility code for getting access to the proper path for a temporary file folder. This code builds for Windows Store apps using <code>/ZW</code> and for Win32 desktop apps.

```cpp
void GetTemporaryDirectory(wchar_t* dir, size_t maxsize)
{
    if (!maxsize) return;
    *dir = 0;
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
    DWORD nChars = GetTempPath(maxsize, dir);
    if (nChars > 0)
        dir[nChars - 1] = '\0'; // Trim trialing '\'
    else
        *dir = 0;
#else // Windows Store WinRT app
    auto folder = Windows::Storage::ApplicationData::Current
        ->TemporaryFolder;
    wcscpy_s(dir, maxsize, folder->Path->Data());
#endif // WINAPI_FAMILY_PARTITION
}
```

Here is a similar function that gets the application local data folder for the Windows Store app using <code>/ZW</code> or for Win32 desktop apps using the Windows Vista <code>IKnownFolder</code> API.

```cpp
void GetApplicationDataDirectory(wchar_t* dir, size_t maxsize)
{
    if (!maxsize) return;
    *dir = 0;
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
    Microsoft::WRL::ComPtr<IKnownFolderManager> mgr;
    HRESULT hr = CoCreateInstance(CLSID_KnownFolderManager,
        nullptr, CLSCTX_INPROC_SERVER, IID_IKnownFolderManager, (LPVOID*)&mgr);
    if (SUCCEEDED(hr))
    {
        Microsoft::WRL::ComPtr<IKnownFolder> folder;
        hr = mgr->GetFolder(FOLDERID_LocalAppData, &folder);
        if (SUCCEEDED(hr))
        {
            LPWSTR szPath = 0;
            hr = folder->GetPath(0, &szPath);
            if (SUCCEEDED(hr))
            {
                wcscpy_s(dir, maxsize, szPath);
                wcscat_s(dir, maxsize, L"\\MyUniqueApplicationName");
                CreateDirectory(dir, nullptr);
                CoTaskMemFree(szPath);
            }
        }
    }
#elif defined(__cplusplus_winrt)
    // Windows Runtime app using /ZW
    auto folder = Windows::Storage::ApplicationData::Current
        ->LocalFolder;
    wcscpy_s(dir, maxsize, folder->Path->Data());
#else
    // Windows Runtime app not using /ZW, perhaps C++/WinRT
    auto folder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();
    wcscpy_s(dir, maxsize, folder.Path().c_str());
#endif
}
```

>  This code assumes that <code>CoInitialize(Ex)</code> was already called by the client application.

Remember that Windows Store apps have a very restricted set of security privileges and access to the hard disk is tightly controlled. You should assume you only have read access to the files included in the AppX package for the Windows Store or the install location in "Program Files" for Win32 desktop apps. You should assume you only have read/write access to a temporary folder, the application local data folder, the application roaming data folder, and only other folders in special permissions scenarios (which may be read-only instead of read-write).

<table border="1">
<tbody>
<tr>
<td><code>Windows::Storage:: ApplicationData</code> property</td>
<td><code>IKnownFolder</code> equivalent</td>
<td><code>SHGetFolderPath</code> equivalent</td>
</tr>
<tr>
<td>LocalFolder</td>
<td>FOLDERID_LocalAppData
+ unique folder name</td>
<td>CSIDL_LOCAL_APPDATA
+ unique folder name</td>
</tr>
<tr>
<td>RoamingFolder</td>
<td>FOLDERID_RoamingAppData
+ unique folder name</td>
<td>CSIDL_APPDATA
+ unique folder name</td>
</tr>
</tbody>
</table>

<strong>Note:</strong> There's no direct equivalent to LocalSettings or RoamingSettings for Win32 desktop apps.

See <a href="https://docs.microsoft.com/en-us/previous-versions/windows/apps/hh967755(v=win.10)
">File access and permissions in Windows Runtime apps</a>

<h1>Resources</h1>

Scott Meyers. More Effective C++. Addison-Wesley, 1996. Print.

<a href="https://msdn.microsoft.com/magazine/msdn-magazine-issues">C++: New Standard Concurrency Features in Visual C++ 11</a>, MSDN Magazine (March 2012)

<a href="https://msdn.microsoft.com/magazine/msdn-magazine-issues">X64 Primer: Everything You Need To Know To Start Programming 64-Bit Windows Systems</a>, MSDN Magazine (May 2006)
