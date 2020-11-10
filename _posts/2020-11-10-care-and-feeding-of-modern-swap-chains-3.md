---
layout: post
title: Care and Feeding of Modern Swap Chains (part 3)
date: 2020-11-10 12:07
author: Chuck Walbourn
comments: true
categories: [direct3d]
---

In [part 1](https://walbourn.github.io/care-and-feeding-of-modern-swapchains/), I covered the split between "blt-style" and "flip-style" swap effects, and in particular the handling of gamma-correct rendering. In [part 2](https://walbourn.github.io/care-and-feeding-of-modern-swap-chains-2/) I addressed implementing MSAA. In this post I'll cover fullscreen rendering, which these days is actually a lot more complicated a topic than it first appears.
<!--more-->

# Fullscreen Exclusive (FSE)

Before I get into the details here, it's useful to step back a bit and understand the evolution of the PC display. Back in the 90s, computer monitors were [cathode-ray tubes](https://en.wikipedia.org/wiki/Cathode_ray_tube) (CRT)--yes, we shot electron beams directly at our heads for hours on end. These devices could support color output, but there were trade-offs for video memory and video bandwidth. Typically a Windows system at the time would be using 600x480x16 (that's *sixteen* colors, not 16-bit color), while games would want to use 320x200x256 (256 colors, i.e. '8-bit' color). This drove a lot of the early design decisions for DirectX in order to convince game developers that it was viable to move on from 32-bit DOS.

This was the original *Fullscreen Exclusive (FSE)* rendering mode. Windows would be running at some high-resolution, but low-color, like 640x480x16, 800x600x16, or 1024x768x16; and games would use DirectX APIs to switch the output resolution to 320x200x256 or 640x480x256.

FSE did mean you couldn't use your Windows applications at the same time, and monitors often had loud clicking noises as they changed resolutions, but it was a lot smoother than rebooting your PC to run a 32-bit DOS extender just to play a game. There were also problems where games might try to use a resolution that your monitor didn't support, which is where that "Press OK to keep this resolution or wait 15 seconds and we'll revert the setting" thing came from.

As PC video systems evolved to support 16-bit color and then 24/32-bit color, Windows was often using a higher-resolution mode that offered fewer colors and thus the resolution switch was still an important part of playing a game.

The other choice from FSE was "windowed" mode which just put your game into a standard Windows window with a title bar and border rendering at the normal Windows resolution. Now days, this has become a practical choice since Windows is using a high-quality resolution with lots of colors all the time.

# "Fake" Fullscreen (a.k.a. Borderless Windowed)

Fast-forward to the 00's and the CRT monitor was phasing out in favor of LCD or plasma displays. These were fundamentally different display systems. These monitors *emulate* all that craziness about resolutions, refresh rates, color-depths, etc. but in fact they always display the same native resolution. The monitor hardware has to scale all the content up or down to drive all the pixels on the screen. Games stuck to the same old pattern they had for CRTs, primarily to provide faster performance on low-end hardware by reducing the number of pixels they had to draw every frame.

This was also the beginning of the era of Massively-Multiplayer Online games (MMOs). Players wanted to use chat apps, voice apps, read websites, see desktop notifications, etc. all while playing the game. The classic "windowed" mode worked as an option for those with high-resolution displays, but the windows border was distracting for some. FSE also made using multi-monitor systems painful, as the game would flip in and out of FSE when you tried to use the secondary monitor--except for that rare game that actively used multiple displays.

In order to make the game interact more smoothly with the rest of the system, developers implemented *fake fullscreen* also known as *borderless windowed mode*. This means they would use a "windowed" rendering mode, set the hosting Win32 window to fill the whole screen (i.e. no border or title bar), and but still switch the resolution of the game's display. This resulted in an immersive experience, let you ALT-TAB to other Windows applications, worked with multiple displays, and generally offered the "best of both worlds".

A downside to "fake" fullscreen was a decrease in rendering performance compared to "FSE". Some multi-GPU systems also relied on switching to "FSE" to get their full performance benefit. From the developer's perspective, it was also just as complicated to implement as "fake" fullscreen as it was to implement "FSE", and many games offered both usually defaulting to "fake" fullscreen. Notably, this also relied on the display's scaling hardware for panel displays.

# "Immersive" Fullscreen

Since modern flat-panels displays look best at their 'native' resolution, a Windows PC is usually already using the optimal display resolution. With Windows 10 it's always using 32-bit color as 16-bit color is no longer supported except as an emulated appcompat setting.

Windows Store apps were therefore designed to never change the display resolution. "Immersive" mode here is just a windowed rendering mode maximized to full screen. This works well with the rest of the system for notifications, multi-tasking, multi-monitor displays, etc. There's also been a lot of optimization work to remove the difference in performance between "immersive fullscreen" and "classic FSE".

