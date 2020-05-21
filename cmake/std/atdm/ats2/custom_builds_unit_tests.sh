#!/bin/bash

CURRENT_SCRIPTS_DIR=`echo $BASH_SOURCE | sed "s/\(.*\)\/.*\.sh/\1/g"`
ATDM_CONFIG_SCRIPT_DIR=`readlink -f ${CURRENT_SCRIPTS_DIR}/..`
ATDM_CONFIG_SYSTEM_DIR=${ATDM_CONFIG_SCRIPT_DIR}/ats2

#
# Test compiler parsing
#

testAll() {

  ATDM_CONFIG_BUILD_NAME=default
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243-xl-2019.08.20-spmpi-rolling_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243_xl-2019.08.20-spmpi-rolling_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243-xl-2019.08.20_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243_xl-2019.08.20_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243-xl-2019_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243_xl-2019_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-xl_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_xl-2019.08.20-spmpi-rolling_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_xl-2019.08.20_spmpi-rolling_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_xl-2019.08.20_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_xl-2019_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_xl_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=xl
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} XL-2019.08.20_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243-gnu-7.3.1-spmpi-rolling_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243_gnu-7.3.1_spmpi-rolling_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243-gnu-7.3.1_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243_gnu-7.3.1_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243-gnu-7_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243_gnu-7_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10.1.243_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda-10_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_cuda_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} CUDA-10.1.243_GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_gnu-7.3.1-spmpi-rolling_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_gnu-7.3.1_spmpi-rolling_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_gnu-7.3.1_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_gnu-7_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  ATDM_CONFIG_BUILD_NAME=before_gnu_after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} GNU-7.3.1_SPMPI-rolling ${ATDM_CONFIG_COMPILER}

  # This should not match anything and should be an error!
  ATDM_CONFIG_BUILD_NAME=anything-cudas-after
  . ${ATDM_CONFIG_SCRIPT_DIR}/utils/set_build_options.sh
  ${_ASSERT_EQUALS_} DEFAULT ${ATDM_CONFIG_COMPILER}

}


#
# Run the unit tests
#

. ${ATDM_CONFIG_SCRIPT_DIR}/test/shunit2/shunit2
