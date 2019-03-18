---
layout: post
title: Known Issue - Direct3D 11 UpdateSubresource and Deferred Contexts
date: 2010-07-28 14:31
author: Chuck Walbourn
comments: true
categories: [direct3d]
---
The <code>UpdateSubresource</code> method on the <code>D3D11DeviceContext</code> interface takes as one of it's parameters an optional destination offset:
<!--more-->

```cpp
void UpdateSubresource( [in] ID3D11Resource *pDstResource,
    [in] UINT DstSubresource,
    [in] const D3D11_BOX *pDstBox, // <---
    [in] const void *pSrcData,
    [in] UINT SrcRowPitch,
    [in] UINT SrcDepthPitch );
```

This works as advertised for the immediate device context which operates directly on the GPU, but there is a problem when it is used in a deferred context through the software runtime emulation unless pDstBox is NULL or 0,0,0. The work-around for this problem is now included in the <em>Remarks </em>documenting the <code>UpdateSubresource</code> function in the Windows DirectX Graphics documentation on <a href="https://docs.microsoft.com/en-us/windows/desktop/api/d3d11/nf-d3d11-id3d11devicecontext-updatesubresource">Microsoft Docs</a> and in the June 2010 DirectX SDK. The work-around assumes that any driver-level command list optimization is implemented 'correctly', hence the call to <code>CheckFeatureSupport</code>.

```cpp
HRESULT UpdateSubresource_Workaround(
  ID3D11Device *pDevice,
  ID3D11DeviceContext *pDeviceContext,
  ID3D11Resource *pDstResource,
  UINT dstSubresource,
  const D3D11_BOX *pDstBox,
  const void *pSrcData,
  UINT srcBytesPerElement,
  UINT srcRowPitch,
  UINT srcDepthPitch,
  bool* pDidWorkAround )
{
     HRESULT hr = S_OK;
     bool needWorkaround = false;
     auto contextType = pDeviceContext->GetType();

     if( pDstBox && (D3D11_DEVICE_CONTEXT_DEFERRED == contextType) )
     {
          D3D11_FEATURE_DATA_THREADING threadingCaps = { FALSE, FALSE };

          hr = pDevice->CheckFeatureSupport( D3D11_FEATURE_THREADING, &threadingCaps, sizeof(threadingCaps) );
          if( SUCCEEDED(hr) )
          {
               if( !threadingCaps.DriverCommandLists )
               {
                    needWorkaround = true;
               }
          }
     }

     const void* pAdjustedSrcData = pSrcData;

     if( needWorkaround )
     {
          D3D11_BOX alignedBox = *pDstBox;

          // convert from pixels to blocks
          if( m_bBC )
          {
               alignedBox.left     /= 4;
               alignedBox.right    /= 4;
               alignedBox.top      /= 4;
               alignedBox.bottom   /= 4;
          }

          pAdjustedSrcData = reinterpret_cast<const BYTE*>(pSrcData) - (alignedBox.front * srcDepthPitch) - (alignedBox.top * srcRowPitch) - (alignedBox.left * srcBytesPerElement);
     }

     pDeviceContext->UpdateSubresource( pDstResource, dstSubresource, pDstBox, pAdjustedSrcData, srcRowPitch, srcDepthPitch );

     if( pDidWorkAround )
     {
          *pDidWorkAround = needWorkaround;
     }

     return hr;
}
```

<strong>Update:</strong> To avoid breaking any existing applications that relied on the 'incorrect' behavior, UpdateSubresource with DirectX 11.1 still behaves this way. The <a href="https://docs.microsoft.com/en-us/windows/desktop/api/d3d11_1/nf-d3d11_1-id3d11devicecontext1-updatesubresource1
">UpdateSubresource1</a> method, however, does not have this issue.
