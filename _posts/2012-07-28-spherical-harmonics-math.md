---
layout: post
title: Spherical Harmonics Math
date: 2012-07-28 00:03
author: Chuck Walbourn
comments: true
categories: [dxsdk, directxmath]
---
<a href="https://walbourn.github.io/introducing-directxmath/">DirectXMath</a> (aka XNAMath version 3) provides almost all the functionality of the original <a href="https://docs.microsoft.com/en-us/windows/desktop/dxmath/pg-xnamath-migration-d3dx">D3DXMath</a> library with two exceptions. The first is the '<a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d10/d3d10-id3dxmatrixstack">matrix stack</a>' helper and the second is the '<a href="http://en.wikipedia.org/wiki/Spherical_harmonics">spherical harmonics'</a> math functions. The <em>matrix stack</em> is fairly easy to implement, but the SH math functions are another story. The original code for SH math in the D3DX utility library was written by <a href="http://research.microsoft.com/en-us/um/people/johnsny/">John Snyder</a> (MSR) and <a href="http://www.ppsloan.org/">Peter-Pike Sloan</a> (former Microsoft now at NVIDIA), and was the basis for a number of DirectX SDK samples and graphics publications as well as several ATI/AMD demos. With the removal of the SH math functionality from D3DX11 and the retirement of the D3DX library generally (see <a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a>), this post provides a replacement for this functionality.
<!--more-->

> This post does not include the <em>Precomputed Radiance Transfer (PRT)</em> simulator that was shipped in D3DX9. You can continue to make use of that library for offline computations, and then use this post's SH math routines for runtime usage in a modern Direct3D 11 application without any legacy D3DX dependencies.

<h1>API</h1>

The <code>DirectXSH.h/.cpp</code> file pair provides the SH math functions. It is based on DirectXMath and requires Visual Studio 2012 or VS 2010 with the Windows 8.0 SDK.

<em>Note it is fairly easy to modify these files if you must use <a href="https://walbourn.github.io/xna-math-version-2-05-smoothing-the-transition-to-directxmath/">XNAMath</a> for compatibility with Xbox 360 or VS 2008 by removing namespaces and changing from SAL2 to VS-style SAL, but that is left as an exercise to the reader.</em>

<table border="1">
<tbody>
<tr>
<td><code>XMSHEvalDirection</code></td>
<td>Evaluates the Spherical Harmonic basis functions. Equivalent to <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d9/d3dxshevaldirection">D3DXSHEvalDirection</a> function.</td>
</tr>
<tr>
<td><code>XMSHRotate</code></td>
<td>Rotates SH vector by a rotation matrix. Equivalent to the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d10/d3d10-d3dxshrotate">D3DXSHRotate</a> function.</td>
</tr>
<tr>
<td><code>XMSHRotateZ</code></td>
<td>Rotates the SH vector in the Z axis by an angle. Equivalent to the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d9/d3dxshrotatez">D3DXSHRotateZ</a> function.</td>
</tr>
<tr>
<td><code>XMSHAdd</code></td>
<td>Adds two SH vectors. Equivalent to the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d9/d3dxshadd">D3DXSHAdd</a> function.</td>
</tr>
<tr>
<td><code>XMSHScale</code></td>
<td>Scales a SH vector. Equivalent to the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d10/d3d10-d3dxshscale">D3DXSHScale</a> function.</td>
</tr>
<tr>
<td><code>XMSHDot</code></td>
<td>Computes the dot product of two SH vectors. Equivalent to the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d9/d3dxshdot">D3DXSHDot</a> function.</td>
</tr>
<tr>
<td><code>XMSHMultiply
XMSHMultiply2
XMSHMultiply3
XMSHMultiply4
XMSHMultiply5
XMSHMultiply6</code></td>
<td>Computes the product of two functions represented using SH. Equivalent to <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d9/d3dxshmultiply2">D3DXSHMultiply2</a>, ``D3DXSHMultiply3``, ``D3DXSHMultiply4``, ``D3DXSHMultiply5``, and ``D3DXSHMultiply6``.</td>
</tr>
<tr>
<td><code>XMSHEvalDirectionalLight</code></td>
<td>Evaluates a directional light and returns spectral SH data. Equivalent to the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d10/d3d10-d3dxshevaldirectionallight">D3DXSHEvalDirectionalLight</a> function.</td>
</tr>
<tr>
<td><code>XMSHEvalSphericalLight</code></td>
<td>Evaluates a spherical light and returns spectral SH data. Equivalent to the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d9/d3dxshevalsphericallight">D3DXEvalSphericalLight</a> function.</td>
</tr>
<tr>
<td><code>XMSHEvalConeLight</code></td>
<td>Evaluates a light that is a cone of constant intensity and returns spectral SH data. Equivalent to the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d10/d3d10-d3dxshevalconelight">D3DXSHEvalConeLight</a> function.</td>
</tr>
<tr>
<td><code>XMSHEvalHemisphereLight</code></td>
<td>Evaluates a light that is a linear interpolant between two colors over the sphere. Equivalent to the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d10/d3d10-d3dxshevalhemispherelight">D3DXSHEvalHemisphereLight</a> function.</td>
</tr>
<tr>
<td><code>SHProjectCubeMap</code></td>
<td>Projects a function represented in a cube map into spherical harmonics. Equivalent to the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/d3dx11shprojectcubemap">D3DX11SHProjectCubeMap</a> function.</td>
</tr>
</tbody>
</table>

