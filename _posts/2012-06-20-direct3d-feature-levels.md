---
layout: msdnpost
title: Direct3D Feature Levels
date: 2012-06-20 11:31
author: Chuck Walbourn
comments: true
categories: [direct3d, winphone, xbox one]
---
In various forums and discussion threads of late, I've seen some confusion about the difference between "DirectX 11" the API and "DirectX 11" the class of video hardware. The key to this is the concept of a "Feature Level" for devices which simplifies the old Direct3D 9 "sea of capabilities bits" to an increasingly capable group of level-sets for video hardware. An application requests a particular feature level (or a set of feature levels where the application can optionally use more advanced features if present), and the majority of the capabilities are known already. There are some specific optional features and format usages that may or may not be present (and thus require the use of <code>CheckFormatSupport</code> or <code>CheckFeatureSupport</code>), but most things can just be assumed based on the current device's Feature Level. This makes writing games and applications much simpler, and more importantly if something works for Feature Level X, then you can assume it will work for Feature Level X+1. This simplifies fallbacks as well, where the application only has to handle a few discrete cases. The HLSL shader profiles are designed so that a shader compiled for <code>4_0_level_9_1</code> will work on all feature levels, and a shader compiled for <code>4_0</code> will work on Feature Level 10.0, 10.1, 11.0, or 11.1 devices to limit the combinatorial explosion problem of shader permutations.
<!--more-->

The concept of Feature Levels was actually introduced back in Direct3D 10.1, but at the time there were only two of them: 10.0 and 10.1. With DirectX 11, we introduced both an 11.0 feature level and the "<a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/d3d11-graphics-reference-10level9">10level9</a>" technology for running on many Direct3D 9 era Shader Model 2.0 and 3.0 parts via the 9.1, 9.2, and 9.3 feature levels. DirectX 11.1 supports the same set of feature levels, and adds a new 11.1 feature level. The concept of feature levels was one of my key talking points for my Gamefest 2010 / GDC 2010 presentation <em><a href="https://walbourn.github.io/download/DirectX-11-Technology-Update.zip">DirectX 11 Technology Update</a>. </em>I've also filed a lot of documentation bugs to get this topic well-covered on <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/overviews-direct3d-11-devices-downlevel-intro">Microsoft Docs</a>.

This is an important topic for Windows Store apps (a.k.a. Metro style apps) as "DirectX 11" the API is required for these applications, but you will see potentially a wide range of feature levels on machines running Windows 8. See the GDC 2012 presentation <em>Developing Metro Style Games on the Full Range of Windows 8 Devices</em>. With the guidelines presented in the <a href="https://docs.microsoft.com/en-us/previous-versions/windows/hardware/cert-program/">Windows 8 Hardware Certification Requirements</a> document, most new desktop systems sold with Windows 8 will have Feature Level 10.0 or greater hardware--actually most gaming systems are likely to have Feature Level 11.0 or 11.1 even newer laptops with integrated graphics. For tablet form-factor systems, particularly those running Windows RT, most will be Feature Level 9.1 or Feature Level 9.3 at least in the near-term. To support any system running Windows 8 including upgraded machines, you have to support Feature Level 9.1 which may be sufficient for some kinds of applications but not others.

In my Gamefest 2010 talk I tried to make this a bit more concrete with a table. Here is the table updated with some new information. Note that the listed video cards are <em>examples</em> and not an exhaustive list of video cards that support that feature level.

