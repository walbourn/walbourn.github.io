---
layout: msdnpost
title: Samples Content Exporter Update
date: 2012-04-24 16:44
author: Chuck Walbourn
comments: true
categories: [dxsdk]
---
<em>DirectX SDK (June 2010) </em>includes the <em>Samples Content Exporter</em> utility for creating <code>.sdkmesh</code> data files using <a href="http://autodesk.com/fbx">Autodesk's FBX SDK</a> library. At the time, this utility used the 2010.2 version of the Autodesk FBX SDK which did not have support for Visual Studio 2010. Therefore, the VS 2010 project file was set up to require the VS 2008 toolset.
<!--more-->

Attached to this blog post is an updated version that uses Autodesk FBX SDK 2011.3.1 which does support VS 2010. The VS 2010 project file no longer requires the VS 2008 toolset. This version of the utility also supports building x64 native configurations and adds a new 'exportScale' export setting.

<strike>The update is subject to the same EULA as the DirectX SDK</a> (June 2010) release.</strike>. For documentation, install the DirectX SDK, open the <em>DirectX Software Development Kit</em> documentation file and view the topics <em>Samples Content Exporter</em> and <em>Overview of the SDK Mesh File Format</em>.
<p />

<strong>Disclaimer:</strong> <code>.SDKMESH</code> has been our long-time samples runtime geometry format since the retiring of the legacy .X file format. It has a number of limitations, and we don't recommend using it as a your production solution for meshes. It is, however, very useful for samples and itself serves as an example of such file containers. The Windows 8 DirectX sample <em>Marble Maze</em> makes use of <code>.SDKMESH</code> and the code for loading and rendering them for a Windows Store app (a.k.a. Metro style apps) can be found on the <a href="http://code.msdn.microsoft.com/windowsapps/DirectX-Marble-Maze-Game-e4806345/">Windows Samples Code Gallery</a>. Traditional Win32 desktop code for loading and rendering an <code>.SDKMESH</code> can be found in the <em>DirectX SDK (June 2010)</em>'s DXUT library. The documentation on the format can be found <a href="https://github.com/Microsoft/DirectXMesh/wiki/Geometry-formats#sdkmesh">here</a>.

Remember to set the <code>FBX_SDK</code> environment variable to the location of the 2011.3.1 <em>Autodesk FBX SDK</em> installed on your system (such as "``C:\Program Files\Autodesk\FBX\FbxSdk\2011.3.1``"). You are free to use either the DLL or static library version of the Autodesk FBX SDK, but would recommend using the DLL version which keeps the content exporter tool itself to around 1 MB instead of being nearly 7 MB.

<strike>The <em>Samples Content Exporter</em> relies on the legacy D3DX9 library that is only available in the DirectX SDK. If trying to build with Visual Studio 11, be sure to read through "<a href="https://aka.ms/dxsdk">Where is the DirectX SDK?</a>"</strike>
<p />

<strong>Update:</strong> This project is now hosted on <a href="https://github.com/walbourn/contentexporter">GitHub</a> and has been updated to support VS 2012 with Autodesk FBX SDK 2014.1 or later, and VS 2013 with Autodesk FBX SDK 2015.1 or later. It is available under the MIT license, and no longer makes use of the legacy DirectX SDK or D3DX9. See <a href="https://walbourn.github.io/samples-content-exporter/">Samples Content Exporter (May 2015)</a>.

<strong>Related: </strong><a href="https://github.com/Microsoft/DirectXTK/">DirectXTK</a> now has support for loading and rendering meshes from <code>.SDKMESH</code> files. Also, the meshconvert sample for <a href="http://go.microsoft.com/fwlink/?LinkID=324981">DirectXMesh</a> can convert Wavefront OBJ files to <code>.SDKMESH</code> files.
