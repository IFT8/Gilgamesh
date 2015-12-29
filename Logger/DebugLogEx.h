/**
 * @file MyLog.h
 * @author Chen Qihua<chenqh@rd.netease.com>
 */

#include "LogEx.h"
#ifndef CDEBUG_TYPE
#define CDEBUG_TYPE _T("COMMON::")
#endif
#ifndef _DEBUG
#undef CWRITE_DEBUG_LOG
#endif

#define MEE_ELOG_FATAL(debugType, str, ...)	ELOG_FATAL( debugType ## str, __VA_ARGS__)
#define ME_ELOG_FATAL(CDEBUG_TYPE, str, ...)	MEE_ELOG_FATAL(CDEBUG_TYPE, str, __VA_ARGS__)
#define CLOG_FATAL( str, ...)	ME_ELOG_FATAL(CDEBUG_TYPE, str, __VA_ARGS__)

#define MEE_ELOGIF_FATA(debugType, condition, str, ... )	ELOGIF_FATA( condition, debugType ## str, __VA_ARGS__ )
#define ME_ELOGIF_FATA(CDEBUG_TYPE, condition, str, ... )	MEE_ELOGIF_FATA(CDEBUG_TYPE, condition, str, __VA_ARGS__ )
#define CIF_LOGFATAL( condition, str, ... )	ME_ELOGIF_FATA(CDEBUG_TYPE, condition, str, __VA_ARGS__ )

#define MEE_ELOG_FATAL_RET(debugType, ret, str, ... )	ELOG_FATAL_RET( ret, debugType ## str, __VA_ARGS__ )
#define ME_ELOG_FATAL_RET(CDEBUG_TYPE, ret, str, ... )	MEE_ELOG_FATAL_RET(CDEBUG_TYPE, ret, str, __VA_ARGS__ )
#define CRET_LOG_FATAL( ret, str, ... )	ME_ELOG_FATAL_RET(CDEBUG_TYPE, ret, str, __VA_ARGS__ )

#define MEE_ELOGIF_FATAL_RET(debugType, condition, ret, str, ... )	ELOGIF_FATAL_RET( condition, ret, debugType ## str, __VA_ARGS__ )
#define ME_ELOGIF_FATAL_RET(CDEBUG_TYPE, condition, ret, str, ... )	MEE_ELOGIF_FATAL_RET(CDEBUG_TYPE, condition, ret, str, __VA_ARGS__ )
#define CIF_RET_LOGFATAL( condition, ret, str, ... )	ME_ELOGIF_FATAL_RET(CDEBUG_TYPE, condition, ret, str, __VA_ARGS__ )

#define MEE_ELOG_FATAL_ASSERT(debugType, str, ...)	ELOG_FATAL_ASSERT( debugType ## str, __VA_ARGS__)
#define ME_ELOG_FATAL_ASSERT(CDEBUG_TYPE, str, ...)	MEE_ELOG_FATAL_ASSERT(CDEBUG_TYPE, str, __VA_ARGS__)
#define CLOG_FATAL_ASSERT( str, ...)	ME_ELOG_FATAL_ASSERT(CDEBUG_TYPE, str, __VA_ARGS__)

#define MEE_ELOGIF_FATA_ASSERT(debugType, condition, str, ... )	ELOGIF_FATA_ASSERT( condition, debugType ## str, __VA_ARGS__ )
#define ME_ELOGIF_FATA_ASSERT(CDEBUG_TYPE, condition, str, ... )	MEE_ELOGIF_FATA_ASSERT(CDEBUG_TYPE, condition, str, __VA_ARGS__ )
#define CIF_LOGFATAL_ASSERT( condition, str, ... )	ME_ELOGIF_FATA_ASSERT(CDEBUG_TYPE, condition, str, __VA_ARGS__ )

