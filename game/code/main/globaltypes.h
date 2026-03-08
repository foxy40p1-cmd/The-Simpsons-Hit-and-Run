//=============================================================================
// Copyright (C) 2002 Radical Entertainment Ltd.  All rights reserved.
//
// File:        globaltypes.h
//
// Description: Declarations of utility types.
//
// History:     2/18/2003 + Created -- Esan
//
//=============================================================================

#ifndef GLOBALTYPES_H
#define GLOBALTYPES_H

//
// define 64 bit integer for all platforms
//
#ifdef RAD_PS2
typedef unsigned long simpsonsUInt64;
#endif

#ifdef RAD_GAMECUBE
typedef unsigned long long simpsonsUInt64;
#endif

#if defined RAD_XBOX || defined RAD_WIN32
typedef unsigned __int64 simpsonsUInt64;
#endif

#ifdef RAD_PS3
typedef unsigned long long simpsonsUInt64;
typedef unsigned long long radTime64;
typedef long long radInt64;
typedef unsigned char PDDI_U8;
typedef unsigned int PDDI_U32;
typedef unsigned int P3D_U32;

#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif

#endif

#endif //GLOBALTYPES_H
