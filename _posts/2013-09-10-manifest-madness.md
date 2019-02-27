---
layout: post
title: Manifest Madness
date: 2013-09-10 02:00
author: walbourn
comments: true
categories: [Uncategorized, win10, win8]
---
<p class="Publishwithline"><em>This blog post discusses </em><a href="http://msdn.microsoft.com/en-us/library/windows/desktop/aa374191.aspx"><em>Application Manifest</em></a><em> elements for use in Win32 desktop applications. This is not about the </em><a href="http://msdn.microsoft.com/en-us/library/windows/apps/br211474.aspx"><em>App package manifest</em></a><em> (aka AppX) used for Windows Store apps for Windows 8.x.</em></p>

<h1>User Account Control</h1>
Back when Windows Vista launched and the User Account Control feature was first introduced, there was one key recommendation for game developer writing PC games: your game should not require administrator rights to run, and you should add the proper embedded manifest to the game EXE so Windows Vista could tell the game was updated for the new OS. With Visual Studio 2005, this was done by turning on some settings for the Linker (Generate Manifest File: Yes) and Manifest Tool (Embed Manifest: Yes) and then setting the “<a href="http://msdn.microsoft.com/en-us/library/ms173401.aspx">Additional Manifest Files</a>” field to point to a text file that contained:
<pre class="scroll"><code class="html">&lt;assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0"&gt;
 &lt;ms_asmv2:trustInfo xmlns:ms_asmv2="urn:schemas-microsoft-com:asm.v2"&gt;
 &lt;ms_asmv2:security&gt;
 &lt;ms_asmv2:requestedPrivileges&gt;
 &lt;ms_asmv2:requestedExecutionLevel level="asInvoker" uiAccess="false" /&gt;
 &lt;/ms_asmv2:requestedPrivileges&gt;
 &lt;/ms_asmv2:security&gt;
 &lt;/ms_asmv2:trustInfo&gt;
 &lt;/assembly&gt; </code></pre>
With Visual Studio 2008 and later, the project settings dialog offered direct support for this under Linker \ Manifest File – “Enable User Account Control (UAC)” and “UAC Execution Level”. This guidance still fully applies to Windows 7, Windows 8 and Windows 8.1. See <a href="http://msdn.microsoft.com/en-us/library/ee419001.aspx">User Account Control for Game Developers</a> for more details on UAC and related implications.
<h1>High-DPI</h1>
Windows Vista also introduced another feature, “High-DPI” which scaled the UI by a factor of 125% or 150% but was off by default. With Windows 7 this was enabled by default depending on the EDID native DPI information so the recommendation is for all Direct3D full-screen applications to declare themselves “High-DPI Aware”. Again, this is done via another manifest element. With Visual Studio 2005 and VS 2008, you add an “Additional Manifest Files” file reference to a text file containing:
<pre class="scroll"><code class="html">&lt;assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0" xmlns:asmv3="urn:schemas-microsoft-com:asm.v3" &gt;
 &lt;asmv3:application&gt;
 &lt;asmv3:windowsSettings xmlns="http://schemas.microsoft.com/SMI/2005/WindowsSettings"&gt;
 &lt;dpiAware&gt;true&lt;/dpiAware&gt;
 &lt;/asmv3:windowsSettings&gt;
 &lt;/asmv3:application&gt;
 &lt;/assembly&gt;</code></pre>
With Visual Studio 2010 and 2012, the project settings dialog offers the choice of “Enable DPI Awareness” set to “No” or “Yes”. See <a href="http://go.microsoft.com/fwlink/?LinkID=129586">Writing High-DPI Win32 applications</a> for more information.

<em>Note the value in the <code>&lt;dpiAware&gt;</code> element is not case-sensitive, so you'll see it as both “true” and “True” in articles and samples.</em>

<b>Windows 10 (Anniversary Update, Creators Update)</b>

In the Windows 10 (14393) update, the system now supports a new element, <code>&lt;dpiAwareness&gt;</code>, for enabling mixed-mode DPI scaling when applications create multiple top-level windows. An additional option for this element was added in Windows 10 (15063). Most games don't create multiple top-level windows, but this fits your usage please see <a href="https://blogs.windows.com/buildingapps/2016/10/24/high-dpi-scaling-improvements-for-desktop-applications-and-mixed-mode-dpi-scaling-in-the-windows-10-anniversary-update/">this post </a>and <a href="https://blogs.windows.com/buildingapps/2017/04/04/high-dpi-scaling-improvements-desktop-applications-windows-10-creators-update/">this one</a> as well as <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/aa374191.aspx">MSDN</a>.
<h1>Program Compatibility Assistant (PCA)</h1>
With Windows Vista, just having the UAC elements was enough to know that the application had been updated for Windows Vista. If no UAC manifest element was found, Windows Vista enabled the Program Compatibility Assistant (PCA) which could check for common failures and resolve them.

