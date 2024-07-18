// @HEADER
// *****************************************************************************
//          Tpetra: Templated Linear Algebra Services Package
//
// Copyright 2008 NTESS and the Tpetra contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#include "TpetraExt_MatrixMatrix.hpp"

#ifdef HAVE_TPETRA_EXPLICIT_INSTANTIATION

#include "TpetraCore_ETIHelperMacros.h"
#include "TpetraExt_MatrixMatrix_def.hpp"

namespace Tpetra {

  TPETRA_ETI_MANGLING_TYPEDEFS()

  TPETRA_INSTANTIATE_SLGN(TPETRA_MATRIXMATRIX_INSTANT)

  // Zoltan2 wants Scalar = int (Bug 6298).
  // This is already covered above for the GO = int case.
  //
  // FIXME (mfh 07 Oct 2015) I'm hand-rolling this for now.
  // It would be better to let CMake do the ETI generation,
  // as with CrsMatrix.

  // NOTE: The Zoltan2 adaptation stuff only gets engaged for full ETI.
  // If we're doing reduced ETI, we disable all of this

#ifndef  HAVE_TPETRA_REDUCED_ETI

#ifdef HAVE_TPETRA_INST_INT_LONG
#ifdef HAVE_TPETRA_INST_LONG_DOUBLE
#define TPETRA_MATRIXMATRIX_INSTANT_SC_LONG_DOUBLE_LO_INT_GO_LONG( NT ) \
  TPETRA_MATRIXMATRIX_INSTANT( longdouble, int, long, NT )

  TPETRA_INSTANTIATE_N(TPETRA_MATRIXMATRIX_INSTANT_SC_LONG_DOUBLE_LO_INT_GO_LONG)
#else 
#define TPETRA_MATRIXMATRIX_INSTANT_SC_INT_LO_INT_GO_LONG( NT ) \
  TPETRA_MATRIXMATRIX_INSTANT( int, int, long, NT )

  TPETRA_INSTANTIATE_N(TPETRA_MATRIXMATRIX_INSTANT_SC_INT_LO_INT_GO_LONG)
#endif //HAVE_TPETRA_INST_LONG_DOUBLE
#endif // HAVE_TPETRA_INST_INT_LONG

#ifdef HAVE_TPETRA_INST_INT_LONG_LONG
#ifdef HAVE_TPETRA_INST_LONG_DOUBLE
#define TPETRA_MATRIXMATRIX_INSTANT_SC_LONG_DOUBLE_LO_INT_GO_LONG_LONG( NT ) \
  TPETRA_MATRIXMATRIX_INSTANT( longdouble, int, longlong, NT )

  TPETRA_INSTANTIATE_N(TPETRA_MATRIXMATRIX_INSTANT_SC_LONG_DOUBLE_LO_INT_GO_LONG_LONG)
#else
#define TPETRA_MATRIXMATRIX_INSTANT_SC_INT_LO_INT_GO_LONG_LONG( NT ) \
  TPETRA_MATRIXMATRIX_INSTANT( int, int, longlong, NT )

  TPETRA_INSTANTIATE_N(TPETRA_MATRIXMATRIX_INSTANT_SC_INT_LO_INT_GO_LONG_LONG)
#endif //HAVE_TPETRA_INST_LONG_DOUBLE
#endif // HAVE_TPETRA_INST_INT_LONG_LONG

#ifdef HAVE_TPETRA_INST_INT_UNSIGNED
#ifdef HAVE_TPETRA_INST_LONG_DOUBLE
#define TPETRA_MATRIXMATRIX_INSTANT_SC_LONG_DOUBLE_LO_INT_GO_UNSIGNED( NT ) \
  TPETRA_MATRIXMATRIX_INSTANT( longdouble, int, unsigned, NT )

  TPETRA_INSTANTIATE_N(TPETRA_MATRIXMATRIX_INSTANT_SC_LONG_DOUBLE_LO_INT_GO_UNSIGNED)
#else
#define TPETRA_MATRIXMATRIX_INSTANT_SC_INT_LO_INT_GO_UNSIGNED( NT ) \
  TPETRA_MATRIXMATRIX_INSTANT( int, int, unsigned, NT )

  TPETRA_INSTANTIATE_N(TPETRA_MATRIXMATRIX_INSTANT_SC_INT_LO_INT_GO_UNSIGNED)
#endif //HAVE_TPETRA_INST_LONG_DOUBLE
#endif // HAVE_TPETRA_INST_INT_UNSIGNED

#ifdef HAVE_TPETRA_INST_INT_UNSIGNED_LONG
#ifdef HAVE_TPETRA_INST_LONG_DOUBLE
#define TPETRA_MATRIXMATRIX_INSTANT_SC_LONG_DOUBLE_LO_INT_GO_UNSIGNED_LONG( NT ) \
  TPETRA_MATRIXMATRIX_INSTANT( longdouble, int, unsignedlong, NT )

  TPETRA_INSTANTIATE_N(TPETRA_MATRIXMATRIX_INSTANT_SC_LONG_DOUBLE_LO_INT_GO_UNSIGNED_LONG)
#else
#define TPETRA_MATRIXMATRIX_INSTANT_SC_INT_LO_INT_GO_UNSIGNED_LONG( NT ) \
  TPETRA_MATRIXMATRIX_INSTANT( int, int, unsignedlong, NT )

  TPETRA_INSTANTIATE_N(TPETRA_MATRIXMATRIX_INSTANT_SC_INT_LO_INT_GO_UNSIGNED_LONG)
#endif //HAVE_TPETRA_INST_LONG_DOUBLE
#endif // HAVE_TPETRA_INST_INT_UNSIGNED_LONG

#endif // HAVE_TPETRA_REDUCED_ETI
    
} // namespace Tpetra

#endif // HAVE_TPETRA_EXPLICIT_INSTANTIATION
