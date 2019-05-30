---
layout: msdnpost
title: Dual-use Coding Techniques for Games, part 1
date: 2012-09-17 15:10
author: Chuck Walbourn
comments: true
categories: [win10, win8, winphone, xbox one]
---
<em>Writing shared code for Windows Store, Xbox One, Universal Windows Platform (UWP) apps, and Win32 desktop apps</em>

<h1>Introduction</h1>

Apps written for the Windows Store make use of the Windows Runtime (WinRT) and a restricted subset of Win32 APIs located in the core API family. Traditional Win32 desktop apps have access to a larger desktop API family, but this is subject to various levels of OS support required for each function. These two taken together can make it challenging to write shared code libraries and helper functions that can successfully compile for both Windows Store apps and Win32 desktop applications supporting Windows Vista, Windows 7, and Windows 8.x.
<!--more-->

In general, applications should be written to target either the Windows Store or the Win32 desktop. Windows Store apps make use of a distinct UI, input, system-integration, and presentation model which is not supported for Win32 desktop applications even on the Windows 8 Desktop. Targeting the Windows RT (a.k.a. <a href="https://channel9.msdn.com/posts/Building-Windows-for-the-ARM-processor-architecture">Windows on ARM</a>) platform requires writing a Window Store app, while targeting down-level platforms such as Windows Vista and Windows 7 require writing Win32 desktop apps. Trying to address both of these with the same EXE is not possible, and each will have significant platform-specific code.

The purpose of this series of posts is to talk about the overlap, and how developers creating shared libraries and game middleware can write C++ code that will successfully compile for both platforms.

<strong>Windows phone and Xbox One:</strong> This article also applies to Windows phone 8.x and Xbox One development using the XDK or ADK (see <a href="http://www.xbox.com/id">ID@Xbox</a>)

<strong>Windows 10:</strong> The guidance here applies to Universal Windows Platform (UWP) apps for Windows 10 as well.

<table border="1">
<tbody>
<tr>
<td>Win32 desktop app</td>
<td><code>WINAPI_FAMILY_DESKTOP_APP</code></td>
</tr>
<tr>
<td>Windows Store app

Universal Windows Platform (UWP) apps for Windows 10</td>
<td><code>WINAPI_FAMILY_APP</code> (Windows 8.0 SDK)
or <code>WINAPI_FAMILY_PC_APP</code> (Windows 8.1 SDK)</td>
</tr>
<tr>
<td>Windows phone 8</td>
<td><code>WINAPI_FAMILY_PHONE_APP</code></td>
</tr>
<tr>
<td>Xbox One XDK</td>
<td><code>WINAPI_FAMILY_TV_TITLE</code></td>
</tr>
<tr>
<td>Xbox One ADK</td>
<td><code>WINAPI_FAMILY_TV_APP</code></td>
</tr>
</tbody>
</table>

<h1>Compiler Toolsets and SDK Selection</h1>

To author Windows Store apps, developers must use Visual Studio 2012 which includes the Windows 8.0 SDK. This same toolset can be used to target Win32 desktop apps for Windows 8 (Desktop), Windows 7, and Windows Vista. For this article, the focus is on using this compiler toolset.

<em>Visual Studio 2013 is used to target Windows Store apps for Windows 8.1 and includes the Windows 8.1 SDK. Visual Studio 2015 is used to target Universal Windows Platform (UWP) apps for Windows 10 when using the Windows 10 SDK. These comparison tables have been updated to compare the C++11 features with the newer compilers.</em>

Note that with careful coding, it is possible to also support Visual Studio 2010 with the Windows 8.x SDK for building Win32 desktop apps. In some specific cases some extra functionality is needed that is otherwise handled by Visual Studio 2012's C++11 Standard Library, and this means restricting language feature use to VS 2010's C++0x support and avoiding the use of C++/CX language extensions.

