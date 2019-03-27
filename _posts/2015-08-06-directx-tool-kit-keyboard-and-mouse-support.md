---
layout: msdnpost
title: DirectX Tool Kit - Keyboard and Mouse support
date: 2015-08-06 12:08
author: Chuck Walbourn
comments: true
categories: [github, win10, win8]
---
The <a href="https://walbourn.github.io/directx-tool-kit-now-with-gamepads/">GamePad</a> abstraction in <em>DirectX Tool Kit</em> was designed to simplify implementing game controller input across the spectrum of platforms supported by <em>DirectX Tool Kit</em>: Windows desktop, Xbox One, Windows 8 Store, and now universal Windows Apps for Windows 10. In a similar vein, the July 2015 release of <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectX Tool Kit</a> includes two new classes for handling keyboard and mouse input across Windows desktop, Windows 8 Store, and universal Windows apps for Windows 10.
<!--more-->

<h1>Keyboard</h1>

The <code>Keyboard</code> class is as usual based on the XNA Game Studio design, with the primary difference being that I needed to use a singleton rather than a static class. As with the XNA Game Studio class, this is intended for using the keyboard as a 'game controller' mapping keys to game input events. To support full text input for chat or text editing, you should make use of the underlying platform's keyboard support to fully handle international input. Integration of the Keyboard class is slightly more complicated than GamePad in that after creating the class instance, you need to make the appropriate calls from either your Win32 message pump for keyboard messages in Windows desktop apps, or you need to provide your application's CoreWindow so that Keyboard can register for the needed callbacks.

For Windows desktop applications, Keyboard takes input from <code>WM_KEYUP</code>, <code>WM_KEYDOWN</code>, <code>WM_SYSKEYUP</code>, and <code>WM_SYSKEYDOWN</code> Win32 messages. For Windows 8 Store and universal Windows apps, it makes use of <code>CoreDispatcher::AcceleratorKeyActivated</code>. As with XNA Game Studio, the <code>Keyboard::State</code> object encodes the virtual keys (rather than scan codes). This works well for most key combinations, but this is a bit quirky when handling Left vs. Right Shift keys (details in the class documentation).

The abstraction makes writing keyboard-based controls quite simple and portable across the supported platforms:

```cpp
void Game::Update(DX::StepTimer const& timer)
{
  auto kb = m_keyboard->GetState();

  if (kb.Up || kb.W) move.y += 1.f;     

  if (kb.Down || kb.S) move.y -= 1.f;

  if (kb.Left || kb.A) move.x += 1.f;

  if (kb.Right || kb.D) move.x -= 1.f;
}
```

See the <a href="https://github.com/Microsoft/DirectXTK/wiki/Keyboard">documentation wiki page</a> on the new class for details, and the related <a href="https://github.com/Microsoft/DirectXTK/wiki/Mouse-and-keyboard-input">tutorial</a>.

<h1>Mouse</h1>

The basics of the <code>Mouse</code> class are borrowed from XNA Game Studio, but is also singleton rather than a static class as well as having explicit support for a 'relative' or 'mouse-look' input mode. Integration of the Mouse class is slightly more complicated than GamePad in that you need to make the appropriate calls from either your Win32 message pump for mouse messages in Windows desktop apps, or you need to provide your application's CoreWindow so that Mouse can register for the needed callbacks.

For Windows desktop applications, Mouse uses <code>WM_MOUSEMOVE</code>, <code>WM_LBUTTONDOWN</code>, <code>WM_MOUSEWHEEL</code>, etc. events for handling the default 'absolute' mouse position mode. When in the 'relative' mode, it uses <code>WM_INPUT</code> per the <a href="https://docs.microsoft.com/en-us/windows/desktop/DxTechArts/taking-advantage-of-high-dpi-mouse-movement">Taking Advantage of High-Definition Mouse Movement</a> article.

For Windows 8 Store and universal Windows apps, Mouse makes use of the standard <code>CoreWindow::PointerMoved</code>, <code>CoreWindow::PointerPressed</code>, etc. events for handling the default 'absolutely' mouse position mode per <a href="https://docs.microsoft.com/en-us/previous-versions/windows/apps/hh994931(v=win.10)">Responding to touch input (DirectX and C++)</a>. For these platforms, the Mouse class also handles the conversion of DIPs to pixels, so be sure to call <code>SetDPI</code> appropriately. When in 'relative' mode, it uses <code>CoreWindow::MouseMoved</code> per <a href="https://docs.microsoft.com/en-us/previous-versions/windows/apps/hh994925(v=win.10)">Developing mouse controls (DirectX and C++)</a>.

The abstraction makes implementing mouse controls simple and reasonably portable between the supported platforms:

```cpp
void Game::Update(DX::StepTimer const& timer)
{
  auto state = g_mouse->GetState();

  if (state.positionMode == Mouse::MODE_RELATIVE)
  {
    // state.x and state.y are relative values; system cursor is not visible
  }
  else
  {
    // state.x and state.y are absolute pixel values; system cursor is visible
  }

  tracker.Update(state);

  if (tracker.leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
  {
    mouse->SetMode(Mouse::MODE_RELATIVE);
  }
  else if (tracker.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
  {
    mouse->SetMode(Mouse::MODE_ABSOLUTE);
  }
}
```

See the <a href="https://github.com/Microsoft/DirectXTK/wiki/Mouse">documentation wiki page</a> on the new class for details, and the related <a href="https://github.com/Microsoft/DirectXTK/wiki/Mouse-and-keyboard-input">tutorial</a>.

<strong>DirectInput:</strong> Developers are strongly discouraged from using legacy DirectInput for handling keyboard and mouse processing as far back as Windows XP. DirectInput should really only be used for supporting legacy HID game controllers and joysticks.