Implementation is very simple, but does it require a change in perspective on performance scaling. Historically game developers have changed the display resolution to reduce the number of pixels to render because the backbuffer is scaled as result. With "immersive fullscreen", you don't change the display resolution but you still have full control over the render target size to speed up rendering.

One approach would be to make the backbuffer on your swapchain smaller in response to your game "resolution" slider setting, and make use of ``DXGI_SCALING_STRETCH``. In this case, the Desktop Windows Compositor will scale up your content to fill the display size.

> This is where ``DXGI_SCALING_ASPECT_RATIO_STRETCH`` can really shine for UWP apps, but alas is not easily available for Win32 desktop apps.

Another approach is to have the backbuffer match the display resolution, and then you render to a smaller render-target. This leaves the scaling under the application control, which allows the developer to control when and how in the post-processing phase the content is scaled. You can then render UI/HUD elements at the 'native' resolution if desired over the scaled content.

Finally, you can choose to make use of DXGI overlays which let video hardware handle the scaling of the render-target, although this feature is mostly aimed at mobile and tablet devices. See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/uwp/gaming/multisampling--scaling--and-overlay-swap-chains).

# Emulated Fullscreen Exclusive (eFSE)

All this brings us to the latest "fullscreen" development. As discussed above, a lot has changed in the 25 years since the introduction of DirectX FSE. With Windows 10, FSE is being deprecated in favor of eFSE. When the application uses DXGI to switch into "fullscreen" state, it's actually getting changed into "immersive" fullscreen behind the scenes. In other words, the display resolution is *never* changed.

eFSE is enabled on Windows 10 for *all* DirectX 9 and DirectX 12 applications. They are enabled on an app-by-app basis for DirectX 10 / DirectX 11 under the label "Fullscreen Optimizations" See the [DirectX Developer Blog](https://devblogs.microsoft.com/directx/demystifying-full-screen-optimizations/) for more details.

For DirectX games aimed at Windows 7 as well as Windows 10, using the classic 'fake fullscreen' and/or FSE is a reasonable choice, but for Windows 10 only games you are better off just implementing "immersive fullscreen" directly.

# Variable refresh-rate displays

There's one more modern swap chain feature to mention. For most of the history of PC display systems, a 'vertical sync' (or vsync) was performed every frame at the "refresh rate" for the display (typically 60Hz). This is another example of flat-panel displays emulating the behavior of the old CRT. For a CRT, if you didn't draw fast enough, the pixels would fade away. For a LCD display, this never happens so it's not require you maintain a specific refresh rate for the display--although it does matter to the user that you keep rendering going fast enough that frames actually blend together smoothly.

High-end modern flat panels now support [Variable refresh rate](https://en.wikipedia.org/wiki/Variable_refresh_rate) through technologies like nVIDIA's G-Sync&trade; or AMD's Freesync&trade;. This is supported on Windows 10 via DXGI 1.5, and you guessed it, only supports 'flip-style' swap chains using borderless fullscreen window rendering.

See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/direct3ddxgi/variable-refresh-rate-displays), and the [DirectX Developer Blog](https://devblogs.microsoft.com/directx/unlocked-frame-rate-and-more-now-enabled-for-uwp/).

# Samples

* For my [directx-vs-templates](https://github.com/walbourn/directx-vs-templates) I implement "immersive fullscreen" for both Win32 and UWP. This uses the classic "ALT+Enter" hot-key combination to toggle. The DeviceResources [DX11](https://github.com/microsoft/DirectXTK/wiki/DeviceResources) / [DX12](https://github.com/microsoft/DirectXTK12/wiki/DeviceResources) implementation provides opt-in support for variable refresh-rate displays as well.

* **D3D12Fullscreen** for [Win32](https://github.com/microsoft/DirectX-Graphics-Samples/tree/master/Samples/Desktop/D3D12Fullscreen) or [UWP](https://github.com/microsoft/DirectX-Graphics-Samples/tree/master/Samples/UWP/D3D12Fullscreen) keeping in mind that DX12 is always using eFSE on Windows 10. This includes support for variable refresh rate displays. This sample also demonstrates scaling the rendering target for performance control.

<b>See also:</b> <a href="https://walbourn.github.io/anatomy-of-direct3d-12-create-device/">Anatomy of Direct3D 12 Create Device</a>, <a href="https://walbourn.github.io/anatomy-of-direct3d-11-create-device/">Anatomy of Direct3D 11 Create Device</a>, <a href="https://walbourn.github.io/hdr-lighting-and-displays/">HDR Lighting and Displays</a>
