// @HEADER
// *****************************************************************************
//                           Intrepid2 Package
//
// Copyright 2007 NTESS and the Intrepid2 contributors.
// SPDX-License-Identifier: BSD-3-Clause
// *****************************************************************************
// @HEADER

/** \file   Intrepid2_HGRAD_TET_C2_FEMDef.hpp
    \brief  Definition file for FEM basis functions of degree 2 for H(grad) functions on TET cells
    \author Created by P. Bochev and D. Ridzal.
            Kokkorized by Kyungjoo Kim
*/

#ifndef __INTREPID2_HGRAD_TET_C2_FEM_DEF_HPP__
#define __INTREPID2_HGRAD_TET_C2_FEM_DEF_HPP__

namespace Intrepid2 {

  // -------------------------------------------------------------------------------------

  namespace Impl {                                                                                                                                                       
                                                                                                                                                                         
    template<EOperator opType>                                                                                                                                           
    template<typename OutputViewType,                                                                                                                                    
             typename inputViewType>                                                                                                                                     
    KOKKOS_INLINE_FUNCTION                                                                                                                                               
    void                                                                                                                                                                 
    Basis_HGRAD_TET_C2_FEM::Serial<opType>::                                                                                                                             
    getValues(       OutputViewType output,                                                                                                                              
               const inputViewType input ) {   
      switch (opType) {
      case OPERATOR_VALUE: {
        const auto x = input(0);
        const auto y = input(1);
        const auto z = input(2);
        
        // output is a rank-2 array with dimensions (basisCardinality_, dim0)
        output.access(0) = (-1. + x + y + z)*(-1. + 2.*x + 2.*y + 2.*z);
        output.access(1) = x*(-1. + 2.*x);
        output.access(2) = y*(-1. + 2.*y);
        output.access(3) = z*(-1. + 2.*z);

        output.access(4) = -4.*x*(-1. + x + y + z);
        output.access(5) =  4.*x*y;
        output.access(6) = -4.*y*(-1. + x + y + z);
        output.access(7) = -4.*z*(-1. + x + y + z);
        output.access(8) =  4.*x*z;
        output.access(9) =  4.*y*z;
        break;
      }
      case OPERATOR_D1:
      case OPERATOR_GRAD: {
        const auto x = input(0);
        const auto y = input(1);
        const auto z = input(2);
        
        // output.access is a rank-3 array with dimensions (basisCardinality_, dim0, spaceDim)
        output.access(0, 0) = -3.+ 4.*x + 4.*y + 4.*z;
        output.access(0, 1) = -3.+ 4.*x + 4.*y + 4.*z;
        output.access(0, 2) = -3.+ 4.*x + 4.*y + 4.*z; 
      
        output.access(1, 0) = -1.+ 4.*x; 
        output.access(1, 1) =  0.;
        output.access(1, 2) =  0.;
      
        output.access(2, 0) =  0.;        
        output.access(2, 1) = -1.+ 4.*y;
        output.access(2, 2) =  0.;

        output.access(3, 0) =  0.;         
        output.access(3, 1) =  0.;
        output.access(3, 2) = -1.+ 4.*z;
 
      
        output.access(4, 0) = -4.*(-1.+ 2*x + y + z);         
        output.access(4, 1) = -4.*x;
        output.access(4, 2) = -4.*x;
      
        output.access(5, 0) =  4.*y;       
        output.access(5, 1) =  4.*x; 
        output.access(5, 2) =  0.;

        output.access(6, 0) = -4.*y;          
        output.access(6, 1) = -4.*(-1.+ x + 2*y + z);
        output.access(6, 2) = -4.*y; 

        output.access(7, 0) = -4.*z;          
        output.access(7, 1) = -4.*z;
        output.access(7, 2) = -4.*(-1.+ x + y + 2*z);

        output.access(8, 0) =  4.*z;     
        output.access(8, 1) =  0.;
        output.access(8, 2) =  4.*x;

        output.access(9, 0) =  0.;         
        output.access(9, 1) =  4.*z;
        output.access(9, 2) =  4.*y;
        break;
      }
      case OPERATOR_D2: {
        output.access(0, 0) =  4.;
        output.access(0, 1) =  4.;
        output.access(0, 2) =  4.;
        output.access(0, 3) =  4.;
        output.access(0, 4) =  4.;
        output.access(0, 5) =  4.;
      
        output.access(1, 0) =  4.;
        output.access(1, 1) =  0.;
        output.access(1, 2) =  0.;
        output.access(1, 3) =  0.;
        output.access(1, 4) =  0.;
        output.access(1, 5) =  0.;

        output.access(2, 0) =  0.;
        output.access(2, 1) =  0.;
        output.access(2, 2) =  0.;
        output.access(2, 3) =  4.;
        output.access(2, 4) =  0.;
        output.access(2, 5) =  0.;

        output.access(3, 0) =  0.;
        output.access(3, 1) =  0.;
        output.access(3, 2) =  0.;
        output.access(3, 3) =  0.;
        output.access(3, 4) =  0.;
        output.access(3, 5) =  4.;

        output.access(4, 0) = -8.;
        output.access(4, 1) = -4.;
        output.access(4, 2) = -4.;
        output.access(4, 3) =  0.;
        output.access(4, 4) =  0.;
        output.access(4, 5) =  0.;

        output.access(5, 0) =  0.;
        output.access(5, 1) =  4.;
        output.access(5, 2) =  0.;
        output.access(5, 3) =  0.;
        output.access(5, 4) =  0.;
        output.access(5, 5) =  0.;

        output.access(6, 0) =  0.;
        output.access(6, 1) = -4.;
        output.access(6, 2) =  0.;
        output.access(6, 3) = -8.;
        output.access(6, 4) = -4.;
        output.access(6, 5) =  0;

        output.access(7, 0) =  0.;
        output.access(7, 1) =  0.;
        output.access(7, 2) = -4.;
        output.access(7, 3) =  0.;
        output.access(7, 4) = -4.;
        output.access(7, 5) = -8.;

        output.access(8, 0) =  0.;
        output.access(8, 1) =  0.;
        output.access(8, 2) =  4.;
        output.access(8, 3) =  0.;
        output.access(8, 4) =  0.;
        output.access(8, 5) =  0.;

        output.access(9, 0) =  0.;
        output.access(9, 1) =  0.;
        output.access(9, 2) =  0.;
        output.access(9, 3) =  0.;
        output.access(9, 4) =  4.;
        output.access(9, 5) =  0.;
        break;
      }
      case OPERATOR_MAX: {
        const ordinal_type jend = output.extent(1);
        const ordinal_type iend = output.extent(0);

        for (ordinal_type j=0;j<jend;++j)
          for (ordinal_type i=0;i<iend;++i)
            output.access(i, j) = 0.0;
        break;
      }
      default: {
        INTREPID2_TEST_FOR_ABORT( opType != OPERATOR_VALUE &&
                                  opType != OPERATOR_GRAD &&
                                  opType != OPERATOR_D1 &&
                                  opType != OPERATOR_D2 &&
                                  opType != OPERATOR_MAX,
                                  ">>> ERROR: (Intrepid2::Basis_HGRAD_TET_C2_FEM::Serial::getValues) operator is not supported");
      }
      }
    }

