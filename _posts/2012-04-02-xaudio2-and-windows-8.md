---
layout: post
title: XAudio2 and Windows 8
date: 2012-04-02 15:12
author: walbourn
comments: true
categories: [audio, dxsdk, Uncategorized, win8, windowssdk, winphone, xbox one]
---
The <em>Windows 8 Consumer Preview</em> includes version 2.8 of the <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh405049.aspx">XAudio2</a> game audio API built in, and this API is fully supported for both Windows Store apps (including x86, x64, and Windows on ARM) and desktop Win32 applications. The full details of the differences compared to XAudio2 2.7 which shipped in the <em>DirectX SDK (June 2010)</em> release are addressed on <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee415802.aspx">MSDN</a>. The headers and libraries for XAudio 2.8 are included in the Windows SDK 8.0 that is part of <a href="http://blogs.msdn.com/b/chuckw/archive/2012/02/29/visual-studio-11-beta.aspx">Visual Studio 11 Beta</a>.

<strong>Update: </strong>This information also applies to <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/31/windows-8-release-preview-and-gdfs.aspx">Windows 8</a> RTM, <a href="http://blogs.msdn.com/b/chuckw/archive/2012/08/15/visual-studio-2012-and-windows-8-0-sdk-rtm-are-now-available.aspx">Visual Studio 2012</a> RTM, Windows 8.1, and <a href="http://blogs.msdn.com/b/chuckw/archive/2013/10/18/visual-studio-2013-and-windows-8-1-sdk-rtm-are-now-available.aspx">Visual Studio 2013</a>.

<strong>Windows phone</strong>: <a href="http://go.microsoft.com/fwlink/?LinkID=261873">Windows phone 8</a> supports XAudio 2.8 as well.

<strong>REDIST:</strong> For XAudio 2.8 or later on Windows 8 and Windows RT, no redistribution is required since XAudio 2.8 is included with the OS. For XAudio 2.7 on any version of Windows, use the <a href="http://blogs.msdn.com/b/chuckw/archive/2010/09/08/not-so-direct-setup.aspx">legacy DirectX SDK REDIST</a>.

