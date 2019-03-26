---
layout: post
title: DirectX SDKs of a certain age
date: 2012-08-21 16:56
author: Chuck Walbourn
comments: true
categories: [dxsdk]
---
Recently many older releases of the DirectX SDK and REDIST packages expired and were removed from the Microsoft Downloads Center site. The DirectX SDK and REDIST packages for all 2008, 2009, and 2010 releases are currently available, but all 2007 and prior releases are no longer hosted by Microsoft.
<!--more-->

Here is a quick summary of DirectX technologies and recommended solutions. Be sure to read <a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a> and <a href="https://walbourn.github.io/where-is-the-directx-sdk-2013-edition/">Where is the DirectX SDK (2013 Edition)?</a> as well.

<table border="1">
<tbody>
<tr>
<td><strong>Technology</strong></td>
<td><strong>Resolution</strong></td>
</tr>
<tr>
<td>Direct3D 11.3/11.4
Direct3D 12</td>
<td><p>The Windows 10 Anniversary Update SDK (14393) includes Direct3D 11.3, Direct3D 11.4, Direct3D 12.0, Direct2D 1.3, DXGI 1.4, and DXGI 1.5.</p>
<p>The DirectX 12/11.3/11.4 Runtime is included with Windows 10.</p></td>
</tr>
<tr>
<td>Direct3D 11.2</td>
<td><p>The Windows SDK 8.1 includes Direct3D 11.2, Direct2D 1.2, and DXGI 1.3.</p>
<p>The DirectX 11.2 Runtime is included with Windows 8.1 / Windows Server 2012 R2.</p></td>
</tr>
<tr>
<td>Direct3D 11.1</td>
<td><p>The Windows SDK 8.0 includes Direct3D 11.1, updated Direct2D/DirectWrite, updated WARP, and DXGI 1.2.</p>
<p>The DirectX 11.1 Runtime is included with Windows 8 / Windows Server 2012. <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3darticles/platform-update-for-windows-7">Partial support</a> is available down-level on Windows 7 / Windows Server 2008 R2 Service Pack 1 via <a href="http://support.microsoft.com/kb/2670838">KB 2670838</a>.</p></td>
</tr>
<tr>
<td>Direct3D 11.0</td>
<td><p>The Windows SDK 7.0 includes Direct3D 11.0, Direct2D, DirectWrite, WARP, and DXGI 1.1.</p>
<p>The DirectX 11.0 Runtime is included with Windows 7 / Windows Server 2008 R2. <a href="https://docs.microsoft.com/en-us/windows/desktop/win7ip/platform-update-for-windows-vista-portal">Support</a> is available down-level on Windows Vista / Windows Server 2008 Service Pack 2 via <a href="http://go.microsoft.com/fwlink/?LinkId=160189">KB 971644</a>.</p></td>
</tr>
<tr>
<td>Direct3D 10.x</td>
<td><p>The Windows SDK 6.0 or later includes Direct3D 10.x and DXGI 1.0.</p>
<p>The DirectX 10.0 Runtime is included with Windows Vista / Windows Server 2008. The DirectX 10.1 Runtime is included with Windows Vista / Windows Server 2008 Service Pack 1.</p>
<p>Windows SDK 7.0 or later includes updates for expanded Direct3D 10.1 <a href="https://walbourn.github.io/direct3d-feature-levels/">feature levels</a> (aka "10level9") included with the DirectX 11.0 Runtime.</p></td>
</tr>
<tr>
<td>Direct3D 9</td>
<td><p>Windows SDK 6.0 or later includes Direct3D 9 and Direct3D9Ex.</p>
<p>Direct3D 9.0c is included with Windows XP Service Pack 2, Windows Server 2003 Service Pack 1, and Windows XP x64 Edition.</p>
<p>Direct3D9Ex is supported by Windows Vista / Windows Server 2008.</p></td>
</tr>
<tr>
<td>Direct3D 8 and prior</td>
<td><p>The <em>August 2007 DirectX SDK</em> was the last version to include Direct3D 8 (<code>d3d8.h d3d8caps.h d3d8types.h</code>) and Direct3D 7 and prior (<code>d3d.h d3dcaps.h d3dvec.inl d3dtypes.h</code>).</p>
<p>Direct3D 9 or later should be used for all applications, and we'd recommend using <a href="https://walbourn.github.io/getting-started-with-direct3d-11/">Direct3D 11</a>.</p></td>
</tr>
<tr>
<td><code>D3DX</code></td>
<td><p>The <a href="https://walbourn.github.io/announcement-directx-sdk-june-2010-is-live/">June 2010 DirectX SDK</a> contains the last release of D3DX9, D3DX10, and D3DX11.</p>
<p><a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a>, <a href="https://walbourn.github.io/directxtex/">DirectXTex</a>, <a href="https://walbourn.github.io/directxmesh/">DirectXMesh</a>, and <a href="https://walbourn.github.io/hlsl-fxc-and-d3dcompile/">D3DCompile</a> replace the majority of the functionality in these utility libraries. <a href="https://walbourn.github.io/directxtk/">DirectXTK</a> provides further alternatives for Direct3D 11 applications. For Direct3D 9 applications, the <a href="https://walbourn.github.io/ddswithoutd3dx-sample-update/">DDSWithoutD3DX</a> sample provides a way to create textures from <code>.DDS</code> files.</p>
<p>The <a href="https://walbourn.github.io/effects-for-direct3d-11-update/">Effects 11</a> library is available as shared-source online.</p>
<p>See <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a> for a master list of D3DX replacements.</p></td>
</tr>
<tr>
<td><code>DXERR9.LIB</code></td>
<td><p>The <em>August 2007 DirectX SDK</em> was the last version to include the <code>dxerr9.lib</code>. It has been replaced by <code>dxerr.lib</code> in <a href="https://walbourn.github.io/announcement-directx-sdk-june-2010-is-live/">June 2010 DirectX SDK</a> which supports all the same error codes plus some new ones. Changing references to <code>dxerr.lib</code> or making a copy as <code>dxerr9.lib</code> should resolve link issues for this library.</p>
<p>Note for Windows 8.x SDK users, see <a href="https://walbourn.github.io/wheres-dxerr-lib/">this</a> post for a replacement solution.</p></td>
</tr>
<tr>
<td>XACT</td>
<td><p>The <a href="https://walbourn.github.io/announcement-directx-sdk-june-2010-is-live/">June 2010 DirectX SDK</a> contains the last release of the Xbox Audio Cross Platform Tool (XACT) for Windows.</p>
<p>For games, we recommend using <a href="https://walbourn.github.io/learning-xaudio2/">XAudio2</a> or a 3rd party middleware solution instead.</p></td>
</tr>
<tr>
<td>DirectDraw</td>
<td><p>While <em>February 2010 DirectX SDK</em> was the last to contain <code>ddraw.h</code> and <code>ddraw.lib</code>, <code>ddraw.h</code> is still available in the Windows SDK 6.0 or later. <code>ddraw.lib</code> isn't needed.</p>
<p>See <a href="https://walbourn.github.io/wither-directdraw/">Wither DirectDraw</a> for details.</p></td>
</tr>
<tr>
<td>DirectInput</td>
<td><p>The <em>August 2007 DirectX SDK</em> was the last version to include DirectInput7 and prior (<code>dinput.lib</code>). DirectInput8 (<code>dinput.h dinput8.lib</code>) is available in the Windows SDK 7.0 or later and is supported for both x86 and x64 native Win32 desktop applications.</p>
<p>For gamepads, we'd recommend supporting XINPUT. XINPUT 9.1.0 headers and libraries are available in the Windows SDK 6.0 or later. See <a href="https://walbourn.github.io/xinput-and-windows-8/">this</a> post for additional information. For mouse and keyboard input, you should use standard Windows messages rather than DirectInput as well.</p></td>
</tr>
<tr>
<td>DirectSound</td>
<td><p>DirectSound8 (<code>dsconf.h dsound.h dsound.lib</code>) is available in the Windows SDK 7.0 or later and is supported for both x86 and x64 native Win32 desktop applications.</p>
<p>For games, we recommend using <a href="https://walbourn.github.io/learning-xaudio2/">XAudio2</a> instead. Audio engines with their own mixing engine and source rate conversion (SRC) support should use <a href="https://docs.microsoft.com/en-us/windows/desktop/CoreAudio/wasapi">WASAPI</a> on Windows Vista or later.</p></td>
</tr>
<tr>
<td>DirectMusic</td>
<td><p>The <em>August 2007 DirectX SDK</em> was the last version to include DirectMusic, and the DirectMusic Producer tool download is no longer hosted by Microsoft. Use of DirectMusic for games is not recommended.</p>
<p>"Core" DirectMusic headers (<code>dls1.h dls2.h dmdls.h dmerror.h dmksctrl.h dmusbuff.h dmusicc.h dmusics.h</code>) for use by professional audio developers are available in the <a href="https://walbourn.github.io/windows-sdk-7-1/">Windows SDK 7.1</a> or later, and supported for both x86 and x64 native Win32 desktop applications by Windows 7 and Windows 8.</p></td>
</tr>
<tr>
<td>DirectShow</td>
<td><p>The<em> February 2005 DirectX SDK</em> was the last to include DirectShow headers, but these are available in the Windows SDK.</p>
<p><a href="https://docs.microsoft.com/en-us/windows/desktop/medfound/microsoft-media-foundation-sdk">Media Foundation</a> available on Windows Vista and later versions of Windows is recommended over DirectShow for video playback. Be sure to read <a href="https://walbourn.github.io/quot-who-moved-my-windows-media-cheese-quot/">this</a> post for some additional considerations.</p></td>
</tr>
<tr>
<td>DirectPlay</td>
<td><p>The <em>August 2007 DirectX SDK</em> was the last version to include DirectPlay (<code>dpaddr.h dplay.h dplobby.h dplay8.h dplobby8.h dpnathlp.h dplayx.lib</code>). The DirectPlay NAT helper is not supported on Windows Vista or newer versions of Windows.</p>
<p>For games we recommend using TCP/IP via the WinSock API for network communication. To replace the 'lobby' functionality, you can utilize any number of the many game services available today from <a href="http://www.xbox.com/en-US/Developers">Microsoft</a> and other vendors.</p></td>
</tr>
<tr>
<td>DirectAnimation</td>
<td><p>The<em> August 2007 DirectX SDK</em> was the last version to include <code>dxtrans.h</code> and <code>dxtrans.lib</code>.</p>
<p>This technology was used at one point by Internet Explorer, but this is no longer in use.</p></td>
</tr>
<tr>
<td>Managed DirectX 1.1</td>
<td><p>The <em>August 2006 DirectX SDK</em> was the last version to include the samples and documentation for Managed DirectX 1.1.</p>
<p>See <a href="https://walbourn.github.io/directx-and-net/">DirectX and .NET</a> for more information.</p></td>
</tr>
<tr>
<td>Direct3D Retained Mode</td>
<td><p>The<em> August 2007 DirectX SDK</em> was the last version to include <code>d3drm.h d3drmdef.h d3drmobj.h d3drmwin.h</code></p>.
<p>This component is not supported on Windows Vista or newer versions of Windows.</p></td>
</tr>
<tr>
<td>DirectPlay Voice</td>
<td><p>The <em>August 2007 DirectX SDK</em> was the last version to include <code>dvoice.h</code>.</p>
<p>This component is not supported on Windows Vista or newer versions of Windows.</p></td>
</tr>
<tr>
<td>DirectX 7/8 Visual Basic 6.0</td>
<td><p>The <em>August 2007 DirectX SDK</em> was the last version to include <code>dx7todx8.h</code>.</p>
<p>This component is not supported on Windows Vista or newer versions of Windows.</p></td>
</tr>
</tbody>
</table>

