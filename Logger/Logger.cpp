#include "Lock.h"
#include "Logger.h"
#include <time.h>
#include <sys/timeb.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sstream>
#include <string>
#include <cassert>
#include <locale.h>
#include <tchar.h>
#include <shlobj.h>

#ifndef NLOGGING

#define CLOSE_FILE(p) \
{\
    if (p != NULL)\
    {\
        fclose(p);\
        p = NULL;\
    }\
}

using namespace std;

typedef basic_ostringstream<TCHAR, char_traits<TCHAR>, allocator<TCHAR> > tostringstream;

#pragma comment(lib, "Shell32.lib")

class LoggerImp
{
public:	
    LoggerImp();
    ~LoggerImp();
    void warning( const TCHAR *format, va_list argptr );	
    void info( const TCHAR *format, va_list argptr );
    void debug( const TCHAR *format, va_list argptr );
    void fatal( const TCHAR *format, va_list argptr );
    void test( const TCHAR *format, va_list argptr );

    static tstring GetLogFilePath();
    void setLogType( int type );
    void setLogLevel( int level );
    void setFileName( const TCHAR* theFileName );
    void setLogFileSize( unsigned int size);
    void setMaxFileNum( int num);

    void setFlushLevel(int level);

private:

    void writeLog(int iLevel, const TCHAR* strLevel, const TCHAR* format, va_list argptr);
    void flush();
    void writeHead(const TCHAR* strLevel);
    void writeBody(const TCHAR* format, va_list argptr);
    void trace(const TCHAR* format, va_list argptr);
    void tryRollOver();
    FILE* createOutputFile(const TCHAR* fname);

    unsigned int m_logLevel;
    int m_logType;
    FILE* m_stream;
    tstring m_fileName;
    unsigned int m_maxFileSize;
    int m_maxFileNum;
    bool m_bflush;
    int m_flushLevel;
};

LoggerImp::LoggerImp()
{
    if( NULL == setlocale(LC_ALL, "chs") )
    {
        setlocale(LC_ALL, ".936");
    }

    //default value;
    m_logLevel = TEST_LEVEL;
    m_logType = LOG_STDERR;
    m_stream = NULL;
    m_maxFileSize = 2 * 1024 * 1024;
    m_maxFileNum = 5;
    m_bflush = true;
    m_flushLevel = WARN_LEVEL;
    setLogType(LOG_TRACE);
}

LoggerImp::~LoggerImp()
{
    if ((m_logType == LOG_FILE) && (m_stream != NULL))
    {
        CLOSE_FILE(m_stream);
    }
}

void LoggerImp::writeHead(const TCHAR* strLevel)
{
    unsigned int _milliSeconds;
    TCHAR bufbuf[32];
    struct timeb tb;
    ::ftime(&tb);
    _milliSeconds = tb.millitm;
    struct tm t;
    localtime_s(&t, &tb.time);
    _tcsftime( bufbuf, 32, _T("%Y-%m-%d %X"), &t);

    if (m_logType != LOG_TRACE)
    {
        FILE* fp = NULL;
        if( m_logType == LOG_FILE && m_stream )
        {
            tryRollOver();
            fp = m_stream;
        }
        else if (m_logType == LOG_STDERR)
        {
            fp = stderr;
        }
        if (fp)
        {
            _ftprintf_s(fp, _T("%s\'%u\" %u\t%s\t"), bufbuf, _milliSeconds, THREADID, strLevel);
        }
    }
    TCHAR output[256];
    _sntprintf_s(output, _countof(output), _countof(output) - 1, _T("%s\'%u\" %u\t%s\t"), bufbuf, _milliSeconds, THREADID, strLevel);
    OutputDebugString(output);
}

void LoggerImp::writeBody(const TCHAR* format, va_list argptr)
{
    tstring strFormat(format);
    strFormat += _T("\r\n");
    if (m_logType != LOG_TRACE)
    {
        FILE* fp = NULL;
        if( m_logType == LOG_FILE && m_stream )
        {
            fp = m_stream;
        }
        else if ( m_logType == LOG_STDERR )
        {
            fp = stderr;
        }
        if (fp)
        {
            _vftprintf_s( fp, strFormat.c_str(), argptr );
            if( m_bflush )
            {
                fflush( fp );
            }
        }
    }
    trace(strFormat.c_str(), argptr);
}

void LoggerImp::flush()
{
    if (m_logType != LOG_TRACE)
    {
        FILE* fp = NULL;
        if( m_logType == LOG_FILE && m_stream )
        {
            fp = m_stream;
        }
        else if ( m_logType == LOG_STDERR )
        {
            fp = stderr;
        }
        if (fp)
        {
            fflush(fp);
        }
    }
}

void LoggerImp::writeLog(int iLevel, const TCHAR* strLevel, const TCHAR* format, va_list argptr)
{
    if ((int(m_logLevel) < iLevel) || (m_logType == LOG_FILE && m_stream == NULL))
    {
        return;
    }
    LOG_LOCK;
    writeHead(strLevel);
    writeBody( format, argptr );
    if( m_flushLevel >= iLevel )
    {
        flush();
    }
    LOG_UNLOCK;
}

void LoggerImp::trace(const TCHAR* format, va_list argptr)
{
#ifndef LINUX
    TCHAR output[1024];
    _vsntprintf_s(output, _countof(output), _countof(output) - 1, format, argptr);
    OutputDebugString(output);
#endif
}

void LoggerImp::fatal( const TCHAR *format, va_list argptr )
{
    writeLog(FATAL_LEVEL, _T("[FATAL]"), format, argptr);
}

