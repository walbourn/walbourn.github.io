---
layout: post
title: The DDS File Format Lives
date: 2010-02-05 15:33
author: walbourn
comments: true
categories: [dds, Uncategorized]
---
<span style="font-family: 'Arial','sans-serif';font-size: 10pt">For anyone doing work with DirectX, you've likely run into texture data being stored as a .DDS file. This format has it roots in the misty dark ages of DirectX history and in fact "DDS" stands for "DirectDraw Surface". The format is largely just a binary blob with a header derived from DirectDraw 7 structures. While DirectDraw itself has passed into the land of 'legacy' API, the file format itself lives on to store any number of hardware and API-specific data used as resources in rendering.</span>

<span style="font-family: 'Arial','sans-serif';font-size: 10pt">In the Direct3D 9 era, the format was reasonably well understood with a number of standard "FourCC" codes being used for common data like "DXT1", "DXT2", etc. and occasionally strange video-related things like "UYVY" data.  Where the format could be expressed as a standard surface, most code did something reasonable and used some FourCC code otherwise. The problem was that some formats didn't really fit here, particularly floating-point surfaces, and people solved this typically by just saying it was a FourCC code in the header and setting the FourCC code directly to the value of the D3DFMT enumeration. This resulted in strange non-ASCII FourCC codes like 110 or 112, but it basically worked.</span>

<span style="font-family: 'Arial','sans-serif';font-size: 10pt">Then along came DirectX 10. Here the formats were no longer using the Direct3D9-specific D3DFMT enumeration and the newer API made use of the DXGI_FORMAT enumeration. Some code actually just starting using FourCC codes set to DXGI_FORMAT enumerations instead, but this immediately ran into a major problem: D3DFMT and DXGI_FORMAT collide since they are different enumerations and there is no indication of the difference in the header. Big problem.</span>

<span style="font-family: 'Arial','sans-serif';font-size: 10pt">The solution was that we introduced an 'extended header'. A typical DDS file has the following header layout:</span>
<blockquote>DWORD               dwMagic; // (ASCII "DDS ")
DDS_HEADER      header;</blockquote>
If looking into the standard header you find a FourCC of "DX10" it has the following header layout:
<blockquote>DWORD               dwMagic; // (ASCII "DDS ")
DDS_HEADER          header;
DDS_HEADER_DXT10    header10;</blockquote>
<span style="font-family: 'Arial','sans-serif';font-size: 10pt">Looking inside header10, you'll find a value that is a DXGI_FORMAT enumeration. </span>

<span style="font-family: 'Arial','sans-serif';font-size: 10pt">Simple, elegant, and unambiguous. Unfortunately, we didn't make much effort to communicate this to the various vendors of texture tools and as a result it was not widely supported outside of D3DX. With DirectX 11, we've introduced a few more new DXGI formats and this "DX10" extended header is the only way to write that data out, so most 3rd party tools don't have the slightest clue how to process these files.</span>

<span style="font-family: 'Arial','sans-serif';font-size: 10pt">I made an attempt to rectify this situation with the DirectX SDK (August 2009) release by updating the Direct3D 10 sample <strong>DDSWithoutD3DX</strong> to include a more robust example of parsing modern DDS files, as well as creating a Direct3D 11 sample <strong>DDSWithoutD3DX11 </strong>to include the few additional formats. There was also some improvements made to the DDS-related <a href="http://msdn.microsoft.com/en-us/library/ee418142.aspx"><span style="color: #0000ff">documentation</span></a> as a DXGI Programmer's Guide in the Windows Graphics documentation.</span>

<span style="font-family: 'Arial','sans-serif';font-size: 10pt">A good first effort, but I missed a few details w.r.t. to BC4 and BC5.</span>

<span style="font-family: 'Arial','sans-serif';font-size: 10pt"><span>1.<span style="font: 7pt 'Times New Roman'">     </span></span></span><span style="font-family: 'Arial','sans-serif';font-size: 10pt">There is a code bug in the DirectX SDK (August 2009) samples. GetSurfaceInfo() in DDSTextureLoader.cpp should return a bytes-per-block size of 8 for DXGI_FORMAT_BC4_TYPELESS, DXGI_FORMAT_BC4_UNORM, and DXGI_FORMAT_BC4_SNORM. Instead the source is actually computing a block size of 16. This is fixed in the DirectX SDK (February 2010) version but it is easy to correct yourself:</span>

<span style="font-family: 'Courier New';font-size: 10pt">static void GetSurfaceInfo( UINT width, UINT height, DXGI_FORMAT fmt, UINT* pNumBytes, UINT* pRowBytes, UINT* pNumRows )</span>

