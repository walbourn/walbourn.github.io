---
layout: post
title: Windows Networking
date: 2011-11-04 13:04
author: Chuck Walbourn
comments: true
categories: [networking]
---
Over the past few years at game conferences we've talked a lot about the Xbox LIVE service and the many great opportunities on Xbox 360, <a href="http://go.microsoft.com/fwlink/?LinkID=155264&clcid=0x409">Windows</a>, and Windows Phone using it. What we've talked less about in these venues are best practices for those writing their own multiplayer clients and servers. While the glory days of <em>DirectPlay </em>are long past (it was a great technology when you had to contend with head-to-head modem play, direct serial connections, TCP/IP over modem, IPX/SPX, and TCP/IP all at once), there's more to Windows networking than <a href="https://docs.microsoft.com/en-us/windows/desktop/WinSock/windows-sockets-start-page-2">WinSock 2</a>.
<!--more-->

<h1>Windows Firewall</h1>

The Windows Firewall included in Windows XP Service Pack 2 was a big part of the network security work for this release, and this firewall is still in place in current versions of Windows. For pure clients, there's not much to do but it does have impact on servers and peer-to-peer communications.

<em><a href="hhttps://docs.microsoft.com/en-us/windows/desktop/DxTechArts/games-and-firewalls">Windows Firewalls for Game Developers</a></em> (DirectX SDK)

<em>Games, Firewalls and Microsoft Windows XP SP2</em> (Meltdown 2004 presentation in the Windows Track)

<em>Related </em><a href="https://github.com/walbourn/directx-sdk-samples/tree/master/InstallHelpers/FirewallInstallHelper">FirewallInstallHelper</a> sample

<h1>IPV6</h1>

Microsoft has invested heavily in preparing for the <a href="https://docs.microsoft.com/en-us/previous-versions/windows/it-pro/windows-server-2008-R2-and-2008/dd379473(v=ws.10)">IPV6</a> Internet, including a IPV4/IPV6 dual-stack in the current generation of operating systems even including Windows XP Service Pack 3. While most games and game servers today are IPV4 only, moving your code to be 'IP-agnostic' is a good way to prepare for a transition to IPV6.</a>

<h1>Peer-to-peer Networking</h1>

Beyond just investing in IPV6, Microsoft has also built some technologies to improve peer-to-peer NAT traversal (called <a href="https://docs.microsoft.com/en-us/previous-versions/windows/it-pro/windows-xp/bb457042(v=technet.10)">Teredo</a>) and peer-to-peer name resolution (<a href="https://docs.microsoft.com/en-us/previous-versions/windows/it-pro/windows-vista/bb726971(v=technet.10)">Peer Name Resolution Protocol</a> aka PNRP). If you want to learn more, check out these resources:

<em>Peer to Peer Connectivity & Communications</a></em> (Meltdown 2005 presentation in the Windows Track)

<h1>InternetGetConnectedState</h1>

This legacy API dates back to Internet Explorer 4 and is used by some games to check for an active Internet connection. There is a much improved API for this available starting with Windows Vista called the <a href="https://docs.microsoft.com/en-us/windows/desktop/NLA/portal">Network List Manager</a> API. A sample of using NLM is attached to the post.

If you still need a Windows XP fallback (i.e. the COM creation in the sample code will always fail), then you should remember that just because <strong>InternetGetConnectedState</strong> returns TRUE does not mean you have an active internet connection, You need to follow it up with an attempt to reach a known Internet location (via <strong>InternetOpen</strong> and <strong>InternetOpenUrl</strong>). If you are curious about how Windows 7 does it's "network connection available" test, check out this <a href="https://docs.microsoft.com/en-us/previous-versions/windows/it-pro/windows-vista/cc766017(v=ws.10)">article</a>.

<a href="https://walbourn.github.io/download/netdetectvista.cpp">netdetectvista.cpp</a>
