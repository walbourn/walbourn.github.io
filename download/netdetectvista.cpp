//-------------------------------------------------------------------------------------
// netdetect.cpp
//  
// Example of using Network List Manager for testing for Internet access on a machine.
// Requires Windows Vista or later
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//-------------------------------------------------------------------------------------

#include <windows.h>

#include <stdio.h>

#include <netlistmgr.h>
#pragma comment(lib, "ole32.lib" )

bool IsInternetAvailable()
{
    bool inetconnection = false;

    // We assume the application has already initialized COM, otherwise the CoCreateInstance will always fail...

    INetworkListManager *networkListManager = NULL;
    HRESULT hr = CoCreateInstance(CLSID_NetworkListManager, NULL, CLSCTX_ALL, IID_INetworkListManager, (LPVOID *)&networkListManager);
    if ( SUCCEEDED(hr) )
    {
        NLM_CONNECTIVITY result;
        hr = networkListManager->GetConnectivity( &result );
        if ( SUCCEEDED(hr) )
        {
            if ( result & NLM_CONNECTIVITY_IPV4_INTERNET )
                inetconnection = true;

            // Ideally this test would be "( result & (NLM_CONNECTIVITY_IPV4_INTERNET|NLM_CONNECTIVITY_IPV6_INTERNET) )"
            // and your application would be a a well-behaved IP-neutral application that could work on IPV6 only systems
            // See http://blogs.msdn.com/b/wndp/archive/2006/08/29/creating-ip-agnostic-applications--part--1.aspx
            //     http://blogs.msdn.com/b/wndp/archive/2006/10/24/creating-ip-agnostic-applications-part-2-dual-mode-sockets.aspx
        }

        networkListManager->Release();
    }

    return inetconnection;
}

void main()
{
    CoInitialize( NULL );

    if ( IsInternetAvailable() )
        printf( "Connected to the Internet\n" );
    else
        printf( "Not connected to the Internet (could be local only, subnet only, inactive, etc.)\n" );
}