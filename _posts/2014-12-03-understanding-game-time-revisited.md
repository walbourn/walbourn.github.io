---
layout: post
title: Understanding Game Time Revisited
date: 2014-12-03 12:43
author: Chuck Walbourn
comments: true
categories: [general]
---
For as simple a task as it seems, tracking time in Windows games is full of potential pitfalls. There are a number of different ways to do it, and the naive ones seem to work fine initially but then you have all kinds of problems later.
<!--more-->

Case in point: the Visual Studio 2012 templates for Windows Store apps for Windows 8.0 and Windows phone 8.0. The initial version of the Direct3D game template included a simple WinRT <code>BasicTimer</code> class. This uses <code>QueryPerformanceCounter</code> to track delta and elapsed time per frame. This variable-length timing approach is very common in games, and is used by the legacy DXUT framework as well. This implementation does suffer from two major problems, however. First, it makes the mistake of using a <code>float</code> rather than a <code>double</code> to track accumulated elapsed time (see <a href="https://randomascii.wordpress.com/2012/02/13/dont-store-that-in-a-float/">Bruce Dawson's blog</a> for why this is a classic blunder). Second, it does not support fixed-step gaming time which is often easier and can be more robust.

XNA Game Studio demonstrated that fixed-step timing can be a lot more useful, which was the default for the framework. See Shawn Hargreaves posts <a href="http://www.shawnhargreaves.com/blog/understanding-gametime.html">Understanding GameTime</a> and <a href="http://www.shawnhargreaves.com/blog/game-timing-in-xna-game-studio-2-0.html">Game timing in XNA Game Studio 2.0</a>.

For the Visual Studio 2013 templates for Windows Store apps for Windows 8.1 and Windows phone 8.1, they no longer include <code>BasicTimer</code> and instead they have the C++ <code>StepTimer</code> class. This class also uses <code>QueryPerformanceCounter</code>, but supports both variable-length and fixed-step timing. It makes use of 64-bit accumulation for elapsed time, and returns time in units of seconds as a <code>double</code>. The timer also ensures that there's an upper-bound to the maximum delta since debugging or pausing can otherwise result in huge time jumps that are not well handled by game code. As an added bonus, since it's no longer a WinRT class you can use it for Win32 desktop C++ programs too (with a minor switch of basic types).

```cpp
#include <windows.h>
#include "StepTimer.h"

DX::StepTimer s_timer;

void Update(DX::StepTimer const& timer)
{
    float delta = float(timer.GetElapsedSeconds());
    // Do your game update here
}

void Render()
{
    // Do your frame render here
}

void Tick()
{
    s_timer.Tick([&]()
    {
        Update(s_timer);
    });
    Render();
}
```

By default <code>StepTimer</code> uses variable-length timing, but you can easily make it used fixed-step timing instead (for example 60 times a second):

```cpp
timer.SetFixedTimeStep(true);
timer.SetTargetElapsedSeconds(1.f / 60.f);
```

For each frame of your game, you'd call <code>Tick</code> once. This will call <code>Update</code> as many times as needed to ensure you are up-to-date, and then call <code>Render</code> once.

For pause/resume behavior, be sure to make use of <code>ResetElapsedTime</code>.

See this <a href="https://github.com/Microsoft/DirectXTK/wiki/StepTimer">topic page</a> for more details.

<strong>Windows Store apps/Windows phone:</strong> If your application is still using <code>BasicTimer</code>, you should consider updating your code to use <code>StepTimer</code> instead. It has no dependencies on Windows 8.1 or Windows phone 8.1.

<strong>Templates: </strong>This class is in use for the stock DirectX app templates in Visual Studio 2013 or later, and in the Xbox One XDK templates. I also make use of it in all the <a href="https://github.com/walbourn/directx-vs-templates">directx-vs-templates</a>.

<h1>QueryPerformanceCounter vs. RDTSC</h1>

The Intel Pentium <code>rdtsc</code> instruction was introduced as a way to reliably get processor cycle counts for profiling and high-resolution timing. Early games used this instruction extensively to get and compute game time. Compared to older techniques like hooking the timer interrupt, this was much better. Over time, however, problems have cropped up. The transition to multiple-core computing was a problem in the Windows XP era when the AMD Athalon X2 did not synchronize the <code>rdtsc</code> clock between the cores (see <a href="https://support.microsoft.com/kb/909944/">KB 909944</a>), breaking a common assumption that time would always be monotonically increasing (i.e. not go backwards!). Aggressive power management schemes like Intel's <a href="http://en.wikipedia.org/wiki/SpeedStep">SpeedStep</a> also broke another basic assumption that the CPU processor frequency (required to convert a processor cycle count into time units of seconds) was fixed. In fact, this is another version of age-old problem with PC games that first lead to the <a href="http://en.wikipedia.org/wiki/Turbo_button">"Turbo button"</a>.

The work around to all these problems is the Win32 API <code>QueryPerformanceCounter</code> and <code>QueryPerformanceFrequency</code>. See <a href="https://docs.microsoft.com/en-us/windows/desktop/SysInfo/acquiring-high-resolution-time-stamps">Acquiring high-resolution time stamps</a> on Microsoft Docs for more details and recommendations.

<em>Note that the main issue game developers have hit switching from <code>rdtsc</code> to QPC is that <code>rdtsc</code> was so cheap that they called it tens of thousands of time a frame, where QPC is a system call that can be a bit slower and potentially relies on some other hardware component in the system to get a steady clock result. The best solution here is to try to centralize your delta and elapsed time computation so you don't feel the need to recompute the delta more than a few times per frame.</em>

<strong>Windows RT/Windows phone: </strong>The ARM instruction <code>rdpmccntr64</code> is not guaranteed to be sync'd between cores, and <code>rdtsc</code> is not supported for this platform. Use <code>QueryPerformanceCounter</code>.

<h1>C++11 <chrono></h1>

With C++11's ``<chrono>`` header you may well be tempted to go with the 'standards-based' solution and use <code>high_precision_clock</code>. Unfortunately, the VS 2012 and VS 2013 implementations of both <code>high_precision_clock</code> and <code>steady_clock</code> are not based on <code>QueryPerformanceCounter</code>, and instead use <code>GetSystemTimeAsFileTime</code> which is not nearly as high-precision as you'd expect--this is fixed in <a href="https://walbourn.github.io/visual-studio-2015-rtm/">Visual Studio 2015</a> or later.

<h1>GetTickCount</h1>

If you don't really need a high-precision timer and instead can handle a resolution of 10 to 16 milliseconds, then <code>GetTickCount</code> may be a good option which returns the number of milliseconds since the system was started. Note that you should really use <code>GetTickCount64</code> (requires Windows Vista or later) instead to avoid potential overflow problems. See <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ms724411.aspx">MSDN</a>.

<strong>Xbox One:</strong> The Xbox One XDK and Xbox One ADK Direct3D game templates also made use of <code>BasicTimer</code>. As of the September 2014 version, they now use <code>StepTimer</code> instead.

The source file is subject to the <a href="http://opensource.org/licenses/MIT">MIT license</a> and is available on <a href="https://github.com/walbourn/directx-vs-templates/blob/master/d3d11game_uwp/StepTimer.h">GitHub</a>
