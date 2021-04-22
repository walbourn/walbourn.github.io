---
layout: msdnpost
title: DirectX Tool Kit for Audio
date: 2013-12-24 23:40
author: Chuck Walbourn
comments: true
categories: [audio, codeplex, github, winphone, xbox one]
---
The December 2013 release of <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectX Tool Kit</a> is now available on <strike>CodePlex</strike>GitHub, and includes a C++ implementation of the XNA Game Studio's low-level audio framework using XAudio2 and X3DAudio. *DirectX Tool Kit for Audio* is included in both the [DirectX 11](https://github.com/microsoft/DirectXTK/tree/master/Audio) and [DirectX 12](https://github.com/microsoft/DirectXTK12/tree/master/Audio) versions of *DirectX Tool Kit*.
<!--more-->

<ul>
<li><strong>AudioEngine</strong> - This class represents an XAudio2 audio graph, device, and mastering voice; similar to XNA's AudioEngine.</li>
<li><strong>SoundEffect</strong> - A container class for sound resources which can be loaded from <code>.wav</code> files similar to XNA's SoundEffect. These can be played as 'one-shots' managed by the engine, or used to create a SoundEffectInstance.</li>
<li><strong>SoundEffectInstance</strong> - Provides a single playing, looped, paused, or stopped instance of a sound similar to XNA's SoundEffectInstance. These support 3D positional audio and optionally reverb effects.</li>
<li><strong>SoundStreamInstance</strong> (<i>new in  May 2020</i>) - SoundEffectInstance for playing waves from a streaming XACT-style <code>.xwb</code> wave bank.</li>
<li><strong>DynamicSoundEffectInstance</strong> - SoundEffectInstance where the application provides the audio data on demand similar to XNA's DynamicSoundEffectInstance.</li>
<li><strong>WaveBank</strong> - A container class for sound resources packaged into an XACT-style <code>.xwb</code> wave bank, similar to XNA's WaveBank but with support for directly playing one-shots and creating SoundEffectInstances that refer to entries in the wave bank.</li>
<li><strong>AudioListener</strong>, <strong>AudioEmitter</strong> - Utility classes used with SoundEffectInstance::Apply3D.</li>
</ul>

<em>DirectXTK for Audio</em> uses XAudio 2.8 for Windows Store apps for Windows 8.1, Windows Store apps for Windows 8.0, and Windows phone 8. The VS projects for these platforms all include the graphics and audio components.

When building Win32 desktop applications, you can either make use of XAudio 2.8 if targeting Windows 8.0 or later, XAudio 2.9 if targeting Windows 10, <strike>or you can make use of XAudio 2.7 with the legacy DirectX SDK (June 2010) to target Windows Vista, Windows 7, or later</strike>. There is one VS project for the graphics component, with distinct projects for the different audio versions.

<strong>Windows 10: </strong>When building with the Windows 10 SDK, <em>DirectX Tool Kit</em> for Audio uses <a href="https://docs.microsoft.com/en-us/windows/win32/xaudio2/xaudio2-versions">XAudio 2.9</a> which includes xWMA format support which was not present in XAudio 2.8. Therefore the projects for UWP, Xbox, and Windows 10 include both graphics and audio components.

<strong>Windows 7 Update: </strong> There is now a [NuGet package](https://www.nuget.org/packages/Microsoft.XAudio2.Redist/) for using XAudio 2.9 down-level on Windows 7 Service Pack 1, Windows 8.0, and Windows 8.1. See [Microsoft Docs](https://aka.ms/XAudio2Redist) for details. Support for legacy XAudio 2.7 has therefore been removed.

The DirectXTK package also includes a new command-line tool, [XWBTool](https://github.com/Microsoft/DirectXTK/wiki/xwbtool), which can be used to build XACT-style wave banks for more efficient management of audio data. <em>DirectXTK for Audio</em> does not make use of the legacy XACT Engine, XACT Cue, or XACT SoundBank. It only uses ``.xwb`` wave banks as a method for packing ``.wav`` data. The WaveBank class can use ``.xwb`` wave banks built with XWBTool or the legacy XACTBLD tool.

> The ``xwbtool`` also fixes some known issues with the XACTBLD tool when trying to create compact wavebanks. See [this commit](https://github.com/microsoft/DirectXTK/commit/60374ec00b72b4123199f30e444859f91975419d).

More detailed <a href="https://github.com/Microsoft/DirectXTK/wiki/Audio">documentation</a>, full release notes, and other information can be found on the DirectXTK <strike>CodePlex</strike>GitHub site. Samples can be found [here](https://github.com/walbourn/directxtk-samples).

<strong>Related:</strong> <a href="https://walbourn.github.io/xaudio2-and-windows-8/">XAudio2 and Windows 8</a>, <a href="https://walbourn.github.io/directxtk/">DirectXTK (March 2012)</a>, <a href="https://walbourn.github.io/directxtk-update/">DirectXTK Update (Jan 2013)</a>, <a href="https://walbourn.github.io/codeplex-vs-2013-refresh/">CodePlex VS 2013 Refresh</a>, <a href="https://walbourn.github.io/directx-tool-kit-for-audio-updates-and-a-direct3d-9-footnote/">DirectXTK for Audio update</a>

<strong>Update:</strong> The January 2014 release of DirectXTK includes voice management and optional mastering volume limiter. Refreshed all the Simple Sample releases to include <em>DirectXTK for Audio</em> demo. DirectX Tool Kit is also hosted on <a href="https://github.com/Microsoft/DirectXTK">GitHub</a>.

The May 2020 release added support for streaming from XACT-style ``.xwb`` files for PCM, ADCPM, xWMA, and XMA2 formats. The ``xwbtool`` can generate both streaming and in-memory wave banks.

The June 2020 release of DirectXTK removes all use of legacy XAudio 2.7 which required the deprecated DirectX SDK. For Windows 7 support, it now uses [XAudio2Redist](https://aka.ms/XAudio2Redist) which provides XAudio 2.9 support for Windows 7 SP1, Windows 8.0, and Windows 8.1 with automatic forwarding to the built-in XAudio 2.9 on Windows 10.
