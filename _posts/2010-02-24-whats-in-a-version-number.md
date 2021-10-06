---
layout: msdnpost
title: What's in a version number?
date: 2010-02-24 11:39
author: Chuck Walbourn
comments: true
categories: [directx]
---
There are many version numbers in Windows, and many different ways to obtain and use them. The plethora of ways to get versioning information, and the many different kinds of components involved, has typically resulted in lots of rope for developers to hang themselves. These messes tend to explode when a new Service Pack comes out or with a new release of the Windows OS. This is often a shame because otherwise the programs work perfectly well on the new version of Windows as long as you lie to them about the OS version number. In fact there's a lot of work put into identifying failing applications and putting in explicit code to lie about the OS version number for each of them, but this manual can't be done for every piece of software on the planet. There's been some <a href="https://docs.microsoft.com/en-us/windows/desktop/Win7AppQual/compatibility---application-manifest">recent work</a> to try to automate this, but it too relies on developers to "do the right thing" so ultimately it isn't a problem that can be completely fixed here in Redmond.
<!--more-->

The recommendation has long been to not use version numbers. For features that might or might not be available, there is usually a trivial way to handle it that works successfully without ever relying on OS version information. Using ``LoadLibrary()`` and ``GetProcAddress()`` is perhaps the most well-known way to test for an entry-point that you want to use that might or might not be available. Clever use of ``/DELAYLOAD`` can also achieve the same effect, although it's <a href="http://blogs.msdn.com/larryosterman/archive/2009/03/06/delay-load-is-not-a-good-way-to-check-for-functionality.aspx">not recommended</a>. Creating a COM factory object and handling failure is also very common. The main point here is that any time you think you need an OS version check in your code: stop and find an alternative. This problem is extremely pervasive, and why we continue to drive this message home through the <a href="https://docs.microsoft.com/en-us/windows/desktop/DxTechArts/games-for-windows-technical-requirements-1-1-0006">Games for Windows TR 2.5</a> advocating the use of the *HighVersionLie* test in **Application Verifier** to make sure this problem isn't lurking in your game.

With that said, there is one extremely common and reasonable use for an OS version check: your installer sets a 'minimum bar' of supported OSes. I like to think of them as "your OS must be this high to ride this ride" tests. The critically important aspect of these version checks is that they, when properly written, are unbounded on high-end of the range. Microsoft developers go through a lot of pain and difficulty to ensure that future versions of the OS continue to support the vast majority of existing applications so assuming the worst of a future OS is generally not worth the cost and hassle of blocking 'forward'. It is, however, completely reasonable to set a point below which you don't want to support legacy versions of Windows. This typically makes for cleaner code, and means you don't have to rely as heavily on the ``LoadLibrary()``/``GetProcAddress()`` solution on every Win32 call introduced after Windows 1.0.

So your sold on the idea of having exactly one OS version check in your entire application and it's limited to the installer. Great, what is the right way to do it? Well, as it turns out there are dozens of incorrect ways people have done this ranging from wonky expressions to registry key shenanigans. An extremely robust way to do it is to use the following C++ code example for <strong>DirectX 9.0c games</strong>:

```cpp
HMODULE hMod = LoadLibraryW( L"kernel32" );
assert( hMod != 0); // Win32 programs have to have this module loaded

OSVERSIONINFOEXW osv = {};
osv.dwOSVersionInfoSize = sizeof(osv);

osv.dwMajorVersion = 5;  // Windows XP Service Pack 3 or later
osv.dwMinorVersion = 1;
osv.wServicePackMajor = 3;
osv.wServicePackMinor = 0;

DWORDLONG mask = 0;

typedef ULONGLONG ( WINAPI* fpSetMask )( ULONGLONG, DWORD, BYTE );
auto fpVerSetConditionMask = reinterpret_cast<fpSetMask>(GetProcAddress( hMod, "VerSetConditionMask" ));
if (fpVerSetConditionMask != 0)
{
  mask = fpVerSetConditionMask( mask, VER_MAJORVERSION, VER_GREATER_EQUAL );
  mask = fpVerSetConditionMask( mask, VER_MINORVERSION, VER_GREATER_EQUAL );
  mask = fpVerSetConditionMask( mask, VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL );
  mask = fpVerSetConditionMask( mask, VER_SERVICEPACKMINOR, VER_GREATER_EQUAL );
}

typedef BOOL ( WINAPI* fpVerify )( LPOSVERSIONINFOEXW, DWORD, DWORDLONG );
auto fpVerifyVersionInfo = reinterpret_cast<fpVerify>(GetProcAddress( hMod, "VerifyVersionInfoW" ));
if ( !fpVerifyVersionInfo
     || !fpVerifyVersionInfo( &osv,
            VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR, mask ) )
{
  error("This program requires Windows XP Service Pack 3 or later\n");
}

osv.dwMajorVersion = 5;  // Windows Server 2003 RTM
osv.dwMinorVersion = 2;
osv.wServicePackMajor = 0;

mask = 0;

if (fpVerSetConditionMask != 0)
{
  mask = fpVerSetConditionMask( mask, VER_MAJORVERSION, VER_EQUAL );
  mask = fpVerSetConditionMask( mask, VER_MINORVERSION, VER_EQUAL );
  mask = fpVerSetConditionMask( mask, VER_SERVICEPACKMAJOR, VER_EQUAL );
}

if ( fpVerifyVersionInfo( &osv,
         VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, mask ) )
{
  error("This program requires Windows Server 2003 SP1 or later\n");
}
```