<table border="1">
<tbody>
<tr>
<td><p><code>D3D_FEATURE_LEVEL_9_1</code>
(e.g. Intel G965 Express Chipset;
Surface RT; Surface 2)</p>
<p><em>Implies a WDDM 1.0 or later driver</em></p></td>
<td>Direct3D 9 hardware: must support Shader Model 2.0 (<code>vs_2_0/ps_2_0</code>), 2K textures, volume textures, event queries, BC1-3 (aka DXTn), and a few other specific capabilities.</td>
</tr>
<tr>
<td><code>D3D_FEATURE_LEVEL_9_2</code>
(e.g. ATI Radeon 9500)</td>
<td>Direct3D 9 hardware: must support Shader Model 2.0 (<code>vs_2_0/ps_2_0</code>), occlusion queries, floating-point formats (no blending), extended caps, all 9_1 features.</td>
</tr>
<tr>
<td><code>D3D_FEATURE_LEVEL_9_3</code>
(e.g. nVidia GeForce 6600;
ATI Radeon X1300)</td>
<td><p>Direct3D 9 hardware: must support Shader Model 2.0 (<code>vs_2_0/ps_2_x</code>) with instancing and additional shader caps, 4K textures, multiple render targets (4 MRTs), floating-point blending (limited), all 9_2 features.</p>
<p><em>Windows phone 8.x developers have access to this feature level.</em></p></td>
</tr>
<tr>
<td><code>D3D_FEATURE_LEVEL_10_0</code>
(e.g. ATI Radeon HD 2000;
nVidia GeForce 8/9;
Intel G965M Express Chipset, HD Graphics "Arrandale/Clarkdale")</td>
<td><p>Direct3D 10 hardware: Shader Model 4.0, geometry shader, stream out, alpha-to-coverage, 8K textures, MSAA textures, 2-sided stencil, general render target views, texture arrays, BC4/BC5, optional DirectCompute (CS 4.0), full floating-point format support, all 9_3 features.</p>
<p><em>Xbox One ADK / UWP developers have access to this feature level.</em></p></td>
</tr>
<tr>
<td><code>D3D_FEATURE_LEVEL_10_1</code>
(e.g. ATI Radeon HD 3000/4000;
nVidia GeForce GTX 300;
Intel HD Graphics 3000/2000 "Sandy
Bridge")</td>
<td>Direct3D 10.1 hardware: Shader Model 4.1, cubemap arrays, extended MSAA, optional DirectCompute (CS 4.1), all 10_0 features.</td>
</tr>
<tr>
<td><p><code>D3D_FEATURE_LEVEL_11_0</code>
(e.g. ATI Radeon HD 5000-7000;
nVidia Geforce GTX 400-700;
Intel HD Graphics 4000/2500 "Ivy Bridge"; Surface Pro)</p>
<p><em>Implies a WDDM 1.1 or later driver</em></p></td>
<td>Direct3D 11 hardware: Shader Model 5.0, hull & domain shaders, mandatory DirectCompute (CS 5.0), 16K textures, BC6H/BC7, all 10_1 features.</td>
</tr>
<tr>
<td><p><code>D3D_FEATURE_LEVEL_11_1</code>
(e.g. AMD Radeon HD 8000; nVidia GeForce GTX 900;
Intel HD Graphics 5000/4x00 "Haswell"; Intel "Broadwell"; Surface 3, Surface Pro 2, Surface Pro 3, Xbox One, HoloLens)</p>
<p><em>Implies a WDDM 1.2 or later driver</em></p></td>
<td><p>Direct3D 11.1 hardware: Shader Model 5.0 with optional extensions, Logical blend operations, Target-independent rasterization, UAVs at every stage, Constant buffer offsetting and partial updates, UAV only rendering with force sample count, all 11_0 features.</p>
<p>Note: This feature level is only available on Windows 8.x / Windows Server 2012 or later. <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/jj863687.aspx">DirectX 11.1 on Windows 7</a> does not support this feature level.</p>
<p><em>Xbox One XDK developers have access to this feature level plus additional platform-specific APIs.</em></p></td>
</tr>
<tr>
<td><p><code>D3D_FEATURE_LEVEL_12_0</code> (e.g. AMD Radeon 400/500 Series, nVidia GeForce 700/800 Series, Intel "Skylake-S")</code><br /><br />
<code>D3D_FEATURE_LEVEL_12_1</code> (e.g. AMD Radeon RX 5000 Series, nVidia GeForce 10/20 Series, Intel Xe-LP, Surface X Pro)</p>
<p><em>Implies a WDDM 2.0 or later driver</em></p></td>
<td><p>See <a href="https://channel9.msdn.com/Events/GDC/GDC-2015/Advanced-DirectX12-Graphics-and-Performance">Advanced DirectX12 Graphics and Performance</a> (GDC 2015).</p></td>
</tr>
<tr>
<td><p><code>D3D_FEATURE_LEVEL_12_2</code> (e.g. AMD Radeon RX 6000 Series, nVidia GeForce RTX 30 Series, Intel Xe-HPG, Xbox Series X/S)</p>
</td>
<td><p>See <a href="https://devblogs.microsoft.com/directx/new-in-directx-feature-level-12_2/">this blog post</a> about this new DirectX12 only feature level. Technical details are <a href="https://microsoft.github.io/DirectX-Specs/d3d/D3D12_FeatureLevel12_2.html#capabilities">here</a>.</p></td>
</tr>
</tbody>
</table>

See *Microsoft Docs: Direct3D feature levels* for <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/overviews-direct3d-11-devices-downlevel-intro">DX11</a> / <a href="https://docs.microsoft.com/en-us/windows/win32/direct3d12/hardware-feature-levels">DX12</a>, and the various <em>Hardware Support for Direct3D9 X Formats</em> pages in the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3ddxgi/dx-graphics-dxgi-overviews">DXGI</a> documentation.

By default, if you call <code>D3D11CreateDevice</code> or <code>D3D11CreateDeviceAndSwapChain</code> with the <code>pFeatureLevels</code> parameter set to <code>NULL</code> (or better yet <code>nullptr</code> for VS 2010 and VS 2012 developers!), then the system will try to create a device using the highest feature level available. Note for compatibility reasons, this does not include Feature Level 11.1 on machines with the DirectX 11.1 runtime installed. If you try to use <code>D3D_FEATURE_LEVEL_11_1</code> on a system with only the DirectX 11.0 runtime installed, it fails immediately. The solution is covered in <a href="https://walbourn.github.io/anatomy-of-direct3d-11-create-device/">Anatomy of Direct3D 11 Create Device</a>--the retry isn't needed for Windows Store apps where you can assume DirectX 11.1 runtime is always available.

<a href="https://docs.microsoft.com/en-us/windows/desktop/direct3darticles/directx-warp">WARP</a> supports Feature Level 9.1, 9.2, 9.3, 10, and 10.1 on systems with the DirectX 11.0 runtime. On a system with the DirectX 11.1 runtime, it supports 11.0 and 11.1 as well. Note that on <a href="https://walbourn.github.io/directx-11-1-and-windows-7-update/">Windows 7 SP1 with DirectX 11.1</a>, WARP supports 11.0, but not 11.1.

A few quirks of this system you should be aware of:

<ul>
 	<li>For technical reasons, you should prefer using Feature Level 10.0 or later when working with DirectX 10 class or later hardware. They typically support Feature Levels 9.1 - 9.3 as well, but it is more efficient to avoid using the "10level9" layer that emulates some aspects of Direct3D 10+ for Direct3D 9 devices.</li>
 	<li>Most hardware that supports a given feature level supports all the feature levels below it, but that is not actually <em>required</em> behavior. There are a few older integrated graphics parts that only support Feature Level 9.1 and Feature Level 10.0, but not 9.2 or 9.3. This also means that while most 10.x or 11.x class cards will also have support for Feature Level 9.1, 9.2, and 9.3 through the Direct3D 9 "10level9" layer, they aren't required to.</li>
 	<li>While compiling an HLSL shader using one of the <code>4_0_level_9_?</code> profiles, the shader is actually compiled twice. Once using a Shader Model 2.0 profile and again using the Shader Model 4.0 profile. This generally means you have to live with the limitations of the Shader Model 2.0 profile for these shaders. Note that these shaders are not actually written as legacy Shader Model 2.0 shaders and instead should use the modern HLSL syntax, but the limits on complexity and features from the older Shader Model 2.0 profiles will apply.</li>
 	<li>You will note there is no feature level which exposes Shader Model 3.0 profiles. Feature Level 9.3 does imply the hardware is actually a <a href="https://docs.microsoft.com/en-us/windows-hardware/drivers/display/reporting-capabilities-for-shader-3-support">Shader Model 3.0 compliant</a> device since it requires instancing. The <code>ps_2_x</code> profile with additional shader capabilities is supported but not the full Shader Model 3.0 profiles. This design was driven by the fact that not all Shader Model 3.0 cards really had the same feature set (notably ATI cards were "Shader Model 3.0" but didn't support vertex shader texture fetch, while other vendors did), and the rule that Shader Model 3.0 vertex and pixel shaders can't be mixed with 2.0 shaders which would have broken the general model for always being able to use a 'lower' profile shader on a 'higher' feature level. You have to use Feature Level 10.0 or later to get vertex shader texture fetch support.</li>
 	<li>There is no way for a given device to expose more features than those defined for a given feature level, with the exception of the few specific optional features defined for that level. For example, Feature Level 9.3 devices can optionally support texture filtering for <code>R16G16B16A16_FLOAT</code> formats, but cannot do so for other ``_FLOAT`` formats that are only supported for point sampling in the Feature Level 9.3 definition. You have to use Feature Level 10.0 or later to get full-featured floating-point resource support.</li>
 	<li>The one exception to the previous note is that maximum supported resource sizes (i.e. maximum texture width, height, or depth) is a minimum for a given feature level, but a device could support larger sizes which you can determine by trying to create a larger sized texture and it will return a failure.</li>
</ul>

<strong>XNA 4 Note:</strong> None of these feature levels directly maps to the XNA "Reach" or "HiDef" profiles. "Reach" is very similar to Feature Level 9.1, and "HiDef" is designed for the Shader Model 3.0 capabilities of the Xbox 360 so it's a bit more than Feature Level 9.3 offers but not as much as Feature Level 10.0.

<strong>Note:</strong> "10level9" feature levels require WDDM drivers and do not support legacy XPDM drivers--XPDM drivers are not supported at all on Windows 8.

<strong>Windows Phone 8:</strong> Windows phone 8 devices are Feature Level 9.3.

<strong>Detecting Feature Levels:</strong> Generally speaking, you determine if a device supports a given feature level by trying to create the device. There isn't an API that lets you enumerate feature level support from devices in DirectX 11. See <a href="https://walbourn.github.io/anatomy-of-direct3d-11-create-device/">Anatomy of Direct3D 11 Create Device</a>.

<strong>DirectX 12:</strong> To date, all Direct3D 12 supporting drivers are Feature Level 11.0 or later. For this reason, all Direct3D 12 samples use ``D3D_FEATURE_LEVEL_11_0`` as the MinimumFeatureLevel. If support for 9.x, 10.0, or 10.1 Direct3D feature level hardware is required, applications needs to make use of Direct3D 11. In DirectX 12, you create a device with a 'minimum' feature level, and then use <code>CheckFeatureSupport</code> to determine if the device supports any higher feature levels. See <a href="https://walbourn.github.io/anatomy-of-direct3d-12-create-device/">Anatomy of Direct3D 12 Create Device</a>. For DirectX 12 Hardware Feature Levels, see [Microsoft Docs](https://docs.microsoft.com/en-us/windows/desktop/direct3d12/hardware-feature-levels).

<strong>Related:</strong> <a href="https://walbourn.github.io/getting-started-with-direct3d-11/">Getting Started with Direct3D 11</a>, <a href="https://walbourn.github.io/getting-started-with-direct3d-12/">Getting Started with Direct3D 12</a>
