---
layout: post
title: Windows Networking
date: 2011-11-04 13:04
author: walbourn
comments: true
categories: [networking, Uncategorized]
---
<p>Over the past few years at game conferences we've talked a lot about the Xbox LIVE service and the many great oppourtunities on Xbox 360, <a title="Games for Windows - LIVE" href="http://go.microsoft.com/fwlink/?LinkID=155264&amp;clcid=0x409">Windows</a>, and Windows Phone using it. What we've talked less about in these venues are best practices for those writing their own multiplayer clients and servers. While the glory days of <em>DirectPlay </em>are long past (it was a great technology when you had to contend with head-to-head modem play, direct serial connections, TCP/IP over modem, IPX/SPX, and TCP/IP all at once), there's more to Windows networking than <a title="MSDN Library" href="http://msdn.microsoft.com/en-us/library/windows/desktop/ms740673.aspx">WinSock 2</a>.</p>
<p>&nbsp;</p>
<p><strong>Windows Firewall</strong></p>
<p>The Windows Firewall included in Windows XP Service Pack 2 was a big part of the network security work for this release, and this firewall is still in place in current versions of Windows. For pure clients, there's not much to do but it does have impact on servers and peer-to-peer communications.</p>
<p><em><a title="DirectX SDK Article" href="http://msdn.microsoft.com/en-us/library/ee417690.aspx">Windows Firewalls for Game Developers</a></em> (DirectX SDK)</p>
<p><em><a title="MS Downloads" href="http://www.microsoft.com/download/en/details.aspx?id=16846">Games, Firewalls and Microsoft Windows XP SP2</a></em> (Meltdown 2004 presentation in the Windows Track)</p>
<p><em>Related </em><a href="http://code.msdn.microsoft.com/Windows-Firewall-Install-c87391b9">FirewallInstallHelper</a> sample</p>
<p>&nbsp;</p>
<p><strong>IPV6</strong></p>
<p>Microsoft has invested heavily in preparing for the <a title="TechNet" href="http://technet.microsoft.com/en-us/network/bb530961">IPV6</a>&nbsp;Internet, including a IPV4/IPV6 dual-stack in the current generation of operating systems even including Windows XP Service Pack 3. While most games and game servers today are IPV4 only, moving your code to be 'IP-agnostic' is a good way to prepare for a transition to IPV6. Some great resources to start with are:</p>
<p><a title="Windows Core Networking Blog" href="http://blogs.msdn.com/b/wndp/archive/2006/08/29/creating-ip-agnostic-applications--part--1.aspx">Creating IP Agonostic Applications part 1</a></p>
<p><a title="Windows Core Networking Blog" href="http://blogs.msdn.com/b/wndp/archive/2006/10/24/creating-ip-agnostic-applications-part-2-dual-mode-sockets.aspx">Creating IP Agonostic Applications part 2</a></p>
<p><em>Related</em> <a href="http://blogs.msdn.com/b/b8/archive/2012/06/05/connecting-with-ipv6-in-windows-8.aspx">Connecting with IPv6 in Windows 8</a></p>
<p>&nbsp;</p>
<p><strong>Peer-to-peer Networking</strong></p>
<p>Beyond just investing in IPV6, Microsoft has also built some technologies to improve peer-to-peer NAT traversal (called <a title="TechNet" href="http://technet.microsoft.com/en-us/network/cc917483.aspx">Teredo</a>) and peer-to-peer name resolution (<a title="TechNet" href="http://technet.microsoft.com/en-us/library/bb726971.aspx">Peer Name Resolution Protocol</a> aka PNRP). If you want to learn more, check out these resources:</p>
<p><a href="http://blogs.msdn.com/b/p2p/">Peer-to-peer networking blog</a></p>
<p><em><a title="MS Downloads" href="http://go.microsoft.com/fwlink/?linkid=50758&amp;clcid=0x409">Peer to Peer Connectivity &amp; Communications</a></em> (Meltdown 2005 presentation in the&nbsp;Windows Track)&nbsp;</p>
<p>&nbsp;</p>
<p><strong>InternetGetConnectedState</strong></p>
<p>This legacy API dates back to Internet Explorer 4 and is used by some games to check for an active Internet connection. There is a much improved API for this available starting with Windows Vista called the <a title="MSDN Library" href="http://msdn.microsoft.com/en-us/library/windows/desktop/aa370803.aspx">Network List Manager</a> API. A sample of using NLM is attached to the post.</p>
<p>If you still need a Windows XP fallback (i.e. the COM creation in the sample code will always fail), then you should remember that just because <strong>InternetGetConnectedState</strong> returns TRUE does not mean you have an active internet connection, You need to follow it up with an attempt to reach a known Internet location (via <strong>InternetOpen</strong> and <strong>InternetOpenUrl</strong>). If you are curious about how Windows 7 does it's "network connection available" test, check out this <a title="TechNet" href="http://technet.microsoft.com/en-us/library/cc766017%28WS.10%29.aspx">article</a>.</p>
<p><a href="https://msdnshared.blob.core.windows.net/media/MSDNBlogsFS/prod.evol.blogs.msdn.com/CommunityServer.Components.PostAttachments/00/10/23/41/59/netdetectvista.cpp" original-url="http://blogs.msdn.com/cfs-file.ashx/__key/communityserver-components-postattachments/00-10-23-41-59/netdetectvista.cpp">netdetectvista.cpp</a></p>