    template<typename DT, 
             typename outputValueValueType, class ...outputValueProperties,
             typename inputPointValueType,  class ...inputPointProperties>
    void
    Basis_HGRAD_TET_C2_FEM::
    getValues( const typename DT::execution_space& space,
                     Kokkos::DynRankView<outputValueValueType,outputValueProperties...> outputValues,
               const Kokkos::DynRankView<inputPointValueType, inputPointProperties...>  inputPoints,
               const EOperator operatorType )  {
      typedef          Kokkos::DynRankView<outputValueValueType,outputValueProperties...>         outputValueViewType;
      typedef          Kokkos::DynRankView<inputPointValueType, inputPointProperties...>          inputPointViewType;
      typedef typename ExecSpace<typename inputPointViewType::execution_space,typename DT::execution_space>::ExecSpaceType ExecSpaceType;

      // Number of evaluation points = dim 0 of inputPoints
      const auto loopSize = inputPoints.extent(0);
      Kokkos::RangePolicy<ExecSpaceType,Kokkos::Schedule<Kokkos::Static> > policy(space, 0, loopSize);

      switch (operatorType) {
    
      case OPERATOR_VALUE: {
        typedef Functor<outputValueViewType,inputPointViewType,OPERATOR_VALUE> FunctorType;
        Kokkos::parallel_for( policy, FunctorType(outputValues, inputPoints) );
        break;
      } 
      case OPERATOR_GRAD:
      case OPERATOR_D1: {
        typedef Functor<outputValueViewType,inputPointViewType,OPERATOR_GRAD> FunctorType;
        Kokkos::parallel_for( policy, FunctorType(outputValues, inputPoints) );
        break;
      } 
      case OPERATOR_CURL: {
        INTREPID2_TEST_FOR_EXCEPTION( (operatorType == OPERATOR_CURL), std::invalid_argument,
                                      ">>> ERROR (Basis_HGRAD_TET_C2_FEM): CURL is invalid operator for rank-0 (scalar) functions in 3D");
        break;
      } 
      case OPERATOR_DIV: {
        INTREPID2_TEST_FOR_EXCEPTION( (operatorType == OPERATOR_DIV), std::invalid_argument,
                                      ">>> ERROR (Basis_HGRAD_TET_C2_FEM): DIV is invalid operator for rank-0 (scalar) functions in 3D");
        break;
      } 
      case OPERATOR_D2: {
        typedef Functor<outputValueViewType,inputPointViewType,OPERATOR_D2> FunctorType;
        Kokkos::parallel_for( policy, FunctorType(outputValues, inputPoints) );
        break;
      } 
      case OPERATOR_D3:
      case OPERATOR_D4:
      case OPERATOR_D5:
      case OPERATOR_D6:
      case OPERATOR_D7:
      case OPERATOR_D8:
      case OPERATOR_D9:
      case OPERATOR_D10: {
        typedef Functor<outputValueViewType,inputPointViewType,OPERATOR_MAX> FunctorType;
        Kokkos::parallel_for( policy, FunctorType(outputValues, inputPoints) );
        break;
      }
      default: {
        INTREPID2_TEST_FOR_EXCEPTION( !( Intrepid2::isValidOperator(operatorType) ), std::invalid_argument,
                                      ">>> ERROR (Basis_HGRAD_TET_C2_FEM): Invalid operator type");
      }
      }
    }
  }
  // -------------------------------------------------------------------------------------

