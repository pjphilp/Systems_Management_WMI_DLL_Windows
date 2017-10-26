///****************************************************************************
//
//    Copyright 2017 by WinSystems Inc.
//
//    Permission is hereby granted to the purchaser of WinSystems GPIO cards
//    and CPU products incorporating a GPIO device, to distribute any binary
//    file or files compiled using this source code directly or in any work
//    derived by the user from this file. In no case may the source code,
//    original or derived from this file, be distributed to any third party
//    except by explicit permission of WinSystems. This file is distributed
//    on an "As-is" basis and no warranty as to performance or fitness of pur-
//    poses is expressed or implied. In no case shall WinSystems be liable for
//    any direct or indirect loss or damage, real or consequential resulting
//    from the usage of this source code. It is the user's sole responsibility
//    to determine fitness for any considered purpose.
//
///****************************************************************************
//
//    Name       : x86_64_port.h
//
//    Project    : generic 64 bit x86 porting defines
//
//    Author     : pjp
//
//    Typdefs & #defines to aid in porting to the x86 platform
//
///****************************************************************************
//
//      Date      Revision    Description
//    --------    --------    ---------------------------------------------
//    06/11/14      0.1       PJP - Original
//
///****************************************************************************

#pragma once

///////////////////////////////////////////////////////////////////////////////

typedef bool *  pbool;
typedef void *  PVOID;
typedef void *  pvoid;

//typedef          _int8     int8_t;
typedef unsigned _int8     uint8_t;
typedef          _int16    int16_t;
typedef unsigned _int16    uint16_t;
typedef          _int32    int32_t;
typedef unsigned _int32    uint32_t;
typedef          _int64    int64_t;
typedef unsigned _int64    uint64_t;

typedef uint8_t  *puint8_t;
typedef uint16_t *puint16_t;
typedef uint32_t *puint32_t;
typedef uint64_t *puint64_t;
//typedef int8_t   *pint8_t;
typedef int16_t  *pint16_t;
typedef int32_t  *pint32_t;
typedef int64_t  *pint64_t;

typedef float    *pfloat_t;

#ifdef __KERNEL_BUILD
#define true	1
#define TRUE	true
#define false	0
#define FALSE	false

#define null    NULL
#endif