<strong>DirectSetup: </strong>For the REDIST package, the current <a href="https://walbourn.github.io/dxwebsetup-update/">web redist</a> and <a href="https://walbourn.github.io/dxsetup-update/">standalone package</a> will install all older and current verisons of the various optional side-by-side DLLs on Windows XP Service Pack 2 or later. See <a href="https://walbourn.github.io/not-so-direct-setup/">Not So Direct Setup</a> for more details and notes about older releases.

<strong>Dark GDK</strong>: For users of the <em>Dark GDK</em> that was promoted for Visual Studio 2008 Express, the retirement of the <em>DirectX SDK (August 2007)</em> poses some challenges. There are some community work-arounds for disabling the use of DirectPlay and resolving the link problems with <code>DXERR9.LIB</code> (such as <a href="http://romsteady.blogspot.com/2010/12/compiling-darkgdk-and-visual-studio.html">this</a> post), and these are preferable to continuing to use a copy of the <em>DirectX SDK (August 2007)</em>.

<strong>DirectX SDK (August 2007):</strong> If you obtain a copy of this package from an unofficial mirror, be very careful as installing executables that require administrator privileges from untrusted websites carries a potential risk of adding your machine to a botnet and getting infected by other malware. Check that the EXE is signed with a valid Microsoft Digital Signature before running it. These unofficial mirrors are not supported or sponsored by Microsoft.

