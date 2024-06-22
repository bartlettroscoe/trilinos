//@HEADER
// *****************************************************************************
//          Tempus: Time Integration and Sensitivity Analysis Package
//
// Copyright 2017 NTESS and the Tempus contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
//@HEADER

#include "Tempus_ExplicitRK_FSA.hpp"

#include "Teuchos_UnitTestRepository.hpp"
#include "Teuchos_GlobalMPISession.hpp"
#include "Teuchos_CommandLineProcessor.hpp"

std::string method_name;

namespace Tempus_Test {

TEUCHOS_UNIT_TEST(ExplicitRK, SinCos_Staggered_FSA)
{
  test_sincos_fsa(method_name, false, false, out, success);
}

TEUCHOS_UNIT_TEST(ExplicitRK, SinCos_Staggered_FSA_Tangent)
{
  test_sincos_fsa(method_name, false, true, out, success);
}

}  // namespace Tempus_Test

int main(int argc, char* argv[])
{
  Teuchos::GlobalMPISession mpiSession(&argc, &argv);

  // Add "--method" command line argument
  Teuchos::CommandLineProcessor& CLP = Teuchos::UnitTestRepository::getCLP();
  method_name                        = "";
  CLP.setOption("method", &method_name, "Stepper method");

  return Teuchos::UnitTestRepository::runUnitTestsFromMain(argc, argv);
}
