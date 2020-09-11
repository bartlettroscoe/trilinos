################################################################################
#
# Set env vars for a selected custom configuration
#
# Called as:
#
#   soruce set_custom_system_info_vars.sh <atdm_custom_config_dir>
#
# and on output sets the env var:
#
#   ATDM_CONFIG_REAL_HOSTNAME
#   ATDM_CONFIG_CDASH_HOSTNAME
#   ATDM_CONFIG_SYSTEM_NAME
#   ATDM_CONFIG_SYSTEM_DIR
#   ATDM_CONFIG_CUSTOM_SYSTEM_DIR
#
################################################################################

# Get input arguments
atdm_custom_config_dir_arg=$1

custom_system_name=$(basename ${ATDM_CUSTOM_CONFIG_DIR})

echo "Selecting custom system configuration '${custom_system_name_arg}'"
export ATDM_CONFIG_REAL_HOSTNAME=`hostname`
export ATDM_CONFIG_CDASH_HOSTNAME=$ATDM_CONFIG_REAL_HOSTNAME
export ATDM_CONFIG_SYSTEM_NAME=$custom_system_name
export ATDM_CONFIG_SYSTEM_DIR=$(readlink -f ${atdm_custom_config_dir_arg})
export ATDM_CONFIG_CUSTOM_CONFIG_DIR=${ATDM_CONFIG_SYSTEM_DIR}
