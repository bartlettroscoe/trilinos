// clang-format off
// @HEADER
// *****************************************************************************
//                            Tacho package
//
// Copyright 2022 NTESS and the Tacho contributors.
// SPDX-License-Identifier: BSD-2-Clause
// *****************************************************************************
// @HEADER
// clang-format on
#ifndef __TACHO_TRSV_SERIAL_HPP__
#define __TACHO_TRSV_SERIAL_HPP__

/// \file  Tacho_Trsv_External.hpp
/// \brief BLAS triangular solve matrix
/// \author Kyungjoo Kim (kyukim@sandia.gov)

#include "Tacho_Blas_Serial.hpp"

namespace Tacho {

template <typename ArgUplo, typename ArgTransA> struct Trsv<ArgUplo, ArgTransA, Algo::Serial> {
  template <typename DiagType, typename ViewTypeA, typename ViewTypeB>
  inline static int invoke(const DiagType diagA, const ViewTypeA &A, const ViewTypeB &B) {

    static constexpr bool runOnHost = run_tacho_on_host_v<typename ViewTypeA::execution_space>;

    if constexpr(runOnHost) {
      typedef typename ViewTypeA::non_const_value_type value_type;
      typedef typename ViewTypeB::non_const_value_type value_type_b;

      static_assert(ViewTypeA::rank == 2, "A is not rank 2 view.");
      static_assert(ViewTypeB::rank == 2, "B is not rank 2 view.");

      static_assert(std::is_same<value_type, value_type_b>::value, "A and B do not have the same value type.");

      const ordinal_type m = B.extent(0), n = B.extent(1);

      if (m > 0 && n > 0) {
        //if (n == 1) {
        //  Blas<value_type>::trsv(ArgUplo::param, ArgTransA::param, diagA.param, m, A.data(), A.stride_1(), B.data(),
        //                         B.stride_0());
        //} else {
          BlasSerial<value_type>::trsm(Side::Left::param, ArgUplo::param, ArgTransA::param, diagA.param, m, n, value_type(1),
                                       A.data(), A.stride_1(), B.data(), B.stride_1());
        //}
      }
    } else {
      TACHO_TEST_FOR_ABORT(true, "This function is only allowed in host space.");
    }
    return 0;
  }

  template <typename MemberType, typename DiagType, typename ViewTypeA, typename ViewTypeB>
  KOKKOS_INLINE_FUNCTION static int invoke(MemberType &member, const DiagType diagA, const ViewTypeA &A,
                                           const ViewTypeB &B) {

    static constexpr bool runOnHost = run_tacho_on_host_v<typename ViewTypeA::execution_space>;

    if constexpr(runOnHost) {
      // Kokkos::single(Kokkos::PerTeam(member), [&]() {
      invoke(diagA, A, B);
      //});
    } else {
      TACHO_TEST_FOR_ABORT(true, "This function is only allowed in host space.");
    }
    return 0;
  }
};

} // namespace Tacho
#endif
