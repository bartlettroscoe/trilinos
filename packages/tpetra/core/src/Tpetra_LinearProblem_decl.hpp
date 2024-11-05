// @HEADER
// *****************************************************************************
//          Tpetra: Templated Linear Algebra Services Package
//
// Copyright 2008 NTESS and the Tpetra contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

#ifndef TPETRA_LINEARPROBLEM_DECL_HPP
#define TPETRA_LINEARPROBLEM_DECL_HPP

/// \file Tpetra_LinearProblem_decl.hpp
/// \brief Declaration of the Tpetra::LinearProblem class

#include "Teuchos_DataAccess.hpp"

#include "Tpetra_Vector_decl.hpp"
#include "Tpetra_MultiVector_decl.hpp"
#include "Tpetra_RowMatrix_decl.hpp"
#include "Tpetra_DistObject.hpp"
#include "Tpetra_Details_ExecutionSpacesUser.hpp"

namespace Tpetra {

  /// \class LinearProblem
  /// \brief Class that encapulates linear problem (Ax = b).
  ///
  /// The LinearProblem class is a wrapper that encapsulates the
  /// general information needed for solving a linear system of
  /// equations.  Currently it accepts a Tpetra matrix/operator,
  /// initial guess and RHS and returns the solution. 
  ///
  /// \tparam Scalar The type of the numerical entries of the matrix.
  ///   (You can use real-valued or complex-valued types here.)
  /// \tparam LocalOrdinal The type of local indices.  See the
  ///   documentation of Map for requirements.
  /// \tparam GlobalOrdinal The type of global indices.  See the
  ///   documentation of Map for requirements.
  /// \tparam Node The Kokkos Node type.  See the documentation
  ///   of Map for requirements.