<table border="1">
<tbody>
<tr>
<td><strong>C++11 Language Feature</strong></td>
<td><strong>VS 2010</strong></td>
<td><strong><a href="https://devblogs.microsoft.com/cppblog/c11-features-in-visual-c-11/">VS 2012</a></strong></td>
<td><strong><a href="https://devblogs.microsoft.com/cppblog/c1114-stl-features-fixes-and-breaking-changes-in-vs-2013/">VS 2013</a></strong></td>
<td><strong><a href="https://devblogs.microsoft.com/cppblog/c111417-features-in-vs-2015-rtm/">VS 2015</a></strong></td>
</tr>
<tr>
<td><code>nullptr</code></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>static_assert</code></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>override / final</code><sup> \* </sup></td><td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Lambda expressions</td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Rvalue references</td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>decltype</code></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>auto</code></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Strongly typed enumerations</td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Forward declared enumerations</td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Ranged-based <code>for</code> loops</td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Variadic templates</td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Uniform initialization and initializer lists</td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Delegating constructors</td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Raw string literals</td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Explicit conversion operators</td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Default template arguments for function templates</td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Alias templates</td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Defaulted functions</td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Deleted functions</td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Non-static data member initializers (NSDMIs)</td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Attributes, <code>constexpr</code>, ref-qualifiers, inheriting constructors,
<code>char16_t</code>, <code>char32_t</code>, Unicode string literals,
user-defined literals, extended <code>sizeof</code>, inline namespaces,
unrestricted unions, <code>noexcept</code>, <code>thread_local</code>, magic statics,
Universal character names in literals</td>
<td></td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>C99: <code>__func__</code>, <code>long long</code></td>
<td></td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>Expression SFINAE</td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><span style="color: red;line-height: 115%;font-family: Wingdings;font-size: 11pt">û</span></td>
<td><a href="https://devblogs.microsoft.com/cppblog/partial-support-for-expression-sfinae-in-vs-2015-update-1/">Update 1</a></td>
</tr>
</tbody>
</table>

> In VS 2010, <code>final</code> was implemented as <code>sealed</code>. Also note that VS 2010 considers <code>override</code> to be a MSVC extension and generates warning C4481.

> VS 2017 supports all C++11 features as well as C++14 and C++17. VS 2019 supports C++11, C++14, C++17, and portions of the C++20 draft.

Use of the older standalone DirectX SDK is not recommended or supported for Windows Store apps. It includes many legacy technologies that are not supported for this platform, and thus their use complicates the goal of 'dual-use' coding. See the blog posts "<a href="https://walbourn.github.io/where-is-the-directx-sdk/">Where is the DirectX SDK?</a>", "<a href="https://walbourn.github.io/where-is-the-directx-sdk-2013-edition/">Where is the DirectX SDK (2013 Edition)?</a>", "<a href="https://walbourn.github.io/where-is-the-directx-sdk-2015-edition/">Where is the DirectX SDK (2015 Edition)?</a>", and "<a href="https://walbourn.github.io/directx-sdks-of-a-certain-age/">DirectX SDKs of a certain age</a>" for more information.

<h1>C++11 Standard Library</h1>

The majority of the C++11 Standard Library is supported for both Windows Store apps and Win32 desktop apps. This provides a large breadth of functionality that is common and safe to use for 'dual-use' scenarios.

<table border="1">
<tbody>
<tr>
<td><strong>C++11 header</strong></td>
<td>
<p align="center"><strong>VS 2010</strong></p>
</td>
<td>
<p align="center"><strong>VS 2012</strong></p>
</td>
<td><strong>VS 2013</strong></td>
<td><strong>VS 2015</strong></td>
</tr>
<tr>
<td><code>&lt;array&gt;, &lt;memory&gt;, &lt;random&gt;, &lt;regex&gt;,
&lt;tuple&gt;, &lt;type_traits&gt;,
&lt;unordered_map&gt;, &lt;unordered_set&gt;</code></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>&lt;stdint.h&gt;, &lt;cstdint&gt;</code></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>unique_ptr&lt;T&gt;</code></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>cbegin(), cend(), crbegin(), crend()</code></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>&lt;forward_list&gt;</code></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>&lt;algorithm&gt;</code> and <code>&lt;exception&gt;</code> updates
<ul>
 	<li><code>find_if_not, copy_if, is_sorted,etc.</code></li>
 	<li><code>exception_ptr</code></li>
