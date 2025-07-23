---
layout: post
title: Modern C++ Bitmask types
date: 2020-06-19 14:38
author: Chuck Walbourn
comments: true
categories: [general]
---

Bitmask flags are a ubiquitous pattern in C & C++ code. In the 'old days', they were typically defined as:

```cpp
#define FLAGS_NONE             0x0
#define FLAGS_DO_A_THING       0x1
#define FLAGS_DISABLE_A_THING  0x2
#define FLAGS_OPTIONAL_FEATURE 0x4

HRESULT MyFunction(int flags);
```

Since C/C++ preprocessor defines tend to have a lot of potential hazards, over time developers have moved to using ``enum``:

```cpp
enum FLAGS_FOR_MYFUNCTION
{
    FLAGS_NONE             = 0x0,
    FLAGS_DO_A_THING       = 0x1,
    FLAGS_DISABLE_A_THING  = 0x2,
    FLAGS_OPTIONAL_FEATURE = 0x4
};

HRESULT MyFunction(int flags);
```

With C++11 you can also provide an underlying type of the ``enum`` so you can use ``unsigned long`` instead of ``int`` without any signed/unsigned mismatch warnings:

```cpp
enum FLAGS_FOR_MYFUNCTION : unsigned long
{
    FLAGS_NONE             = 0x0,
    FLAGS_DO_A_THING       = 0x1,
    FLAGS_DISABLE_A_THING  = 0x2,
    FLAGS_OPTIONAL_FEATURE = 0x4
};

HRESULT MyFunction(unsigned long flags);
```

This still leaves the use of flags 'loosely typed' since if you had a second set of (possibly unrelated) flags you can easily write:

```cpp
HRESULT MyFunction(FLAGS_DO_A_THING | UNRELATED_FLAGS_FEATURE);
```

Modern C++ recommends solving this with Bitmask flags per the [standard](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3485.pdf) (section 17.5.2.1.3). DirectX 11 used the older loosely typed ``DWORD`` (a.k.a ``unsigned long``) plus ``enum`` flags, but DirectX 12 adopts this new *typed bitmask flags* pattern. Therefore, I've updated my GitHub libraries to use the pattern as well, and this does have some implications for existing code.
<!--more-->

The Modern C++ recommendation is to change our example as follows:

```cpp
enum FLAGS_FOR_MYFUNCTION
{
    FLAGS_NONE             = 0x0,
    FLAGS_DO_A_THING       = 0x1,
    FLAGS_DISABLE_A_THING  = 0x2,
    FLAGS_OPTIONAL_FEATURE = 0x4
};

constexpr inline T operator~ (T a) { return static_cast<T>( ~static_cast<std::underlying_type<T>::type>(a) ); }
constexpr inline T operator| (T a, T b) { return static_cast<T>( static_cast<std::underlying_type<T>::type>(a) | static_cast<std::underlying_type<T>::type>(b) ); }
constexpr inline T operator& (T a, T b) { return static_cast<T>( static_cast<std::underlying_type<T>::type>(a) & static_cast<std::underlying_type<T>::type>(b) ); }
constexpr inline T operator^ (T a, T b) { return static_cast<T>( static_cast<std::underlying_type<T>::type>(a) ^ static_cast<std::underlying_type<T>::type>(b) ); }
constexpr inline T& operator|= (T& a, T b) { return reinterpret_cast<T&>( reinterpret_cast<std::underlying_type<T>::type&>(a) |= static_cast<std::underlying_type<T>::type>(b) ); }
constexpr inline T& operator&= (T& a, T b) { return reinterpret_cast<T&>( reinterpret_cast<std::underlying_type<T>::type&>(a) &= static_cast<std::underlying_type<T>::type>(b) ); }
constexpr inline T& operator^= (T& a, T b) { return reinterpret_cast<T&>( reinterpret_cast<std::underlying_type<T>::type&>(a) ^= static_cast<std::underlying_type<T>::type>(b) ); }

HRESULT MyFunction(FLAGS_FOR_MYFUNCTION flags);
```

This provides the various bit-wise operators so you can call:

```cpp
hr = MyFunction(FLAGS_DISABLE_A_THING | FLAGS_DO_A_THING);
```

