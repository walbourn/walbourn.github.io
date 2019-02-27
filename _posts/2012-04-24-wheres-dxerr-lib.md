---
layout: post
title: Where's DXERR.LIB?
date: 2012-04-24 12:28
author: walbourn
comments: true
categories: [dxsdk, Uncategorized]
---
One of the little utility libraries in the <em>DirectX SDK</em> is a static library for converting HRESULTs to text strings for debugging and diagnostics known as <code>DXERR.LIB</code>. There were once even older versions of this library, <code>DXERR8.LIB</code> and <code>DXERR9.LIB</code>, but they were removed from the <em>DirectX SDK</em> many years back in favor of a unified <code>DXERR.LIB</code>. The <em>DirectX Error Lookup Utility</em> is nothing more than a little front-end UI tool for getting results from <code>DXERR.LIB</code>.

For the <em>Windows SDK 8.0</em> this library was not brought forward (see "<a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">Where is the DirectX SDK?</a>"). This is primarily because HRESULTS for DirectX graphics APIs were added to the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ms679351.aspx">FormatMessage</a> function when using <code>FORMAT_MESSAGE_FROM_SYSTEM</code> in Windows 8 which already supports most of the system error codes reported by DXERR. The <em>DirectX SDK</em> version of <code>DXERR.LIB</code> also contained a lot of error codes for legacy components that are no longer relevant to development using the <em>Windows SDK 8.0</em>.

<code>DXERR.LIB</code> contained the following functions (both ASCII and UNICODE):
<ul>
 	<li><code>DXGetErrorString</code></li>
 	<li><code>DXGetErrorDescription</code></li>
 	<li><code>DXTrace</code></li>
</ul>
And the macros <code>DXTRACE_MSG, DXTRACE_ERR, DXTRACE_ERR_MSGBOX</code>

If you are still using legacy components like D3DX, DXUT, etc. from the <em>DirectX SDK</em> then you can continue to link to the legacy version of <code>DXERR.LIB</code> as well. For those wanting to get away from dependancies on the <em>DirectX SDK</em> as we've recommended, I've attached a streamlined version of the library to this post. It only supports UNICODE and I had to change <code>DXGetErrorDescription</code> to copy the result to a buffer rather than return a static string in order to make use of <code>FormatMessage</code> where possible, but otherwise it should serve much the same purpose. You can modify it to suit your needs a well.

<strong>Note:</strong> The <code>FormatMessage</code> flag <code>FORMAT_MESSAGE_ALLOCATE_BUFFER</code> is not supported for Windows Store apps because it makes use of <code>LocalAlloc</code>.

The source code for this package is bound to the <a href="http://www.microsoft.com/en-us/openness/licenses.aspx#MPL">Microsoft Public License (Ms-PL)</a>.

While we are on the topic of utility libraries, the <code>DXGUID.LIB</code> static library is also present in the <em>Windows SDK 8.0</em> with the Direct3D 11.1, Direct2D, DirectWrite, and WIC GUIDs added; and the XACT and XAUDIO2 GUIDs removed. There's nothing particular special about <code>DXGUID.LIB</code> because you could easily define the GUIDs using <code>#define INITGUID</code> before including the relevant headers in one (and only one) module of your program yourself, but it is very convenient not to have to do that.

<strong>Update:</strong> in <code>DXTraceW</code> now takes <code>__FILEW__</code> along with some /analyze and /W4 cleanup, support for <code>WINAPI_FAMILY</code> macros; define NOMINMAX; some fixes for VS 2015 printf string portability, package updated on November 9, 2015.

<strong>DXUT: </strong>This DXERR is included in the <a href="http://blogs.msdn.com/b/chuckw/archive/2013/09/14/dxut-for-win32-desktop-update.aspx">DXUT for Win32 Desktop Update</a>

<strong>VS 2015/2017: </strong>The VS 2015/2017 C Runtime is not compatible with the <code>DXERR.LIB</code> that ships in the legacy DirectX SDK. You will get link errors trying to use it. You can use this module to replace DXERR LIB but will have to rebuild the code that uses it. You can try linking with <code>legacy_stdio_definitions.lib</code> instead, but ideally you'd remove this dependency on the legacy DirectX SDK.

<a href="https://msdnshared.blob.core.windows.net/media/MSDNBlogsFS/prod.evol.blogs.msdn.com/CommunityServer.Components.PostAttachments/00/10/29/73/07/dxerr_nov2015.zip">dxerr_nov2015.zip</a>
