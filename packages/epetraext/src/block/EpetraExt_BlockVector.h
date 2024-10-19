//@HEADER
// ***********************************************************************
//
//     EpetraExt: Epetra Extended - Linear Algebra Services Package
//                 Copyright (2011) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Michael A. Heroux (maherou@sandia.gov)
//
// ***********************************************************************
//@HEADER

#ifndef EPETRAEXT_BLOCKVECTOR_H
#define EPETRAEXT_BLOCKVECTOR_H

#if defined(EpetraExt_SHOW_DEPRECATED_WARNINGS)
#ifdef __GNUC__
#warning "The EpetraExt package is deprecated"
#endif
#endif

#include "Epetra_ConfigDefs.h"
#include "Epetra_Vector.h" 
#include "Teuchos_RCP.hpp"
#include <vector>

//! EpetraExt::BlockVector: A class for constructing a distributed block vector

/*! The EpetraExt::BlockVector allows construction of a block vector made up of Epetra_Vector blocks as well as access to the full systems as a Epetra_Vector.  It derives from and extends the Epetra_Vector class

<b>Constructing EpetraExt::BlockVector objects</b>

*/    

namespace EpetraExt {

class BlockVector: public Epetra_Vector {
 public:

  //@{ \name Constructors/Destructor.
  //! BlockVector constuctor with one block row per processor.
  /*! Creates a BlockVector object and allocates storage.  
    
	\param In
	BaseMap - Map determining local structure, can be distrib. over subset of proc.'s
	\param In 
	GlobalMap - Full map describing the overall global structure, generally generated by the construction of a BlockCrsMatrix object
	\param In 
	NumBlocks - Number of local blocks
  */
  BlockVector( const Epetra_BlockMap & BaseMap, const Epetra_BlockMap & GlobalMap);

  /*! Creates a BlockVector object from an existing Epetra_Vector.  
    
	\param In 
        Epetra_DataAccess - Enumerated type set to Copy or View.
        \param In
	BaseMap - Map determining local structure, can be distrib. over subset of proc.'s
	\param In 
	BlockVec - Source Epetra vector whose map must be the full map for the block vector
  */
  BlockVector(Epetra_DataAccess CV, const Epetra_BlockMap & BaseMap, 
	      const Epetra_Vector & BlockVec);
  
  //! Copy constructor.
  BlockVector( const BlockVector & MV );

  //! Destructor
  virtual ~BlockVector();
  //@}
  
  //! Extract a single block from a Block Vector: block row is global, not a stencil value
  int ExtractBlockValues( Epetra_Vector & BaseVec, long long BlockRow) const;

  //! Load a single block into a Block Vector: block row is global, not a stencil value
  int LoadBlockValues(const Epetra_Vector & BaseVec, long long BlockRow);

#ifndef EPETRA_NO_32BIT_GLOBAL_INDICES
  //! Load entries into BlockVector with base vector indices offset by BlockRow
  int BlockSumIntoGlobalValues(int NumIndices, double* Values,
                               int* Indices, int BlockRow);
  //! Load entries into BlockVector with base vector indices offset by BlockRow
  int BlockReplaceGlobalValues(int NumIndices, double* Values,
                               int* Indices, int BlockRow);
#endif

#ifndef EPETRA_NO_64BIT_GLOBAL_INDICES
  //! Load entries into BlockVector with base vector indices offset by BlockRow
  int BlockSumIntoGlobalValues(int NumIndices, double* Values,
                               long long* Indices, long long BlockRow);
  //! Load entries into BlockVector with base vector indices offset by BlockRow
  int BlockReplaceGlobalValues(int NumIndices, double* Values,
                               long long* Indices, long long BlockRow);
#endif

  //! Return Epetra_Vector for given block row
  Teuchos::RCP<const Epetra_Vector> GetBlock(long long BlockRow) const;

  //! Return Epetra_Vector for given block row
  Teuchos::RCP<Epetra_Vector> GetBlock(long long BlockRow);

  //! Return base map
  const Epetra_BlockMap& GetBaseMap() const;
	
 protected:

  Epetra_BlockMap BaseMap_;

  long long Offset_;

};

} //namespace EpetraExt

#endif /* EPETRAEXT_BLOCKVECTOR_H */
