/***********************************************************************
 *
 *  Copyright (c) 2006-2007  Broadcom Corporation
 *  All Rights Reserved
 *
<:license-public
 *
 ************************************************************************/

#ifndef __CMS_SECLOG_H__
#define __CMS_SECLOG_H__

/*!\enum CmsSecurityLogIDs
 * \brief Security Log identifiers.
 * 
 */
typedef enum
{
   LOG_SECURITY_CUSTOM         = 0, /**< Used for custom strings, blank default text */
   LOG_SECURITY_PASSWD_CHANGED = 1, /**< One of the passwords has been changed. */
   LOG_SECURITY_AUTH_LOGIN_PASS,    /**< An authorized user successfully logged in. */
   LOG_SECURITY_AUTH_LOGIN_FAIL,    /**< An authorized user failed login. */
   LOG_SECURITY_AUTH_LOGOUT,        /**< An authorized user has logged out. */
   LOG_SECURITY_LOCKOUT_END,        /**< Security lockout removed. */
   LOG_SECURITY_AUTH_RESOURCES,     /**< Authorized attempt to access resources. */
   LOG_SECURITY_UNAUTH_RESOURCES,   /**< Unauthorized attempt to access resources. */
   LOG_SECURITY_SOFTWARE_MOD,       /**< Software update occurred. */
   LOG_SECURITY_MAX,                /**< Used for range checking */
} CmsSecurityLogIDs;


/** Max number of ms to wait for a MDM read lock. */
#define CMSLOG_LOCK_TIMEOUT  (3 * MSECS_IN_SEC)


#define CMSLOG_SEC_COUNT_FLAG    (1 << 0)
#define CMSLOG_SEC_PORT_FLAG     (1 << 1)
#define CMSLOG_SEC_SRC_IP_FLAG   (1 << 2)
#define CMSLOG_SEC_USER_FLAG     (1 << 3)
#define CMSLOG_SEC_LEVEL_FLAG    (1 << 4)

#define CMSLOG_SEC_SET_COUNT(p, d)   {(p)->count = (d); (p)->data_flags |= CMSLOG_SEC_COUNT_FLAG;}
#define CMSLOG_SEC_SET_PORT(p, d)    {(p)->port = (d);  (p)->data_flags |= CMSLOG_SEC_PORT_FLAG;}
#define CMSLOG_SEC_SET_SRC_IP(p, d)  {(p)->src_ip.s_addr = (d);  (p)->data_flags |= CMSLOG_SEC_SRC_IP_FLAG;}
#define CMSLOG_SEC_SET_USER(p, d)    {(p)->user = (d);  (p)->data_flags |= CMSLOG_SEC_USER_FLAG;}
#define CMSLOG_SEC_SET_LEVEL(p, d)   {(p)->security_level = (d);  (p)->data_flags |= CMSLOG_SEC_LEVEL_FLAG;}

/** security log length */
#define SECURITY_LOG_RD_OFFSET   (0)
#define SECURITY_LOG_RD_SIZE     (sizeof(uint32_t))
#define SECURITY_LOG_WR_OFFSET   (4)
#define SECURITY_LOG_WR_SIZE     (sizeof(uint32_t))
#define SECURITY_LOG_DATA_OFFSET (8)
#define SECURITY_LOG_DATA_SIZE   (4 * 1024)
#define SECURITY_LOG_FILE_NAME  "/data/securitylog"

/** Structure to hold relevant data regarding security log events.
 *
 */
typedef struct 
{
   UINT32         count;
   UINT32         port;
   struct in_addr src_ip;
   char *         user;
   UINT32         security_level;
   UINT32         data_flags;
} CmsSecurityLogData;


/** Security log file structure 
 *
 */
typedef struct
{
   unsigned long read_offset;       /** offset of oldest log */
   unsigned long write_offset;      /** offset of newest log */
   char log[SECURITY_LOG_DATA_SIZE];     /** security log strings */   
} CmsSecurityLogFile;


/** Log a security log in the system.
 *
 * This function logs security logs into flash for non-volatile storage.
 * There are a specified list of logs that can be used, or the user may 
 * add their own string.
 *
 * @param id (IN) Predefined security log message string.
 * @param pdata (IN) Structure containing relevant log information. 
 * @param pFmt (IN) The message string.
 *
 * @return CMSRET_SUCCESS on success, otherwise an error occurred.
 */
CmsRet cmsLog_security(CmsSecurityLogIDs id, CmsSecurityLogData * pdata,
                           const char *pFmt, ... );


/** Retrieve the security log from the system.
 *
 * @param log (OUT) Pointer to CmsSecurityLogFile structure. 
 *                  Memory must be allocated by the caller.
 *
 * @return CMSRET_SUCCESS on success, otherwise an error occurred.
 */
CmsRet cmsLog_getSecurityLog(CmsSecurityLogFile * log);


/** Print the security log to stdout.
 *
 * @param log (OUT) Pointer to CmsSecurityLogFile structure. 
 *                  Memory must be allocated by the caller.
 *
 * @return None
 */
void cmsLog_printSecurityLog(CmsSecurityLogFile * log);


/** Reset and clear all entries in the security log in the system.
 *
 * @return CMSRET_SUCCESS on success, otherwise an error occurred.
 */
CmsRet cmsLog_resetSecurityLog(void);

#endif /* CMS_SECURITY_LOG */

