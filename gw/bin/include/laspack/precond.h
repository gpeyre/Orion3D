/****************************************************************************/
/*                                precond.h                                 */
/****************************************************************************/
/*                                                                          */
/* PRECONDitioners for iterative solvers of systems of linear equations     */
/*                                                                          */
/* Copyright (C) 1992-1995 Tomas Skalicky. All rights reserved.             */
/*                                                                          */
/****************************************************************************/
/*                                                                          */
/*        ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE TERMS          */
/*              OF THE COPYRIGHT NOTICE (SEE FILE COPYRGHT.H)               */
/*                                                                          */
/****************************************************************************/

#ifndef PRECOND_H
#define PRECOND_H

#include "laspack/lastypes.h"
#include "laspack/vector.h"
#include "laspack/qmatrix.h"
#include "laspack/copyrght.h"

typedef Vector *(*PrecondProcType)(QMatrix *, Vector *, Vector *, double);

/* declaration of preconditioners */

Vector *JacobiPrecond(QMatrix *A, Vector *y, Vector *c, double Omega);
Vector *SSORPrecond(QMatrix *A, Vector *y, Vector *c, double Omega);
Vector *ILUPrecond(QMatrix *A, Vector *y, Vector *c, double Omega);

#endif /* PRECOND_H */