<span style="font-family: 'Courier New';font-size: 10pt">{</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span>UINT numBytes = 0;</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span>UINT rowBytes = 0;</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span>UINT numRows = 0;</span>

<span style="font-family: 'Courier New';font-size: 10pt"> </span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span>bool bc = true;</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span>int bcnumBytesPerBlock = 16;</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span>switch (fmt)</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span>{</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span>case DXGI_FORMAT_BC1_TYPELESS:</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span>case DXGI_FORMAT_BC1_UNORM:</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span>case DXGI_FORMAT_BC1_UNORM_SRGB:</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span><span style="background: yellow">case DXGI_FORMAT_BC4_TYPELESS:</span></span>

<span style="font-family: 'Courier New';background: yellow;font-size: 10pt"><span>    </span>case DXGI_FORMAT_BC4_UNORM:</span>

<span style="font-family: 'Courier New';background: yellow;font-size: 10pt"><span>    </span>case DXGI_FORMAT_BC4_SNORM:</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span> </span><span>       </span>bcnumBytesPerBlock = 8;</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>        </span>break;</span>

<span style="font-family: 'Arial','sans-serif';font-size: 10pt"><span>2.<span style="font: 7pt 'Times New Roman'">     </span></span></span><span style="font-family: 'Arial','sans-serif';font-size: 10pt">There are 4 common FourCC codes used by the current versions of D3DX10 and D3DX11 when writing out BC4 and BC5 formats that should also be handled and documented. Alas this was brought to my attention too late for the February 2010 release, but should be corrected in a future release. Here too is a fairly easy fix to make in the DDSTextureLoader.cpp code in those samples. In the GetDXGIFormat() function under the FourCC case, just add four more cases ("BC4U", "BC4S", "ATI2", and "BC5S"):</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span>else if( ddpf.dwFlags &amp; DDS_FOURCC )</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>    </span>{</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>        </span>if( MAKEFOURCC( 'D', 'X', 'T', '1' ) == ddpf.dwFourCC )</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>            </span>return DXGI_FORMAT_BC1_UNORM;</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>        </span>if( MAKEFOURCC( 'D', 'X', 'T', '3' ) == ddpf.dwFourCC )</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>            </span>return DXGI_FORMAT_BC2_UNORM;</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>        </span>if( MAKEFOURCC( 'D', 'X', 'T', '5' ) == ddpf.dwFourCC )</span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>            </span>return DXGI_FORMAT_BC3_UNORM;</span>

<span style="font-family: 'Courier New';font-size: 10pt"> </span>

<span style="font-family: 'Courier New';font-size: 10pt"><span>        </span><span style="background: yellow">if( MAKEFOURCC( 'B', 'C', '4', 'U' ) == ddpf.dwFourCC )</span></span>

<span style="font-family: 'Courier New';background: yellow;font-size: 10pt"><span>            </span>return DXGI_FORMAT_BC4_UNORM;</span>

<span style="font-family: 'Courier New';background: yellow;font-size: 10pt"><span>        </span>if( MAKEFOURCC( 'B', 'C', '4', 'S' ) == ddpf.dwFourCC )</span>

<span style="font-family: 'Courier New';background: yellow;font-size: 10pt"><span>            </span>return DXGI_FORMAT_BC4_SNORM;</span>

<span style="font-family: 'Courier New';background: yellow;font-size: 10pt"> </span>

<span style="font-family: 'Courier New';background: yellow;font-size: 10pt"><span>        </span>if( MAKEFOURCC( 'A', 'T', 'I', '2' ) == ddpf.dwFourCC )</span>

<span style="font-family: 'Courier New';background: yellow;font-size: 10pt"><span>            </span>return DXGI_FORMAT_BC5_UNORM;</span>

<span style="font-family: 'Courier New';background: yellow;font-size: 10pt"><span> </span><span>       </span>if( MAKEFOURCC( 'B', 'C', '5', 'S' ) == ddpf.dwFourCC )</span>

<span style="font-family: 'Courier New';background: yellow;font-size: 10pt"><span>            </span>return DXGI_FORMAT_BC5_SNORM;</span>

<span style="font-family: 'Courier New';font-size: 10pt"> </span>

<span style="font-family: 'Arial','sans-serif';font-size: 10pt">In general, a robust <span> </span>DDS reader should handle all these common legacy cases, which is what DDSTextureLoader.cpp does, but robust DDS writer code should prefer using the new "DX10" extended header particularly for anything that uses FourCC codes beyond the basic Direct3D 9 set ("DXT1", "DXT3", "DXT5", "RGBG", "GRGB") and avoiding further use of the FourCC to hold an enumeration be it D3DFMT or DXGI_FORMAT.</span><span style="font-family: 'Courier New';font-size: 10pt"> </span>

&nbsp;

<strong>Update:</strong>  It should be noted that D3DX10 and D3DX11 will accept a FourCC of "BC5U" for the DXGI_FORMAT_BC5_UNORM format. It will also map "DXT2" to DXGI_FORMAT_BC2_UNORM and "DXT4" to DXGI_FORMAT_BC3_UNORM even though in Direct3D 9 these are interpreted differently. Also, some of the 3rd party DDS tools available will write BC4 format data with the FourCC "ATI1" which is not recognized by D3DX.

There's a newer version of "DDSWithoutD3DX" in the DirectX SDK (June 2010) release that includes these fixes, and a newer version still <a href="http://blogs.msdn.com/b/chuckw/archive/2010/07/15/ddswithoutd3dx-sample-update.aspx" title="Games for Windows and the DirectX SDK blog">here</a> that includes code for loading cubemaps, volume maps, etc.

<strong>DirectXTex:</strong> The <a href="http://go.microsoft.com/fwlink/?LinkId=248926">DirectXTex</a> library on <span style="text-decoration: line-through">CodePlex</span>GitHub fully supports the DDS file format. When possible it generate DDS files using the 'legacy' DirectX 9 header for maximum compatibility, but will use 'DX10' header extensions when necessary--an important special case for <code>DXGI_FORMAT_R10G10B10A2_UNORM</code> is covered in <a href="https://blogs.msdn.microsoft.com/chuckw/2010/06/15/dds-update-and-1010102-problems/">this post</a>. Users can also force the library to always generate 'DX10' header extension files which are slightly more efficient for loading.

<strong>Tools:</strong> The latest DDS.H header can obtained from <a href="https://github.com/Microsoft/DirectXTex/blob/master/DirectXTex/DDS.h">GitHub</a>. A DDSDUMP.CPP command-line tool for examining the contents of a DDS file is also <a href="https://raw.githubusercontent.com/wiki/Microsoft/DirectXTex/ddsdump.cpp">available</a>.
