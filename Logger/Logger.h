/**
* @file        Logger.h
* @modifier    Zhan WANG <wangzhan@rd.netease.com>
* @brief       Used to output the debug information, it comes from the dictionary client project
*/
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <cstdio>

#define FATAL_LEVEL 0
#define WARN_LEVEL 1
#define INFO_LEVEL 2
#define DEBUG_LEVEL 3
#define TEST_LEVEL 4

enum {LOG_STDERR = 1, LOG_FILE, LOG_TRACE};

#if defined ( NLOGGING )
#define LOG_TO_STDERR
#define LOG_TO_FILE
#define LOG_FATAL_LEVEL
#define LOG_WARN_LEVEL
#define LOG_INFO_LEVEL
#define LOG_DEBUG_LEVEL
#define LOG_TEST_LEVEL
#define LOG_FATAL
#define LOG_WARN
#define LOG_INFO
#define LOG_DEBUG
#define LOG_TEST
#define SET_LOG_FLUSH_LEVEL(level)

#else

#define LOG_TO_STDERR \
    do {\
        Logger& loger___ = Logger::instance();\
        loger___.setLogType(LOG_STDERR);\
    }while(0)

#define LOG_TO_FILE \
    do {\
        Logger& loger___ = Logger::instance();\
        loger___.setLogType(LOG_FILE);\
    }while(0)

#define LOG_FATAL_LEVEL \
    do {\
        Logger& loger___ = Logger::instance();\
        loger___.setLogLevel(FATAL_LEVEL);\
    }while(0)

#define LOG_WARN_LEVEL \
    do {\
        Logger& loger___ = Logger::instance();\
        loger___.setLogLevel(WARN_LEVEL);\
    }while(0)

#define LOG_INFO_LEVEL \
    do {\
        Logger& loger___ = Logger::instance();\
        loger___.setLogLevel(INFO_LEVEL);\
    }while(0)

#define LOG_DEBUG_LEVEL \
    do {\
        Logger& loger___ = Logger::instance();\
        loger___.setLogLevel(DEBUG_LEVEL);\
    }while(0)

#define LOG_TEST_LEVEL \
    do {\
        Logger& loger___ = Logger::instance();\
        loger___.setLogLevel(TEST_LEVEL);\
    }while(0)

#define SET_LOG_LEVEL(level) \
    do {\
    Logger& loger___ = Logger::instance();\
    loger___.setLogLevel(level);\
    }while(0)

#define LOG_TEST LoggerWrapper(TEST_LEVEL)
#define LOG_DEBUG LoggerWrapper(DEBUG_LEVEL)
#define LOG_INFO LoggerWrapper(INFO_LEVEL)
#define LOG_WARN LoggerWrapper(WARN_LEVEL)
#define LOG_FATAL LoggerWrapper(FATAL_LEVEL)

#define SET_LOG_FLUSH_LEVEL(level)\
    do {\
    Logger& loger___ = Logger::instance();\
    loger___.setFlushLevel(level);\
    }while(0)

#endif /* NLOGGING */

#ifdef LOG_EXPORTS
#define LOG_API __declspec(dllexport)
#else
#define LOG_API
#endif

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tstring;

#ifndef NLOGGING

class LoggerImp;

/**
* @class Logger
*/
class LOG_API Logger
{
public:
    static Logger& instance();
    void warning( const TCHAR *format, va_list argptr );	
    void info( const TCHAR *format, va_list argptr );
    void debug( const TCHAR *format, va_list argptr );
    void fatal( const TCHAR *format, va_list argptr );
    void test( const TCHAR *format, va_list argptr );

    void setLogType( int type );
    void setLogLevel( int level );
    void setFileName( const TCHAR* theFileName );
    void setLogFileSize( unsigned int size);
    void setMaxFileNum( int num);
    void setFlushLevel( int iLevel );
    static tstring GetLogFilePath();
private:
    Logger();
    ~Logger();
    LoggerImp* m_pLoggerImp;
};

class LoggerWrapper
{
public:
    LoggerWrapper(int level) : m_level(level){};
    void operator()(const TCHAR* format, ...)
    {
        va_list list;
        va_start(list, format);
        switch (m_level)
        {
        case FATAL_LEVEL:
            Logger::instance().fatal(format, list);
            break;
        case WARN_LEVEL:
            Logger::instance().warning(format, list);
            break;
        case INFO_LEVEL:
            Logger::instance().info(format, list);
            break;
        case DEBUG_LEVEL:
            Logger::instance().debug(format, list);
            break;
        case TEST_LEVEL:
            Logger::instance().test(format, list);
            break;
        }
        va_end( list );
    }


private:
    int m_level;
};

#endif 

#endif  /* __LOGGER_H__ */