  template<typename DT, typename OT, typename PT>
  Basis_HGRAD_TET_C2_FEM<DT,OT,PT>::
  Basis_HGRAD_TET_C2_FEM() {
    const ordinal_type spaceDim = 3;
    this->basisCardinality_     = 10;
    this->basisDegree_          = 2;    
    this->basisCellTopologyKey_ = shards::Tetrahedron<4>::key;
    this->basisType_            = BASIS_FEM_DEFAULT;
    this->basisCoordinates_     = COORDINATES_CARTESIAN;
    this->functionSpace_        = FUNCTION_SPACE_HGRAD;

    // intialize tags
    {
      // Basis-dependent intializations
      const ordinal_type tagSize  = 4;        // size of DoF tag
      const ordinal_type posScDim = 0;        // position in the tag, counting from 0, of the subcell dim 
      const ordinal_type posScOrd = 1;        // position in the tag, counting from 0, of the subcell ordinal
      const ordinal_type posDfOrd = 2;        // position in the tag, counting from 0, of DoF ordinal relative to the subcell
  
      // An array with local DoF tags assigned to basis functions, in the order of their local enumeration 
      ordinal_type tags[40]  = { 0, 0, 0, 1,
                                 0, 1, 0, 1,
                                 0, 2, 0, 1,
                                 0, 3, 0, 1,
                                 1, 0, 0, 1,
                                 1, 1, 0, 1,
                                 1, 2, 0, 1,
                                 1, 3, 0, 1,
                                 1, 4, 0, 1,
                                 1, 5, 0, 1,
      };

      // host tags
      OrdinalTypeArray1DHost tagView(&tags[0], 40);
    
      // Basis-independent function sets tag and enum data in tagToOrdinal_ and ordinalToTag_ arrays:
      this->setOrdinalTagData(this->tagToOrdinal_,
                              this->ordinalToTag_,
                              tagView,
                              this->basisCardinality_,
                              tagSize,
                              posScDim,
                              posScOrd,
                              posDfOrd);
    }

    // dofCoords on host and create its mirror view to device
    Kokkos::DynRankView<typename ScalarViewType::value_type,typename DT::execution_space::array_layout,Kokkos::HostSpace>
      dofCoords("dofCoordsHost", this->basisCardinality_,spaceDim);

    dofCoords(0,0) = 0.0;   dofCoords(0,1) = 0.0; dofCoords(0,2) = 0.0;
    dofCoords(1,0) = 1.0;   dofCoords(1,1) = 0.0; dofCoords(1,2) = 0.0;
    dofCoords(2,0) = 0.0;   dofCoords(2,1) = 1.0; dofCoords(2,2) = 0.0;
    dofCoords(3,0) = 0.0;   dofCoords(3,1) = 0.0; dofCoords(3,2) = 1.0;

    dofCoords(4,0) = 0.5;   dofCoords(4,1) = 0.0; dofCoords(4,2) = 0.0;
    dofCoords(5,0) = 0.5;   dofCoords(5,1) = 0.5; dofCoords(5,2) = 0.0;
    dofCoords(6,0) = 0.0;   dofCoords(6,1) = 0.5; dofCoords(6,2) = 0.0;
    dofCoords(7,0) = 0.0;   dofCoords(7,1) = 0.0; dofCoords(7,2) = 0.5;
    dofCoords(8,0) = 0.5;   dofCoords(8,1) = 0.0; dofCoords(8,2) = 0.5;
    dofCoords(9,0) = 0.0;   dofCoords(9,1) = 0.5; dofCoords(9,2) = 0.5;

    this->dofCoords_ = Kokkos::create_mirror_view(typename DT::memory_space(), dofCoords);
    Kokkos::deep_copy(this->dofCoords_, dofCoords);
  }

