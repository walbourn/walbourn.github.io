---
layout: post
title: Visual C++ Runtime Update
date: 2011-05-20 11:07
author: walbourn
comments: true
categories: [Uncategorized, visualc]
---
<p>For those of you who have not yet moved to <a title="Games for Windows and the DirectX SDK Blog" href="http://blogs.msdn.com/b/chuckw/archive/2011/03/16/visual-studio-2010-service-pack-1.aspx">Visual Studio 2010 Service Pack 1</a>, be aware that the April 2011 Security Bulletin <a title="Microsoft TechNet Security Bulletin" href="http://www.microsoft.com/technet/security/bulletin/ms11-025.mspx">MS11-025</a> includes a security fix to Microsoft Foundation Classes (MFC) runtime&nbsp;for Visual Studio 2005 Service Pack 1, Visual Studio 2008 Service Pack 1, and Visual Studio 2010 RTM. There are new CRT redistribution packages available for each of these that include the fix.</p>
<p>Some developers had problems when the last such update was rolled out, the ATL security fix <a title="Microsoft TechNet Security Bulletin" href="http://www.microsoft.com/technet/security/bulletin/ms09-035.mspx">MS09-35</a>, because of the impact it had on developers building code after applying the Windows Update. For Visual Studio 2005 SP1, the default behavior is for the Side-By-Side manifest system to default to the 'most current' version on the system. For Visual Studio 2008 SP1 this was changed to bind to the RTM version unless the code is compiled with a 'bind to latest' control define. Be sure to review <a title="Microosft Visual C++ Blog" href="http://blogs.msdn.com/b/vcblog/archive/2008/05/15/vc-runtime-binding.aspx">this blog entry</a> on Visual Studio CRT binding if you are still using Visual Studio 2005 or Visual Studio 2008.</p>
<p>Visual Studio 2010 does not make use of the Side-By-Side technology. Review the Visual Studio 2010 CRT <a title="MSDN Library" href="http://msdn.microsoft.com/en-us/library/dd293574.aspx">deployment documentation</a> for more details.</p>
<p><strong>Note:</strong> Due to some issues in the original Visual Studio 2010 CRT REDIST package, the updated VS 2010 CRT files can cause problems when trying to install the <a href="http://support.microsoft.com/kb/2728613">DirectX SDK (June 2010)</a> or the <a href="http://support.microsoft.com/kb/2717426">Windows SDK 7.1</a> that requires a workaround.</p>
