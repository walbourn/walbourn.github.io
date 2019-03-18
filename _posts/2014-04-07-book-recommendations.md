---
layout: post
title: Book Recommendations
date: 2014-04-07 10:00
author: Chuck Walbourn
comments: true
categories: [direct3d]
---
Over the years, I've been asked about book recommendations, and it's been challenging to keep up with them. I recently had a chance to review some books including a few prior to publication, so I've rounded up some recommendations for DirectX 11. Here I present them in chronological order of their publication date.
<!--more-->

<h1>Practical Rendering and Computation with Direct3D 11</h1>

Zink et al, <em>Practical Rendering and Computation with Direct3D 11</em>, A K Peters/CRC Press (July 27, 2011)

<a href="http://www.amazon.com/Practical-Rendering-Computation-Direct3D-11/dp/1568817207/ref=sr_1_1?ie=UTF8&qid=1395900582&sr=8-1&keywords=practical+rendering+and+computation+with+direct3d+11">Amazon</a>, <a href="http://www.crcpress.com/product/isbn/9781568817200">Publisher</a>

If you are looking for comprehensive coverage for the entire Direct3D 11.0 API, this is the book to get. The detail and completeness is impressive, and it covers it all including HLSL. This text is definitely handy for both C++ and C# developers using a wrapper like SharpDX or SlimDX. The book was released before Direct3D 11.1 or 11.2 so the current printing doesn't cover these, but the foundation here is great. If you ever wished there was a "Red Book" for Direct3D, then this is a great addition to your library.
<h1>Introduction to 3D Game Programming with DirectX 11</h1>
Luna, <em>Introduction to 3D Game Programming with DirectX 11</em>, Mercury Learning & Information (March 2, 2012)

<a href="http://www.amazon.com/Introduction-3D-Game-Programming-DirectX/dp/1936420228/ref=sr_1_1?s=books&ie=UTF8&qid=1395900748&sr=1-1">Amazon</a>, <a href="http://www.merclearning.com/titles/3d_game_programming_directx11.html">Publisher</a>

This is the latest in a series of such books, and the format is well-honed and refined. If you are looking for an introduction to all the basics of 3D transformation math and Direct3D rendering techniques, with samples in C++, this is a good place to start. That said, it's very much rooted in the now legacy DirectX SDK and Win32 desktop programming model. It's still very relevant for more modern Direct3D 11.x platforms, but you'll need to keep in mind the differences between XNA Math and DirectXMath, the replacements for D3DX11, and the status of Effects 11. This book also serves as an excellent introductory text and with extensive examples for DirectXMath.

<strong>Update:</strong> There is also a Luna, <em>Introduction to 3D Game Programming with DirectX 12, </em>Mercury Learning & Information (March 24, 2016). It's the same basic material but using DirectX 12 instead of DirectX 11. My general belief is that if you are new to DirectX development, you should start with DirectX 11 before attempting to use DirectX 12 which is a much less forgiving API. In general the DirectX 12 book is quite good, although I noted a few places where the original DirectX 11 material wasn't updated. The only downside to the new book IMO is that it was published before the <a href="https://github.com/Microsoft/DirectXTK12">DirectX Toolkit for DirectX 12</a> was available which would have simplified some of the utility code required for loading textures, etc. Otherwise, a good start to finish introduction to the new API.
<h1>Direct3D Rendering Cookbook</h1>
Stenning, <em>Direct3D Rendering Cookbook</em>, Packt Publishing (January 21, 2014)

<a href="http://www.amazon.com/Direct3D-Rendering-Cookbook-Justin-Stenning/dp/1849697108/ref=sr_1_1?ie=UTF8&qid=1395900538&sr=8-1&keywords=Direct3D+Rendering+Cookbook">Amazon</a>, <a href="http://www.packtpub.com/direct3d-rendering-cookbook/book">Publisher</a>

For developers more comfortable with C#, this book demonstrates the Direct3D 11.x API using SharpDX in a very step-by-step manner. The coverage includes advanced techniques including hardware tessellation and deferred shading, so it's definitely a good resource for anyone doing graphics or 3D games in C#. It also covers Windows Store apps development in some detail.
<h1>Real-Time 3D Rendering with DirectX and HLSL</h1>
Varcholik, <em>Real-Time 3D Rendering with DirectX and HLSL: A Practical Guide to Graphics Programming</em>, Addison-Wesley (May 31, 2014)

<a href="http://www.amazon.com/Real-Time-Rendering-DirectX-HLSL-Programming/dp/0321962729/ref=sr_1_fkmr1_1?ie=UTF8&qid=1395900459&sr=8-1-fkmr1&keywords=Real+Time+3D+Rendering+with+DirectX+11+and+HLSL%3A">Amazon</a>, <a href="http://www.informit.com/store/real-time-3d-rendering-with-directx-and-hlsl-a-practical-9780321962720">Publisher</a>

This book focuses on implementing numerous techniques using HLSL with Direct3D 11.1. With the emphasis on HLSL code, it should be equally useful to both C++ and C# developers looking to implement advanced graphics techniques.

<strong>Related:</strong> <a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a>, <a href="https://walbourn.github.io/where-is-the-directx-sdk-2013-edition/">Where is the DirectX SDK (2013 Edition)?</a>, <a href="https://walbourn.github.io/where-is-the-directx-sdk-2015-edition/">Where is the DirectX SDK (2015 Edition)?</a>, <a href="https://walbourn.github.io/living-without-d3dx/">Living without D3DX</a>, <a href="https://walbourn.github.io/effects-for-direct3d-11-update/">Effects for Direct3D 11 Update</a>
