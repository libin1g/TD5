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

#include <iostream>

#ifdef _DEBUG
#define WRITE_LOG(fmt, ...) \
    (CRuntimeLog::Instance().WriteLog(fmt, __VA_ARGS__))
#else
#define WRITE_LOG(fmt, ...)
#endif // _DEBUG


class CRuntimeLog
{
public:
    static CRuntimeLog & Instance()
    {
        static CRuntimeLog m_instance;
        return m_instance;
    }

public:
    CRuntimeLog()
    {
        static CMutex mutex;
        static LogFile file;
        if (!m_pMutex || !m_pfile)
        {
            m_pMutex = &mutex;
            m_pfile = &file;
        }
        m_clockStart = clock();
    }

    ~CRuntimeLog()
    {
        double dTimeElapsed = (double)(clock() - m_clockStart) / CLOCKS_PER_SEC * 1.0;
        WriteLog("RuntimeLog: Time Elapsed: %f second(s)", dTimeElapsed);
    }


    void WriteLog(const char* pfmt, ...)
    {
        if (m_pfile->path.empty())
        {
            m_pfile->path = "/SCADA/DebugLog/BMFUtilities/";
            m_pfile->name = "BMFUtilities";
            m_pfile->extname = ".log";
#ifdef _WINDOWS
        CreateDirectory(m_pfile->path.c_str(), NULL);
#else
        mkdir(m_pfile->path.c_str(), 0644);
#endif //_WINDOWS
        }

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

        char timeStr2[256];
        memset(timeStr2, 0, sizeof(timeStr2));
        snprintf(timeStr2, sizeof(timeStr2), "%04u%02u%02u%02u%02u%02u",
            st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
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

        char timeStr2[256];
        memset(timeStr2, 0, sizeof(timeStr2));
        strftime(timeStr2, sizeof(timeStr2), "%Y%m%d%H%M%S", timeinfo);
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

        m_pMutex->lock();
        if (!m_pfile->pOfs)
        {
            m_pfile->pOfs = new  std::ofstream((m_pfile->path + "/" + m_pfile->name + m_pfile->extname),
                std::ios::ate | std::ios::app);
        }
        m_pfile->pOfs->write(logbuf, strlen(logbuf));
        m_pfile->pOfs->flush();
        if (m_pfile->pOfs->tellp() > 2 * 1024 * 1024)
        {
            m_pfile->pOfs->close();
            delete m_pfile->pOfs;
            m_pfile->pOfs = NULL;

            rename((m_pfile->path + "/" + m_pfile->name + m_pfile->extname).c_str(),
                (m_pfile->path + "/" + m_pfile->name + timeStr2 + m_pfile->extname).c_str());
        }
        m_pMutex->unlock();
    }

private:
    class CMutex
    {
    public:
        CMutex()
        {
#ifdef _WINDOWS
            InitializeCriticalSection(&m_cs);
#else
            pthread_mutex_init(&m_mutex, NULL);
#endif //_WINDOWS
        }

        ~CMutex()
        {
#ifdef _WINDOWS
            DeleteCriticalSection(&m_cs);
#else
            pthread_mutex_destroy(&m_mutex);
#endif // _WINDOWS
        }

    public:
        void lock()
        {
#ifdef _WINDOWS
            EnterCriticalSection(&m_cs);
#else
            pthread_mutex_lock(&m_mutex);
#endif // _WINDOWS
        }

        void unlock()
        {
#ifdef _WINDOWS
            LeaveCriticalSection(&m_cs);
#else
            pthread_mutex_unlock(&m_mutex);
#endif // _WINDOWS
        }

    private:
#ifdef _WINDOWS
        CRITICAL_SECTION m_cs;
#else
        pthread_mutex_t m_mutex;
#endif // _WINDOWS
    } *m_pMutex;

    struct LogFile
    {
        std::string path;
        std::string name;
        std::string extname;
        std::ofstream *pOfs;
        LogFile():path(""), name(""),extname(""),pOfs(NULL)
        {}
    } *m_pfile;

private:
    clock_t m_clockStart;
};
#endif // CRUNTIMELOG_H