  template <class Scalar,
            class LocalOrdinal,
            class GlobalOrdinal,
            class Node>
  class LinearProblem :
    public DistObject<Scalar, LocalOrdinal, GlobalOrdinal, Node>,
    public Details::Spaces::User
  {

  private:
    /// Type of the DistObject specialization from which this class inherits.
    using dist_object_type = DistObject<Scalar, LocalOrdinal, GlobalOrdinal, Node>;

  public:
    //! @name Typedefs
    //@{

    using map_type = Map<LocalOrdinal, GlobalOrdinal, Node>;
    using row_matrix_type = RowMatrix<Scalar, LocalOrdinal, GlobalOrdinal, Node>;
    using multivector_type = MultiVector<Scalar, LocalOrdinal, GlobalOrdinal, Node>;
    using vector_type = Vector<Scalar, LocalOrdinal, GlobalOrdinal, Node>;
    using operator_type = Operator<Scalar, LocalOrdinal, GlobalOrdinal, Node>;
    using linear_problem_type = LinearProblem<Scalar, LocalOrdinal, GlobalOrdinal, Node>;

    //@}

    //! @name Constructors/Destructor
    //@{

    /// \brief Default Constructor.
    ///
	  /// Creates an empty LinearProblem instance. The operator
	  /// A, left-hand-side X and right-hand-side B must be set
	  /// use the setOperator(), SetLHS() and SetRHS() methods
	  /// respectively.
    LinearProblem();

    /// \brief Constructor with a matrix as the operator.
    ///
    /// Creates a LinearProblem instance where the operator
	  /// is passed in as a matrix.
    LinearProblem(const Teuchos::RCP<row_matrix_type> & A,
                  const Teuchos::RCP<multivector_type>& X,
                  const Teuchos::RCP<multivector_type>& B);

    /// \brief Constructor with Operator.
    ///
    /// Creates a LinearProblem instance for the case where
	  /// an operator is not necessarily a matrix.
    LinearProblem(const Teuchos::RCP<operator_type>   & A,
                  const Teuchos::RCP<multivector_type>& X,
                  const Teuchos::RCP<multivector_type>& B);

    //! Copy Constructor.
    LinearProblem(const LinearProblem<Scalar, LocalOrdinal,
                             GlobalOrdinal, Node>& Problem);

    //! LinearProblem Destructor.
    virtual ~LinearProblem() = default;

    //@}

    //! @name Integrity check method
    //@{

    /// \brief Check input parameters for existence and size consistency.
    ///
    /// Returns 0 if all input parameters are valid.  Returns +1
	  /// if operator is not a matrix.  This is not necessarily
	  /// an error, but no scaling can be done if the user passes
    /// in an operator that is not an matrix.
    int checkInput(bool fail_on_error = true) const;

    //@}

    //! @name Implementation of DistObject interface
    //@{

    virtual bool
    checkSizes (const SrcDistObject& source) override;

    //@}


    //! @name Set methods
    //@{

    /// \brief Set Operator A of linear problem AX = B using a RowMatrix.
    ///
    /// Sets an RCP to a RowMatrix.  No copy of the operator is made.
    void setOperator(Teuchos::RCP<row_matrix_type> A)
      { A_ = A; Operator_ = A; }

    /// \brief Set Operator A of linear problem AX = B using an Operator.
    ///
    /// Sets an RCP to an Operator.  No copy of the operator is made.
    void setOperator(Teuchos::RCP<operator_type> A)
      { A_ = Teuchos::rcp_dynamic_cast<row_matrix_type>(A); Operator_ = A; }

    /// \brief Set left-hand-side X of linear problem AX = B.
    ///
    /// Sets an RCP to a MultiVector.  No copy of the object is made.
    void setLHS(Teuchos::RCP<multivector_type> X) {X_ = X;}

    /// \brief Set right-hand-side B of linear problem AX = B.
    ///
    /// Sets an RCP to a MultiVector.  No copy of the object is made.
    void setRHS(Teuchos::RCP<multivector_type> B) {B_ = B;}

    //@}

    //! @name Computational methods
    //@{

    /// \brief Perform left scaling of a linear problem.
    ///
    /// Applies the scaling vector D to the left side of the
	  /// matrix A() and to the right hand side B().  Note that
	  /// the operator must be a RowMatrix, not just an Operator.
    ///
    /// \param In
    ///      D - Vector containing scaling values.  D[i] will
    ///          be applied to the ith row of A() and B().
    ///   mode - Indicating if transposed.
    /// \return Integer error code, set to 0 if successful. 
    ///         Return -1 if operator is not a matrix.
    void leftScale(const Teuchos::RCP<const vector_type> & D,
                   Teuchos::ETransp mode = Teuchos::NO_TRANS);

    /// \brief Perform right scaling of a linear problem.
    ///
	  /// Applies the scaling vector D to the right side of the
	  /// matrix A().  Apply the inverse of D to the initial
	  /// guess.  Note that the operator must be a RowMatrix,
	  /// not just an Operator.
    /// 
    /// \param In
    ///      D - Vector containing scaling values.  D[i] will
    ///          be applied to the ith row of A().  1/D[i] will
    ///          be applied to the ith row of B().
    ///   mode - Indicating if transposed.
    /// \return Integer error code, set to 0 if successful.
    ///         Return -1 if operator is not a matrix.
    void rightScale(const Teuchos::RCP<const vector_type> & D,
                    Teuchos::ETransp mode = Teuchos::NO_TRANS);

    //@}

    //! @name Accessor methods
    //@{

    //! Get an RCP to the operator A.
    Teuchos::RCP<operator_type> getOperator() const {return(Operator_);};
    //! Get an RCP to the matrix A.
    Teuchos::RCP<row_matrix_type> getMatrix() const {return(A_);};
    //! Get an RCP to the left-hand-side X.
    Teuchos::RCP<multivector_type> getLHS() const {return(X_);};
    //! Get an RCP to the right-hand-side B.
    Teuchos::RCP<multivector_type> getRHS() const {return(B_);};

    //@}

 private:

  Teuchos::RCP<operator_type> Operator_;
  Teuchos::RCP<row_matrix_type> A_;
  Teuchos::RCP<multivector_type> X_;
  Teuchos::RCP<multivector_type> B_;

  LinearProblem & operator=(const LinearProblem<Scalar, LocalOrdinal,
                                       GlobalOrdinal, Node>& Problem) = default;
};

} // namespace Tpetra

#endif // TPETRA_LINEARPROBLEM_DECL_HPP
