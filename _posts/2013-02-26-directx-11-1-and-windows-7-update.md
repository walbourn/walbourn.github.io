---
layout: msdnpost
title: DirectX 11.1 and Windows 7 Update
date: 2013-02-26 11:11
author: Chuck Walbourn
comments: true
categories: [directx, pixw, win7]
---
As of today, <em>IE 10 for Windows 7</em> has been <a href="https://blogs.msdn.microsoft.com/ie/2013/02/26/ie10-for-windows-7-globally-available-for-consumers-and-businesses/">officially released</a>. <em>IE10 for Windows 7</em> includes portions of the DirectX 11.1 runtime for Windows 7 Service Pack 1 and Windows Server 2008 R2 Service Pack 1 via <a href="http://support.microsoft.com/kb/2670838">KB 2670838</a>.

Full technical details of what's included in KB 2670838 are covered on <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3darticles/platform-update-for-windows-7">Microsoft Docs</a>. The primary difference between the prerelease and the final version is that WARP supports Feature Level 11.0 with the updated runtime.
<!--more-->

See <a href="https://walbourn.github.io/directx-11-1-and-windows-7/">DirectX 11.1 and Windows 7</a> for some additional notes about KB 2670838 as it impacts <em>PIX for Windows</em>, the debug runtime, and VS 2012 Graphics Diagnostics. The key issue is that the legacy DirectX SDK (June 2010) release version of the Debug Runtime is not compatible with KB 2670838. You can resolve this by installing the <a href="http://msdn.microsoft.com/en-us/windows/desktop/hh852363">Windows 8.0 SDK standalone</a>, <a href="http://www.microsoft.com/visualstudio/eng/downloads">VS 2012</a> which includes the Windows 8.0 SDK, or the VS 2012 Remote Debugging Tools (<a href="http://go.microsoft.com/?linkid=9810454">x86</a> or <a href="http://go.microsoft.com/?linkid=9810464">x64</a>).

<strong>Note: </strong>If you have the prerelease of either IE10 or KB 2670838 installed, you should update your system. Windows Update will be offering an update soon, but you can manually install it as well.

<strong>IE11: </strong>There is an <a href="http://go.microsoft.com/fwlink/?LinkID=316880">IE11 Preview for Windows 7</a> now available. It requires KB 2670838 as well.

<strong>DXDIAG:</strong> Even after applying KB 2670838 to Windows 7 SP1, DXDIAG will still report it as "DirectX 11".

<strong>XINPUT and XAUDIO2: </strong>KB 2670838 does not include XINPUT 1.4 or XAudio 2.8 on Windows 7. These remain Windows 8 exclusive. See <a href="https://walbourn.github.io/xinput-and-windows-8/">XINPUT and Windows 8</a> and <a href="https://walbourn.github.io/xaudio2-and-windows-8/">XAudio2 and Windows 8</a> for guidance on handling this difference in Win32 desktop applications.

<strong>WIC:</strong> KB 2670838 includes WIC2 for Windows 7. See <a href="https://walbourn.github.io/windows-imaging-component-and-windows-8/">Windows Imaging Component and Windows 8</a> for details.

<p><strong>Media Foundation:</strong> KB 2670838 does <em>not</em> include the updates to Media Foundation to use DirectX 11 Video support. To render video to a texture, you must use DXGI shared surfaces prior to Windows 8.0.

<strong>DirectX 11 vs. 11.1:</strong> For Windows 7 and Windows Vista, you can continue to use the same DirectX 11.0 APIs as always even with this update installed. The only thing you have to do is to install the updated SDK Debug Layers to restore <code>D3D11_CREATE_DEVICE_DEBUG</code> functionality. If you want to take advantage of some of the new DirectX 11.1 APIs now available on Windows 7 as well, you need to use the Windows 8.0 SDK with VS 2010 or VS 2012 rather than continuing to use the legacy DirectX SDK. See <a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a> and <a href="https://walbourn.github.io/directx-sdks-of-a-certain-age/">DirectX SDKs of a certain age</a> for details.

<strong>VS 2012:</strong> There is improved support for using VS 2012 Graphics Diagnostics on Windows 7 with KB 2670838 installed in the <a href="https://walbourn.github.io/visual-studio-2012-update-2/">VS 2012 Update 2</a>. Installing the KB also enables GPU debugging for C++ AMP programs.

<strong>VS 2013</strong>: The original release of VS 2013 RTM had a prerequisite of installing IE10, which in turn required KB 2670838. This setup requirement has been removed for Windows 7 systems in a refreshed setup, but may result in some reduced functionality (see <a href="http://go.microsoft.com/fwlink/?LinkID=330043">KB 2906882</a>).
