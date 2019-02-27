---
layout: post
title: Known Issue: Direct3D 11 UpdateSubresource and Deferred Contexts
date: 2010-07-28 14:31
author: walbourn
comments: true
categories: [direct3d, Uncategorized]
---
<p>The <code>UpdateSubresource</code> method on the <code>D3D11DeviceContext</code> interface takes as one of it's parameters an optional destination offset:</p>
<p><code>void UpdateSubresource( [in] ID3D11Resource *pDstResource, [in] UINT DstSubresource, <span style="background-color: #ffff00;">[in] const D3D11_BOX *pDstBox,</span> [in] const void *pSrcData, [in] UINT SrcRowPitch, [in] UINT SrcDepthPitch ); </code></p>
<p>&nbsp;This works as advertised for the immediate device context which operates directly on the GPU, but there is a problem when it is used in a deferred context through the software runtime emulation unless pDstBox is NULL or 0,0,0. The work-around for this problem is now included in the <em>Remarks </em>documenting the <code>UpdateSubresource</code> function in the Windows DirectX Graphics documentation on <a title="MSDN" href="http://msdn.microsoft.com/en-us/library/ff476486.aspx">MSDN</a>&nbsp;and in the June 2010 DirectX SDK. The work-around assumes that any driver-level command list optimization is implemented 'correctly', hence the call to <code>CheckFeatureSupport</code>.</p>
<pre>HRESULT UpdateSubresource_Workaround(
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
     D3D11_DEVICE_CONTEXT_TYPE contextType = pDeviceContext-&gt;GetType();

     if( pDstBox &amp;&amp; (D3D11_DEVICE_CONTEXT_DEFERRED == contextType) )
     {
          D3D11_FEATURE_DATA_THREADING threadingCaps = { FALSE, FALSE };

          hr = pDevice-&gt;CheckFeatureSupport( D3D11_FEATURE_THREADING, &amp;threadingCaps, sizeof(threadingCaps) );
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

          pAdjustedSrcData = ((const BYTE*)pSrcData) - (alignedBox.front * srcDepthPitch) - (alignedBox.top * srcRowPitch) - (alignedBox.left * srcBytesPerElement);
     }

     pDeviceContext-&gt;UpdateSubresource( pDstResource, dstSubresource, pDstBox, pAdjustedSrcData, srcRowPitch, srcDepthPitch );

     if( pDidWorkAround )
     {
          *pDidWorkAround = needWorkaround;
     }

     return hr;
}
</pre>
<pre>&nbsp;</pre>
<p><strong>Update:</strong> To avoid breaking any existing applications that relied on the 'incorrect' behavior, UpdateSubresource with DirectX 11.1 still behaves this way. The <a href="http://msdn.microsoft.com/en-us/library/windows/desktop/hh446790.aspx">UpdateSubresource1</a> method, however, does not have this issue.</p>
