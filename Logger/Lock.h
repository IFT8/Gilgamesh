/**
 * @file        Lock.h
 * @modifier    Zhan WANG <wangzhan@rd.netease.com>
 * @brief       Used to lock in multi thread, it comes from the dictionary client project
 */

#pragma once
#ifdef LINUX
#include <syslog.h>
#include <pthread.h>

#define THREADID pthread_self()
static pthread_mutex_t MUTEx = PTHREAD_MUTEX_INITIALIZER;
#define LOG_LOCK   pthread_mutex_lock(&MUTEx)
#define LOG_UNLOCK  pthread_mutex_unlock(&MUTEx)

#else
#include <Windows.h>
#include <Winbase.h>

HANDLE hMutex = CreateMutex( NULL, FALSE, NULL);
#define LOG_LOCK    WaitForSingleObject( hMutex, INFINITE )
#define LOG_UNLOCK  ReleaseMutex( hMutex )
#define THREADID GetCurrentThreadId()

#endif /* LINUX */