At this point we know the OS already includes the DirectX 9.0c Runtime or later. We know that Direct3D 9, DirectSound8, DirectInput8, etc are all present. We only need to use the DirectX SDK DirectSetup REDIST if our application makes use of optional side-by-side components like D3DX, XAUDIO2, XINPUT, XACT, etc. See <a href="https://docs.microsoft.com/en-us/windows/desktop/DxTechArts/directx-setup-for-game-developers">DirectX Installation for Game Developers</a> for details on how to configure a minimal package for this purpose.

> The one thing this doesn't capture is that some seldom used DirectX components were removed from the OS starting with Windows Vista. As long as your application doesn't make use of **Direct3D Retained Mode**, **DirectPlay Voice**, or **Visual Basic 6.0 DirectX interfaces** this should not be an issue.

For Direct3D 9 Windows games, it is worth going one step further...

```cpp
osv.dwMajorVersion = 6;  // Windows Vista / Server 2008 RTM
osv.dwMinorVersion = 0;
osv.wServicePackMajor = 0;

// Reuse mask from last test (equals test)

if ( fpVerifyVersionInfo( &osv,
  VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, mask ) )
{
  error("This program requires Windows Vista SP2, Windows Server 2008 SP2, or later\n");
}

osv.dwMajorVersion = 6;  // Windows Vista / Server 2008 SP1
osv.dwMinorVersion = 0;
osv.wServicePackMajor = 1;

// Reuse mask from last test (equals test)

if ( fpVerifyVersionInfo( &osv,
  VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, mask ) )
{
  error("This program requires Windows Vista SP2, Windows Server 2008 SP2, or later\n");
}
```

At this point we have excluded Windows Vista / Server 2008 RTM. This is useful because it ensures you already have the KB 940105 VA space fix, as well as the Direct3D 10.1 Runtime.

<strong>Windows XP:</strong> The sample code has been modified from the original posting to use Windows XP SP3 as the baseline instead of Windows XP SP2 as this was the last version of Windows XP supported with security updates.

<strong>Windows Vista:</strong> The sample code has been modified from the original posting to exclude both Windows Vista RTM and Windows Vista SP1 as this is the last version of Windows Vista supported with security updates.

<strong>DirectX 11 Games:</strong> The check above assumes you require DirectX 9.0c as your baseline. For newer games that use DirectX 11.0 as their baseline, the check should be >= Windows Vista SP2 if you use the techniques in <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3darticles/direct3d11-deployment">Direct3D 11 Deployment for Game Developers</a> to handle detection of KB971644, or use >= Windows 7 for simplicity.

<strong>Windows 7:</strong> Windows 7 Service Pack 1 is mandatory at this point in the Windows 7 lifecycle, so excluding support for Windows 7 RTM is strongly recommended. VS 2013 and VS 2015 do not support targeting Windows 7 RTM and the C++ REDIST requires Windows 7 Service Pack 1.

<strong>Windows 8:</strong> This check works as designed on Windows 8 for Win32 desktop applications. Windows 8 is officially version "6.2"

<strong>Windows 8.1:</strong> This check works as designed on Windows 8.1 for Win32 desktop applications. Windows 8.1 is officially version "6.3". Note that the ``GetVersion(Ex)`` API has been actively deprecated on Windows 8.1 and by default will still return "6.2". See this <a href="https://docs.microsoft.com/en-us/windows/desktop/w8cookbook/operating-system-version-changes-in-windows-8-1">link</a> and this [blog post](https://walbourn.github.io/manifest-madness/) for more details.

<strong>Windows 10:</strong> This check works as designed on Windows 10 for Win32 desktop applications. Windows 10 is officially version "10.0" (it was "6.4" in the original Windows 10 Technical Preview build 9841). Note that the ``GetVersion(Ex)`` API has been actively deprecated and by default will still return "6.2" or "6.3". With Windows 10 ``VerifyVersionInfo`` is also subject to the same manifest-based behavior as ``GetVersion(Ex)``--``IsWindows8_1OrGreater`` and ``IsWindows10OrGreater`` will both return FALSE on Windows 10 without a proper embedded manifest in the EXE. See this [blog post](https://walbourn.github.io/manifest-madness/) for more details.

<strong>Universal Windows Platform apps:</strong> There is a <a href="https://docs.microsoft.com/en-us/uwp/api/Windows.System.Profile.AnalyticsInfo#Windows_System_Profile_AnalyticsInfo_VersionInfo">Windows Runtime API</a> you should use for telemetry in the ``Windows.System.Profile`` namespace.

<strong>Windows 8.1 SDK / VS 2013:</strong> There is a new header <a href="https://docs.microsoft.com/en-us/windows/desktop/SysInfo/version-helper-apis">VersionHelpers.h</a> that provides similar 'you must be this high to ride this ride' checks as well. These helpers just use the same ``VerifyVersionInfo`` function I do above, but do so with implicit rather than explicit linking. That means the code won't work on Windows 9x/Windows ME like the code I wrote here would, but that's well below the supported OS level for either the Windows 8.1 SDK or the VS 2013 compiler anyhow.

<strong>Diagnostic Logs:</strong> If you are just trying to obtain a version number for a diagnostic log output, the best thing to do is just call ``GetVersion(Ex)`` and add the [compatibly manifest](https://walbourn.github.io/manifest-madness/) to your EXE. If you are in a scenario where you can't add the manifest, you can make use of WMI with the <a href="https://docs.microsoft.com/en-us/windows/desktop/CIMWin32Prov/win32-operatingsystem">Win32_OperatingSystem</a> class.

<strong>Windows 11:</strong> See [Windows SDK for Windows 11](https://walbourn.github.io/windows-sdk-for-windows-11) for details on Windows 11 OS version checks.

[source code](https://walbourn.github.io/download/oscheck_direct3d9.cpp)
