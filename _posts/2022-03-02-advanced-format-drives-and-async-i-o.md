---
layout: post
title: Advanced Format drives and Async I/O
date: 2022-03-02 16:34
author: Chuck Walbourn
comments: true
categories: [general]
---

One of the on-going challenges for shipping games on PC is the constant evolution of the platform. Each time a game or application makes an assumption about how the system works, it becomes a potential bug when those assumptions change. Recently I encountered one of those changing assumptions: the sector size to use for non-buffered asynchronous I/O.

<!--more-->

For many years we've advocated for game developers targeting Windows and Xbox to take full advantage of asynchronous I/O--also called *overlapped* I/O. This means making a bunch of requests using ``FILE_FLAG_OVERLAPPED``, and then doing more work while the disk drive fetches your data rather than blocking the loading thread and potentially wasting CPU. This is particularly important today with <abbr title="nonvolatile memory express">NVMe</abbr> drives that can read a *lot* of data in the time it takes you to do thread switching and scheduling. Beyond just doing asynchronous I/O, there are times when you also want to use 'non-buffered' asynchronous I/O (``FILE_FLAG_NO_BUFFERING``) so the data is placed directly into memory where you want it, rather than being read into system RAM and then copied into your program's memory.

Doing this is a bit tricky, and there are plenty of times when just relying on the file system cache with the appropriate hint (``FILE_FLAG_SEQUENTIAL_SCAN`` or ``FILE_FLAG_RANDOM_ACCESS``) is a better choice, but historically the non-buffered asynchronous I/O approach has been used for 'streaming' digital music or voice from disk to keep the memory foot-print minimal. This was implemented in the deprecated [XACT](https://en.wikipedia.org/wiki/Cross-platform_Audio_Creation_Tool) engine, and I implemented it in [DirectX Tool Kit for Audio](https://walbourn.github.io/directx-tool-kit-for-audio/) as well.

> As an aside, for indie games without a huge amount of content, given the memory sizes of most PCs and consoles these days, it's often easier to just load *all* your music into memory and play it from there rather than fussing about with streaming.

When doing non-buffered asynchronous I/O, you need to meet some technical requirements per [Microsoft Docs](https://docs.microsoft.com/windows/win32/fileio/synchronous-and-asynchronous-i-o): The offset in the file you are reading must be aligned to the 'sector size' of the hard-disk since that's the physical size of request the hardware is designed to handle, -and- the destination memory must be aligned to virtual memory pages. You use this information to lay out how your content is organized on disk, placing individual assets aligned to the right place in the file to meet these requirements.

There are a few choices here, but historically **2048** was the magic number to use because this is the sector size of DVD media, it mapped well to the 4K memory alignment of virtual memory pages, and it was a multiple of HDD sector sizes (typically 512 or 1024).

The emphasis here is the "*was*" part.

As drive technology has advanced, and especially with the advent of <abbr title="solid state drives">SSD</abbr> storage, the classic sector size of 512 or even 2048 was becoming inefficient. The [Advanced Format](https://en.wikipedia.org/wiki/Advanced_Format) drive standard uses a 4096 sector size (with possibly extra bytes per physical sector for error-correcting in the hardware; but it still has 4096 bytes of data). This, of course, broke assumptions for the OS and applications about the sector size.  As an interim solution, many drives support **Advanced Format (512e)** which means the hardware emulates a 512 byte sector size to make existing software work. There are now drives supporting **Advanced Format (4Kn)** (i.e. 4K Native Disk) which expose their native 4096 byte sector size because the 512e emulation has a 5-10% performance hit in write performance.

> Windows 8 or later supports both 512e and 4Kn modes. See [Microsoft Docs](https://docs.microsoft.com/windows/compatibility/advanced-format-disk-compatibility-update).

Specifically in my case, the storage on an Xbox Series X\|S console is a **Advanced Format (4Kn)** drive.

The ``xwbtool`` which builds XACT-style WaveBanks for both in-memory and streaming scenarios used the 2048 sector size for streaming wave banks, which worked fine but fails when used on an Xbox Series X\|S depending on how exactly the data ends up laying out. For the February 2022 release of the *DirectX Tool Kit* for [DX11](https://github.com/microsoft/DirectXTK/releases/tag/feb2022) / [DX12](https://github.com/microsoft/DirectXTK12/releases/tag/feb2022), I updated the tool to support a new ``-af`` switch which uses a 4096 sector size alignment instead. I also updated the ``SoundStreamInstance`` class to support using either 2048 or 4096 sector alignment based on the content of the ``.xwb`` file.

Even for buffered asynchronous I/O, using the 4096 sector size to align your data is a good idea for best performance, and most game engines already moved to this for the current console generation. The difference here is that buffered asynchronous I/O "just works" albeit with some extra penalty, but the ``ReadFile`` for a non-buffered asynchronous I/O request that doesn't meet the sector size requirement fails at runtime.

> For older software (such as games that used XACT audio streaming), you can make use of the `RemoveNoBufferingFlagFromCreateFile` shim in the [Microsoft Application Compatibility Toolkit (ACT)](https://docs.microsoft.com/windows/deployment/planning/compatibility-fixes-for-windows-8-windows-7-and-windows-vista) to work around non-buffered I/O read failures with AF (4Kn) drives.
