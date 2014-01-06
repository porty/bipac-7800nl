/******************************************************************************
 *
 *  Copyright (c) 2009  Broadcom Corporation
 *  All Rights Reserved
 *
# 
# 
# This program is the proprietary software of Broadcom Corporation and/or its 
# licensors, and may only be used, duplicated, modified or distributed pursuant 
# to the terms and conditions of a separate, written license agreement executed 
# between you and Broadcom (an "Authorized License").  Except as set forth in 
# an Authorized License, Broadcom grants no license (express or implied), right 
# to use, or waiver of any kind with respect to the Software, and Broadcom 
# expressly reserves all rights in and to the Software and all intellectual 
# property rights therein.  IF YOU HAVE NO AUTHORIZED LICENSE, THEN YOU HAVE 
# NO RIGHT TO USE THIS SOFTWARE IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY 
# BROADCOM AND DISCONTINUE ALL USE OF THE SOFTWARE. 
# 
# Except as expressly set forth in the Authorized License, 
# 
# 1. This program, including its structure, sequence and organization, 
#    constitutes the valuable trade secrets of Broadcom, and you shall use 
#    all reasonable efforts to protect the confidentiality thereof, and to 
#    use this information only in connection with your use of Broadcom 
#    integrated circuit products. 
# 
# 2. TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS" 
#    AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES, REPRESENTATIONS OR 
#    WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH 
#    RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY DISCLAIMS ANY AND 
#    ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, 
#    FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR 
#    COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE 
#    TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING OUT OF USE OR 
#    PERFORMANCE OF THE SOFTWARE. 
# 
# 3. TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL BROADCOM OR 
#    ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL, INCIDENTAL, SPECIAL, 
#    INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER ARISING OUT OF OR IN ANY 
#    WAY RELATING TO YOUR USE OF OR INABILITY TO USE THE SOFTWARE EVEN 
#    IF BROADCOM HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES; 
#    OR (ii) ANY AMOUNT IN EXCESS OF THE AMOUNT ACTUALLY PAID FOR THE 
#    SOFTWARE ITSELF OR U.S. $1, WHICHEVER IS GREATER. THESE LIMITATIONS 
#    SHALL APPLY NOTWITHSTANDING ANY FAILURE OF ESSENTIAL PURPOSE OF ANY 
#    LIMITED REMEDY. 
#
 *
 ************************************************************************/
#ifndef _MOCALIB_CLI_H_
#define _MOCALIB_CLI_H_

#include "devctl_moca.h"

