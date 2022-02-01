//
// This is the original source for this blog post. It is designed
// to ensure that the current OS is one that includes the
// DirectX 9.0c Runtime -and- is the most recent servicing update
// of the relevant OS.
//
// https://walbourn.github.io/whats-in-a-version-number
//
// For modern DirectX 11 games, the VersionHelpers.h test IsWindows7SP1OrGreater
// is all you should need.
//
// https://docs.microsoft.com/en-us/windows/win32/sysinfo/version-helper-apis
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//

#define UNICODE
#define _UNICODE

#include <windows.h>
#include <stdio.h>
#include <assert.h>

int main()
{
    HMODULE hMod = LoadLibraryW(L"kernel32");
    assert(hMod != 0);

    OSVERSIONINFOEXW osv = {};
    osv.dwOSVersionInfoSize = sizeof(osv);

    osv.dwMajorVersion = 5; // Windows XP SP3 or later as Service Pack 3 is a mandatory update
    osv.dwMinorVersion = 1;
    osv.wServicePackMajor = 3;
    osv.wServicePackMinor = 0;

    DWORDLONG mask = 0;

    typedef ULONGLONG(WINAPI* fpSetMask)(ULONGLONG, DWORD, BYTE);
    auto fpVerSetConditionMask = reinterpret_cast<fpSetMask>(GetProcAddress(hMod, "VerSetConditionMask"));

    if (fpVerSetConditionMask != 0)
    {
        mask = fpVerSetConditionMask(mask, VER_MAJORVERSION, VER_GREATER_EQUAL);
        mask = fpVerSetConditionMask(mask, VER_MINORVERSION, VER_GREATER_EQUAL);
        mask = fpVerSetConditionMask(mask, VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);
        mask = fpVerSetConditionMask(mask, VER_SERVICEPACKMINOR, VER_GREATER_EQUAL);
    }

    typedef BOOL(WINAPI* fpVerify)(LPOSVERSIONINFOEXW, DWORD, DWORDLONG);
    auto fpVerifyVersionInfo = reinterpret_cast<fpVerify>(GetProcAddress(hMod, "VerifyVersionInfoW"));

    if (!fpVerifyVersionInfo
        || !fpVerifyVersionInfo(&osv, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR, mask))
    {
        printf("This program requires Windows XP Service Pack 3 or later\n");
        return 1;
    }

    // Now we exclude Windows Server 2003 RTM
    osv.dwMajorVersion = 5;
    osv.dwMinorVersion = 2;
    osv.wServicePackMajor = 0;

    mask = 0;

    if (fpVerSetConditionMask != 0)
    {
        mask = fpVerSetConditionMask(mask, VER_MAJORVERSION, VER_EQUAL);
        mask = fpVerSetConditionMask(mask, VER_MINORVERSION, VER_EQUAL);
        mask = fpVerSetConditionMask(mask, VER_SERVICEPACKMAJOR, VER_EQUAL);
    }

    if (fpVerifyVersionInfo(&osv,
        VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, mask))
    {
        printf("This program requires Windows Server 2003 Service Pack 1 or later\n");
        return 1;
    }

    // At this point we know the OS already includes the DirectX 9.0c Runtime
    //
    // Only need DirectSetup / REDIST for any optional bits we might use like D3DX, XAUDIO2, XINPUT, XACT, etc.

    // Now we exclude Windows Vista / Server 2008 RTM to ensure we have the KB 940105 fix
    osv.dwMajorVersion = 6;
    osv.dwMinorVersion = 0;
    osv.wServicePackMajor = 0;

    // Reuse mask from last test

    if (fpVerifyVersionInfo(&osv,
        VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, mask))
    {
        printf("This program requires Windows Vista / Server 2008 Service Pack 2 or later\n");
        return 1;
    }

    // Now we exclude Windows Vista / Server 2008 SP1 as Service Pack 2 is a mandatory update
    osv.dwMajorVersion = 6;
    osv.dwMinorVersion = 0;
    osv.wServicePackMajor = 1;

    // Reuse mask from last test

    if (fpVerifyVersionInfo(&osv,
        VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, mask))
    {
        printf("This program requires Windows Vista / Server 2008 Service Pack 2 or later\n");
        return 1;
    }

    // Finally we exclude Windows 7 RTM as Service Pack 1 is a mandatory update
    osv.dwMajorVersion = 6;
    osv.dwMinorVersion = 1;
    osv.wServicePackMajor = 0;

    // Reuse mask from last test

    if (fpVerifyVersionInfo(&osv,
        VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, mask))
    {
        printf("This program requires Windows 7 Service Pack 1 or later\n");
        return 1;
    }

    printf("Success\n");

    return 0;
}