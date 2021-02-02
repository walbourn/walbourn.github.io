---
layout: post
title: Where is the DirectX SDK (2021 Edition)?
date: 2021-01-29 15:19
author: Chuck Walbourn
comments: true
categories: [directx, dxsdk]
---

Microsoft announced last year that it was retiring all SHA-1 signed content from Microsoft Downloads in [this blog post](https://techcommunity.microsoft.com/t5/windows-it-pro-blog/sha-1-windows-content-to-be-retired-august-3-2020/ba-p/1544373) since the SHA-1 algorithm is no longer considered secure. The original timeline was stretched out a bit due to COVID-19, but as of January 2021 this content is no longer hosted by Microsoft servers.

In particular, this means the legacy *DirectX SDK*, the *DirectX End-User Runtime*, and the *DirectX End-User Runtime Web Installer* are **no longer available for download from Microsoft**.
<!--more-->

# Impact for existing games

As I've communicated numerous times, this legacy installer *never installs DirectX* (i.e. it doesn't change Direct3D, DirectDraw, DirectSound, DirectInput, etc.) at all. These components are strictly serviced as part of the Operating System. See [this blog post](https://walbourn.github.io/not-so-direct-setup/).

For games that included the *DirectX SDK* ``REDIST`` folder in their installation, there is no impact as that continues to work. Following the legacy recommendations of cutting down the number of ``.cab`` files you ship to control overall download/media sizes remains a useful option per [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/dxtecharts/directx-setup-for-game-developers).

For legacy DirectX SDK-built games using [**Desktop Bridge**](https://developer.microsoft.com/en-us/windows/bridges/desktop), you can still make use of the of the "DirectX Framework Package" [Microsoft.DirectX.x86](https://download.microsoft.com/download/c/c/2/cc291a37-2ebd-4ac2-ba5f-4c9124733bf1/UAPSignedBinary_Microsoft.DirectX.x86.appx) / [Microsoft.DirectX.x64](https://download.microsoft.com/download/c/c/2/cc291a37-2ebd-4ac2-ba5f-4c9124733bf1/UAPSignedBinary_Microsoft.DirectX.x64.appx) which remain available as the ``appx`` is signed with SHA-256.

# Impact for existing developers

As has been the case the past decade, the strong recommendation is to no longer rely on the legacy DirectX SDK or it's legacy DirectSetup redist solution. The bulk of the "DirectX" headers are already in the modern Windows SDK, so you *do not need the legacy DirectX SDK at all* for these components:

DirectX component|Developer files in Windows SDK
-|-
Common |  Dcommon.h, D3Dcommon.h, DXGUID.LIB
Direct2D | D2D1.h, D2D1Helper.h, D2DBaseTypes.h, D2Derr.h, d2d1.lib
DirectWrite | DWrite.h, dwrite.lib
Direct3D 11 | D3D11.h, D3D11SDKLayers.h, D3D11Shader.h, d3d11.lib
Direct3D 10.1 | D3D10_1.h, D3D10_1shader.h, d3d10_1.lib
Direct3D 10 | D3D10.h, D3D10effect.h, d3d10misc.h, d3d10sdklayers.h, D3D10shader.h, d3d10.lib
Direct3D 9 | d3d9.h, d3d9caps.h, d3d9types.h, d3d9.lib
DXGI | DXGI.h, DXGIFormat.h, DXGIType.h, dxgi.lib
DirectDraw | DDraw.h. *See [this blog post](https://walbourn.github.io/whither-directdraw/) for why there is no ddraw.lib*.
DirectInput | dinput.h, dinputd.h, dinput8.lib
DirectSound | dsconf.h, dsound.h, dsound.lib
DXDiagProvider | dxdiag.h
Game Explorer UX | gameux.h
HLSL Compiler | D3Dcompiler.h, d3dcompiler.lib. *See [this blog post](https://walbourn.github.io/hlsl-fxc-and-d3dcompile/) for more information.*
D3DX11 Compute Shader Utility  |  D3DCSX.h, D3DCSX.lib, D3DCSXd.lib

> DirectX 12 was never part of the legacy DirectX SDK. Those headers and libraries are part of the Windows SDK as well as on [GitHub](https://github.com/microsoft/DirectX-Headers/).

## D3DX

Numerous replacements for legacy D3DX11 are detailed on this blog, most of which are open-source: [Living without D3DX](https://walbourn.github.io/living-without-d3dx/).

For users of D3DX10, the strong recommendation is to port to Direct3D 11 and use the D3DX11 replacements above. There is no technical reason to use Direct3D 10.x. See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/direct3d11/d3d11-programming-guide-migrating) for a detailed porting guide.

> D3DX12 (i.e. D3DX for DirectX 12) is of course still a thing. It never shipped in the legacy DirectX SDK, nor does it have any dependency on the legacy DirectSetup redist. See [this blog post](https://walbourn.github.io/the-many-faces-of-d3dx12/).

## XAudio2

The best option is to upgrade to XAudio 2.9. For Windows 10, this is built-in and everything is included in the Windows SDK. For Windows 7 / Windows 8.x you can make use of [XAudio2Redist](https://aka.ms/xaudio2redist). See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/xaudio2/xaudio2-versions). Primarily the change is in device numeration, obtaining the channel mask for the output device, and the move to a unified ``xaudio2.lib``, so it's a quick and simple port.

For samples, see [GitHub](https://github.com/walbourn/directx-sdk-samples/tree/master/XAudio2).

> Do not use XAudio 2.7 or earlier. It has a number of known bugs as well as relying on the legacy redistribution.

## XInput

The Windows SDK includes ``xinput.h`` / ``xinput.lib`` / ``Xinput9_1_0.lib``. You can use XInput 9.1.0 for Windows 7 support as it's always present in the OS. See [this blog post](https://walbourn.github.io/xinput-and-windows-8/).

For samples, see [GitHub](https://github.com/walbourn/directx-sdk-samples/tree/master/XInput).

> Do not use XInput 1.1, 1.2, or 1.3. These rely on the legacy redistribution.

## XNAMath

For the XNAMath library (``xnamath.h``), the best and simplest solution is to upgrade to [DirectXMath](https://walbourn.github.io/introducing-directxmath/) which is available in the Windows SDK, [GitHub](https://github.com/microsoft/DirectXMath), [NuGet](https://www.nuget.org/packages/directxmath), and [vcpkg](https://github.com/microsoft/vcpkg/tree/master/ports/directxmath).

See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/dxmath/pg-xnamath-migration) for the detailed porting guide.

## Managed DX 1.1

Managed DirectX 1.1 assemblies have been deprecated for a long time. They should no longer be used at all. See [this blog post](https://walbourn.github.io/directx-and-net/).

# Miscellaneous

* For ``DXERR.H`` / ``DXERR.LIB``, see [this blog post](https://walbourn.github.io/wheres-dxerr-lib/).

* For the ``XDSP.H`` math helper header, you can find this on [GitHub](https://github.com/microsoft/DirectXMath/tree/master/XDSP). It relies on DirectXMath.

* XACT never saw wide-spread adoption. There's no direct replacement option for XACT. Use in new projects is not recommended.

# Developer Runtimes

The legacy DirectX SDK included a DirectX Developer Runtime which provided the "Debug" device support for Direct3D 9 on Windows 7 or earlier. It also included a somewhat dated Direct3D 10/Direct3D 11 debug layer that are not compatible with DirectX 11.1 or later.

For Windows 10, you enable the *Graphics Tools* optional component to enable the DirectX Developer Runtime. *This does not include support for legacy Direct3D 9 debugging*.

For Windows 7 with DirectX 11.1 or Windows 8.x, the DirectX Developer Runtime is installed by the Windows SDK. *Again, this does not include support for legacy Direct3D 9 debugging*.

See [Microsoft Docs](https://docs.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-layers), [Direct3D SDK Debug Layer Tricks](https://walbourn.github.io/direct3d-sdk-debug-layer-tricks/), and [DXGI Debug Device](https://walbourn.github.io/dxgi-debug-device/)

<b>See Also:</b> [The Zombie DirectX SDK](https://walbourn.github.io/the-zombie-directx-sdk/)