The <code>DirectXSHD3D11.cpp</code> module provides the function for computing the SH projection of a cubemap.

<table border="1">
<tbody>
<tr>
<td><code>SHProjectCubeMap</code></td>
<td>Projects a function represented in a cube map into spherical harmonics. Equivalent to the <a href="https://docs.microsoft.com/en-us/windows/desktop/direct3d11/d3dx11shprojectcubemap">D3DX11SHProjectCubeMap</a> function.</td>
</tr>
</tbody>
</table>

<strong>Update: </strong>The source code for this project is now available on <a href="https://github.com/Microsoft/DirectXMath">GitHub</a> under the <a href="http://opensource.org/licenses/MIT">MIT license</a>.

<h1>Further Reading</h1>

Green, Robin. <em>Spherical Harmonic Lighting: The Gritty Details</em>. <strong>Game Developers' Conference</strong>, San Jose, CA, March 2003. <a href="http://www.cs.columbia.edu/~cs4162/slides/spherical-harmonic-lighting.pdf">PDF</a>

<span class="reference-text"><span class="citation web">Kautz, Jan. Peter-Pike Sloan, Jaakko Lehtinen. <em>Precomputed Radiance Transfer: Theory and Practice</em>. <strong>SIGGRAPH 2005 Course</strong>. <a href="http://www0.cs.ucl.ac.uk/staff/j.kautz/PRTCourse/">Website</a>.</span></span>

Oat, Chris Oat and Natalya Tatarchuk. <em>Irradiance Volumes for </em>Games. <strong>Game Developers' Conference 2005</strong>, ATI Technologies, GDC 2005. <a href="http://developer.amd.com/media/gpu_assets/Tatarchuk_Irradiance_Volumes.pdf">PDF</a>

Sloan, Peter-Pike.<em> Stupid Spherical Harmonics (SH) Tricks. </em><strong>Game Developer Conference 2008 </strong><a href="http://www.ppsloan.org/publications/StupidSH36.pdf">PDF</a> <a href="http://www.ppsloan.org/publications/GDC08SH_web.pptx">PPTX</a>

Sloan, Peter-Pike, Jan Kautz, and John Snyder. <em>Precomputed Radiance Transfer for Real-Time Rendering in Dynamic, Low-Frequency Lighting Environments</em>. <strong>ACM Transactions on Graphics (TOG)</strong>, Proceedings of the 29th Annual Conference on Computer Graphics and Interactive Techniques (SIGGRAPH), pp. 527-536. New York, NY: ACM Press, 2002. <a href="http://www.ppsloan.org/publications/shillum_final23.pdf">PDF</a>

Sloan, Peter-Pike, Jesse Hall, John Hart, and John Snyder. <em>Clustered Principal Components for Precomputed Radiance Transfer</em>. <strong>ACM Transactions on Graphics (TOG)</strong>, Vol. 22, Issue 3 (SIGGRAPH), pp. 382-391. New York, NY: ACM Press, July 2003. <a href="http://www.ppsloan.org/publications/rtpca_final27.pdf">PDF</a>

Sloan, Peter-Pike, Ben Luna and John Snyder. <em>Local, Deformable Precomputed Radiance Transfer</em>. <strong>ACM Transaction on Graphics</strong> 24(3) [Proceedings of SIGGRAPH], 2005. <a href="http://www.ppsloan.org/publications/ldprt_final05.pdf">PDF</a> <a href="http://www.ppsloan.org/publications/LDPRT_28.ppt">PPT</a>

Sloan, Peter-Pike.<em> Normal Mapping for Precomputed Radiance Transfer</em>. <strong>ACM Symposium on Interactive 3D Graphics and Games 2006</strong>. March, 2006. <a href="http://www.ppsloan.org/publications/NMPRT.pdf">PDF</a> <a href="http://www.ppsloan.org/publications/I3D06_final.ppt">PPT</a>

Xinguo Liu, Peter-Pike Sloan, Heung-Yeung Shum and John Snyder. <em>All-Frequency Precomputed Radiance Transfer for Glossy Objects</em>. <strong>Eurographics Symposium on Rendering 2004</strong>, June, 2004. <a href="http://www.ppsloan.org/publications/allfreqegsr_final_electronicNEW.pdf">PDF</a>
