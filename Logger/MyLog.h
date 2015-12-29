/**
 * @file MyLog.h
 *
 * @author Liu JC <liujc@rd.netease.com>
 */

#pragma once
#include "Logger.h"
#include "FormatCheck.h"

//instead of the following two Macros, please use SET_LOG_FLUSH_LEVEL
//#define LOG_DISABLE_FLUSH   
//#define LOG_ENABLE_FLUSH 

#define LOG_SET_FILE_NAME(name) \
	Logger::instance().setFileName(name)

///���г�����Ϣ(�ļ����кš�����)
#define LOG_TEST_REGULAR(str, ...) \
    AssetFunction(CheckFormat(str, __VA_ARGS__));\
    LOG_TEST(str ## _T("; File: %s, Line: %d, Function: %s"), __VA_ARGS__, __FILEW__, __LINE__, __FUNCTIONW__)

#define LOG_INFO_REGULAR(str, ...) \
    AssetFunction(CheckFormat(str, __VA_ARGS__));\
    LOG_INFO(str ## _T("; File: %s, Line: %d, Function: %s"), __VA_ARGS__, __FILEW__, __LINE__, __FUNCTIONW__)

#define LOG_DEBUG_REGULAR(str, ...) \
    AssetFunction(CheckFormat(str, __VA_ARGS__));\
    LOG_DEBUG(str ## _T("; File: %s, Line: %d, Function: %s"), __VA_ARGS__, __FILEW__, __LINE__, __FUNCTIONW__)

#define LOG_WARN_REGULAR(str, ...) \
    AssetFunction(CheckFormat(str, __VA_ARGS__));\
    LOG_WARN(str ## _T("; File: %s, Line: %d, Function: %s"), __VA_ARGS__, __FILEW__, __LINE__, __FUNCTIONW__)

#define LOG_FATAL_REGULAR(str, ...) \
    AssetFunction(CheckFormat(str, __VA_ARGS__));\
    LOG_FATAL(str ## _T("; File: %s, Line: %d, Function: %s"), __VA_ARGS__, __FILEW__, __LINE__, __FUNCTIONW__)


///������ͬ�����log��־����¼�´�����־������p
#define LOG_FATAL_WRAPPER(p) \
    LOG_FATAL(_T("Condition: %s; Function: %s, Line: %d"), p, __FUNCTIONW__, __LINE__);

#define LOG_DEGUG_WRAPPER(p) \
    LOG_DEBUG(_T("Condition: %s; Function: %s, Line: %d"), p, __FUNCTIONW__, __LINE__);

#define LOG_INFO_WRAPPER(p) \
    LOG_INFO(_T("Condition: %s; Function: %s, Line: %d"), p, __FUNCTIONW__, __LINE__);

#define LOG_WARN_WRAPPER(p) \
    LOG_WARN(_T("Condition: %s; Function: %s, Line: %d"), p, __FUNCTIONW__, __LINE__);

///������ͬ�����log��־����¼�´�����־������p
#define MY_LOG_FATAL(p) \
	LOG_FATAL(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p);

#define MY_LOG_DEGUG(p) \
	LOG_DEBUG(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p);

#define MY_LOG_INFO(p) \
	LOG_INFO(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p);

#define MY_LOG_WARN(p) \
	LOG_WARN(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p);

#define MY_LOG_FATAL_INT(p) \
    LOG_FATAL(_T("File: %s, Line: %d, Function: %s, Condition: %s, value: %d"), __FILEW__, __LINE__, __FUNCTIONW__, L###p, p);

#define MY_LOG_DEGUG_INT(p) \
    LOG_DEBUG(_T("File: %s, Line: %d, Function: %s, Condition: %s, value: %d"), __FILEW__, __LINE__, __FUNCTIONW__, L###p, p);

#define MY_LOG_INFO_INT(p) \
    LOG_INFO(_T("File: %s, Line: %d, Function: %s, Condition: %s, value: %d"), __FILEW__, __LINE__, __FUNCTIONW__, L###p, p);

#define MY_LOG_WARN_INT(p) \
    LOG_WARN(_T("File: %s, Line: %d, Function: %s, Condition: %s, value: %d"), __FILEW__, __LINE__, __FUNCTIONW__, L###p, p);



///������ͬ�����log��־����¼�´�����־������p����assert
#define MY_LOG_FATAL_ASSERT(p) \
	LOG_FATAL(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p);\
	ASSERT(FALSE);

#define MY_LOG_DEGUG_ASSERT(p) \
	LOG_DEBUG(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p);\
	ASSERT(FALSE);

#define MY_LOG_INFO_ASSERT(p) \
	LOG_INFO(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p);\
	ASSERT(FALSE);

#define MY_LOG_WARN_ASSERT(p) \
	LOG_WARN(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p);\
	ASSERT(FALSE);

///������ͬ�����log��־����¼�´�����־������p�������ض�ֵret
#define MY_LOG_FATAL_RETURN(p, ret) \
	LOG_FATAL(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p); \
	return ret;

#define MY_LOG_DEGUG_RETURN(p, ret) \
	LOG_DEBUG(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p); \
	return ret;

#define MY_LOG_INFO_RETURN(p, ret) \
	LOG_INFO(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p); \
	return ret;

#define MY_LOG_WARN_RETUEN(p, ret) \
	LOG_WARN(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p); \
	return ret;


///������ͬ�����log��־����¼�´�����־������p�������ض�ֵret����assert
#define MY_LOG_FATAL_ASSERT_RETURN(p, ret) \
	LOG_FATAL(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p);\
	ASSERT(FALSE);\
	return ret;

#define MY_LOG_DEGUG_ASSERT_RETURN(p, ret) \
	LOG_DEBUG(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p);\
	ASSERT(FALSE);\
	return ret;

#define MY_LOG_INFO_ASSERT_RETURN(p, ret) \
	LOG_INFO(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p);\
	ASSERT(FALSE);\
	return ret;

#define MY_LOG_WARN_ASSERT_RETURN(p, ret) \
	LOG_WARN(_T("File: %s, Line: %d, Function: %s, Condition: %s"), __FILEW__, __LINE__, __FUNCTIONW__, L###p);\
	ASSERT(FALSE);\
	return ret;

///���ָ���Ƿ�Ϊ�գ����Ϊ�գ�����ret
#define CHECK_POINTER(p, ret) \
	if(p == NULL)\
	{\
	MY_LOG_FATAL(p);\
	return ret;\
	}

///���ָ���Ƿ�Ϊ�գ����Ϊ�գ�����ret����assert
#define CHECK_POINTER_ASSERT(p, ret) \
	if(p == NULL)\
	{\
	MY_LOG_FATAL_ASSERT(p);\
	return ret;\
	}