  template<typename DT, typename OT, typename PT>
  void 
  Basis_HGRAD_TET_C2_FEM<DT,OT,PT>::getScratchSpaceSize(       
                                    ordinal_type& perTeamSpaceSize,
                                    ordinal_type& perThreadSpaceSize,
                              const PointViewType inputPoints,
                              const EOperator operatorType) const {
    perTeamSpaceSize = 0;
    perThreadSpaceSize = 0;
  }

  template<typename DT, typename OT, typename PT>
  KOKKOS_INLINE_FUNCTION
  void 
  Basis_HGRAD_TET_C2_FEM<DT,OT,PT>::getValues(       
          OutputViewType outputValues,
      const PointViewType  inputPoints,
      const EOperator operatorType,
      const typename Kokkos::TeamPolicy<typename DT::execution_space>::member_type& team_member,
      const typename DT::execution_space::scratch_memory_space & scratchStorage, 
      const ordinal_type subcellDim,
      const ordinal_type subcellOrdinal) const {

      INTREPID2_TEST_FOR_ABORT( !((subcellDim <= 0) && (subcellOrdinal == -1)),
        ">>> ERROR: (Intrepid2::Basis_HGRAD_TET_C2_FEM::getValues), The capability of selecting subsets of basis functions has not been implemented yet.");

      (void) scratchStorage; //avoid unused variable warning

      const int numPoints = inputPoints.extent(0);

      switch(operatorType) {
        case OPERATOR_VALUE:
          Kokkos::parallel_for (Kokkos::TeamThreadRange (team_member, numPoints), [=] (ordinal_type& pt) {
            auto       output = Kokkos::subview( outputValues, Kokkos::ALL(), pt, Kokkos::ALL() );
            const auto input  = Kokkos::subview( inputPoints,                 pt, Kokkos::ALL() );
            Impl::Basis_HGRAD_TET_C2_FEM::Serial<OPERATOR_VALUE>::getValues( output, input);
          });
          break;
        case OPERATOR_GRAD:
          Kokkos::parallel_for (Kokkos::TeamThreadRange (team_member, numPoints), [=] (ordinal_type& pt) {
            auto       output = Kokkos::subview( outputValues, Kokkos::ALL(), pt, Kokkos::ALL() );
            const auto input  = Kokkos::subview( inputPoints,                 pt, Kokkos::ALL() );
            Impl::Basis_HGRAD_TET_C2_FEM::Serial<OPERATOR_GRAD>::getValues( output, input);
          });
          break;
        default: {}
    }
  }
  
}// namespace Intrepid2
#endif
