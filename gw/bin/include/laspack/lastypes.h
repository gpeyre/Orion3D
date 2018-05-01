/****************************************************************************/
/*                                lastypes.h                                 */
/****************************************************************************/
/*                                                                          */
/* basic LASpack TYPES                                                      */
/*                                                                          */
/* Copyright (C) 1992-1995 Tomas Skalicky. All rights reserved.             */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*        ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE TERMS          */
/*              OF THE COPYRIGHT NOTICE (SEE FILE COPYRGHT.H)               */
/*                                                                          */
/****************************************************************************/

#ifndef LASTYPES_H
#define LASTYPES_H

#include "laspack/copyrght.h"

#ifndef BOOLEAN
#define BOOLEAN

typedef enum {
    False = 0,
    True  = 1
} Boolean; /* boolean type */

#endif /* BOOLEAN */

typedef enum {
    Rowws,
    Clmws
} ElOrderType;

typedef enum {
    Normal,
    Tempor
} InstanceType;

#endif /* LASTYPES_H */
