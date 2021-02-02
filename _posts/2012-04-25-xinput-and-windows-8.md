---
layout: msdnpost
title: XINPUT and Windows 8
date: 2012-04-25 18:39
author: Chuck Walbourn
comments: true
categories: [audio, input, win8]
---
<em>Windows 8.x and Windows 10</em> include version 1.4 of the <a href="https://docs.microsoft.com/en-us/windows/desktop/xinput/programming-guide">XInput</a> API for use with Xbox Common Controller compatible game devices, and this API is fully supported for both Windows Store apps (including x86, x64, and Windows on ARM) and desktop Win32 applications. The full details of the differences compared to XInput 1.3 which shipped in the DirectX SDK (June 2010) release are addressed on <a href="https://docs.microsoft.com/en-us/windows/desktop/xinput/xinput-versions">Microsoft Docs</a>. The headers and libraries for Xinput 1.4 are included in the Windows 8.x/10 SDK. Windows 8 or later also includes an updated driver for these devices, <code>XUSB22.SYS</code>.

<!--more-->

<strong>REDIST:</strong> For XInput 1.4 on Windows 8.x, Windows 10, and Windows RT; no redistribution is required since XInput 1.4 is included with the OS. For XInput 9.1.0 on Windows Vista, Windows 7, Windows 8.x, or Windows 10, no redistribution is required since XInput 9.1.0 is included with the OS. For XInput 1.3 on any version of Windows, use the <a href="https://walbourn.github.io/not-so-direct-setup/">legacy DirectX SDK REDIST</a>.

Since Xinput version 1.4 is not available on Windows 7, Win32 desktop games that support older versions of Windows can use either XInput 1.3 or the still supported older XInput 9.1.0 which is included in Windows Vista, Windows 7, and Windows 8.

When building an application that is 'down-level' using headers in the Windows 8.x/10 SDK, be sure to explicitly select the correct 'minimum' ``_WIN32_WINNT`` value. For Windows 8, that is 0x0602 (which is the default when building code with Visual Studio 2012 and for all Windows Store apps). For Windows 7 use 0x0601, and for Windows Vista use 0x0600. Typically this is done as part of the project configuration via <em>Preprocessor Definitions</em>.

If you set ``_WIN32_WINNT`` correctly and try building with the Windows 8.0 SDK version of the <code>xinput.h</code> header, you will be using XInput 1.4 if set to 0x0602, or XInput 9.1.0 otherwise. If using XInput 1.4, you should link with <code>XINPUT.LIB</code>. If using XInput 9.1.0, link with <code>XINPUT9_1_0.LIB</code> instead.

If your usage of XInput is limited to basic gamepad functionality via <code>XInputGetState</code> and <code>XInputSetState</code>, then XInput 9.1.0 may be all the functionality you require and is supported on a broad range of Windows OSes without the need to use the DirectSetup redistribution package. A few things to note about XInput 9.1.0 are that <code>XInputGetCapabilities</code> returns a fixed set of values regardless of the attached device (notably including the subtype), and this version of XInput does not support headset audio functionality.

The following code will compile using all three versions of XInput:

```cpp
#include <xinput.h>

XINPUT_STATE state = {};

if (XInputGetState(0, &state) == ERROR_SUCCESS)
{
    // Controller is connected
    if ( state.Gamepad.wButtons & XINPUT_GAMEPAD_A )
    {
        // Button A is pressed
    }

    XINPUT_VIBRATION motor = {};
    if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
    {
        motor.wLeftMotorSpeed = state.Gamepad.bLeftTrigger << 8;
    }

    if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
    {
        motor.wRightMotorSpeed = state.Gamepad.bRightTrigger << 8;
    }

    XInputSetState(0, &motor);
}
else
{
    // Controller is not connected, shouldn't recheck it for a few seconds
}
```

If using the XInput 1.3 solution, You should follow the instructions on <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">Microsoft Docs</a> to use the Windows 8.x/10 SDK headers and libraries where possible and explicitly link to the <code>DXSDK_DIR</code> for the headers where you need older versions to support older versions of Windows. (see "<a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a>").

> **NOTICE:** The *DirectX SDK*, the *DirectX End-User Runtime*, and the files for the *DirectX End-User Web Installer* were all SHA-1 signed, and therefore have been removed from Microsoft Downloads per [this policy](https://techcommunity.microsoft.com/t5/windows-it-pro-blog/sha-1-windows-content-to-be-retired-august-3-2020/ba-p/1544373). Therefore, it's best to avoid using XInput 1.1, 1.2, or 1.3 entirely.

In a future <a href="https://walbourn.github.io/xinput-and-xaudio2/">post</a>, I address the details of using XInput 1.4's audio features, and how to implement similar behavior down-level using XInput 1.3. XInput 9.1.0 doesn't support audio features.

<strong>Note:</strong> The <a href="https://walbourn.github.io/windows-sdk-7-1/">Windows 7.1 SDK</a> includes the <code>xinput.h</code> header and <code>xinput.lib</code> import library for the the Xinput 9.1.0 version as well. XInput 9.1.0 can be deployed on Windows XP using the legacy DirectX SDK's REDIST (aka DirectSetup).

<strong>Windows Server:</strong> Note that XInput is not included in Windows Server 2012. XInput 9.1.0 is also not present on Windows Server 2008 or 2012.

<strong>Xbox One Controller:</strong> The Xbox One controller is not supported by the ``XUSB21.SYS`` (Windows 7) or ``XUSB22.SYS`` (Windows 8.x) driver. There is a ``X1USB1.SYS`` driver <a href="http://majornelson.com/2014/06/05/pc-drivers-for-the-xbox-one-controller-available-now/">now available</a> which does support the Xbox One Controller for XINPUT when using a micro-USB cable--the Xbox One controller is not compatible with the <em>Xbox 360 Wireless Receiver for Windows</em>.

<strong>Windows 10:</strong> To continue to use XInput 1.4 with Universal Windows Platform (UWP) apps, be sure to link with <code>xinputuap.lib</code> rather than <code>xinput.lib</code>. Alternatively, you can make direct use of the new <a href="https://docs.microsoft.com/en-us/uwp/api/Windows.Gaming.Input">Windows.Gaming.Input</a> API or the <a href="https://walbourn.github.io/directx-tool-kit-now-with-gamepads/">GamePad</a> class in <a href="https://github.com/Microsoft/DirectXTK">DirectX Tool Kit</a>.

Also note that for Windows 10, input focus is automatic like it is with mouse and keyboard. For this reason,  using ``XInputEnable`` when building with ``_WIN32_WINNT`` set to ``0x0A00`` will generate a deprecation compiler warning.

<strong>Related:</strong> <a href="https://github.com/walbourn/directx-sdk-samples/tree/master/XInput">XInput Win32 Samples</a>, <a href="https://walbourn.github.io/directx-tool-kit-now-with-gamepads/">DirectX Tool Kit - Now with GamePads</a>