</ul>
</td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>&lt;allocators&gt;</code></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>&lt;codecvt&gt;</code></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>&lt;system_error&gt;</code></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>emplace(), emplace_front(), emplace_back(),</code> etc.</td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>&lt;chrono&gt; \* </code></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>&lt;ratio&gt;</code></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>&lt;scoped_allocator&gt;</code></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>&lt;atomic&gt;, &lt;condition_variable&gt;, &lt;future&gt;, &lt;mutex&gt;,
&lt;thread&gt;</code></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>&lt;intializer_list&gt;</code></td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><code>std::make_unique&lt;T&gt;</code> (C++14)</td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td><a href="https://devblogs.microsoft.com/cppblog/c99-library-support-in-visual-studio-2013/">C99</a>: <code>&lt;stdbool.h&gt;, &lt;complex.h&gt; / &lt;ccomplex,
&lt;fenv.h&gt; / &lt;cfenv&gt;,
&lt;inttypes.h&gt; / &lt;cinttypes&gt;, &lt;ctgmath&gt;</code></td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>C99: <code>&lt;uchar.h&gt;</code> / <code>&lt;cuchar&gt;</code></td>
<td></td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
<tr>
<td>C99: <code>&lt;tgmath.h&gt;</code>, some <code>printf</code> format specifiers</td>
<td></td>
<td></td>
<td></td>
<td><span style="line-height: 115%;font-family: Wingdings;font-size: 11pt">ü</span></td>
</tr>
</tbody>
</table>

> VS 2012 / VS 2013's ``high_resolution_clock`` has some <a href="https://connect.microsoft.com/VisualStudio/feedback/details/719443/">known issues</a>. This is fixed in VS 2015 or later.

The majority of Visual C++ functions in the C Runtime are available for Windows Store apps, but there are some specific headers which are not fully available.

<table border="1">
<tbody>
<tr>
<td><strong>Visual C++ header</strong></td>
<td><strong>Notes</strong></td>
</tr>
<tr>
<td><code>agents.h
concrt.h</code></td>
<td>The majority of the Concurrency Runtime (ConcRT) is available.
There is, however, no support for the advanced scheduler (i.e. schedule groups, contexts)</td>
</tr>
<tr>
<td><code>concrtrm.h</code></td>
<td>The Concurrent Runtime (ConcRT) resource manager is not available to Windows Store apps.</td>
</tr>
<tr>
<td><code>conio.h</code></td>
<td>No functions in this header are available</td>
</tr>
<tr>
<td><code>ctype.h, cctype</code></td>
<td><code>isleadbyte</code> and <code>_isleadbyte_l</code> are not available</td>
</tr>
<tr>
<td><code>direct.h</code></td>
<td>Only <code>_mkdir, _rmdir, _wmkdir,</code> and <code>_wrmdir</code> are available</td>
</tr>
<tr>
<td><code>io.h</code></td>
<td><code>_pipe</code> is not available</td>
</tr>
<tr>
<td><code>locale.h, clocale</code></td>
<td>Obsolete locale functions are not available</td>
</tr>
<tr>
<td><code>malloc.h</code></td>
<td><code>_resetstkoflw</code> is not available.</td>
</tr>
<tr>
<td><code>mbctype.h, mbstring.h</code></td>
<td>All multi-byte (<code>_ismb, _mb*</code>) functions are not available.</td>
</tr>
<tr>
<td><code>process.h</code></td>
<td>Most process and DLL related functions are not available.
<code>exit</code> and <code>abort</code> are the only functions available for Windows Store apps.</td>
</tr>
<tr>
<td><code>stdio.h, cstdio</code></td>
<td><code>_pclose, _popen, _wpopen</code> functions are not available.</td>
</tr>
<tr>
<td><code>stdlib.h, cstdlib</code></td>
<td>POSIX/DOS-style environment variables and related functions & types are not supported for Windows Store apps.
There is also no equivalent for <code>_seterromode, _beep,</code> or <code>_sleep</code>.</td>
</tr>
<tr>
<td><code>tchar.h</code></td>
<td>The <code>_MBCS</code> mode is not supported for Windows Store apps. You can only use <code>_UNICODE</code>.</td>
</tr>
<tr>
<td><code>time.h, ctime</code></td>
<td>System-time functions (<code>_getsystime, _setsystime</code>) are not available.
Note you can use Win32 APIs for <code>GetSystemTime</code> and <code>GetLocalTime</code>, but not set the time in a Windows Store app.</td>
</tr>
<tr>
<td><code>wchar.h, cwchar</code></td>
<td><code>codeisleadbyte, _Isleadbyte_l, _wgetcwd,</code> and <code>_getddcwd</code> are not supported.</td>
</tr>
<tr>
<td><code>wctype.h, cwctype</code></td>
<td>Obsolete <code>is_wctype</code> is not supported.</td>
</tr>
</tbody>
</table>

