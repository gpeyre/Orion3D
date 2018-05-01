/****************************************************************************/
/*                                  rtc.h                                   */
/****************************************************************************/
/*                                                                          */
/* Residual Termination Control                                             */
/*                                                                          */
/* Copyright (C) 1992-1995 Tomas Skalicky. All rights reserved.             */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*        ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE TERMS          */
/*              OF THE COPYRIGHT NOTICE (SEE FILE COPYRGHT.H)               */
/*                                                                          */
/****************************************************************************/

#ifndef RTC_H
#define RTC_H

#include "laspack/lastypes.h"
#include "laspack/vector.h"
#include "laspack/itersolv.h"
#include "laspack/copyrght.h"

/* identifiers for iteration methods */

typedef enum {
    /* classical iterative methods */
    JacobiIterId,
    SORForwIterId,
    SORBackwIterId,
    SSORIterId,

    /* semi-iterative methods */
    ChebyshevIterId,

    /* CG and CG-like methods */
    CGIterId,
    CGNIterId,
    GMRESIterId,
    BiCGIterId,
    QMRIterId,
    CGSIterId,
    BiCGSTABIterId,

    /* multigrid and multigrid based methods */
    MGIterId,
    NestedMGIterId,
    MGPCGIterId,
    BPXPCGIterId
} IterIdType;

typedef void (*RTCAuxProcType)(int, double, double, IterIdType);

void SetRTCAccuracy(double Eps);
void SetRTCAuxProc(RTCAuxProcType AuxProc);
Boolean RTCResult(int Iter, double rNorm, double bNorm, IterIdType IterId);
int GetLastNoIter(void);
double GetLastAccuracy(void);

#endif /* RTC_H */