C++11 introduced the idea of *strongly typed enumerations* in the form of [enum class](https://en.cppreference.com/w/cpp/language/enum) which prevents the implicit conversion of an ``enum`` to it's underlying type as well as scoping the ``enum`` members to it's namespace. While you can use it for these Bitmask types, it does make bit-testing them a little less intuitive:

```cpp
// This compiles if you used enum, but not if you use enum class
if (flags & FLAGS_DISABLE_A_THING)
    ...

// For an enum class, you have to use:
if ((flags & FLAGS_FOR_MYFUNCTION::FLAGS_DISABLE_A_THING) == FLAGS_FOR_MYFUNCTION::FLAGS_DISABLE_A_THING)
    ...
```

In DirectX 12, DirectX Tool Kit for [DX11](https://github.com/microsoft/DirectXTK) / [DX12](https://github.com/microsoft/DirectXTK12), [DirectXTex](https://github.com/microsoft/DirectXTex), and [DirectMesh](https://github.com/microsoft/DirectXMesh) they all make use of a macro from ``winnt.h`` that defines the operators for a given type:

```cpp
enum FLAGS_FOR_MYFUNCTION
{
    FLAGS_NONE             = 0x0,
    FLAGS_DO_A_THING       = 0x1,
    FLAGS_DISABLE_A_THING  = 0x2,
    FLAGS_OPTIONAL_FEATURE = 0x4
};

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-dynamic-exception-spec"
#pragma clang diagnostic ignored "-Wextra-semi-stmt"
#endif

DEFINE_ENUM_FLAG_OPERATORS(FLAGS_FOR_MYFUNCTION);

#ifdef __clang__
#pragma clang diagnostic pop
#endif

HRESULT MyFunction(FLAGS_FOR_MYFUNCTION flags);
```

> Prior to Windows 10 SDK (14393), the ``DEFINE_ENUM_FLAG_OPERATORS`` macro did not make use of ``constexpr``, meaning that the resulting flags couldn't be used in ``constexpr`` expressions. This issue should only impact legacy Xbox One XDK code at this point.

> With the Windows 10 SDK (19041) and clang v10, there are some conformance issues with ``DEFINE_ENUM_FLAG_OPERATORS`` that generates ``-Wdeprecated-dynamic-exception-spec`` so I suppress those in my libraries when using this macro.

> Technically the `;` after the macro results in an `-Wextra-semi-stmt` warning. Without it, however, C++ code formatting will be incorrectly indented. Hence the second warning suppression.

# Client code impact

What does this all actually mean for a developer using the libraries?

Well, for one thing the literal ``0`` is not a valid flags value.

```cpp
// This won't build with the June 2020 release or later of DirectXTex
hr = DirectX::LoadFromDDSFile("texture.dds", 0, nullptr, image);

// Instead you must use the default enum value:
hr = DirectX::LoadFromDDSFile("texture.dds", DDS_FLAGS_NONE, nullptr, image);
```

Also, anywhere you 'build-up' a flags setting, you need to use the correct type instead of ``DWORD``.

```cpp
// This used to build but now does not.
DWORD flags = DDS_FLAGS_NONE;
if (somesetting)
    flags |= DDS_FLAGS_FORCE_RGB;

// The modern C++ way to write it is:
DDS_FLAGS flags = DDS_FLAGS_NONE;
if (somesetting)
    flags |= DDS_FLAGS_FORCE_RGB;
```

DirectXTex in particular has numerous sets of flags, so this improves type-safety so you can't use the incorrect flags for a particular context:

```cpp
// This used to build and didn't do what you expected...
// It now results in a compile-time error.
hr = DirectX::LoadFromDDSFile("texture.dds", WIC_FLAGS_ALLOW_MONO, nullptr, image);
```

That said, there are a few specific cases where I was a little 'too clever' in my overlapping of loosely typed flags. For example, the ``TEX_FILTER_POINT``, ``TEX_FILTER_LINEAR``, ``TEX_FILTER_CUBIC``, and ``TEX_FILTER_FANT`` flags were designed to exactly match ``WIC_FLAGS_FILTER_POINT``, ``WIC_FLAGS_FILTER_LINEAR``, ``WIC_FLAGS_FILTER_CUBIC``, and ``WIC_FLAGS_FILTER_FANT``. Therefore there are a few specific ``operator|`` overloads defined to handle these cases.

```cpp
// This used to build and work before
DWORD filterFlags = TEX_FILTER_CUBIC;
hr = DirectX::LoadFromWICFile("texture.dds", filterFlags, nullptr, image);

// As of DirectXTex June 2020 or later, it needs to be:
TEX_FILTER filterFlags = TEX_FILTER_CUBIC;
hr = DirectX::LoadFromWICFile("texture.dds", WIC_FLAGS_NONE | filterFlags, nullptr, image);
```

> Note that I don't define every possible permutation of the ``operator|`` for these cross-type cases. The 'destination' type must be the first flag type. IOW: ``filterFlags | WIC_FLAGS_NONE`` will not compile. I also don't define all the other bit-wise operators for these combo cases, even though each flag type does support them.
