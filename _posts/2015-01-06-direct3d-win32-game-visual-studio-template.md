---
layout: msdnpost
title: Direct3D Win32 Game Visual Studio template
date: 2015-01-06 04:00
author: Chuck Walbourn
comments: true
categories: [direct3d, uwp, visualc]
---
For people new to DirectX development, <a href="https://docs.microsoft.com/en-us/previous-versions/windows/apps/hh452744(v=win.10)">Microsoft Docs</a> provides numerous tutorials for writing Windows Store apps, Windows phone apps, and Universal apps which all begin with creating a new project using a Visual Studio template built into to VS 2012 or VS 2013. For people targeting Win32 desktop (i.e. when developing on or for Windows 7), however, there's no "DirectX" project template to be found in Visual Studio. Instead, you have to use the generic Win32 project and then add support for Direct3D such as is done with the <a href="https://github.com/walbourn/directx-sdk-samples/tree/master/Direct3D11Tutorials">Direct3D Win32 tutorial</a>.
<!--more-->

Ideally, I'd like a Win32 desktop project template that looks similar to the other C++ DirectX templates as a common starting point for some tutorials and other explanatory posts. And so, here it is! This is a Visual Studio extension for VS 2013 Pro, VS 2013 Premium, VS 2013 Ultimate, or VS 2013 Community which installs a <em>Direct3D Win32 Game</em> project template for <em>Visual C++</em>.

<strong>VS Express for Windows Desktop:</strong> I recommend taking a look at the <a href="http://www.visualstudio.com/en-us/news/vs2013-community-vs.aspx">VS 2013 Community edition</a> if you don't have the budget for purchasing a license for the VS 2013 Pro+ editions.

<strong>DirectX 12:</strong> The details of the Direct3D 12 versions of Direct3D Win32 Game is different than the Direct3D 11 version since the APIs are quite different, but it's the same design. See <a href="https://github.com/Microsoft/DirectXTK12/wiki/The-basic-game-loop">this page</a> for a more detailed overview.

<strong>Related:</strong> <a href="https://walbourn.github.io/direct3d-game-visual-studio-templates-redux/">Direct3D Game Visual Studio templates (Redux)</a>

<h1>Using the VSIX</h1>

<strong>To Install</strong>, launch <code>Direct3DWin32Game.vsix</code> on a system with VS 2013 installed. If VS 2013 was already open, exit and restart it.

<strong>To Uninstall</strong>, in VS 2013 go to <em>Tools / Extensions and Updates...</em> then uninstall "Direct3DWin32Game". You then restart VS 2013.
<h1>Creating a new project</h1>
To create a new project, use <strong>File / New -> Project...</strong>

<a href="https://raw.githubusercontent.com/walbourn/walbourn.github.io/master/images/4380.newproject.png"><img src="https://raw.githubusercontent.com/walbourn/walbourn.github.io/master/images/4380.newproject.png" alt="" border="0" /></a>

When finished, you have a Win32 desktop app project that is ready to use for <a href="https://walbourn.github.io/getting-started-with-direct3d-11/">learning Direct3D 11</a> on Windows 7 or Windows 8.x. For those familiar with the existing "DirectX App" VS templates or <em>XNA Game Studio</em>, it has a similar structure with a <code>Game</code> class with methods like <code>Render</code>, <code>Update</code>, and <code>Clear</code>. Search for <strong><code>TODO</code></strong> for hints as to where to add your code.

<h1>Template overview</h1>

The project has the following properties:

<ul>
	<li>It creates a window, <a href="https://walbourn.github.io/anatomy-of-direct3d-11-create-device/">Direct3D 11 device</a>, and swap chain with depth buffer. This supports both DirectX 11.0 and DirectX 11.1 runtime systems. Debug configurations enable the <a href="https://walbourn.github.io/direct3d-sdk-debug-layer-tricks/">Direct3D debug device</a> with some additional debugging features enabled.</li>
	<li>By default it supports all possible <a href="https://walbourn.github.io/direct3d-feature-levels/">Direct3D feature levels</a> from 9.1 to 11.1.</li>
	<li>The default swapchain format is BGRA 8-bit UNORM with a D24S8 depth buffer.</li>
	<li>The default is for <code>Game::Clear</code> to render a classic "Cornflower blue" screen.</li>
	<li>This project makes use of <a href="https://walbourn.github.io/understanding-game-time-revisited/">StepTimer</a> calling the <code>Game::Update</code> method as needed to update the game state, and defaults to variable-time steps.</li>
	<li>The application handles resizing--the smallest window allowed is 320 x 200, defaulting to 800 x 600 or whatever is returned by <code>Game::GetDefaultSize</code>. When the window is resized, <code>Game::OnWindowSizeChanged</code> is called which in turn calls <code>Game::CreateResources</code> in order update the swap chain, re-create any window-sized dependent resources like the depth buffer, and reset the default viewport.</li>
