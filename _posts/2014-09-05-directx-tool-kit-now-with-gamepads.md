---
layout: post
title: DirectX Tool Kit - Now with GamePads
date: 2014-09-05 13:04
author: Chuck Walbourn
comments: true
categories: [input, xbox one]
---
The <strong>XInput</strong> API is almost trivial to use at first glance which is basically two simple C APIs with very simple parameters. There are, however, a number of subtleties that have crept in over the years, including the split between Windows 8 and previous releases. There is also a potential performance problem if you naively try to search for multiple gamepads that are not currently connected every frame due to the underlying overhead of device enumeration to look for newly connected gamepads. Also, while XInput was available on Xbox 360, the Xbox One makes use of a WinRT IGamePad API instead.
<!--more-->

At this point, it would be useful to have a nice abstraction to handle all this that you could code against while keeping your application's code elegant and simple to use. As usual, when looking for a design to start with, it turns out this problem was already nicely solved for C# developers with the XNA Game Studio **GamePad** class.

<h1>GamePad class</h1>

The September 2014 release of <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectX Tool Kit</a> includes a C++ version of the GamePad class. To make it broadly applicable, it makes use of XInput 9.1.0 on Windows Vista or Windows 7, XInput 1.4 on Windows 8.x, and IGamePad on Xbox One. It's a simple class to use, and it takes care of the nuanced issues above. It implements the same thumb stick deadzone handling system as XNA, which is covered in detail by Shawn Hargreaves in his blog entry "<a href="http://www.shawnhargreaves.com/blog/gamepads-suck.html">Gamepads suck</a>". The usage issue that continues to be the responsibility of the application is ensuring that you poll it fast enough to not miss user input, which mostly means ensuring your game has a good frame rate.

See the <a href="https://github.com/Microsoft/DirectXTK/wiki/GamePad">documentation wiki page</a> on the new class for details, and the <a href="https://github.com/Microsoft/DirectXTK/wiki/Game-controller-input">tutorial</a>.

<em>The headset audio features of XInput are not supported by the GamePad class. Headset audio is not supported by XInput 9.1.0, has some known issues in XInput 1.3 on Windows 7 and below, works a bit differently in XInput 1.4 on Windows 8, and is completely different again on the Xbox One platform. </em>

The GamePad class is supported on all the DirectX Tool Kit platforms: Win32 desktop applications for Windows Vista or later, Windows Store apps for Windows 8.x, and Xbox One. You can create and poll the GamePad class on Windows Phone 8.x as well, but since there's no support for gamepads on that platform it always returns 'no gamepad connected'.

<h1>Xbox One Controller</h1>

Support for the Xbox One Controller on Windows was announced by <a href="http://majornelson.com/2014/06/05/pc-drivers-for-the-xbox-one-controller-available-now/">Major Nelson</a> in June and drivers are now hosted on Windows Update, so using it is a simple as plugging it into a Windows PC via a USB cable (see the <a href="https://support.xbox.com/en-US/xbox-on-windows/accessories/connect-xbox-one-controller-to-pc">Xbox One support website</a>). The controller is supported through the XInput API as if it were an Xbox 360 Common Controller with the <em>View </em>button being reported as ``XINPUT_GAMEPAD_BACK``, and the <em>Menu</em> button being reported as ``XINPUT_GAMEPAD_START``. All the other controls map directly, as do the left and right vibration motors. The left and right trigger impulse motors cannot be set via XInput, so they are not currently accessible on Windows.

The Xbox One Wireless controller is not compatible with the <em>Xbox 360 Wireless Receiver for Windows</em>, so you have to use a USB cable to use it with Windows. Note also that it will unbind your controller from any Xbox One it is currently setup for, so you'll need to rebind it when you want to use it again with your console.

<strong>Update: </strong>DirectX Tool Kit is also hosted on <a href="https://github.com/Microsoft/DirectXTK">GitHub</a>.

<strong>Windows 10:</strong> There is a new WinRT API in the <a href="https://docs.microsoft.com/en-us/uwp/api/Windows.Gaming.Input">Windows.Gaming.Input</a> namespace for universal Windows apps. This API supports both the Xbox 360 Common Controller and the Xbox One controller, including access to the left/right trigger motors. The latest version of GamePad is implemented using this new API when built for Windows 10. Note that existing XInput-based Windows Store applications can link against <code>xinputuap.lib</code> which is an adapter for the new API for universal Windows apps--this adapter does not exist headset audio either.

<strong>Related:</strong> <a href="https://walbourn.github.io/xinput-and-windows-8-consumer-preview/">XInput and Windows 8</a>, <a href="https://walbourn.github.io/xinput-and-xaudio2/">XInput and XAudio2</a>
