---
layout: post
title: Object Naming
date: 2010-04-15 12:07
author: walbourn
comments: true
categories: [direct3d, pixw, Uncategorized]
---
<p>One of the new features for the <em>PIX for Windows </em>tool for the upcoming June 2010 DirectX SDK release&nbsp;is support for object naming. This is a long-standing feature of the Direct3D 10.x and Direct3D 11 SDK Debug Layers, but not a well advertised one. We've mentioned it in a few talks (including in the appendix to my recent Gamefest 2010 and GDC 2010 <em>DirectX 11 Technology Update</em>), but as we are still going through the process of posting this material I thought I would take a few moments to highlight it.</p>
<p>When using the SDK Debug Layer, you will get diagnostic messages about resources like:</p>
<p><code>D3D11: INFO: Destroy Buffer: Name="unnamed", Addr=0x002A55A4 [ STATE_CREATION INFO #2097230: DESTROY_BUFFER ]</code></p>
<p>While I'm sure everyone finds hexidecimal dumps of pointers incredibly informative, it would be nice if you&nbsp;had an easy way to associate a label with it for debugging purposes. That's where Object Naming comes in. You see the <code>Name="unnamed" part</code>? That's because the default name is being used here and looks like every other unnamed object in your application.</p>
<p>To name objects for the SDK Debug Layer, you make use of the <strong>SetPrivateData</strong> API that is part of the root interface for both Direct3D 10.x and 11. The method's signature is:</p>
<p><code>HRESULT SetPrivateData(&nbsp; REFGUID guid, UINT DataSize,&nbsp; const void *pData );</code></p>
<p>Which as you can see is very generic. The runtime itself does not recognize any GUID here, but the SDK's Debug Layer does intercept it when using certain special&nbsp;GUIDs. The only one currently defined is <strong>WKPDID_D3DDebugObjectName</strong> (the "WK" standing for, somewhat ironically in this case, "Well Known"), defined in the <code>D3DCommon.h</code> header. It takes a pointer to an&nbsp;ASCII (not Unicode) buffer, and the size should be the length of the string ignoring the terminating NUL. Something like the following:</p>
<p><code>#if defined(_DEBUG) || defined(PROFILE)<br />// Only works if device is created with the D3D10 or D3D11 debug layer, or when attached to PIX for Windows<br />const char c_szName[] = "texture.jpg";<br />pObject-&gt;SetPrivateData( WKPDID_D3DDebugObjectName,<br />&nbsp;sizeof( c_szName ) - 1, c_szName );<br />#endif</code></p>
<p>This ASCII string is captured by the SDK Debug Layer and included in diganostic messages using that object.</p>
<p>Neat!</p>
<p>The new <em>PIX for Windows</em> feature for June 2010 is that it too recognizes these names and includes them in the buffer views, making them useful for both the debug layer as well as PIX debugging and performance work. This could also be used by other third-party tools as well since it is a "well-known" GUID. To make this feature easier to use, we've also added a helper macro <code>DXUT_SetDebugName()</code> to both <strong>DXUT </strong>and <strong>DXUT11 </strong>in the <code>DXUTmisc.h</code> header for June 2010, as well as defining the GUID in the DXGUID.LIB library.</p>
<p><strong>Update: </strong>Note that we also updated the Direct3D 11 samples, DXUT, and DXUT11 to populate debug names (in DEBUG and PROFILE configurations). Running <em>PIX for WIndows </em>on these samples should show object names for most items in the "Objects" window.</p>
<p><strong>Additional:</strong> There is also a nice C++ way to do this as well:</p>
<p><code class="cplusplus">template&lt;UINT TNameLength&gt;<br />inline void SetDebugObjectName(_In_ ID3D11DeviceChild* resource,<br />_In_z_ const char (&amp;name)[TNameLength])<br /> {<br />&nbsp; #if defined(_DEBUG) || defined(PROFILE)<br />&nbsp;&nbsp;&nbsp;&nbsp; resource-&gt;SetPrivateData(WKPDID_D3DDebugObjectName, TNameLength - 1, name);<br />&nbsp; #endif<br /> }<br /> <br /> SetDebugObjectName( pObject, "texture.jpg" );</code></p>
<p><strong>Direct3D 12:</strong> There is a <code>SetName</code> method you can use for object naming. Note that it takes a Unicode rather than ANSI string.</p>