Since XAudio2 version 2.8 is not available on Windows 7, Win32 desktop games that support older versions of Windows will need to continue to use XAudio 2.7. In general it is fairly easy to write code that successfully complies both for "Windows 8 only" which is the case for Windows Store apps and for 'down-level', but requires you mix both the Windows SDK 8.0 and DirectX SDK headers (see "<a href="http://blogs.msdn.com/b/chuckw/archive/2012/03/22/where-is-the-directx-sdk.aspx">Where is the DirectX SDK?</a>").
<ul>
	<li>When building an application that is 'down-level' using headers in the Windows 8.0 SDK, be sure to explicitly select the correct 'minimum' <code>_WIN32_WINNT</code> value. For Windows 8, that is 0x0602 (which is the default when building code with Visual Studio 2012 and for all Windows Store apps). For Windows 7 use 0x0601, and for Windows Vista use 0x0600. Typically this is done as part of the project configuration via <em>Preprocessor Definitions</em>.</li>
</ul>
<em>If you set _WIN32_WINNT correctly and try building with the Windows 8.x SDK version of xaudio2.h headers, you'll get an error letting you know that you have to use the DirectX SDK version of that header. You should follow the instructions on <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/ee663275.aspx">MSDN</a> to use the Windows 8.x SDK headers and libraries, listing the <code>DXSDK_DIR</code> paths in VC++ Directories after the Windows SDK header/libs, and explicitly link to the headers in the 'default' location--environment variables in #include statements doesn't work--where you need older versions to support older versions of Windows.</em>
<ul>
	<li>The DirectX SDK version of XAudio2 used <code>CoCreateInstance</code> and was registered with COM, and required an explicit <code>Initialize</code> method to be called. The DirectX SDK  'xaudio2.h' header contained a wrapper inline function <code>XAudio2Create</code> that did this to simplify portability with the Xbox 360 version. For the Windows 8 version, you don't use COM creation and instead call the <code>XAudio2Create</code> function and link with "xaudio2.lib". For the DirectX SDK, you must explicitly enable the debugging support if desired, but the <code>XAUDIO2_DEBUG_ENGINE</code> flag doesn't exist for the Windows 8 version.  Note: If using the xAPOs XAudio2CreateVolumeMeter or XAudio2CreateReverb from the xaudio2fx.h header, they have the same link requirement for XAudio 2.8.</li>
</ul>
<pre class="scroll"><code class="cplusplus">
 #if (_WIN32_WINNT &gt;= 0x0602 /*_WIN32_WINNT_WIN8*/)
 #include &lt;xaudio2.h&gt;
 #pragma comment(lib,"xaudio2.lib")
 #else
 #include &lt;C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2.h&gt;
 #endif
 #pragma comment(lib,"ole32.lib")
 
 CoInitializeEx( nullptr, 0 ); 
 
 UINT32 flags = 0;
 #if (_WIN32_WINNT &lt; 0x0602 /*_WIN32_WINNT_WIN8*/) &amp;&amp; defined(_DEBUG)
 flags |= XAUDIO2_DEBUG_ENGINE;
 #endif
 
 hr = XAudio2Create( &amp;pXAudio2, flags );
 if( FAILED( hr ) ) {
 ... 
 } 
 #if (_WIN32_WINNT &gt;= 0x0602 /*_WIN32_WINNT_WIN8*/) &amp;&amp; defined(_DEBUG)
 // To see the debug output, you need to view ETW logs for this application:
 // Go to Control Panel, Administrative Tools, Event Viewer.
 // View-&gt;Show Analytic and Debug Logs.
 // Applications and Services Logs / Microsoft / Windows / XAudio2.
 // Right click on Microsoft Windows XAudio2 debug logging, Properties, then Enable Logging, and hit OK
 XAUDIO2_DEBUG_CONFIGURATION debug ={0};
 debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
 pXAudio2-&gt;SetDebugConfiguration( &amp;debug, 0 );
 #endif </code></pre>
<ul>
	<li>Any calls to <code>IXAudio2::GetDeviceCount()</code> or <code>IXAudio2::GetDeviceDetails()</code> must be guarded since these APIs do not exist in the Windows 8 version. For Windows 8, all explicit device enumeration is done using WinRT APIs. If using the default audio device, the same code will compile for both as the default parameters in both versions do the same thing. If doing an explicit device selection, you must code two versions. The Windows 8 version requires a <code>szDeviceId</code> that is an <code>LPWSTR</code>. The XAudio 2.7 version requires a <code>UINT32 DeviceIndex</code>. <em>Note this Windows 8 version is not the ideal usage since it forces the device enumeration to be synchronous.</em></li>
</ul>
<pre class="scroll"><code class="cplusplus">
 #if (_WIN32_WINNT &gt;= 0x0602 /*_WIN32_WINNT_WIN8*/)
 using Windows::Devices::Enumeration::DeviceClass;
 using Windows::Devices::Enumeration::DeviceInformation;
 using Windows::Devices::Enumeration::DeviceInformationCollection;
 
 auto operation = DeviceInformation::FindAllAsync(DeviceClass::AudioRender);
 while (operation-&gt;Status != Windows::Foundation::AsyncStatus::Completed)
 ;
 
 DeviceInformationCollection^ devices = operation-&gt;GetResults();
 
 for (unsigned i=0; i &lt; devices-&gt;Size; ++i)
 {
 using Windows::Devices::Enumeration::DeviceInformation;
 
 DeviceInformation^ d = devices-&gt;GetAt(i);
 // display name is d-&gt;Name-&gt;Data()
 // device id is d-&gt;Id-&gt;Data() used for creating the mastering voice
 }
#else
 UINT32 dCount = 0;
 hr = pXAudio2-&gt;GetDeviceCount( &amp;dCount );
 if (FAILED(hr) )
 ...
 
 for( UINT32 index=0; index &lt; dCount; ++index )
 {
 XAUDIO2_DEVICE_DETAILS details;
 hr = pXAudio2-&gt;GetDeviceDetails( index, &amp;details );
 if (FAILED(hr))
 break;
 
 // display name is details.DisplayName
 // internal device ID is details.DeviceID
 // the 'index' is used for creating the mastering voice
 }
#endif
</code></pre>
<ul>
	<li>When creating the mastering voice, the two versions take very similar inputs. If using mostly default values, the same code can compile under both conditions. Otherwise, there are two differences: (1) The Windows 8 version takes a <code>szDeviceId</code> for specifying the device to use, while the XAudio 2.7 version uses a <code>DeviceIndex</code> (2) The Windows 8 version takes one additional parameter for registering the output with the correct <code>AUDIO_STREAM_CATEGORY</code>.</li>
</ul>
<pre class="scroll"><code class="cplusplus"> #if (_WIN32_WINNT &gt;= 0x0602 /*_WIN32_WINNT_WIN8*/)
 
 hr = pXAudio2-&gt;CreateMasteringVoice( &amp;pMasteringVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, deviceID, NULL, AudioCategory_GameEffects );
 
 #else
 
 hr = pXAudio2-&gt;CreateMasteringVoice( &amp;pMasteringVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, deviceIndex, NULL );
 
 #endif</code></pre>
<ul>
	<li>If you are using X3DAudio you will need the mastering voice's 'channel mask'. If using the XAudio 2.7 version, you get this information back from <code>IXAudio2::GetDeviceDetails</code>. Since that method is not used for the Windows 8 version, you obtain that information from the mastering voice instead. You likely need the number of channels as well. For the XAudio 2.7 version you need to link to <code>x3daudio.lib</code>, but for the Windows 8 version it is included in <code>xaudio2.lib</code>.</li>
</ul>
<pre class="scroll"><code class="cplusplus"> #if (_WIN32_WINNT &gt;= 0x0602 /*_WIN32_WINNT_WIN8*/)
 #include &lt;x3daudio.h&gt;
 #pragma comment(lib,"xaudio2.lib")
 #else
 #include &lt;C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\include\x3daudio.h&gt;
 #pragma comment(lib,"x3daudio.lib")
 #endif

 #if (_WIN32_WINNT &gt;= 0x0602 /*_WIN32_WINNT_WIN8*/)
 
 DWORD dwChannelMask;
 pMasteringVoice-&gt;GetChannelMask( &amp;dwChannelMask );
 
 XAUDIO2_VOICE_DETAILS vdetails;
 pMasteringVoice-&gt;GetVoiceDetails( &amp;vdetails );
 UINT32 nChannels = vdetails.InputChannels;
 
 #else
 
 XAUDIO2_DEVICE_DETAILS details;
 hr = pXAudio2-&gt;GetDeviceDetails( deviceIndex, &amp;details );
 if ( FAILED(hr) )
 ...
 
 DWORD dwChannelMask = details.OutputFormat.dwChannelMask;
 UINT32 nChannels = details.OutputFormat.Format.nChannels;
 
 #endif
 
 X3DAUDIO_HANDLE x3DInstance;
 X3DAudioInitialize( dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, x3DInstance );</code></pre>
<ul>
	<li>The xAPO function CreateFX in XAudio 2.8 takes an optional initial parameters structure. When using the xAPO CreateFX with XAudio 2.7, you cannot pass the initial parameters until you bind to a voice and use SetEffectParameters and need to link to xapofx.lib.</li>
</ul>
<pre class="scroll"><code class="cplusplus"> #if (_WIN32_WINNT &gt;= 0x0602 /*_WIN32_WINNT_WIN8*/)
 #include &lt;xapofx.h&gt;
 #pragma comment(lib,"xaudio2.lib")
 #else
 #include &lt;C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\include\xapofx.h&gt;
 #pragma comment(lib,"xapofx.lib")
 #endif
 
 IUnknown* effect = nullptr;
 #if (_WIN32_WINNT &gt;= 0x0602 /*_WIN32_WINNT_WIN8*/)
 hr = CreateFX( _uuidof(...), &amp;effect, &amp;params, sizeof(params) );
 #else
 hr = CreateFX( _uuidof(...), &amp;effect );
 ...
 voice-&gt;SetEffectParameters( 0, &amp;params, sizeof(params) );
 #endif</code></pre>
<ul>
	<li>From here the rest of XAudio2 API calls should be the same. The only further difference is that the Windows 8 version will not process audio data compressed using 'xWMA', but it does support both PCM and ADPCM data that would work with XAudio 2.7. For advanced compression options for the Windows 8 version, the solution is to use Media Foundation to do the decompression and then pass the resulting data to XAudio 2.8 which is demonstrated in the Windows Store app <a href="http://code.msdn.microsoft.com/windowsapps/XAudio2-Stream-Effect-3f95c8f2">XAudio2 Audio Stream Effect sample</a> and the <strong>XAudio2MFStream</strong> sample.</li>
</ul>
See <a href="http://blogs.msdn.com/b/chuckw/archive/2012/05/15/learning-xaudio2.aspx">Learning XAudio2</a>, <a href="http://code.msdn.microsoft.com/XAudio2-Win32-Samples-024b3933">XAudio2 Win32 Samples</a>, <a href="http://go.microsoft.com/fwlink/?LinkId=248929">DirectXTK for Audio</a>, <a href="http://blogs.msdn.com/b/chuckw/archive/2015/10/09/known-issues-xaudio-2-7.aspx">Known Issues: XAudio 2.7</a>

<strong>WIndows Server 2012:</strong> Note that XAudio 2.8 is not included in Windows Server 2012.

<strong>Windows phone 8:</strong> Windows phone 8 development uses XAudio 2.8.

<strong>Xbox One:</strong> Xbox One development uses XAudio 2.8 with additional support for xWMA. Xbox One XDK developers can also make use of XMA2.

<strong>Windows 10:</strong> Windows 10 SDK includes XAudio 2.9 which assumes you are building with <code>_WIN32_WINT=0x0A00</code> when linking against <code>xaudio2.lib</code>. To continue to use XAudio 2.8, build with <code>_WIN32_WINNT=0x0602</code> or <code>_WIN32_WINNT=0x0603</code> and link against <code>xaudio2_8.lib</code>. See <a href="https://msdn.microsoft.com/en-us/library/windows/desktop/ee415802.aspx">MSDN</a> for more information about XAudio 2.9.