Windows 7 needed a new way to detect if the EXE really understood Windows 7 to avoid any use of the <a href="http://blogs.msdn.com/b/cjacks/archive/2011/11/22/managing-the-windows-7-program-compatibility-assistant-pca.aspx">PCA</a>, and UAC manifest elements alone wasn't sufficient. The solution was... (drum roll, please): more manifest elements! You again add an “Additional Manifest Files” file reference to a text file containing:
<pre class="scroll"><code class="html">&lt;assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0"&gt;
 &lt;compatibility xmlns="urn:schemas-microsoft-com:compatibility.v1"&gt; 
 &lt;application&gt; 
 &lt;!-- Windows Vista --&gt;
 &lt;supportedOS Id="{e2011457-1546-43c5-a5fe-008deee3d3f0}"/&gt; 
 &lt;!-- Windows 7 --&gt;
 &lt;supportedOS Id="{35138b9a-5d96-4fbd-8e2d-a2440225f93a}"/&gt;
 &lt;/application&gt; 
 &lt;/compatibility&gt;
 &lt;/assembly&gt; </code></pre>
Windows 8 also used the same mechanism with a new GUID to indicate <a href="http://msdn.microsoft.com/en-us/library/hh848036.aspx">Windows 8 support</a>.
<pre class="scroll"><code class="html">&lt;!-- Windows 8 --&gt;
 &lt;supportedOS Id="{4a2f28e3-53b9-4441-ba9c-d69d4a4a6e38}"/&gt;</code></pre>
For most programs, the PCA behavior impact wasn't really noticeable, so the <code>&lt;compatibility&gt;</code> section was mostly ignored by developers. This, by the way, is what determines the column “Operating System Context” in the Windows 7 or Windows 8 Resource Monitor (resmon) which defaults to “Windows Vista” if there's no <code>&lt;compatibility&gt;</code> manifest elements. On Windows 8.x, you can also see “Operating System Context” as a column in the Task Manager (taskmgr).

<em>Ideally every Windows application would declare a <code>&lt;compatibility&gt;</code> section in their manifest to make it easier for future appcompat solutions to kick in automatically. This is a lot more robust than case-by-case debugging or having to manually apply shims.</em>
<h1>Windows 8.1</h1>
Windows 8.1 has two important changes to this guidance. First, without the Windows 8.1 GUID in the <code>&lt;compatibility&gt;</code> section, <code>GetVersion(Ex)</code> APIs will always return “6.2” and not “6.3”. The default behavior improves appcompat for the vast majority of applications, but it could cause problems for custom OS-version telemetry, support tools, and potentially 3<sup>rd </sup>party DRM solutions. Adding the latest GUID to the manifest causes the process to get “6.3” when running on Windows 8.1:
<pre class="scroll"><code class="html">&lt;!-- Windows 8.1 --&gt;
 &lt;supportedOS Id="{1f676c76-80e1-4239-95bb-83d0f6d0da78}"/&gt; </code></pre>
See <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/dn302074.aspx">Windows 8.1 and Windows Server 2012 AppCompat Cookbook</a> for more details, as well as <a href="http://go.microsoft.com/fwlink/p/?LinkID=237298">Certification requirements for Windows desktop apps</a>. As I've recommended in the past, you really shouldn't be using <code>GetVersion(Ex)</code> APIs at all except perhaps in very specialized cases, and there are better ways to handle 'minimum supported OS' checks (See <a href="http://blogs.msdn.com/b/chuckw/archive/2010/02/24/what-s-in-a-version-number.aspx">What's in a version number?</a>)--the Windows 8.1 SDK also offers a set of helpers in VersionHelpers.h that are useful for such checks.

