//@HEADER
// *****************************************************************************
//          Tempus: Time Integration and Sensitivity Analysis Package
//
// Copyright 2017 NTESS and the Tempus contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
//@HEADER

#include "Tempus_ExplicitTemplateInstantiation.hpp"

#ifdef HAVE_TEMPUS_EXPLICIT_INSTANTIATION
#include "Tempus_CombinedForwardSensitivityModelEvaluator_decl.hpp"
#include "Tempus_CombinedForwardSensitivityModelEvaluator_impl.hpp"

namespace Tempus {
TEMPUS_INSTANTIATE_TEMPLATE_CLASS(CombinedForwardSensitivityModelEvaluator)
}

#endif
