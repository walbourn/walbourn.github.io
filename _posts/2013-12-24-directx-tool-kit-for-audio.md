---
layout: post
title: DirectX Tool Kit for Audio
date: 2013-12-24 23:40
author: walbourn
comments: true
categories: [audio, codeplex, Uncategorized, winphone, xbox one]
---
<p>The December 2013 release of <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK</a> is now available on CodePlex, and includes a C++ implementation of the XNA Game Studio's low-level audio framework using XAudio2 and X3DAudio.</p>
<ul>
<li><strong>AudioEngine</strong> - This class represents an XAudio2 audio graph, device, and mastering voice; similar to XNA's <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.audio.audioengine.aspx">AudioEngine</a>.</li>
<li><strong>SoundEffect</strong> - A container class for sound resources which can be loaded from .wav files similar to XNA's <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.audio.soundeffect.aspx">SoundEffect</a>.</li>
<li><strong>SoundEffectInstance</strong> - Provides a single playing, paused, or stopped instance of a sound similar to XNA's <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.audio.soundeffectinstance.aspx">SoundEffectInstance</a>.</li>
<li><strong>DynamicSoundEffectInstance</strong> - SoundEffectInstance where the application provides the audio data on demand similar to XNA's <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.audio.dynamicsoundeffectinstance.aspx">DynamicSoundEffectInstance</a>.</li>
<li><strong>WaveBank</strong> - A container class for sound resources packaged into an XACT-style .xwb wave bank, similar to XNA's <a href="http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.audio.wavebank.aspx">WaveBank</a> but with support for directly playing one-shots and creating SoundEffectInstances that refer to entries in the wave bank.</li>
<li><strong>AudioListener</strong>, <strong>AudioEmitter</strong> - Utility classes used with SoundEffectInstance::Apply3D.</li>
</ul>
<p><em>DirectXTK for Audio</em> uses XAudio 2.8 for Windows Store apps for Windows 8.1, Windows Store apps for Windows 8.0, Windows phone 8, and Xbox One*. The VS projects for these platforms all include the graphics and audio components.</p>
<p>When building Win32 desktop applications, you can either make use of XAudio 2.8 if targeting Windows 8.0 or later, or you can make use of XAudio 2.7 with the legacy DirectX SDK (June 2010) to target Windows Vista, Windows 7,&nbsp;or later. There is one VS project for the graphics component, another for the Windows 8.x version of the audio components, and another for the down-level version that requires the legacy DirectX SDK to build.</p>
<p>The DirectXTK package also includes a new command-line tool, XWBTool, which can be used to build XACT-style wave banks for more efficient management of audio data. <em>DirectXTK for Audio</em> does not make use of the legacy XACT Engine, XACT Cue, or XACT SoundBank. It only uses .xwb wave banks as a method for packing .wav data. The WaveBank class can use .xwb wave banks built with XWBTool or the legacy XACTBLD tool.</p>
<p>More detailed <a href="https://directxtk.codeplex.com/wikipage?title=Audio">documentation</a>, full release notes, and other information can be found on the DirectXTK CodePlex site.</p>
<ul>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-for-Audio-Simple-9d6a7da2">DirectXTK for Audio Simple Win32 Sample (Windows 8.x)</a></li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-for-Audio-Simple-928e0700">DirectXTK for Audio Simple Win32 Sample (DirectX SDK)</a></li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Sample-608bc274">DirectXTK Simple Sample for Windows Store apps (Windows&nbsp;8.0)</a></li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Sample-a0b6de36">DirectXTK Simple Sample for Windows Store apps (Windows 8.1)</a></li>
<li><a href="http://code.msdn.microsoft.com/DirectXTK-Simple-Windows-80e6b591">DirectXTK Simple Sample for Windows phone</a></li>
<li><a href="https://developer.xboxlive.com/en-us/platform/development/education/Pages/Samples.aspx">DirectXTK Simple Sample for Xbox One XDK</a> (login required)</li>
<li><a href="https://developer.xboxlive.com/en-us/platform/development/adk/Pages/ADKSamples.aspx">DirectXTK Simple Sample for Xbox One ADK</a> (login required)</li>
</ul>
<p><strong>Related:</strong> <a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/02/xaudio2-and-windows-8-consumer-preview.aspx">XAudio2 and Windows 8</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/02/directxtk.aspx">DirectXTK (March 2012)</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/01/27/directxtk-update.aspx">DirectXTK Update (Jan 2013)</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2013/10/29/codeplex-vs-2013-refresh.aspx">CodePlex VS 2013 Refresh</a></p>
<p>* = The December 2013 releases of <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK</a> and <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a> on CodePlex fully support development for both Xbox One ADK and Xbox One XDK developers. See <a href="http://www.xbox.com/en-us/Developers/id">ID@Xbox</a>.</p>
<p><strong>Update:</strong> The January 2014 release of DirectXTK includes voice management and optional mastering volume limiter. Refreshed all the Simple Sample releases to include <em>DirectXTK for Audio</em> demo. DirectX Tool Kit is also hosted on <a href="https://github.com/Microsoft/DirectXTK">GitHub</a></p>
<p><strong>Windows 10: </strong>When building with the Windows 10 SDK, <em>DirectX Tool Kit</em> for Audio uses <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/ee415802.aspx">XAudio 2.9</a>.</p>
