// @HEADER
// *****************************************************************************
//          Tpetra: Templated Linear Algebra Services Package
//
// Copyright 2008 NTESS and the Tpetra contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#ifndef TPETRA_LINEARPROBLEM_DEF_HPP
#define TPETRA_LINEARPROBLEM_DEF_HPP

/// \file Tpetra_LinearProblem_def.hpp
/// \brief Definition of the Tpetra::LinearProblem class
///
/// If you want to use Tpetra::LinearProblem, include
/// "Tpetra_LinearProblem.hpp" (a file which CMake generates and installs
/// for you).  If you only want the declaration of Tpetra::LinearProblem,
/// include "Tpetra_LinearProblem_decl.hpp".

#include "Teuchos_DataAccess.hpp"
#include "Teuchos_TestForException.hpp"
#include "Tpetra_Details_Behavior.hpp"
#include "Tpetra_MultiVector.hpp"
#include "Tpetra_MultiVector_decl.hpp"

namespace Tpetra {

  template <class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  LinearProblem<Scalar, LocalOrdinal, GlobalOrdinal, Node>::
  LinearProblem ()
    : dist_object_type (Teuchos::rcp (new map_type ())),
      Operator_(Teuchos::null),
      A_(Teuchos::null),
      X_(Teuchos::null),
      B_(Teuchos::null)
  {
  }

  template <class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  LinearProblem<Scalar, LocalOrdinal, GlobalOrdinal, Node>::
  LinearProblem (const Teuchos::RCP<row_matrix_type> & A,
                 const Teuchos::RCP<multivector_type>& X,
                 const Teuchos::RCP<multivector_type>& B)
    : dist_object_type (A->getDomainMap()),
      Operator_(Teuchos::null),
      A_(A),
      X_(X),
      B_(B)
  {
    // Try to make matrix an operator
    Operator_ = Teuchos::rcp_dynamic_cast<operator_type>(A_);
  }

  template <class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  LinearProblem<Scalar, LocalOrdinal, GlobalOrdinal, Node>::
  LinearProblem (const Teuchos::RCP<operator_type>   & A,
                 const Teuchos::RCP<multivector_type>& X,
                 const Teuchos::RCP<multivector_type>& B)
    : dist_object_type (*X),
      Operator_(A),
      A_(Teuchos::null),
      X_(X),
      B_(B)
  {
    // Try to make operator a matrix
    A_ = Teuchos::rcp_dynamic_cast<row_matrix_type>(Operator_);
  }

  template <class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  LinearProblem<Scalar, LocalOrdinal, GlobalOrdinal, Node>::
  LinearProblem (const LinearProblem<Scalar, LocalOrdinal, GlobalOrdinal, Node>& Problem)
    : dist_object_type (Problem),
      Operator_(Problem.Operator_),
      A_(Problem.A_),
      X_(Problem.X_),
      B_(Problem.B_)
  {
  }

  template <class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  void LinearProblem<Scalar, LocalOrdinal, GlobalOrdinal, Node>::
  leftScale(const Teuchos::RCP<const vector_type> & D, Teuchos::ETransp mode)
  {
    const Scalar ST0 = Teuchos::ScalarTraits<Scalar>::zero();
    const Scalar ST1 = Teuchos::ScalarTraits<Scalar>::one();
    if (mode == Teuchos::NO_TRANS) {
      A_->leftScale(*D);
      B_->elementWiseMultiply(ST1, *D, *B_, ST0);
    }
    else {
      A_->rightScale(*D);
      vector_type R(*D, Teuchos::DataAccess::Copy);
      R.reciprocal(*D);
      X_->elementWiseMultiply(ST1, R, *X_, ST0);
    }
  
    return;
  }

  template <class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  void LinearProblem<Scalar, LocalOrdinal, GlobalOrdinal, Node>::
  rightScale(const Teuchos::RCP<const vector_type> & D, Teuchos::ETransp mode)
  {
    const Scalar ST0 = Teuchos::ScalarTraits<Scalar>::zero();
    const Scalar ST1 = Teuchos::ScalarTraits<Scalar>::one();
    if (mode == Teuchos::NO_TRANS) {
      A_->rightScale(*D);
      vector_type R(*D, Teuchos::DataAccess::Copy);
      R.reciprocal(*D);
      X_->elementWiseMultiply(ST1, R, *X_, ST0);
    }
    else {
      A_->leftScale(*D);
      B_->elementWiseMultiply(ST1, *D, *B_, ST0);
    }
    return;
  }

  template <class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  int LinearProblem<Scalar, LocalOrdinal, GlobalOrdinal, Node>::
  checkInput(bool fail_on_error) const {

    int error = 0;
    if (fail_on_error) {

      const char tfecfFuncName[] = "checkInput: ";

      TEUCHOS_TEST_FOR_EXCEPTION_CLASS_FUNC(Operator_==Teuchos::null, 
        std::logic_error, "Operator_ is unset.");

      TPETRA_ABUSE_WARNING(A_==Teuchos::null, std::runtime_error, 
        "Linear problem does not have a matrix (A_), just an operator.");
  
      TEUCHOS_TEST_FOR_EXCEPTION_CLASS_FUNC(X_==Teuchos::null, 
        std::logic_error, "Solution vector (X_) is unset.");

      TEUCHOS_TEST_FOR_EXCEPTION_CLASS_FUNC(B_==Teuchos::null, 
        std::logic_error, "RHS vector (B_) is unset.");
  
      TEUCHOS_TEST_FOR_EXCEPTION_CLASS_FUNC(!A_->getRowMap()->isSameAs(*(X_->getMap())),
        std::logic_error, "Domain map of matrix is not the 'same as' the solution map.");

      TEUCHOS_TEST_FOR_EXCEPTION_CLASS_FUNC(!A_->getRowMap()->isSameAs(*(B_->getMap())),
        std::logic_error, "Range map of matrix is not the 'same as' the RHS map.");
    }
    else {
      if (Operator_==Teuchos::null) error = -1;
      if (A_==Teuchos::null) error = 1; // Return warning error because this problem has no matrix (just an operator)
      if (X_==Teuchos::null) error = -2;
      if (B_==Teuchos::null) error = -3;

      if (!A_->getRowMap()->isSameAs(*(X_->getMap()))) error = -4;
      if (!A_->getRowMap()->isSameAs(*(B_->getMap()))) error = -5;
    }

    return error;
  }

  template<class Scalar, class LocalOrdinal, class GlobalOrdinal, class Node>
  bool LinearProblem<Scalar, LocalOrdinal, GlobalOrdinal, Node>::
  checkSizes (const SrcDistObject& sourceObj)
  {
    // Check whether the source object is a LinearProblem.  If not, then
    // we can't even compare sizes.
    typedef LinearProblem<Scalar, LocalOrdinal, GlobalOrdinal, Node> LP;
    const LP* src = dynamic_cast<const LP*> (&sourceObj);
    if (src == nullptr) {
      return false;
    }
    else {
      this->checkInput(false);
      src->checkInput(false);

      return ((this->A_->getDomainMap() == src->getMatrix()->getDomainMap()) and
              (this->A_->getRangeMap() == src->getMatrix()->getRangeMap()));
    }
  }

} // namespace Tpetra

//
// Explicit instantiation macro
//
// Must be expanded from within the Tpetra namespace!
//

#define TPETRA_LINEARPROBLEM_INSTANT(SCALAR,LO,GO,NODE) \
  template class LinearProblem< SCALAR , LO , GO , NODE >;


#endif // TPETRA_LINEARPROBLEM_DEF_HPP