#define MEE_ELOG_FATAL_ASSERT_RET(debugType, ret, str, ... )	ELOG_FATAL_ASSERT_RET( ret, debugType ## str, __VA_ARGS__ )
#define ME_ELOG_FATAL_ASSERT_RET(CDEBUG_TYPE, ret, str, ... )	MEE_ELOG_FATAL_ASSERT_RET(CDEBUG_TYPE, ret, str, __VA_ARGS__ )
#define CRET_FALAL_ASSERT( ret, str, ... )	ME_ELOG_FATAL_ASSERT_RET(CDEBUG_TYPE, ret, str, __VA_ARGS__ )

#define MEE_ELOGIF_FATAL_ASSERT_RET(debugType, condition, ret, str, ... )	ELOGIF_FATAL_ASSERT_RET( condition, ret, debugType ## str, __VA_ARGS__ )
#define ME_ELOGIF_FATAL_ASSERT_RET(CDEBUG_TYPE, condition, ret, str, ... )	MEE_ELOGIF_FATAL_ASSERT_RET(CDEBUG_TYPE, condition, ret, str, __VA_ARGS__ )
#define CIF_RET_LOGFATAL_ASSERT( condition, ret, str, ... )	ME_ELOGIF_FATAL_ASSERT_RET(CDEBUG_TYPE, condition, ret, str, __VA_ARGS__ )
// CWRITE_DEBUG_LOG_ON_RELEASE 表明即使在release模式下也要输出结果
#if defined(CWRITE_DEBUG_LOG) || defined(CWRITE_DEBUG_LOG_ON_RELEASE)
#define MEE_ELOG_DEBUG(debugType, str, ...)	ELOG_DEBUG( debugType ## str, __VA_ARGS__)
#define ME_ELOG_DEBUG(CDEBUG_TYPE, str, ...)	MEE_ELOG_DEBUG(CDEBUG_TYPE, str, __VA_ARGS__)
#define CLOG_DEBUG( str, ...)	ME_ELOG_DEBUG(CDEBUG_TYPE, str, __VA_ARGS__)

#define MEE_ELOGIF_DEBUG(debugType, condition, str, ... )	ELOGIF_DEBUG( condition, debugType ## str, __VA_ARGS__ )
#define ME_ELOGIF_DEBUG(CDEBUG_TYPE, condition, str, ... )	MEE_ELOGIF_DEBUG(CDEBUG_TYPE, condition, str, __VA_ARGS__ )
#define CIF_LOGDEBUG( condition, str, ... )	ME_ELOGIF_DEBUG(CDEBUG_TYPE, condition, str, __VA_ARGS__ )

#define MEE_ELOG_DEBUG_RET(debugType, ret, str, ... )	ELOG_DEBUG_RET( ret, debugType ## str, __VA_ARGS__ )
#define ME_ELOG_DEBUG_RET(CDEBUG_TYPE, ret, str, ... )	MEE_ELOG_DEBUG_RET(CDEBUG_TYPE, ret, str, __VA_ARGS__ )
#define CRET_LOGDEBUG( ret, str, ... )	ME_ELOG_DEBUG_RET(CDEBUG_TYPE, ret, str, __VA_ARGS__ )

#define MEE_ELOGIF_DEBUG_RET(debugType, condition, ret, str, ... )	ELOGIF_DEBUG_RET( condition, ret, debugType ## str, __VA_ARGS__ )
#define ME_ELOGIF_DEBUG_RET(CDEBUG_TYPE, condition, ret, str, ... )	MEE_ELOGIF_DEBUG_RET(CDEBUG_TYPE, condition, ret, str, __VA_ARGS__ )
#define CIF_RET_LOGDEBUG( condition, ret, str, ... )	ME_ELOGIF_DEBUG_RET(CDEBUG_TYPE, condition, ret, str, __VA_ARGS__ )

#else
#define CLOG_DEBUG(str,...)
#define CIF_LOGDEBUG(condition,str,...)
#define CRET_LOGDEBUG(ret,str,...)
#define CIF_RET_LOGDEBUG(condition,ret,str,...)
#endif