void LoggerImp::info( const TCHAR *format, va_list argptr )
{
    writeLog(INFO_LEVEL, _T("[INFO]"), format, argptr);
}

void LoggerImp::debug( const TCHAR *format, va_list argptr )
{
    writeLog(DEBUG_LEVEL, _T("[DEBUG]"), format, argptr);
}

void LoggerImp::test( const TCHAR *format, va_list argptr )
{
    writeLog(TEST_LEVEL, _T("[TEST]"), format, argptr);
}

void LoggerImp::warning( const TCHAR* format, va_list argptr )
{
    writeLog(WARN_LEVEL, _T("[WARN]"), format, argptr);
}

void LoggerImp::setLogType( int type )
{
    //nothing to do
    if (m_logType == type)
    {
        return;
    }

    //clean old log context
    if (m_logType == LOG_FILE)
    {
        CLOSE_FILE(m_stream);
        m_stream = NULL;
    }

    //setup new log context
    if (type == LOG_FILE)
    {
        if( m_fileName.length() == 0 )
        {
            m_fileName = GetLogFilePath();
        }

        m_stream = createOutputFile(m_fileName.c_str());
        if (m_stream != NULL)
        {
            setvbuf( m_stream, NULL, _IOFBF, 300 * 1024 ); // bufsize : 300K
        }
    }
    m_logType = type;

}

tstring LoggerImp::GetLogFilePath()
{
    TCHAR fileName[MAX_PATH] = {0};
    // 取log所在的路径
    SHGetSpecialFolderPath(NULL, fileName, CSIDL_LOCAL_APPDATA, FALSE);
    tstring strTempFileName = fileName;
    tstring strDir = strTempFileName + _T("\\youdao\\ynote\\");

    // 取进程对应的执行程序路径
    fileName[0] = 0;
    ::GetModuleFileName(NULL, fileName, MAX_PATH);
    strTempFileName = fileName;
    size_t pos = strTempFileName.find_last_of(_T('\\'));
    tstring strName = strTempFileName.substr(pos + 1);

    // 产生默认的log文件路径，如果log目录不存在，不会产生log
    return strDir + _T("log\\") + strName + _T(".log");
}

void LoggerImp::setLogLevel( int level )
{
    m_logLevel = level;
}

void LoggerImp::setFlushLevel(int level)
{
    m_flushLevel = level;
}

void LoggerImp::setFileName( const TCHAR* theFileName )
{
    assert(theFileName);
    m_fileName = theFileName;
}

void LoggerImp::setLogFileSize( unsigned int size)
{
    assert(size > 0);
    m_maxFileSize = size;
}

void LoggerImp::setMaxFileNum( int num)
{
    assert(num > 0);
    m_maxFileNum = num;
}

void LoggerImp::tryRollOver()
{
    int offset = ftell( m_stream );
    if( static_cast<size_t>(offset) < m_maxFileSize )
    {
        return;
    }

    CLOSE_FILE( m_stream );
    int maxFileIndex = m_maxFileNum - 1;
    if ( maxFileIndex > 0 ) 
    {
        tostringstream ossName;
        ossName << m_fileName << _T(".") << maxFileIndex << std::ends;
        tstring oldName = ossName.str();
        _tremove(oldName.c_str());
        for(unsigned int i = maxFileIndex; i > 1; i--) 
        {
            tstring newName = oldName;
            tostringstream ossName;
            ossName << m_fileName <<_T(".")<< i-1 << std::ends;
            oldName = ossName.str();
            _trename(oldName.c_str(), newName.c_str());
        }
        _trename( m_fileName.c_str(), oldName.c_str() );
    }
    m_stream = createOutputFile(m_fileName.c_str());
}

FILE* LoggerImp::createOutputFile(const TCHAR* fname)
{
    //以append的模式创建文件
    FILE* stream = _tfsopen(fname, _T("a+b"), _SH_DENYWR);

#ifdef _UNICODE
    if(stream)
    {
        unsigned char mark[2] = {0xFF, 0xFE};
        fwrite(mark, 1, 2, stream);
    }
#endif
    return stream;
}

Logger::Logger()
{
    m_pLoggerImp = new LoggerImp();
}

Logger::~Logger()
{
    delete m_pLoggerImp;
}

Logger& Logger::instance()
{
    static Logger me;
    return me;
}
void Logger::warning( const TCHAR *format, va_list argptr )
{
    m_pLoggerImp->warning(format, argptr);
}

void Logger::info( const TCHAR *format, va_list argptr )
{
    m_pLoggerImp->info(format, argptr);
}

void Logger::debug( const TCHAR *format, va_list argptr )
{
    m_pLoggerImp->debug(format, argptr);
}

void Logger::fatal( const TCHAR *format, va_list argptr )
{
    m_pLoggerImp->fatal(format, argptr);
}

void Logger::test( const TCHAR *format, va_list argptr )
{
    m_pLoggerImp->test(format, argptr);
}

void Logger::setLogType( int type )
{
    m_pLoggerImp->setLogType(type);
}

void Logger::setLogLevel( int level )
{
    m_pLoggerImp->setLogLevel(level);
}

void Logger::setFileName( const TCHAR* theFileName )
{
    m_pLoggerImp->setFileName(theFileName);
}

void Logger::setLogFileSize( unsigned int size)
{
    m_pLoggerImp->setLogFileSize(size);
}

void Logger::setMaxFileNum( int num)
{
    m_pLoggerImp->setMaxFileNum(num);
}

void Logger::setFlushLevel( int iLevel )
{
    m_pLoggerImp->setFlushLevel(iLevel);
}

tstring Logger::GetLogFilePath()
{
    return LoggerImp::GetLogFilePath();
}

#endif
