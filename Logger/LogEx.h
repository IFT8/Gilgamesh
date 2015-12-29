/**
 * @file MyLog.h
 *
 * @author Chen Qihua<chenqh@rd.netease.com>
 */

#include "MyLog.h"

#define VOID_RET

#define ELOG_FATAL( str, ...) LOG_FATAL_REGULAR( str, __VA_ARGS__ )
#define ELOGIF_FATA( condition, str, ... )\
    do{\
    if( condition ){\
        ELOG_FATAL( str, __VA_ARGS__ );\
    }\
    }while(0)
#define ELOG_FATAL_RET( ret, str, ... )\
    do{\
    ELOG_FATAL( str, __VA_ARGS__ );\
    return ret;\
    }while(0)
#define ELOGIF_FATAL_RET( condition, ret, str, ... )\
    do{\
    if( condition )\
        ELOG_FATAL_RET( ret, str, __VA_ARGS__ );\
    }while(0)

#define ELOG_FATAL_ASSERT( str, ...) \
    do{\
        LOG_FATAL_REGULAR( str, __VA_ARGS__ );\
        ASSERT( FALSE );\
    }while(0)
#define ELOGIF_FATA_ASSERT( condition, str, ... )\
    do{\
    if( condition ){\
    ELOG_FATAL_ASSERT( str, __VA_ARGS__ );\
    }\
    }while(0)
#define ELOG_FATAL_ASSERT_RET( ret, str, ... )\
    do{\
    ELOG_FATAL_ASSERT( str, __VA_ARGS__ );\
    return ret;\
    }while(0)
#define ELOGIF_FATAL_ASSERT_RET( condition, ret, str, ... )\
    do{\
    if( condition )\
    ELOG_FATAL_ASSERT_RET( ret, str, __VA_ARGS__ );\
    }while(0)


#define ELOG_DEBUG( str, ...) LOG_DEBUG_REGULAR( str, __VA_ARGS__ )
#define ELOGIF_DEBUG( condition, str, ... )\
    do{\
    if( condition ){\
        ELOG_DEBUG( str, __VA_ARGS__ );\
    }\
    }while(0)
#define ELOG_DEBUG_RET( ret, str, ... )\
    do{\
        ELOG_DEBUG( str, __VA_ARGS__ );\
        return ret;\
    }while(0)
#define ELOGIF_DEBUG_RET( condition, ret, str, ... )\
    do{\
    if( condition )\
        ELOG_DEBUG_RET( ret, str, __VA_ARGS__ );\
    }while(0)