</ul>

The project template makes some simplifying assumptions:

<ul>
	<li>If the window is minimized, <code>Game::OnSuspending</code> is called (same as if a power management state is encountered).</li>
	<li>No support for either 'exclusive' full-screen or 'fake' full-screen.</li>
	<li>It does not have any handling of input (keyboard/mouse), which you can add by modifying the <code>WndProc</code> in <code>Main.cpp</code>. You can easily add support for the Xbox Common Controller gamepad using <em>DirectX Tool Kit</em>'s <a href="https://walbourn.github.io/directx-tool-kit-now-with-gamepads/"><code>GamePad</code> class</a>.</li>
</ul>

Some additional notes:

<ul>
	<li>This makes use of <code>Microsoft::WRL::ComPtr</code> as a <a href="https://docs.microsoft.com/en-us/cpp/windows/wrl/comptr-class">smart-pointer</a> to manage the lifetime of the COM objects.</li>
	<li>It makes use of <a href="https://walbourn.github.io/dual-use-coding-techniques-for-games-part-1/">C++ Exception handling</a> for errors, including the <code>DX::ThrowIfFailed</code> helper present in the other DirectX templates.</li>
	<li>The modules default to using the <code>DirectX</code> namespace to simplify use of <a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a> or other helper libraries like <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectX Tool Kit</a>. Following good C++ coding practice, you should use fully qualified names in the headers (i.e. in <code>Game.h</code>).</li>
	<li>If <code>Game::Present</code> detects as a device-removed or device-reset case, it will call <code>Game::OnDeviceLost</code> which releases all Direct3D objects and then calls <code>Game::CreateDevice</code> and <code>Game::CreateResources</code> again to re-create them.</li>
	<li>COM is initialized using a multi-threading model to simplify use of Windows Imaging Component (WIC) or XAudio2.</li>
	<li>The project sets <a href="https://docs.microsoft.com/en-us/windows/desktop/WinProg/using-the-windows-headers">``_WIN32_WINNT`` to 0x0600</a> in pch<code>.h</code> to support Windows Vista, Windows 7, or Windows 8.x. Set this to 0x0601 to require Windows 7 or later (i.e. you don't want to deal with <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3darticles/direct3d11-deployment">Windows Vista Direct3D 11 deployment</a>), or 0x0602 to require Windows 8.0 or later (so you can rely on <a href="https://walbourn.github.io/xaudio2-and-windows-8/">XAudio 2.8</a> or <a href="https://walbourn.github.io/xinput-and-windows-8/">XInput 1.4</a>).</li>
	<li>The project includes a complete embedded <a href="https://walbourn.github.io/manifest-madness/">manifest</a>.</li>
	<li>The project supports both Win32 (32-bit) and x64 native configurations (Debug and Release).</li>
</ul>

<h1>Adding DirectX Tool Kit</h1>

The basic project template is self-contained. If you want to make use of <em>DirectX Tool Kit</em> with this template, there are two ways to add it:

<h2>Use NuGet</h2>

Go to <strong>Project / </strong><strong>Manage NuGet Packages...</strong>

Search for "DirectX Tool Kit" online and select the package with <strong>Id: directxtk_desktop_2013</strong> (use the latest one which is 2014.11.24.2 at this time; if you have an older version you can update it using the NuGet interface)

<a href="https://raw.githubusercontent.com/walbourn/walbourn.github.io/master/images/8546.nuget.png"><img src="https://raw.githubusercontent.com/walbourn/walbourn.github.io/master/images/8546.nuget.png" alt="" border="0" /></a>

<h2>Use Project-to-project references</h2>

Follow the directions given on the <a href="https://github.com/Microsoft/DirectXTK/wiki/DirectXTK
">GitHub</a> site under <strong>Adding to a VS solution</strong> with the <code>DirectXTK_Desktop_2013.vcxproj</code> project, and adding the appropriate <em>Additional Include Directories </em>property for all platforms & configurations.

<strong>Note:</strong> This applies to adding use of <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a>, <a href="http://go.microsoft.com/fwlink/?LinkID=324981">DirectXMesh</a>, <a href="http://go.microsoft.com/fwlink/p/?LinkId=271568">Effects 11</a>, and/or <a href="http://go.microsoft.com/fwlink/?LinkID=512686">UVAtlas</a> to the project as well.

<h2>Adding DirectX Tool Kit headers</h2>

Edit the pch<code>.h</code> file in the project and add the following lines at the end:

```cpp
#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "DirectXHelpers.h"
#include "Effects.h"
#include "GamePad.h"
#include "GeometricPrimitive.h"
#include "Model.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
#include "WICTextureLoader.h"
```

Then add the following line near the top of <code>Game.cpp</code> after the existing <code>using namespace</code> statement to make it easier to use <a href="http://www.shawnhargreaves.com/blog/simplemath-a-simplified-wrapper-for-directxmath.html">SimpleMath</a> in your code.

```cpp
using namespace DirectX::SimpleMath;
```

<h1>Windows Store 8.1 / Windows phone 8.1 / Universal apps</h1>

You can get a similar "empty" starting project creating a new <strong>DirectX App</strong> project, removing/deleting all files under the <code>Content</code> folder and then replacing them with these two files:

```cpp
// Game.h
#pragma once

#include "..\Common\DeviceResources.h"
#include "..\Common\StepTimer.h"

namespace DXTKApp1 // TODO: Change to match project namespace
{
  class Game
  {
    public:
    Game(const std::shared_ptr<DX::DeviceResources>& deviceResources);
    void Update(DX::StepTimer const& timer);
    void Render();
    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();
    void ReleaseDeviceDependentResources();

  private:
    // Cached pointer to device resources.
    std::shared_ptr<DX::DeviceResources> m_deviceResources;

    // Direct3D Objects (cached)
    D3D_FEATURE_LEVEL m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device2> m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext2> m_d3dContext;
  };
}
```

```cpp
// Game.cpp
#include "pch.h"
#include "Game.h"

#include "..\Common\DirectXHelper.h"

using namespace DXTKApp1; // TODO: Change to match project namespace

using namespace DirectX;
using namespace Windows::Foundation;

Game::Game(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
m_deviceResources(deviceResources)
{
  CreateDeviceDependentResources();
  CreateWindowSizeDependentResources();
}

void Game::Update(DX::StepTimer const& timer)
{
  float elapsedTime = float(timer.GetElapsedSeconds());

  // TODO: Add your game logic here
  elapsedTime;
}

void Game::Render()
{
  // TODO: Add your rendering code here
}

void Game::CreateDeviceDependentResources()
{
  m_featureLevel = m_deviceResources->GetDeviceFeatureLevel();
  m_d3dDevice = m_deviceResources->GetD3DDevice();
  m_d3dContext = m_deviceResources->GetD3DDeviceContext();

  // TODO: Initialize device dependent objects here (independent of window size)
}

void Game::CreateWindowSizeDependentResources()
{
  // TODO: Initialize windows-size dependent objects here
}

void Game::ReleaseDeviceDependentResources()
{
  m_d3dDevice.Reset();
  m_d3dContext.Reset();

  // TODO: Add Direct3D resource cleanup here
}
```

After that, update the ``*Main.cpp/.h`` files to use the new <code>Game</code> class rather than <code>Sample3DSceneRenderer</code>, and remove <code>SampleFpsTextRenderer</code> usage. Remember to update the <code>DXTKApp1</code> namespace in both <code>Game.cpp/.h</code> files to match that in the rest of the project.

You can use NuGet (Id: <em>directxtk_windowsstore_8_1</em> or <em>directxtk_windowsphone_8_1</em>) or project-to-project references (<code>DirectXTK_Windows81.vcxproj</code> or <code>DirectXTK_WindowsPhone81.vcxproj</code>) to add <em>DirectX Tool Kit.</em>

<strong>DirectX Tool Kit: </strong>This template is used extensively in the <a href="https://github.com/Microsoft/DirectXTK/wiki/Getting-Started">DirectX Tool Kit tutorial series</a>.

<strong>GitHub: </strong>The files for the template are also hosted on <a href="https://github.com/walbourn/directx-vs-templates">GitHub</a>.

<strong>Download:</strong> <a href="https://github.com/walbourn/directx-vs-templates/raw/master/VSIX/Direct3DWin32Game.vsix">Direct3DWin32Game.vsix</a> (VS 2013), <a href="https://github.com/walbourn/directx-vs-templates/raw/master/VSIX/Direct3DUWPGame.vsix">Direct3DUWPGame</a> (VS 2015 for both Win32 and UWP)