> <strong>Update:</strong> If you are interesting in using <a href="http://www.boost.org/">Boost</a>, take a look at this <a href="https://devblogs.microsoft.com/cppblog/using-boost-libraries-in-windows-store-and-phone-applications/">blog post</a>.

<h1>Machine Architectures</h1>

Windows Store apps should compile for Windows x86 (32-bit), Windows x64 (64-bit) native, and Windows RT (ARM). Win32 desktop apps should compile for Windows x86 and Windows x64 native. Most C/C++ code should work fine across all platforms if using platform-neutral types.

<ul>
 	<li><strong>Use portable types.</strong> Use <code>size_t</code>, <code>ptrdiff_t</code>, and the various <code>&lt;stdint.h&gt;</code> (<code>&lt;cstdint&gt;</code>) types (i.e. <code>int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, intptr_t,</code> and <code>uintptr_t</code>).</li>
 	<li><strong>Group pointers in structures and classes.</strong> Most data types do not change size when moving to x64 native, but pointers become 8 bytes (known as the "<a href="http://en.wikipedia.org/wiki/64-bit">LLP64</a>" data model). The default pack setting for x64 is 16 rather than 8 to ensure structures are padded to a natural alignment including pointers. Mixing pointers with other data types in structures results in more padding than would happen if the pointers were grouped together.</li>
 	<li><strong>Prefer C++ style casts.</strong> Use of <code>const_cast&lt;&gt;</code>, <code>static_cast&lt;&gt;</code>, and <code>reinterpret_cast&lt;&gt;</code> rather than C-style casts can help highlight potential pointer-truncation issues more easily.</li>
 	<li><strong>Use maximum warnings (<code>/Wall</code>).</strong> A number of warnings that tend to highlight 64-bit portability issues include C4302 and C4826 are off by default. You can disable specific warnings to reduce 'noise' as they are identified by <code>#pragma warning</code> or <code>/wd</code>.</li>
 	<li><strong>Use <code>/analyze</code>.</strong> Static code analysis will highlight a number of issues, particularly using the incorrect <code>printf</code> format specifications--note that <a href="https://devblogs.microsoft.com/cppblog/format-specifiers-checking/">VS 2015 does check</a> <code>printf</code> format specifications even without using <code>/analyze</code>, but it is not as extensive.</li>
</ul>

Inline assembly is not supported for x64 native or ARM compilation, so it should be avoided generally. You can make use of intrinsics instead. Avoid using MMX™ intrinsics (i.e. those from the mmintrin.h header or that operate with the <code>__m64</code> type) to ensure the same code works for both x86 and x64 native. For ARM, there is a full set of intrinsics available in <code>armintr.h</code> and <code>arm_neon.h</code>.

The ability to write standalone assembly for all machine architectures is not supported for Windows Store apps for Windows 8.0 and requires the VS 2013 toolset with the Windows Driver Kit 8.1. Use of standalone assembly is not recommended for 'dual-use' code.

When writing architecture-specific code, make use of the <code>_M_IX86</code> (32-bit), <code>_M_X64</code> (64-bit), <code>_M_ARM</code>, and <code>_M_ARM64</code>  machine architecture defines for conditional compilation. All are "Little Endian" platforms.

> The VS 2012, VS 2013, and VS 2015 toolsets support x86, x64, and ARM. VS 2017 (15.9 update) or later also supports ARM64. VS 2010 has no support for ARM targets.

<h1>Exception-Safe Coding</h1>

Windows Store apps make use of C++ exception handling and are compiled with <code>/EHsc</code>. Many Win32 desktop applications use <code>HRESULT</code>s and do not enable exception handling of any kind, although some do use it. Dual-use shared code can use <code>HRESULT</code>s or other error codes and leave the decision to use exception handling to the client code. (See <a href="https://github.com/Microsoft/DirectXTex">DirectXTex</a> for an example of this approach.) Alternatively, dual-use shared code can throw either C++ standard exceptions or Windows Store app <code>Platform</code> exceptions through specific compiler techniques. (See <a href="https://github.com/Microsoft/DirectXTK">DirectXTK</a> for an example of this approach.)

Since dual-use code can be used in the context of exception handling, it is strongly recommended that you make use of 'exception-safe' coding practices. C++ exception handling takes advantage of the language and ensures that objects are properly destructed when leaving scope normally or when processing an exception. When using the C++11 Standard Library, those containers are already written to be 'exception-safe'.

The main area where this impacts 'dual-use' shared code and C++ code in general is when allocating resources. The guidance here is to never rely on calling <code>delete, delete [], CloseHandle, Release,</code> etc. directly but have the destructor of a class instance handle it automatically. This technique is known as <em>Resource Acquisition Is Initialization</em> (<a href="http://en.wikipedia.org/wiki/Resource_Acquisition_Is_Initialization">RAII</a>). This ensures that the code will behave well both in normal operation and in the cases where exception handling is used. The C++11 Standard Library provides a number of classes that make implementing this pattern fairly straight-forward.

<table border="1">
<tbody>
<tr>
<td><strong>Traditional C++</strong></td>
<td><strong>Exception-safe C++</strong></td>
</tr>
<tr>
<td><code>MyObject \* obj = new MyObject; </code></td>
<td><code>std::unique_ptr&lt;MyObject&gt; obj(new MyObject);</code><br />
<br />
-or-
<br /><br />
<code>auto obj = std::make_unique&lt;MyObject&gt;();</code><br />
<br />
<strong>Note:</strong> VS 2013 or later includes <code>std::make_unique&lt;T&gt;</code>, but it is not available in older toolsets.
<br /><br />
-or-
<br /><br />
<code>auto obj = std::make_shared&lt;MyObject&gt;();</code></td>
</tr>
<tr>
<td><code>BYTE \* buffer = new BYTE[ 2048 ];</code></td>
<td><code>std::array&lt;uin8_t, 2048&gt; buffer;</code>
<br /><br />
-or-
<br /><br />
<code>std::unique_ptr&lt;uin8_t[]&gt; buffer( new uint8_t[2048]; )</code></td>
</tr>
<tr>
<td><code>float \* buffer = _aligned_malloc( 2048, 16 );</code></td>
<td><code>struct aligned_deleter</code> <br />
<code>{</code> <br />
<code>void operator()(void \* p)</code> <br />
<code>{ _aligned_free(p); }</code> <br />
<code>};</code> <br />
<code>std::unique_ptr&lt;float, aligned_deleter&gt; buffer( _aligned_malloc(2048,16));</code></td>
</tr>
<tr>
<td><code>HANDLE h = CreateFile(…);</code><br />
<code>if ( h == INVALID_HANDLE)</code><br />
<code>// error</code></td><br />
<td><code>struct handle_closer</code><br />
<code>{</code><br />
<code>void operator()(HANDLE h)</code><br />
<code>{</code>
<code>assert(h != INVALID_HANDLE_VALUE);</code><br />
<code>if (h) CloseHandle(h);</code><br />
<code>}</code><br />
<code>};</code><br />
<code>inline HANDLE safe_handle( HANDLE h )</code><br />
<code>{</code><br />
<code>return (h==INVALID_HANDLE_VALUE) ? nullptr:h;</code><br />
<code>}</code><br />
<code>std::unique_ptr&lt;void, handle_closer&gt;</code><br />
<code>hFile( safe_handle( CreateFile(…) ) );</code><br />
<code>if ( !hFile )</code><br />
<code>// error</code></td>
</tr>
<tr>
<td><code>CRITICAL_SECTION cs;</code><br />
<code>InitializeCriticalSection(&amp;cs);</code><br />
<br />
<code>EnterCriticalSection(&amp;cs </code><br />
...
<br />
<code>LeaveCriticalSection(&amp;cs);</code></td>
<td><code>std::mutex m;</code><br />
<code>{</code><br />
<code>std::lock_guard lock(m);</code><br />
<code>// lock on m held until end of scope</code><br />
<code>}</code></td>
</tr>
<tr>
<td><code> ID3D11InputLayout \* inputLayout = NULL;</code><br />
<br />
<code>device->CreateInputLayout( …, &amp;inputLayout );</code>

<code>SAFE_RELEASE(inputLayout);</code></td>
<td><code> #include <wrl/client.h></code><br />
<br />
<code>using Microsoft::WRL::ComPtr;</code>
<br />
<code>ComPtr&lt;ID3D11InputLayout&gt; inputLayout;</code><br />
<br />
<code>device->CreateInputLayout(…, &amp;inputLayout );</code>
<br /><br />
-or-
<br /><br />
<code>device->CreateInputLayout(…, inputLayout.ReleaseAndGetAddressOf() )</code></td>
</tr>
</tbody>
</table>

When building with the Windows 8.x SDK for both Win32 desktop applications and Windows Store apps you can use Windows Runtime Library's <code>ComPtr</code>. This is similar to ATL's <code>CComPtr</code>. See <a href="https://github.com/Microsoft/DirectXTK/wiki/ComPtr">this page</a> for more information.

When passing these objects to other functions, you can use <code>.get()</code> on the smart pointer on each call and pass the parameter as a raw pointer, or you can pass the smart pointer object directly. When using smart pointer objects as parameters, pass them by constant reference, similar to other STL containers, in order to avoid additional temporary copies and to avoid excessive reference count increment and decrement cycles.

The use of this 'exception-safe' pattern has the added benefit of ensuring you do not need to make use of explicit <code>try / catch</code> blocks in your code to handle resource cleanup. This contributes to keeping 'dual-use' code agnostic to the use of Exception Handling while still being 'exception-safe' when it is used.

<strong>Visual C++: </strong>If you call <code>new</code>, then by default it will throw a C++ exception for out-of-memory conditions per the C++ Standard. If you want to explicitly check for null instead, then you must use <code>new (std::nothrow)</code> instead. See <a href="https://devblogs.microsoft.com/cppblog/new-in-vs-2015-zcthrowingnew/">this blog post</a> as well.

<strong>ThrowIfFailed:</strong> Modern Microsoft samples make use of a helper <code>ThrowIfFailed</code> which generates a C++ exception if an HRESULT is a failure. This is intended as a 'fatal fast fail', and generally simplifies COM-based code handling. See <a href="https://github.com/Microsoft/DirectXTK/wiki/ThrowIfFailed">this page</a> for usage and implementation notes.

(continued in <a href="https://walbourn.github.io/dual-use-coding-techniques-for-games-part-2/">part 2</a>)