#ifdef __cplusplus
extern "C" {
#endif


/* Limit values */
#define CMD_NAME_LEN                        64
#define MAX_OPTS                            64
#define MAX_SUB_CMDS                        64
#define MAX_PARMS                           64
#define MAX_IFNAME_INPUTS                   16

/* Argument type values. */
#define ARG_TYPE_COMMAND                    1
#define ARG_TYPE_OPTION                     2
#define ARG_TYPE_PARAMETER                  3

#define MOCA_LIST_PQOS_NONE                 0
#define MOCA_LIST_PQOS_SINGLE               1
#define MOCA_LIST_PQOS_ALL                  2

#define MOCA_LAB_SNR_PRINTS                 (1 << 0)
#define MOCA_LAB_CIR_PRINTS                 (1 << 1)

#define MOCA_CONST_TX_OPTION_NONE           0
#define MOCA_CONST_TX_OPTION_TONE           1
#define MOCA_CONST_TX_OPTION_NO_POWER       2

/** More Typedefs. **/

typedef struct
{
   char *pszOptName;
   char *pszParms[MAX_PARMS];
   int nNumParms;
} OPTION_INFO, *POPTION_INFO;

typedef int (*FN_COMMAND_HANDLER) (POPTION_INFO pOptions, int nNumOptions);

typedef struct
{
   char szCmdName[CMD_NAME_LEN];
   char *pszOptionNames[MAX_OPTS];
   FN_COMMAND_HANDLER pfnCmdHandler;
} COMMAND_INFO, *PCOMMAND_INFO;


/** Parses a moca cli argument type.
 *
 * This function parses "moca" CLI commands returns the argument type of
 * the supplied string.
 *
 * @param pszArg (IN) String pointer to the command line arguments.
 * @param pCmds (IN) Pointer to (global) array of moca commands.
 * @param ppszOptions (IN) Pointer to string array of options.
 * @return One of: ARG_TYPE_COMMAND, ARG_TYPE_OPTION, ARG_TYPE_PARAMETER.
 */
int mocacli_get_arg_type( char *pszArg, PCOMMAND_INFO pCmds, char **ppszOptions );


/** Parses a moca cli command string.
 *
 * This function parses "moca" CLI string and returns the command that 
 * matches from the pCmds array.
 *
 * @param pszArg (IN) String pointer to the command line arguments.
 * @param pCmds (IN) Pointer to (global) array of moca commands.
 * @return Pointer to PCOMMAND_INFO entry from pCmds matching supplied 
 * string.
 */
PCOMMAND_INFO mocacli_get_command( char *pszArg, PCOMMAND_INFO pCmds );

/** Processes a moca cli command.
 *
 * Gets the options and option paramters for a command and
 * calls the command handler function to process the command.
 *
 * @param pszPgmName (IN) string pointer to applciation name used for error 
 * prints
 * @param pCmd (IN) Pointer to the command info.
 * @param argc (IN) Number of command line arguments
 * @param argv (IN) String array of command line arguments
 * @param pCmds (IN) Pointer to global array of CLI commands
 * @param pnArgNext (OUT) Argument count of next argument following this 
 *    command's completion
 * @return 0 - success, non-0 - error
 */
int mocacli_process_command( char * pszPgmName, PCOMMAND_INFO pCmd, int argc, 
	char **argv, PCOMMAND_INFO pCmds, int *pnArgNext );


/** Parses moca initialization parmaters from cli input
 *
 * Parses the pOptions array and populates the pParms structure,
 * pu32Mask, and plocal structure based on the input.
 *
 * @param pszPgmName (IN) string pointer to applciation name used for error 
 * prints
 * @param pOptions (IN) Pointer to the CLI options.
 * @param nNumOptions (IN) Number of command line options
 * @param pParms (OUT) MoCA initialization parameters as parsed from 
 * CLI string
 * @param pu32Mask (OUT) Bit mask of init parameters set by CLI string
 * @param plocal (OUT) Extra information parsed from CLI string to be used
 * locally by the CLI application
 * @return 0 - success, non-0 - error
 */
int mocacli_parse_init_parms (char * pszPgmName, POPTION_INFO pOptions, 
	int nNumOptions, PMoCA_INITIALIZATION_PARMS pParms, uint64_t *pu32Mask);


/** Parses moca configuration parmaters from cli input
 *
 * Parses the pOptions array and populates the pConfigParms structure,
 * and pConfigMask based on the input.
 *
 * @param pszPgmName (IN) string pointer to applciation name used for error 
 * prints
 * @param pOptions (IN) Pointer to the CLI options.
 * @param nNumOptions (IN) Number of command line options
 * @param pConfigParms (OUT) MoCA configuration parameters as parsed from 
 * CLI string
 * @param pConfigMask (OUT) Bit mask of init parameters set by CLI string
 * @return 0 - success, non-0 - error
 */
int mocacli_parse_config_parms ( char * pszPgmName, POPTION_INFO pOptions, 
	int nNumOptions, MoCA_CONFIG_PARAMS * pConfigParms, 
	unsigned long long * pConfigMask, MoCA_CONFIG_PARAMS * pCurrParms );


/** Parses moca trace configuration parmaters from cli input
 *
 * Parses the pOptions array and populates the pTraceParmas structure,
 * based on the input.
 *
 * @param pszPgmName (IN) string pointer to applciation name used for error 
 * prints
 * @param pOptions (IN) Pointer to the CLI options.
 * @param nNumOptions (IN) Number of command line options
 * @param pTraceParms (OUT) MoCA trace parameters as parsed from 
 * CLI string
 * @return 0 - success, non-0 - error
 */
int mocacli_parse_trace_parms ( 
	char * pszPgmName, 
	POPTION_INFO pOptions, 
	int nNumOptions,
	MoCA_TRACE_PARAMS * pTraceParams );



/** Convert init string parameters to structure.
 *
 * Takes the 'initString' variable which holds the parameters to 
 * the CLI command "mocactl start" or "mocactl restart" and converts
 * it into the MoCA_INITIALIZATION_PARMS structure.
 *
 * @param initString (IN) pointer to init param string
 * @param pInitParms (OUT) Pointer to init param structure
 * @param mask (OUT) Pointer to bit mask of fields set in string 
 *
 * @return none
 */
void mocacli_convert_init_string(
	char * initString, 
	PMoCA_INITIALIZATION_PARMS pInitParms, 
	unsigned long long * mask);


/** Convert config string parameters to structure.
 *
 * Takes the 'cfgString' variable which holds the parameters to 
 * the CLI command "mocactl config" and converts it into the 
 * MoCA_CONFIG_PARAMS structure.
 *
 * @param cfgString (IN) pointer to config param string
 * @param pCfgParms (OUT) Pointer to config param structure
 * @param mask (OUT) Pointer to bit mask of fields set in string 
 *
 * @return none
 */
void mocacli_convert_cfg_string(
	char * cfgString, 
	PMoCA_CONFIG_PARAMS pCfgParms, 
	unsigned long long * mask);


/** Convert trace string parameters to structure.
 *
 * Takes the 'traceString' variable which holds the parameters to 
 * the CLI command "mocactl trace" and converts it into the 
 * MoCA_TRACE_PARAMS structure.
 *
 * @param traceString (IN) pointer to trace param string
 * @param pTraceParms (OUT) Pointer to trace param structure
 *
 * @return none
 */
void mocacli_convert_trace_string(
	char * traceString, 
	PMoCA_TRACE_PARAMS pTraceParms );


/** Print moca initialization parmaters
 *
 * Prints MoCA initialization parameters stored in pInitParms structure in
 * a clean way.
 *
 * @param pInitParms (IN) pointer to MoCA initialization parameters
 * @return None.
 */
void mocacli_print_init_parms ( MoCA_INITIALIZATION_PARMS * pInitParms );


/** Print moca bit loading data
 *
 * Prints MoCA bit loading data stored in pBitLoading and pSecBitLoading
 *
 * @param pBitLoading (IN) pointer to first bit loading data array
 * @param pSecBitLoading (IN) pointer to second bit loading data array
 * @return None.
 */
void mocacli_display_bit_loading (UINT32 *pBitLoading, UINT32 *pSecBitLoading);


/** Print moca node status
 *
 * Prints MoCA node status data stored in pNodeStatus and bitLoading
 *
 * @param pNodeStatus (IN) pointer to node status data
 * @param bitLoading (IN) flag indicating whether to print bit loading data 
 * or not
 * @return None.
 */
void mocacli_display_node_status (PMoCA_NODE_STATUS_ENTRY pNodeStatus, int bitLoading);


/** Print moca node stats
 *
 * Prints MoCA node stats data stored in pNodeStats
 *
 * @param pNodeStats (IN) pointer to node stats data
 * @return None.
 */
void mocacli_display_node_stats (PMoCA_NODE_STATISTICS_ENTRY pNodeStats);


/** Print extended moca node stats
 *
 * Prints extended MoCA node stats data stored in pNodeStats
 *
 * @param pNodeStats (IN) pointer to extended node stats data
 * @return None.
 */
void mocacli_display_node_stats_ext (PMoCA_NODE_STATISTICS_EXT_ENTRY pNodeStats);


/** Print moca configuration
 *
 * Prints MoCA configuration data stored in pCfg
 *
 * @param pCfg (IN) pointer to config data
 * @param showAbsSnrTable (IN) flag indicating whether or not to print
 *                             absolute value SNR table
 * @param rftype (IN) MoCA RF type, from init params, used to print 
 *                    out midrf/hirf specific information
 * @return None.
 */
void mocacli_print_config( MoCA_CONFIG_PARAMS * pCfg, UINT32 showAbsSnrTable, UINT32 rftype );


/** Print moca trace configuration
 *
 * Prints MoCA trace configuration data stored in pTraceCfg
 *
 * @param pCfg (IN) pointer to trace config data
 * @return None.
 */
void mocacli_print_trace_config( MoCA_TRACE_PARAMS * pTraceCfg );

int ParseMacAddress ( char * macAddrString, MAC_ADDRESS * pMacAddr );


#ifdef __cplusplus
}
#endif

#endif