<strong>VS 2005:</strong> Windows 7.1 SDK and DirectX SDK (February 2005) were the last releases to support Visual Studio 2005.

<strong>VS 2008:</strong> Windows 7.1 SDK and DirectX SDK (June 2010) were the last releases to support Visual Studio 2008.

<strong>VS 2010: </strong>Visual Studio 2010 comes with the Windows 7.0 SDK included. You can make use of the Windows 7.1 SDK with VS 2010 by using a <a href="https://walbourn.github.io/windows-sdk-7-1/">Platform Toolset</a> setting. You can use the Windows 8.0 or 8.1 SDK by creating a <a href="https://devblogs.microsoft.com/cppblog/using-the-windows-8-sdk-with-visual-studio-2010-configuring-multiple-projects/">property sheet</a> for your project.

<strong>VS 2012:</strong> Visual Studio 2012 comes with the Windows 8.0 SDK included. Mixing the Windows 8.x SDK with the legacy DirectX SDK requires some specific <a href="https://docs.microsoft.com/en-us/windows/desktop/directx-sdk--august-2009-">build settings</a>.

<strong>VS 2012 Update 1:</strong> Support for Windows XP the "<a href="https://walbourn.github.io/visual-studio-2012-update-1/">v110_xp</a>" Platform Toolset makes use of a Windows SDK 7.1A which is basically the same as 7.1.

<strong>VS 2013:</strong> Visual Studio 2013 comes with the Windows 8.1 SDK included.

<strong>Related</strong>: <a href="https://walbourn.github.io/a-brief-history-of-windows-sdks/">A Brief History of Windows SDKs</a>