Windows 8.1 also includes enhancements to High-DPI support including per-monitor scaling, 200% scaling, and <a href="http://blogs.windows.com/windows/b/extremewindows/archive/2013/07/15/windows-8-1-dpi-scaling-enhancements.aspx">improved UI behavior</a>. This has necessitated two additional settings for the &lt;dpiaware&gt; manifest value: “Per Monitor” means the application is Per-Monitor DPI-Aware on Windows 8.1. There is also a “True/PM” setting which is both “Per Monitor DPI-Aware” on Windows 8.1, and “System DPI-Aware” on Windows Vista / Windows 7 / Windows 8-- Per Monitor” by itself is interpreted the same as setting “false” down-level. The recommended High-DPI manifest elements for Direct3D full-screen applications is now:
<pre class="scroll"><code class="html">&lt;assembly xmlns="urn:schemas-microsoft-com:asm.v1" manifestVersion="1.0" xmlns:asmv3="urn:schemas-microsoft-com:asm.v3" &gt;
 &lt;asmv3:application&gt;
 &lt;asmv3:windowsSettings xmlns="http://schemas.microsoft.com/SMI/2005/WindowsSettings"&gt;
 &lt;dpiAware&gt;True/PM&lt;/dpiAware&gt;
 &lt;/asmv3:windowsSettings&gt;
 &lt;/asmv3:application&gt;
 &lt;/assembly&gt;</code></pre>
Visual Studio 2010 and 2012 do not offer the new “Per Monitor” or “True/PM” settings, so you will need to go back to using “Additional Manifest Files” and set the “Enable DPI Awareness” project setting to “No”.

See <a href="http://go.microsoft.com/fwlink/p/?LinkID=307061">Writing DPI-Aware Desktop Applications in Windows 8.1 Preview</a>.

Some examples of what can go wrong for a game that fails to use the proper High-DPI manifest setting are covered by <a href="http://support.microsoft.com/kb/2908279/">KB 2908279</a> and <a href="http://support.microsoft.com/kb/2907016/">KB 2907016</a>.
<h1>Windows 10</h1>
Note that the <a href="http://blogs.windows.com/bloggingwindows/2014/09/30/announcing-windows-10/">latest version of Windows</a> includes the default version lie shim that was present in Windows 8.1. If you have the 8.1 GUID present in the <code>&lt;compatibility&gt;</code> section of the manifest, Windows 10 will report version 6.3 if your application uses the legacy <code>GetVersion(Ex)</code> APIs. Without it or with only older GUIDs, it will report 6.2. To get the version number reported as 10.0 (note this was 6.4 with the original Windows 10 Technical Preview build 9841), you must add another GUID to your manifest:
<pre class="scroll"><code class="cplusplus">&lt;!-- Windows 10 --&gt;
 &lt;supportedOS Id="{8e0f7a12-bfb3-4fe8-b9a5-48fd50a15a9a}"/&gt;</code></pre>
<strong>Update: </strong>With Windows 10 <code>VerifyVersionInfo</code> is now subject to the same manifest-based behavior as <code>GetVersion(Ex)</code>: by default <code>IsWindows8OrGreater</code> and earlier will return 'true' as expected on Windows 10, but both <code>IsWindows8Point1OrGreater</code> and <code>IsWindows10OrGreater</code> will return 'false' without the appropriate GUIDs present in the <code>&lt;compatibility&gt;</code> section.

<strong>Windows 10 &amp; High DPI:</strong> The Windows 10 High DPI settings can be 100%, 125%, 150%, 175%, 200%, 225%, 250%, 300%, 350%, 400%, or 450%. See <a href="http://blogs.technet.com/b/askcore/archive/2015/12/08/display-scaling-in-windows-10.aspx">this post</a> for details.

<strong>Related: </strong><a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/23/desktop-games-on-windows-8-consumer-preview.aspx">Desktop Games on Windows 8.x</a>

<strong>Certification requirements for Windows desktop apps</strong>: The WACK 3.0 test will generate warnings if your application is missing any of these manifest elements.

<strong>Manifest Tool Note:</strong> Older versions of MT.EXE (including the one that comes with VS 2010 and the Windows 7.0 SDK) will generate a harmless warning for the <code>&lt;compatibility&gt;</code> section. This can be resolved by updating to a newer version of the Manifest Tool by copying MT.EXE out of the <a href="http://blogs.msdn.com/b/chuckw/archive/2010/06/15/windows-sdk-7-1.aspx">Windows 7.1 SDK</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/08/15/visual-studio-2012-and-windows-8-0-sdk-rtm-are-now-available.aspx">Windows 8.0 SDK</a>, or <a href="http://go.microsoft.com/fwlink/?LinkID=323507">Windows 8.1 SDK</a> into a directory on your project's <code>$(ExecutablePath)</code>. This issue does not affect VS 2012 or VS 2013.

<strong>Dynamic Link Library (DLL):</strong> Embedded manifests can be applied to DLLs for specific elements, but none of the elements listed in this article apply. They only work if provided in the original launching EXE.

<a href="https://msdnshared.blob.core.windows.net/media/MSDNBlogsFS/prod.evol.blogs.msdn.com/CommunityServer.Components.PostAttachments/00/10/44/76/45/settings.manifest">settings.manifest</a>
