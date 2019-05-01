---
layout: msdnpost
title: Direct3D Game Visual Studio templates (Redux)
date: 2015-12-17 12:45
author: Chuck Walbourn
comments: true
categories: [direct3d, uwp, visual]
---
Back in <a href="https://walbourn.github.io/direct3d-win32-game-visual-studio-template/">January</a>, I released a <strong>D3D11Win32Game</strong> Visual Studio 2013 template for Win32 desktop development primarily to support my <a href="https://github.com/Microsoft/DirectXTK/wiki/Getting-Started">DirectX Tool Kit tutorials</a>. I modeled it after the basic template that we ship with the Xbox One XDK that consist of a <code>Game</code> class which sets up a device, swap chain, and timed rendering loop. I've since updated the templates on <a href="https://github.com/walbourn/directx-vs-templates">GitHub</a> and now have versions for VS 2015, for the Universal Windows Platform, for Direct3D 12, and versions with the <code>DeviceResources</code> abstraction that is used in the official Windows Store and UWP templates.
<!--more-->

<strong>VS Express users:</strong> I recommend taking a look at the VS Community edition which supports Windows desktop development if you don't have the budget for purchasing a license for the Pro+ editions

<h1>Using the VSIX</h1>

<strong>To install</strong>: VS 2013 users should run <a href="https://github.com/walbourn/directx-vs-templates/raw/master/VSIX/Direct3DWin32Game.vsix">Direct3DWin32Game.vsix</a> and VS 2015 / VS 2017 / VS 2019 users should run <a href="https://github.com/walbourn/directx-vs-templates/raw/master/VSIX/Direct3DUWPGame.vsix">Direct3DUWPGame.vsix</a>. These packages install all the templates supported for that version of Visual Studio under the "Visual C++" node of the <em>New Project</em> dialog. If you have Visual Studio open, you should shut it down and restart it. If you have an older version installed of this VSIX installed, you should uninstall the old one first.

<strong>To remove: </strong>Go to <em>Tools / Extensions and Updates...</em> then uninstall "Direct3DWin32Game" or "Direct3DUWPGame".

<table border="1">
<tbody>
<tr>
<td><strong>Template</strong></td>
<td><strong>VS 2013</strong></td>
<td><strong>VS 2015 / 2017 / 2019</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td>Direct3D Win32 Game</td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td>Win32 desktop Direct3D 11 Game template</td>
</tr>
<tr>
<td>Direct3D Win32 Game DR</td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td>Win32 desktop Direct3D 11 Game template with <code>DeviceResources</code> abstraction</td>
</tr>
<tr>
<td>Direct3D UWP Game</td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td>Universal Windows app Direct3D 11 Game template using C++/CX (<code>/ZW</code>)</td>
</tr>
<tr>
<td>Direct3D UWP Game (C++/WinRT)</td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td>Universal Windows app Direct3D 11 Game template using C++/WinRT language projections.</td>
</tr>
<tr>
<td>Direct3D UWP Game DR</td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td>Universal Windows app Direct3D 11 Game template with <code>DeviceResources</code> abstraction using C++/CX</td>
</tr>
<tr>
<td>Direct3D UWP Game DR (C++/WinRT)</td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td>Universal Windows app Direct3D 11 Game template with <code>DeviceResources</code> abstraction using C++/WinRT</td>
</tr>
<tr>
<td>Direct3D 12 Win32 Game</td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td>Win32 desktop Direct3D 12 Game template</td>
</tr>
<tr>
<td>Direct3D 12 Win32 Game DR</td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td>Win32 desktop Direct3D 12 Game template with <code>DeviceResources</code> abstraction</td>
</tr>
<tr>
<td>Direct3D 12 UWP Game</td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td>Universal Windows app Direct3D 12 Game template using C++/CX</td>
</tr>
<tr>
<td>Direct3D 12 UWP Game (C++/WinRT)</td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td>Universal Windows app Direct3D 12 Game template using C++/WinRT</td>
</tr>
<tr>
<td>Direct3D 12 UWP Game DR</td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td>Universal Windows app Direct3D 12 Game template with <code>DeviceResources</code> abstraction using C++/CX</td>
</tr>
<tr>
<td>Direct3D 12 UWP Game DR (C++/WinRT)</td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td>Universal Windows app Direct3D 12 Game template with <code>DeviceResources</code> abstraction using C++/WinRT</td>
</tr>
</tbody>
</table>

<strong>DirectX 12:</strong> The Direct3D 12 versions of the template set ``_WIN32_WINNT`` to 0x0A00 (Windows 10), while the Direct3D 11 versions still use 0x0600 (Windows Vista). You need to have the <a href="https://devblogs.microsoft.com/somasegar/building-apps-for-windows-10-with-visual-studio-2015/">Windows 10 SDK installed</a> to build the Direct3D 12 templates, and Windows 10 to run it.

