---
layout: msdnpost
title: DirectX Tool Kit for Audio
date: 2013-12-24 23:40
author: Chuck Walbourn
comments: true
categories: [audio, codeplex, winphone, xbox one]
---
The December 2013 release of <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK</a> is now available on <strike>CodePlex</strike>GitHub, and includes a C++ implementation of the XNA Game Studio's low-level audio framework using XAudio2 and X3DAudio.
<!--more-->

<ul>
<li><strong>AudioEngine</strong> - This class represents an XAudio2 audio graph, device, and mastering voice; similar to XNA's AudioEngine.</li>
<li><strong>SoundEffect</strong> - A container class for sound resources which can be loaded from ``.wav`` files similar to XNA's SoundEffect.</li>
<li><strong>SoundEffectInstance</strong> - Provides a single playing, paused, or stopped instance of a sound similar to XNA's SoundEffectInstance.</li>
<li><strong>DynamicSoundEffectInstance</strong> - SoundEffectInstance where the application provides the audio data on demand similar to XNA's DynamicSoundEffectInstance.</li>
<li><strong>WaveBank</strong> - A container class for sound resources packaged into an XACT-style ``.xwb`` wave bank, similar to XNA's WaveBank but with support for directly playing one-shots and creating SoundEffectInstances that refer to entries in the wave bank.</li>
<li><strong>AudioListener</strong>, <strong>AudioEmitter</strong> - Utility classes used with SoundEffectInstance::Apply3D.</li>
</ul>

<em>DirectXTK for Audio</em> uses XAudio 2.8 for Windows Store apps for Windows 8.1, Windows Store apps for Windows 8.0, Windows phone 8, and Xbox One*. The VS projects for these platforms all include the graphics and audio components.

When building Win32 desktop applications, you can either make use of XAudio 2.8 if targeting Windows 8.0 or later, or you can make use of XAudio 2.7 with the legacy DirectX SDK (June 2010) to target Windows Vista, Windows 7, or later. There is one VS project for the graphics component, another for the Windows 8.x version of the audio components, and another for the down-level version that requires the legacy DirectX SDK to build.

The DirectXTK package also includes a new command-line tool, [XWBTool](https://github.com/Microsoft/DirectXTK/wiki/xwbtool), which can be used to build XACT-style wave banks for more efficient management of audio data. <em>DirectXTK for Audio</em> does not make use of the legacy XACT Engine, XACT Cue, or XACT SoundBank. It only uses ``.xwb`` wave banks as a method for packing .wav data. The WaveBank class can use ``.xwb`` wave banks built with XWBTool or the legacy XACTBLD tool.

More detailed <a href="https://github.com/Microsoft/DirectXTK/wiki/Audio">documentation</a>, full release notes, and other information can be found on the DirectXTK <strike>CodePlex</strike>GitHub site.

<ul>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-for-Audio-Simple-9d6a7da2">DirectXTK for Audio Simple Win32 Sample (Windows 8.x)</a></li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-for-Audio-Simple-928e0700">DirectXTK for Audio Simple Win32 Sample (DirectX SDK)</a></li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Sample-608bc274">DirectXTK Simple Sample for Windows Store apps (Windows 8.0)</a></li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Sample-a0b6de36">DirectXTK Simple Sample for Windows Store apps (Windows 8.1)</a></li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Windows-80e6b591">DirectXTK Simple Sample for Windows phone</a></li>
<li><a href="https://developer.xboxlive.com/en-us/platform/development/education/Pages/Samples.aspx">DirectXTK Simple Sample for Xbox One XDK</a> (login required)</li>
<li><a href="https://developer.xboxlive.com/en-us/platform/development/adk/Pages/ADKSamples.aspx">DirectXTK Simple Sample for Xbox One ADK</a> (login required)</li>
</ul>

<strong>Related:</strong> <a href="https://walbourn.github.io/xaudio2-and-windows-8/">XAudio2 and Windows 8</a>, <a href="https://walbourn.github.io/directxtk/">DirectXTK (March 2012)</a>, <a href="https://walbourn.github.io/directxtk-update/">DirectXTK Update (Jan 2013)</a>, <a href="https://walbourn.github.io/codeplex-vs-2013-refresh/">CodePlex VS 2013 Refresh</a>

``*`` = The December 2013 releases of <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK</a> and <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a> on CodePlex fully support development for both Xbox One ADK and Xbox One XDK developers. See <a href="http://www.xbox.com/en-us/Developers/id">ID@Xbox</a>.

<strong>Update:</strong> The January 2014 release of DirectXTK includes voice management and optional mastering volume limiter. Refreshed all the Simple Sample releases to include <em>DirectXTK for Audio</em> demo. DirectX Tool Kit is also hosted on <a href="https://github.com/Microsoft/DirectXTK">GitHub</a>

<strong>Windows 10: </strong>When building with the Windows 10 SDK, <em>DirectX Tool Kit</em> for Audio uses <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/ee415802.aspx">XAudio 2.9</a>.
