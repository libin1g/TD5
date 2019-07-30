#ifndef CRUNTIMELOG_H
#define CRUNTIMELOG_H

#include <string>
#include <cstring>
#include <cstdarg>
#include <cstdlib>
#include <ctime>
#include <fstream>

#ifdef _WINDOWS
#include <windows.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif // _MSC_VER

#else
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#endif // _WINDOWS

class CRuntimeLog {
public:
    static CRuntimeLog & Instance()
    {
        static CRuntimeLog m_instance;
        return m_instance;
    }

    void WriteLog(const char* pfmt, ...)
    {
        int pid = 0;
        int tid = 0;
#ifdef _WINDOWS
        pid = GetCurrentProcessId();
        tid = GetCurrentThreadId();

        SYSTEMTIME st;
        GetLocalTime(&st);

        char timeStr[256];
        memset(timeStr, 0, sizeof(timeStr));
        snprintf(timeStr, sizeof(timeStr), "%u-%u-%u %u:%u:%u.%03u",
                st.wYear, st.wMonth, st.wDay,
                st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#else
        pid = getpid();
        //tid = gettid();

        struct timeval tv;
        gettimeofday(&tv, NULL);

        struct tm* timeinfo;
        timeinfo = localtime(&tv.tv_sec);

        char timeBuf[128];
        memset(timeBuf, 0, sizeof(timeBuf));
        strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", timeinfo);

        char timeStr[256];
        memset(timeStr, 0, sizeof(timeStr));
        snprintf(timeStr, sizeof(timeStr), "%s.%06d", timeBuf, int(tv.tv_usec));
#endif // _WINDOWS

        va_list vl;
        va_start (vl, pfmt);
        char buf[512];
        memset(buf, 0, sizeof(buf));
        vsnprintf(buf, sizeof(buf), pfmt, vl);
        va_end(vl);

        char logbuf[1024];
        memset(logbuf, 0, sizeof(logbuf));
        sprintf(logbuf, "%s: (%d|%d) %s \n", timeStr, pid, tid, buf);

#ifdef _WINDOWS
        EnterCriticalSection(&m_cs);
#else
        pthread_mutex_lock(&m_mutex);
#endif // _WINDOWS
        if (!m_pOfs)
        {
            m_pOfs = new  std::ofstream(m_strLogfile, std::ios::ate | std::ios::app);
        }
        m_pOfs->write(logbuf, strlen(logbuf));
        m_pOfs->flush();
        if (m_pOfs->tellp() > 2 * 1024 * 1024)
        {
            m_pOfs->close();
            delete m_pOfs;
            m_pOfs = NULL;

            time_t t;
            time(&t);
            struct tm* tm;
            tm = localtime(&t);
            char buf[126];
            memset(buf, 0, sizeof(buf));
            strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", tm);
            rename((m_strLogfile + ".log").c_str(), (m_strLogfile + buf + ".log").c_str());
        }
#ifdef _WINDOWS
        LeaveCriticalSection(&m_cs);
#else
        pthread_mutex_unlock(&m_mutex);
#endif // _WINDOWS
    }

private:
    CRuntimeLog()
    {
        std::string strDir = "/SA/DebugLog/Controller";
#ifdef _WINDOWS
        InitializeCriticalSection(&m_cs);
        EnterCriticalSection(&m_cs);

        CreateDirectory(strDir.c_str(), NULL);
#else
        pthread_mutex_init(&m_mutex, NULL);
        pthread_mutex_lock(&m_mutex);

        mkdir(strDir.c_str(), 0644);
#endif //_WINDOWS

        m_strLogfile = strDir + "/Controller.log";
        if (!m_pOfs)
        {
            m_pOfs = new  std::ofstream(m_strLogfile, std::ios::ate | std::ios::app);
        }
        m_clockStart = clock();

#ifdef _WINDOWS
        LeaveCriticalSection(&m_cs);
#else
        pthread_mutex_unlock(&m_mutex);
#endif //_WINDOWS
    }

    ~CRuntimeLog()
    {
        double dTimeElapsed = (double)(clock() - m_clockStart) / CLOCKS_PER_SEC * 1.0;
        WriteLog("RuntimeLog: %s %f %s %s", m_strLogfile.c_str(), dTimeElapsed,
            __LINE__, __FUNCTION__, __FILE__);

#ifdef _WINDOWS
        EnterCriticalSection(&m_cs);
#else
        pthread_mutex_lock(&m_mutex);
#endif //_WINDOWS

        if (m_pOfs)
        {
            delete m_pOfs;
            m_pOfs = NULL;
        }

#ifdef _WINDOWS
        LeaveCriticalSection(&m_cs);
        DeleteCriticalSection(&m_cs);
#else
        pthread_mutex_unlock(&m_mutex);
        pthread_mutex_destroy(&m_mutex);
#endif // _WINDOWS
    }


private:

#ifdef _WINDOWS
    CRITICAL_SECTION m_cs;
#else
    pthread_mutex_t m_mutex;
#endif // _WINDOWS

    std::ofstream *m_pOfs;
    std::string m_strLogfile;
    clock_t m_clockStart;
};




#ifdef _DEBUG
#define WRITE_LOG(fmt, ...) \
    (CRuntimeLog::Instance().WriteLog(fmt, __VA_ARGS__))
#else
#define WRITE_LOG(fmt, ...)
#endif //_DEBUG

#endif // CRUNTIMELOG_H