<strong>UWP:</strong> You have to be using Windows 8.1 or Windows 10 with the <a href="https://devblogs.microsoft.com/somasegar/building-apps-for-windows-10-with-visual-studio-2015/">Windows 10 SDK installed</a> to build the UWP templates. You need a Windows 10 device to run it.

<strong>C++/WinRT:</strong> See <a href="https://walbourn.github.io/directx-tool-kit-and-cwinrt/">this post</a> for more information. C++/WinRT--prior to the Windows 10 SDK ([17134](https://moderncpp.com/2017/11/01/cppwinrt-in-the-windows-sdk/))--requires the <a href="https://www.nuget.org/packages/cppwinrt/">cppwinrt</a> NuGet package.

<h1>DeviceResources</h1>

The basic template puts all the code for creating the device and swapchain into the main <code>Game</code> class. This makes it very simple to reference especially in the tutorial lessons. This does have the result, however, of putting a fair amount of 'boiler plate' code that clutters up the main <code>Game</code> class. The alternative for larger projects are the "DR" versions which add a helper class called <code>DeviceResources</code>. This class owns the Direct3D device, the DXGI swap chain, the depth/stencil buffer, and the render views needed for basic rendering. This does requires a few changes in the <code>Game</code> class.

```cpp
Game::Game()
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();
    ...
}
```

```cpp
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    // TODO: Add your rendering code here.

    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    // Clear the views
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetBackBufferRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);
}
```

```cpp
void Game::CreateDeviceDependentResources()
{
    // TODO: Initialize device dependent objects here (independent of window size).
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
```

A few key things to note about this code compared with the non-DR version:

<ul>
 	<li>The <code>Game::CreateDevice</code> method has been replaced with a call to <code>DeviceResources::CreateDeviceResources</code> and <code>Game::CreateDeviceDependentResources</code>.</li>
 	<li>The <code>Game::CreateResources</code> method has been replaced with a call to <code>DeviceResources::CreateWindowSizeDependentResources</code> and <code>Game::CreateWindowSizeDependentResources</code>.</li>
 	<li>The <code>Game::OnDeviceLost</code> method is now a callback from <code>DeviceResources</code> and only handles the cleanup. The <code>Game::OnDeviceRestored</code> call is made when the device has been re-recreated.</li>
 	<li>The usage difference can be seen in <code>Game::Clear</code> where instead of using local member variables, accessors on <code>DeviceResources</code> are used to obtain the device, context, etc.</li>
</ul>

Otherwise the DR version of the template is the same as the <a href="https://walbourn.github.io/direct3d-win32-game-visual-studio-template/">original D3DGame templates</a>, including using <a href="https://walbourn.github.io/understanding-game-time-revisited/">StepTimer</a>. See <a href="https://github.com/Microsoft/DirectXTK/wiki/DeviceResources">this page</a> for a more detailed overview.

<strong>DirectX 12:</strong> The details of the Direct3D 12 versions of <code>DeviceResources</code> is different than the Direct3D 11 version since the APIs are quite different, but it's the same design. See <a href="https://github.com/Microsoft/DirectXTK12/wiki/DeviceResources">this page</a> for a more detailed overview.

<strong>VS 2013 vs. 2015:</strong> Note there is one minor code difference between the VS 2013 and VS 2015 version of the templates because VS 2013 does not support C++11 uniform initialization. Otherwise the code is basically the same. VS 2015 is required for UWP development, and the Windows 10 SDK is required for Direct3D 12 development which only officially integrates with VS 2015--you can use a <a href="https://walbourn.github.io/windows-10-sdk-november-2015/">props</a> solution to get it to work with VS 2013.

> Note that the VS 2013 version of the template was last updated in [July 2017](https://github.com/walbourn/directx-vs-templates/releases/tag/jul2017).

<strong>VS 2017:</strong> The latest version of the ``Direct3DUWPGame.vsix`` (March 2017 or later) now supports both VS 2015 and VS 2017. On VS 2015, it will use Platform Toolset ``v140`` while for VS 2017 it uses ``v141``. The Direct3D 11 Win32 game template originally used the VS 2015 default Windows 8.1 SDK while the other templates all require a Windows 10 SDK. Since VS 2017 only includes a Windows 10 SDK by default, the Direct3D 11 Win32 game template and it's DeviceResources variant now trigger the same Windows 10 SDK selection wizard as the UWP and Direct3D 12 templates.

<strong>VS 2019:</strong> The latest version of the ``Direct3DUWPGame.vsix`` (April 2019 or later) now supports VS 2015, 2017, and 2019. It uses a Platform Toolset of ``v140``, ``v141``, or ``v142`` accordingly.
