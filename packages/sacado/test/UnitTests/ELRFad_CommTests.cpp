// @HEADER
// *****************************************************************************
//                           Sacado Package
//
// Copyright 2006 NTESS and the Sacado contributors.
// SPDX-License-Identifier: LGPL-2.1-or-later
// *****************************************************************************
// @HEADER

#include "Teuchos_UnitTestHarness.hpp"
#include "Teuchos_UnitTestRepository.hpp"
#include "Teuchos_GlobalMPISession.hpp"

#include "Sacado.hpp"
#include "Fad_CommTests.hpp"

typedef int Ordinal;
typedef Sacado::ELRFad::DFad<double> Fad_DFadType;
typedef Sacado::ELRFad::SLFad<double,10> Fad_SLFadType;
typedef Sacado::ELRFad::SFad<double,5> Fad_SFadType;
Sacado::Random<double> rnd;
FAD_COMM_TESTS(Fad_DFadType, ELRFad_DFad)
FAD_COMM_TESTS(Fad_SLFadType, ELRFad_SLFad)
FAD_COMM_TESTS(Fad_SFadType, ELRFad_SFad)

int main( int argc, char* argv[] ) {
  Teuchos::GlobalMPISession mpiSession(&argc, &argv);

  return Teuchos::UnitTestRepository::runUnitTestsFromMain(argc, argv);
}
