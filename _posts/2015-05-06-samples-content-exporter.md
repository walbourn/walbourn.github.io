---
layout: post
title: Samples Content Exporter
date: 2015-05-06 14:36
author: walbourn
comments: true
categories: [dxsdk, github, Uncategorized]
---
<p>The legacy<em>&nbsp;DirectX SDK (June 2010) </em>included the <em>Samples Content Exporter</em> utility for creating <code>.sdkmesh</code> data files using <a href="http://autodesk.com/fbx">Autodesk's FBX SDK</a> library. At the time, this utility used the 2010.2 version of the Autodesk FBX SDK which did not have support for Visual Studio 2010, and only worked with the VS 2008 toolset.</p>
<p>The latest version of this sample is now hosted on <a href="https://github.com/walbourn/contentexporter">GitHub</a> under the MIT license.</p>
<p>You can build this version&nbsp;of the utility using VS 2013 and Autodesk FBX SDK 2015.1 or 2016.0; VS 2012 and Autodesk FBX SDK&nbsp;2014.1 or later; or VS 2010 with the <a href="http://go.microsoft.com/fwlink/?LinkID=323507">standalone Windows 8.1 SDK</a> and Autodesk FBX SDK 2013.3.1 or later.</p>
<p>For the latest documentation on the Samples Content Exporter, see the <a href="https://github.com/walbourn/contentexporter/wiki">wiki on GitHub</a>.</p>
<p><strong>Disclaimer:</strong> <code>.SDKMESH</code> has been our long-time samples runtime geometry format since the retiring of the legacy .X file format. It has a number of limitations, and we don't recommend using it as a your production solution for meshes. It is, however, very useful for samples and itself serves as an example of such file containers. Support for loading this file format can be found in <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectX Tool Kit library</a> and the <a href="http://go.microsoft.com/fwlink/?LinkId=320437">DXUT for Direct3D 11 framework</a>. The documentation on the format can be found <a href="https://github.com/walbourn/contentexporter/wiki/SDKMESH">here</a>.</p>
<p><strong>Related: </strong><a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/24/samples-content-exporter-update.aspx">Samples Content Exporter Update (April 2012)</a></p>
