---
layout: post
title: DirectX and UWP on Xbox Series X|S
date: 2022-05-20 23:51
author: Chuck Walbourn
comments: true
categories: [uwp, xbox]
---

A number of years ago, I wrote [DirectX and UWP on Xbox One](https://walbourn.github.io/directx-and-uwp-on-xbox-one/) to provide some details on how "Game Mode" worked for [UWP on Xbox One](https://docs.microsoft.com/windows/uwp/xbox-apps/) with respect to Direct3D. While the bulk of that article still applies, there have been a few changes recently with the release of the Xbox Series X\|S that warrant a new blog post.

<!--more-->

# Game Mode

The first thing to note is that "Game Mode" as a thing for UWP on PC Desktop has been deprecated as of [Windows 10, Version 1809](https://docs.microsoft.com/previous-versions/windows/desktop/gamemode/game-mode-portal). That said, the concept of "Game Mode" still applies to the Xbox where *expandedResources* specifically means "Runs with the CPU/GPU resources of a Game title instead of the resources of an App". The instructions in [original blog post](https://walbourn.github.io/directx-and-uwp-on-xbox-one/) all still apply when using [Xbox Developer Mode](https://docs.microsoft.com/windows/uwp/xbox-apps/devkit-activation).

# Direct3D Feature Levels

For Xbox One, DirectX 11 now supports 10.1 instead of 10.0 as of the March 2022 Xbox recovery. There are some additional capabilities exposed when running a UWP on Xbox Series X\|S.

 Mode | Xbox One | Xbox Series X\|S
 ---|---|---
 <b>App Mode</b> | DirectX 11 Feature Level 10.1<br /><br />DirectX 12 not supported* | DirectX 11 Feature Level 11.0<br /><br />DirectX 12 Feature Level 11.0
 <b>Game Mode</b> | DirectX 11 Feature Level 10.1<br /><br />DirectX 12 Feature Level 11.0 | DirectX 11 Feature Level 11.0<br /><br />DirectX 12 Feature Level 11.0

For DirectX 12, Shader Models 5.1 to 6.4 is supported.

 > `*` = Note that in Developer Mode, you can use WARP on DirectX 12 even in App Mode, but this is not supported for retail mode.

# Gaming Device Information

**Windows 10, Version 1709** introduced the [**GetGamingDeviceModelInformation**](https://docs.microsoft.com/windows/win32/api/gamingdeviceinformation/nf-gamingdeviceinformation-getgamingdevicemodelinformation) API which reports a "VID/PID" style platform identity marker at runtime. This is intended to detect which member of the Xbox family is currently being used for UWP on Xbox.

The originally defined Device IDs for ``vendorId==GAMING_DEVICE_VENDOR_ID_MICROSOFT`` are as follows:

deviceId | Value
---|---
GAMING_DEVICE_DEVICE_ID_NONE | 0
GAMING_DEVICE_DEVICE_ID_XBOX_ONE | 0x768BAE26
GAMING_DEVICE_DEVICE_ID_XBOX_ONE_S | 0x2A7361D9
GAMING_DEVICE_DEVICE_ID_XBOX_ONE_X | 0x5AD617C7
GAMING_DEVICE_DEVICE_ID_XBOX_ONE_X_DEVKIT | 0x10F7CDE3

As of the **April 2022** Xbox recovery, the following additional values are now reported:

deviceId | Value
---|---
GAMING_DEVICE_DEVICE_ID_XBOX_SERIES_S | 0x1D27FABB
GAMING_DEVICE_DEVICE_ID_XBOX_SERIES_X | 0x2F7A3DFF
GAMING_DEVICE_DEVICE_ID_XBOX_SERIES_X_DEVKIT | 0xDE8A5661

These symbols will be added to the enumeration in the next release of the Windows SDK, but for know you can use the following:

```cpp
#ifndef NTDDI_WIN10_NI
#define GAMING_DEVICE_DEVICE_ID_XBOX_SERIES_S static_cast<GAMING_DEVICE_DEVICE_ID>(0x1D27FABB)
#define GAMING_DEVICE_DEVICE_ID_XBOX_SERIES_X static_cast<GAMING_DEVICE_DEVICE_ID>(0x2F7A3DFF)
#define GAMING_DEVICE_DEVICE_ID_XBOX_SERIES_X_DEVKIT static_cast<GAMING_DEVICE_DEVICE_ID>(0xDE8A5661)
#endif
```

See the latest updates to the [SystemInfoUWP](https://github.com/microsoft/Xbox-ATG-Samples/tree/main/UWPSamples/System/SystemInfoUWP) sample on GitHub.

# 4K / 1440p

As before, you can create a swapchain at 1080p or 4K, and the console will scale as needed based on the user's display settings. With the updated GGDMI API, you can now properly support 4K on Xbox Series X, as well as make use of 1440p which is recommended for the Xbox Series S.

 ```cpp
#include "Gamingdeviceinformation.h"
...
GAMING_DEVICE_MODEL_INFORMATION info = {};
GetGamingDeviceModelInformation(&info);
if (info.vendorId == GAMING_DEVICE_VENDOR_ID_MICROSOFT)
{
    switch (info.deviceId)
    {
    case GAMING_DEVICE_DEVICE_ID_XBOX_ONE:
    case GAMING_DEVICE_DEVICE_ID_XBOX_ONE_S:
        // Keep swapchain at 1920 x 1080 which is what's sent
        // as the UWP window size.
        break;

    case GAMING_DEVICE_DEVICE_ID_XBOX_SERIES_S:
        m_outputWidth = 2560;
        m_outputHeight = 1440;
        break;

    case GAMING_DEVICE_DEVICE_ID_XBOX_ONE_X:
    case GAMING_DEVICE_DEVICE_ID_XBOX_ONE_X_DEVKIT:
    case GAMING_DEVICE_DEVICE_ID_XBOX_SERIES_X:
    case GAMING_DEVICE_DEVICE_ID_XBOX_SERIES_X_DEVKIT:
    default: // Forward compatibility
        m_outputWidth = 3840;
        m_outputHeight = 2160;
        break;
    }
}
 ```

 > Note that if your minimum supported version of Windows is set to something older than 10.0.16299, then see the code snippet in the [original blog post](https://walbourn.github.io/directx-and-uwp-on-xbox-one/) that details using this API via ``QueryOptionalDelayLoadedAPI``.

# HDR, DirectX Raytracing, etc.

For games looking to implement High-Dynamic Range (HDR), DirectX Raytracing (DXR), or other [DirectX Ultimate](https://devblogs.microsoft.com/directx/announcing-directx-12-ultimate/) features, contact the <a href="https://www.xbox.com/Developers/id">ID@Xbox program</a>.
