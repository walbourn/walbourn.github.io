---
layout: post
title: XDSP.H: Digital Signal Processing helper functions
date: 2012-04-30 16:52
author: walbourn
comments: true
categories: [audio, Uncategorized, xnamath]
---
The <em>DirectX SDK (June 2010)</em> release includes a little utility header, <code>XDSP.H</code>. This contains CPU-based functions for computing the Fast Fourier Transform (FFT) as well as some related multi-channel audio interleave/deinterleave functionality primarily used in writing custom xAPOs for XAUDIO2. The DirectX SDK version makes use of SSE intrinsics, which means it supports Windows x86 and x64 native code generation. This header is not included in the Windows SDK 8.0 (see "<a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">Where is the DirectX SDK?</a>"). If writing a custom xAPO for Windows Store apps (a.k.a. Metro style apps), you also likely want to support the Windows RT (aka Windows on ARM) platform as well.

Attached to this post is a version of <code>XDSP.H</code> that uses <a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/27/introducing-directxmath.aspx">DirectXMath</a> and compiles for x86, x64, and ARM. It can be used with either Visual Studio 2012 (aka VS 11) or VS 2010 with the Windows 8.0 SDK, and compiles for both Win32 desktop applications and Windows Store apps.

Full documentation for XDSP can be found in the offline help for the <em>DirectX SDK (June 2010)</em> release. These functions are in the <code>XDSP</code> C++ namespace, and memory buffers provided to these functions must be 16-byte aligned.
<table>
<tbody>
<tr>
<td><strong>Deinterleave</strong></td>
<td>Deinterleaves audio samples.</td>
</tr>
<tr>
<td><strong>FFT</strong></td>
<td>Fast Fourier Transform with an arbitrary number of samples.</td>
</tr>
<tr>
<td><strong>FFT4</strong></td>
<td>Four sample Fast Fourier Transform.</td>
</tr>
<tr>
<td><strong>FFT8</strong></td>
<td>Eight sample Fast Fourier Transform.</td>
</tr>
<tr>
<td><strong>FFT16</strong></td>
<td>Sixteen sample Fast Fourier Transform.</td>
</tr>
<tr>
<td><strong>IFFTDeinterleaved</strong></td>
<td>Inverse Fast Fourier Transform, plus interleaved multichannel audio.</td>
</tr>
<tr>
<td><strong>FFTInitializeUnityTable</strong></td>
<td>Initializes unity roots lookup table used by Fast Fourier Transform
functions (<code>FFT</code>, <code>FFTDeinterleaved</code>, and <code>FFTInterleaved</code>)</td>
</tr>
<tr>
<td><strong>FFTInterleaved</strong></td>
<td>Fast Fourier Transform, plus deinterleaves multichannel audio before
processing.</td>
</tr>
<tr>
<td><strong>FFTPolar</strong></td>
<td>Converts complex components to polar form.</td>
</tr>
<tr>
<td><strong>FFTUnswizzle</strong></td>
<td>Arranges Fast Fourier Transform function output by order of increasing frequency.</td>
</tr>
<tr>
<td><strong>Interleave</strong></td>
<td>Interleaves audio samples.</td>
</tr>
</tbody>
</table>
Note that <code>vmulComplex</code>, <code>ButterflyDIT4_1</code>, and <code>ButterflyDIT4_4</code> are internal implementation functions and not intended for direct use.

<strong>Note:</strong> There is a Windows Store app sample on <a href="https://code.msdn.microsoft.com/windowsapps/XAudio2-Stream-Effect-3f95c8f2/">MSDN Code Gallery</a> that makes use of this header.

<strong>Update:</strong> This project is now available on <a href="https://github.com/Microsoft/DirectXMath">GitHub</a> under the <a href="http://opensource.org/licenses/MIT">MIT license</a>.
