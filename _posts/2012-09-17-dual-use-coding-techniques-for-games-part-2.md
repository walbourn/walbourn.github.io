---
layout: post
title: Dual-use Coding Techniques for Games, part 2
date: 2012-09-17 17:25
author: walbourn
comments: true
categories: [Uncategorized, win10, win8, winphone, xbox one]
---
<em>Writing shared code for Windows Store, Xbox One, Universal Windows Platform (UWP) apps, and Win32 desktop apps</em>

(continued from <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/17/dual-use-coding-techniques-for-games.aspx">part 1</a>)
<h1>Win32 APIs</h1>
The majority of the “core” API family are new Windows Runtime (WinRT) style APIs which are not available for down-level Win32 desktop applications. Therefore the overlap is in Win32 APIs that are available to both kinds of applications. In many cases, the Windows Store apps ‘core’ API family contains a Win32 API that is very recent. Therefore, a key technique for writing dual-use code properly is learning to leverage the <code>_WIN32_WINNT</code> control define for <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745.aspx">Windows Headers</a>.
<ul>
 	<li>For Windows 8.1 support, <code>_WIN32_WINNT</code> is 0x0603 which is the default with the Windows 8.1 SDK / VS 2013 and is the value you expect to use for Windows Store apps for Windows 8.1 and Windows phone 8.1.</li>
 	<li>For Windows 8.x support, <code>_WIN32_WINNT</code> is 0x0602 which is the default with the Windows 8.0 SDK / VS 2012 and is the value you expect to use for Windows Store apps for Windows 8.0, Windows phone 8.0, and Xbox One.</li>
 	<li>For Windows 7 and Windows 8.x Win32 desktop support, <code>_WIN32_WINNT</code> should be 0x0601.</li>
 	<li>For Windows Vista, Windows 7, and Windows 8.x Win32 desktop support, <code>_WIN32_WINNT</code> should be 0x0600.</li>
 	<li>For Windows XP SP3 or Windows Server 2003 SP2, you must set <code>_WIN32_WINNT</code> to 0x0501 and use a Platform Toolset of "v110_xp" or "v120_xp" which selects the Windows 7.1 SDK that has <a href="http://blogs.msdn.com/b/chuckw/archive/2012/11/26/visual-studio-2012-update-1.aspx">limited DirectX integration</a>. <em>The Windows 8.x SDK does not support any platform prior to Windows Vista</em>.</li>
</ul>
<strong>Windows 10: </strong>For Windows 10 support, <code>_WIN32_WINNT</code> is 0x0A00 which is the default with the Windows 10 SDK / VS 2015 and is the value you expect to use for Universal Windows Platform (UWP) apps.

<strong>Note: </strong>There are defines for these version constants, but be aware of the mix of Windows SDK versions you are building your code against. For example, <code>_WIN32_WINNT_WIN10 </code>is only defined for Windows 10 SDK, <code>_WIN32_WINNT_WINBLUE </code>is missing from the Windows 8.0 SDK, and <code>_WIN32_WINNT_WIN8</code> is not in the Windows 7.1 SDK. You can define your own symbol if it is not already defined, but particularly in 'public' headers the direct use of the version numbers is the most robust choice.

<strong>Note: </strong>For Win32 APIs, you should prefer the use of the standard <code>_WIN32_WINNT</code> control define to conditional compile for Windows Store apps rather than symbol trying to make use of <code>WINAPI_FAMILY</code> macros directly.

For example, for Windows Store apps <code>CreateFile2</code> must be used which is a Windows 8 only API. For down-level support, you will want to use <code>CreateFile</code>.
<pre class="scroll"><code class="cplusplus"> #if (_WIN32_WINNT &gt;= 0x0602 /*_WIN32_WINNT_WIN8*/)
ScopedHandle hFile( safe_handle(
CreateFile2( szFile, GENERIC_READ, FILE_SHARE_READ,
OPEN_EXISTING, nullptr ) ) );

#else

ScopedHandle hFile( safe_handle(
CreateFile( szFile, GENERIC_READ, FILE_SHARE_READ, nullptr,
OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr ) ) );

#endif

if ( !hFile )
{
return HRESULT_FROM_WIN32( GetLastError() );
}
</code></pre>
<strong>Note:</strong> There's one more detail in this particular case. For Windows Store apps, the typical default <code>dwShareMode</code> of 0 is likely to cause problems when you are trying to open a file for read-only access because ‘exclusive’ mode is only granted for files which the app has write privileges. If using a <code>dwDesiredAccess</code> of <code>GENERIC_READ</code>, you want to use <code>dwShareMode</code> of <code>FILE_SHARE_READ</code> as shown here.

Dual-use shared code should always make use of Unicode to support Windows Store apps (<code>UNICODE</code> and <code>_UNICODE</code> are defined) and is fully supported on down-level Win32 desktop apps. Universal use of Unicode and <code>wchar_t</code> is recommended, although <code>TCHAR</code> is still available if legacy ASCII/multi-byte support is required for some Win32 desktop scenario.

Here are a number of Win32 APIs that are available to Windows Store apps when using the latest version.
<table border="1">
<tbody>
<tr>
<td><strong>Older API</strong></td>
<td><strong>“Core” Win32 API</strong></td>
<td><strong><code>_WIN32_WINNT</code> Required</strong></td>
</tr>
<tr>
<td><code>GetDiskFreeSpace*</code></td>
<td><code>GetDiskFreeSpaceEx</code></td>
<td></td>
</tr>
<tr>
<td><code>GetFileAttributes*</code></td>
<td><code>GetFileAttributesEx</code></td>
<td></td>
</tr>
<tr>
<td><code>FindFirstFile*</code></td>
<td><code>FindFirstFileEx</code></td>
<td></td>
</tr>
<tr>
<td><code>LockFile</code></td>
<td><code>LockFileEx</code></td>
<td></td>
</tr>
<tr>
<td><code>MoveFile</code></td>
<td><code>MoveFileEx</code></td>
<td></td>
</tr>
<tr>
<td><code>SetFilePointer*</code></td>
<td><code>SetFilePointerEx</code></td>
<td></td>
</tr>
<tr>
<td><code>UnlockFile</code></td>
<td><code>UnlockFileEx</code></td>
<td></td>
</tr>
<tr>
<td><code>WaitForMultipleObjects*</code></td>
<td><code>WaitForMultipleObjectsEx</code></td>
<td></td>
</tr>
<tr>
<td><code>WaitForSingleObject*</code></td>
<td><code>WaitForSingleObjectEx</code></td>
<td></td>
</tr>
<tr>
<td><code>CreateEvent*</code></td>
<td><code>CreateEventEx</code></td>
<td>0x0600 (Windows Vista)</td>
</tr>
<tr>
<td><code>CreateMutex*</code></td>
<td><code>CreateMutexEx</code></td>
<td>0x0600 (Windows Vista)</td>
</tr>
<tr>
<td><code>CreateSemaphore*</code></td>
<td><code>CreateSemaphoreEx</code></td>
<td>0x0600 (Windows Vista)</td>
</tr>
<tr>
<td><code>GetFileSize
GetFileSizeEx*</code></td>
<td><code>GetFileInformationByHandleEx</code></td>
<td>0x0600 (Windows Vista)</td>
</tr>
<tr>
<td><code>GetTickCount
timeGetTime</code></td>
<td><code>GetTickCount64</code></td>
<td>0x0600 (Windows Vista)</td>
</tr>
<tr>
<td><code>InitializeCriticalSection*
InitializeCriticalSectionAndSpinCount*</code></td>
<td><code>InitializeCriticalSectionEx</code></td>
<td>0x0600 (Windows Vista)</td>
</tr>
<tr>
<td><code>CopyFile, CopyFileEx</code></td>
<td><code>CopyFile2</code></td>
<td>0x0601 (Windows 7)</td>
</tr>
<tr>
<td><code>CoCreateInstance*
CoCreateInstanceEx*</code></td>
<td><code>CoCreateInstanceFromApp</code></td>
<td>0x0602 (Windows 8)</td>
</tr>
<tr>
<td><code>CreateFile</code></td>
<td><code>CreateFile2</code></td>
<td>0x0602 (Windows 8)</td>
</tr>
<tr>
<td><code>CreateFileMapping*</code></td>
<td><code>CreateFileMappingFromApp</code></td>
<td>0x0602 (Windows 8)</td>
</tr>
<tr>
<td><code>GetOverlappedResult*</code></td>
<td><code>GetOverlappedResultEx</code></td>
<td>0x0602 (Windows 8)</td>
</tr>
<tr>
<td><code>MapViewOfFile*
MapViewOfFileEx<strong></strong></code></td>
<td><code>MapViewOfFileFromApp</code></td>
<td>0x0602 (Windows 8)</td>
</tr>
</tbody>
</table>
<strong>Windows 10:</strong> The APIs denoted by * above were added back for Universal Windows Platform (UWP) apps as of the Windows 10 Anniversary Update SDK (14393) to reduce porting changes.

<strong>Note: </strong><code>ReadFile</code> and <code>WriteFile</code> are available for Windows Store apps and Windows phone 8, but <code>ReadFileEx</code> and <code>WriteFileEx</code> are not. They are supported for Universal Windows Platform (UWP) apps as of the Windows 10 Anniversary Update SDK (14393).

Here are some additional notes on Win32 APIs commonly used by games.
<table border="1">
<tbody>
<tr>
<td><strong>Win32 API</strong></td>
<td><strong>Description</strong></td>
</tr>
<tr>
<td><code>CreateThread
SetThreadIdealProcessor
SetThreadPriority
Sleep(Ex)
TlsAlloc</code></td>
<td>Windows Store apps for Windows 8.0 do not support POSIX-style threading APIs. These applications must use the Windows Runtime (WinRT) ThreadPool API in <code>Windows.System.Threading</code>.

For dual-use coding, you can make use of the C++11 Standard Library threading support and/or the Concurrency Runtime (ConcRT) which is supported for both Windows Store apps and Win32 desktop apps.

<strong>Update</strong>: Windows Store apps for Windows 8.1 can now use these threading APIs as of VS 2013 Update 4. They are also supported for Windows phone 8.1, Xbox One apps, and Universal Windows Platform (UWP) apps for Windows 10.</td>
</tr>
<tr>
<td><code>CreateProcess
GetCommandLine
GetEnvironmentStrings</code></td>
<td>Windows Store apps do not support POSIX-style process, command-line or environment variable APIs. These applications must use the Launcher class in the <code>Windows.System</code> namespace.

<em>Note:</em> Xbox One XDK supports some of these Win32 process APIs.</td>
</tr>
<tr>
<td><code>FindResource(Ex)
LoadResource
LockResource</code>
etc.</td>
<td>Windows Store apps do not use Win32 style resource files. The recommendation is to include the required data as part of the AppX package and use standard file I/O to access them.</td>
</tr>
<tr>
<td><code>RegOpenKey(Ex)
RegQueryKey(Ex)
RegSetKey(Ex)</code>
etc.</td>
<td>Windows Store apps do not use the Win32 registry. The recommendation is to store settings data in the application local directory using standard file I/O.</td>
</tr>
<tr>
<td><code>GlobalMemoryStatus(Ex)</code></td>
<td>There is no Windows Store app function available that will return physical or virtual memory information.

<strong>Windows 10:</strong> This is now supported for Universal Windows Platform (UWP) apps as of the Windows 10 Anniversary Update SDK (14393).</td>
</tr>
<tr>
<td><code>HeapAlloc</code></td>
<td>This is the standard memory allocation routine family is available for all applications.

<code>LocalAlloc, GlobalAlloc</code> are only available for Win32 desktop applications..

<code>VirtualAlloc</code> is not available for Windows 8.x Store apps or Windows phone 8.x apps.

<em>Note:</em> Xbox One XDK does support <code>VirtualAlloc</code> but does not allow EXECUTE page-level permission.

<strong>Windows 10:</strong> <code>VirtualAlloc</code> is supported for Universal Windows Platform (UWP) apps for Windows 10 as a remap for the new <code>VirtualAllocFromApp</code>.</td>
</tr>
<tr>
<td><code>LoadLibrary(Ex)</code></td>
<td>Windows Store apps must use <code>LoadPackagedLibrary</code> and the target DLL must be present in the application package or listed in the AppX manifest. The target DLL must therefore pass the Windows App Certification Kit (WACK) tool validation.

You have to use implicit linking with system DLLs, although you can use <code>/DELAYLOAD</code> if desired.</td>
</tr>
<tr>
<td><code>LoadString</code></td>
<td>Windows Store apps do not use Win32 style resource files for localization. These applications use <code>ResourceLoader</code> in the <code>Windows.ApplicationModel.Resources</code> namespace. See <a href="https://msdn.microsoft.com/en-us/library/windows/apps/hh694557.aspx">MSDN</a> for more details.

Dual-use shared code should avoid directly displaying strings and should leave localization to the client application.</td>
</tr>
<tr>
<td><code>GetLogicalProcessorInformation</code></td>
<td>Windows store apps can't call GLPI. They can use <code>GetNativeSystemInfo</code> to get a rough count of the number of logical processors, and <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/mt186420.aspx">CPU Sets</a> offers more details.

<strong>Windows 10:</strong> This is now supported for Universal Windows Platform (UWP) apps as of the Windows 10 Anniversary Update SDK (14393). CPU Sets is still a better option for UWPs running on non-Desktop family devices.</td>
</tr>
<tr>
<td>OpenGL</td>
<td>OpenGL is not supported for Windows Store apps, Windows phone 8.x, Xbox One, or Universal Windows Platform (UWP) apps for Windows 10.

<em>Note: </em>For OpenGL ES applications, you may find the <a href="https://code.google.com/p/angleproject/">Angle project</a> useful.</td>
</tr>
<tr>
<td><code>QueryPerformanceCounter
QueryPeformanceFrequency</code></td>
<td>These functions are supported for all applications as the basis for <a href="http://blogs.msdn.com/b/chuckw/archive/2014/12/03/understanding-game-time-revisited.aspx">high-resolution timers</a>.</td>
</tr>
<tr>
<td><code>timeBeginPeriod
timeEndPeriod</code></td>
<td>Windows Store apps cannot change the global system timer resolution as this can negatively impact power-saving modes.</td>
</tr>
<tr>
<td>WinSock</td>
<td>The Windows Sockets 2 API is not available for Windows Store apps for Windows 8.0 and they must use the Windows Runtime (WinRT) API <code>Windows.Networking.Sockets</code> instead. TCP and UDP layer network communications are therefore not a good candidate for dual-use shared code, although an abstraction could be written with two different implementations.

<strong>Update:</strong> Windows Store apps for Windows 8.1 can now use WinSock 2.x as of VS 2013 Update 3. See <a href="http://blogs.windows.com/buildingapps/2014/10/13/winsock-and-more-open-source-for-your-windows-store-apps/">this post</a>. Winsock 2.x is also supported for Windows phone 8.x, Xbox One apps, and Universal Windows Platform (UWP) apps for Windows 10. Note that this support requires an <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/bb513665.aspx">IP-neutral dual-stack</a> implementation (i.e. not legacy IPv4 only)

<em>DirectPlay is not supported for Windows Store apps, Windows phone 8.x, Xbox One, or Universal Windows Platform (UWP) apps for Windows 10. DirectPlay is not recommended for Win32 desktop apps.</em></td>
</tr>
</tbody>
</table>
<h1>DirectX and Media Technologies</h1>
One of the reasons that dual-use shared code is possible for game technology is because many of the traditional DirectX Win32 APIs are available for Windows Store apps as well as down level for Win32 desktop apps.
<table border="1">
<tbody>
<tr>
<td><strong>DirectX Technology</strong></td>
<td><strong>Notes</strong></td>
</tr>
<tr>
<td>Direct3D 11.0, DXGI 1.1, Direct2D, and DirectWrite</td>
<td>These technologies are available for Windows Store apps, Universal Windows Platform (UWP) apps for Windows 10, and Win32 desktop apps for Windows 10, Windows 8.x, Windows 7, and Windows Vista SP2+<a href="http://support.microsoft.com/kb/971644">KB971644</a>.

<em>Direct3D 9 and Direct3D 10.x are not supported for Windows Store apps, Windows phone 8.x, Universal Windows Platform (UWP) apps for Windows 10, or Xbox One</em>.

<em>Note:</em> Windows phone 8.0 and Xbox One XDK do not support Direct2D or DirectWrite.</td>
</tr>
<tr>
<td>Direct3D 11.1, DXGI 1.2, improved Direct2D and DirectWrite</td>
<td>These technologies are available for Windows Store apps, Universal Windows Platform (UWP) apps for Windows 10, and Win32 desktop apps on Windows 8.x and Windows 10. <a href="http://msdn.microsoft.com/en-us/library/jj863687.aspx">Partial support</a> for these APIs is available for Win32 desktop applications on Windows 7 Service Pack 1 via <a href="http://support.microsoft.com/kb/2670838">KB 2670838</a>.

Windows Store apps can rely on these technologies always being present, while Win32 desktop applications need to provide suitable fallbacks for older versions of Windows.</td>
</tr>
<tr>
<td>Direct3D 11.2, DXGI 1.3</td>
<td>These technologies are available for Windows Store apps, Universal Windows Platform (UWP) apps for Windows 10, and Win32 desktop apps for Windows 8.1 and Windows 10.

Windows Store apps for Windows 8.1 can rely on these technologies always being present, while Win32 desktop applications need to provide suitable fallbacks for older versions of Windows.

<em>Note: </em>Windows phone 8.0 and Xbox One XDK do not support Direct3D 11.2 / DXGI 1.3</td>
</tr>
<tr>
<td>Diret3D 12, Direct3D 11.3/11.4, DXGI 1.4/1.5</td>
<td>These technologies are available for Universal Windows Platform (UWP) apps for Windows 10 and Win32 desktop apps for Windows 10.

Universal Windows Platform (UWP) apps for Windows 10 can rely on these technologies always being present, while Win32 desktop applications need to provide suitable fallbacks for older versions of Windows.</td>
</tr>
<tr>
<td>D3DX</td>
<td>All versions of the D3DX utility library (D3DX9, D3DX10, and D3DX11) are deprecated, and are not supported for Windows Store apps, Windows phone 8, Xbox One, or Universal Windows Platform (UWP) apps for Windows 10.

<a href="http://directxtk.codeplex.com/">DirectXTK</a>, <a href="http://directxtex.codeplex.com/">DirectXTex</a>, and <a href="http://go.microsoft.com/fwlink/?LinkID=324981">DirectXMesh</a> support Windows Store apps, Universal Windows Platform (UWP) apps for Windows 10, Windows phone 8.x, Xbox One, and Win32 desktop applications on Windows 10, Windows 8.x, Windows 7, and Windows Vista. These provide <a href="http://blogs.msdn.com/b/chuckw/archive/2013/08/21/living-without-d3dx.aspx">replacements</a> for much of the functionality in D3DX for Direct3D 11. See "<a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/04/direct3d-11-textures-and-block-compression.aspx">Direct3D 11 Textures and Block Compression</a>" for more information.

The D3DCSX Compute Shader helper utility is available for Win32 desktop applications, but not for Windows Store apps or Windows phone 8.</td>
</tr>
<tr>
<td>HLSL Compiler / D3DCompile</td>
<td>The HLSL compiler (<code>FXC.EXE</code>) and the D3DCompile (<code>D3DCompiler_*.DLL</code>) APIs are supported for both Windows Store apps and Win32 desktop apps.

Note that for Windows Store apps on Windows 8.0 and Windows phone 8.0, the HLSL compiler / D3DCompile APIs are only supported for development and not for deployment.

Windows Store apps for Windows 8.1, Windows Phone 8.1, Xbox One, and Universal Windows Platform (UWP) apps for Windows 10 have complete support for D3DCompile APIs. See “<a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/07/hlsl-fxc-and-d3dcompile.aspx">HLSL, FXC, and D3DCompile</a>” for more information.</td>
</tr>
<tr>
<td>Effects 11 (FX11)</td>
<td>The <a href="http://go.microsoft.com/fwlink/p/?LinkId=271568">Effects 11</a> technology relies on runtime shader reflection via <code>D3DReflect</code> in the D3DCompiler. Due to the limitations above, this makes Effects 11 library unsuited to use in Windows Store apps for Windows 8.0 or Windows phone 8.0.

<em>Note:</em> HLSL Compiler support for the <code>fx_5_0</code> profile required to use Effects 11 is deprecated.</td>
</tr>
<tr>
<td>DirectXMath</td>
<td>The DirectXMath library is supported for Windows Store, Universal Windows Platform (UWP) apps for Windows 10, Windows phone 8.x, Xbox One, and Win32 desktop apps. This library provides SSE/SSE2 optimizations for Windows x86 and x64 native, as well as ARM-NEON optimizations for Windows RT and Windows phone 8.x. See “<a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/27/introducing-directxmath.aspx">Introducing DirectXMath</a>” for more information.

<em>Note:</em> DirectXMath on Xbox One also makes use of SSE3, SSSE3, SSE 4.1, AVX, and F16C as described in this blog <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/11/directxmath-sse-sse2-and-arm-neon.aspx">series</a>.</td>
</tr>
<tr>
<td>XAudio2</td>
<td>Windows 8.x and Windows 10 includes XAudio 2.8 which is supported for Windows Store apps, Universal Windows Platform (UWP) apps for Windows 10, Windows phone 8.x, and Xbox One. See “<a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/02/xaudio2-and-windows-8-consumer-preview.aspx">XAudio2 and Windows 8</a>” for more details.

Windows Core Audio (WASAPI) is also available for use by low-level audio libraries.

<em>DirectSound is not supported for Windows Store apps, Windows phone 8.x, Xbox One, or Universal Windows Platform (UWP) apps for Windows 10.</em></td>
</tr>
<tr>
<td>XINPUT</td>
<td>Windows 8.x and Windows 10 includes XInput 1.4 which is supported for Windows store apps and Win32 desktop apps. Windows Vista, Windows 7, Windows 8.x, and Windows 10 also include XInput 9.1.0 which is supported for Win32 desktop applications. See “<a href="http://blogs.msdn.com/b/chuckw/archive/2012/04/26/xinput-and-windows-8-consumer-preview.aspx">XInput and Windows 8</a>” for more details.

<em>DirectInput is not supported for Windows Store apps, Universal Windows Platform (UWP) apps for Windows 10, Windows phone 8.x, or Xbox One</em>

<em>Note:</em> XINPUT is not supported by Windows phone 8.x or Xbox One.

Xbox One and Universal Windows Platform (UWP) apps for Windows 10 make use of a WinRT <a href="http://blogs.msdn.com/b/chuckw/archive/2014/09/05/directx-tool-kit-now-with-gamepads.aspx">gamepad API</a> which has similar functionality.</td>
</tr>
<tr>
<td>Windows Imaging Component (WIC)</td>
<td>This technology is available for Windows Store apps,Universal Windows Platform (UWP) apps for Windows 10, and Win32 desktop apps for Windows 10, Windows 8, Windows 7, and Windows Vista. Be sure to set the <code>_WIN32_WINNT</code> definition properly to ensure use of the correct version of the WIC factory. See "<a href="http://blogs.msdn.com/b/chuckw/archive/2012/11/19/windows-imaging-component-and-windows-8.aspx">Windows Imaging Component and Windows 8</a>" for more information.

<em>Note:</em> Windows phone 8.0 does not support WIC, but this is supported for Windows phone 8.1. Xbox One XDK does not support the JPEG XR / HD Photo codec and a few other aspects of 'standard' WIC.</td>
</tr>
<tr>
<td>Windows Media Foundation (MF)</td>
<td>The Windows Media Foundation is available for Windows Store apps, Universal Windows Platform (UWP) apps for Windows 10, and Win32 desktop applications on Windows 10, Windows 8, Windows 7, and Windows Vista. Be sure to read <a href="http://blogs.msdn.com/b/chuckw/archive/2010/08/13/quot-who-moved-my-windows-media-cheese-quot.aspx">this</a> post for some additional guidance.

<em>DirectShow is not supported for Windows Store apps, Windows phone 8.x, Xbox One, or Universal Windows Platform (UWP) apps for Windows 10.</em>

<em>Note:</em> Windows phone 8.0 has partial support for the Media Foundation API, specifically <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh447918.aspx">IMFMediaEngine</a>. Xbox One XDK also has partial support for the Media Foundation API.</td>
</tr>
</tbody>
</table>
&nbsp;

(continued in <a href="http://blogs.msdn.com/b/chuckw/archive/2012/09/18/dual-use-coding-techniques-for-games-part-3.aspx">part 3</a>)
