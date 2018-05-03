#include "tea.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stdarg.h>
#include <time.h>


#ifdef _DEBUG
#define WRITE_LOG _writelog

void _writelog(const char* pfmt, ...)
{
    char timeBuf[128];
    memset(timeBuf, 0, sizeof(timeBuf));
    time_t t;
    struct tm* timeinfo;

    time(&t);
    timeinfo = localtime(&t);
    strftime(timeBuf, sizeof(timeBuf), "%Y.%m.%d %H:%M:%S %Z", timeinfo);

    va_list vl;
    va_start (vl, pfmt);
    char logBuf[256];
    memset(logBuf, 0, sizeof(logBuf));
    vsnprintf(logBuf, sizeof(logBuf), pfmt, vl);
    va_end(vl);

    char buf[512];
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s:  %s \n", timeBuf, logBuf);
    TEA::LogStream().write(buf, strlen(buf));
    TEA::LogStream().flush();
}

#else
#define WRITE_LOG
#endif



ofstream* TEA::m_ofsp = NULL;

/**
*	\brief	 TEA构造函数
*
*
*	\param	key - 加密或解密用的128-bit(16byte)密钥
*	\param	round - 加密或解密的轮数，常用的有64，32，16
*   \param  isNetByte - 用来标记待处理的字节是不是来自网络，为true时在加密/解密前
*                       先要转换成本地字节，执行加密/解密，然后再转换回网络字节
*	\retval	
*
*   \note  
*/
TEA::TEA(const byte *key, int nRound /*= 32*/, bool bNetByte /*= false*/)
    : m_nRound(nRound), m_bNetByte(bNetByte) 
{
    SetKey(key);
}

TEA::~TEA()
{
    if (m_ofsp)
    {
        if (m_ofsp->is_open())
        {
            m_ofsp->close();
        }
        delete m_ofsp;
        m_ofsp = NULL;
    }
}


TEA::TEA(const TEA &rhs) : m_nRound(rhs.m_nRound)
    ,m_bNetByte(rhs.m_bNetByte) 
{
    memcpy(m_key, rhs.m_key, 16);
}


TEA& TEA::operator=(const TEA &rhs) 
{
    if (&rhs != this) 
    {
        m_nRound = rhs.m_nRound;
        m_bNetByte = rhs.m_bNetByte;
        memcpy(m_key, rhs.m_key, 16);
    }

    return *this;
}


void TEA::SetKey(const byte *key)
{
    if (key != 0)
    {
        memcpy(m_key, key, 16);
    }
    else
    {
        memset(m_key, 0, 16);
    }
}

const byte* TEA::Key() const
{
    return m_key;
}

bool TEA::IsValid() const
{
    bool bValid = false;
    /*算法以长度为4字节的unsigned int存放临时数据参与计算*/ 
    if (sizeof(unsigned int) == 4)
    {
        bValid = true;
    }
    else
    {
        bValid = false;
        WRITE_LOG("ERROR: The algorithm assumes that the sizeof(unsigned int) is 4."
            "(Actually is %d)", sizeof(unsigned int));
    }
    return bValid;
}


void TEA::Encrypt(const byte *in, byte *out) 
{
    WRITE_LOG("TEA::Encrypt  IN:[%s] deal with encrypt key:[%s]", 
        BytesToHexString(in, BYTES_OF_DATA_BLOCK).c_str(), 
        BytesToHexString(m_key, BYTES_OF_KEY).c_str());

    Encrypt((uint32*)in, (uint32*)out, (uint32*)m_key);

    WRITE_LOG("TEA::Encrypt OUT:[%s]", 
        BytesToHexString(out, BYTES_OF_DATA_BLOCK).c_str());
}


void TEA::Decrypt(const byte *in, byte *out) 
{
    WRITE_LOG("TEA::Decrypt  IN:[%s] deal with decrypt key:[%s]", 
        BytesToHexString(in, BYTES_OF_DATA_BLOCK).c_str(), 
        BytesToHexString(m_key, BYTES_OF_KEY).c_str());

    Decrypt((uint32*)in, (uint32*)out, (uint32*)m_key);

    WRITE_LOG("TEA::Decrypt OUT:[%s]", 
        BytesToHexString(out, BYTES_OF_DATA_BLOCK).c_str());
}


void TEA::Encrypt(const uint32 *in, uint32 *out, uint32 *k) 
{
    register uint32 y = NetToHost(in[0]);
    register uint32 z = NetToHost(in[1]);
    register uint32 a = NetToHost(k[0]);
    register uint32 b = NetToHost(k[1]);
    register uint32 c = NetToHost(k[2]);
    register uint32 d = NetToHost(k[3]);
    register uint32 delta = 0x9E3779B9; /* (sqrt(5)-1)/2*2^32 */
    register int round = m_nRound;
    register uint32 sum = 0;
 
    // basic cycle start
    while (round--) 
    {   
        sum += delta;
        y += ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
        z += ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);
    } // end cycle
    out[0] = NetToHost(y);
    out[1] = NetToHost(z);
}

void TEA::Decrypt(const uint32 *in, uint32 *out, uint32 *k) 
{
    register uint32 y = NetToHost(in[0]);
    register uint32 z = NetToHost(in[1]);
    register uint32 a = NetToHost(k[0]);
    register uint32 b = NetToHost(k[1]);
    register uint32 c = NetToHost(k[2]);
    register uint32 d = NetToHost(k[3]);
    register uint32 delta = 0x9E3779B9; /* (sqrt(5)-1)/2*2^32 */
    register int round = m_nRound;
    register uint32 sum = 0;

    if (round == 32)
    {
        sum = 0xC6EF3720; /* delta << 5*/
    }
    else if (round == 16)
    {
        sum = 0xE3779B90; /* delta << 4*/
    }
    else
    {
        double dValue = log(round * 1.0) / log(2 * 1.0);
        sum = delta << static_cast<int>(dValue);
    }

    // basic cycle start
    while (round--) 
    {
        z -= ((y << 4) + c) ^ (y + sum) ^ ((y >> 5) + d);
        y -= ((z << 4) + a) ^ (z + sum) ^ ((z >> 5) + b);
        sum -= delta;
    } // end cycle 
    out[0] = NetToHost(y);
    out[1] = NetToHost(z);
}


std::string TEA::BytesToHexString(const byte aBytes[] , int nSize) 
{
    static const char HEX[16] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F'
    };

    std::string strHexString = "";
    for (int i = 0; i < nSize; ++i) 
    {
        int t = aBytes[i];
        int a = t / 16;
        int b = t % 16;
        strHexString += HEX[a];
        strHexString += HEX[b];
        if (i != nSize - 1)
        {
            strHexString += ' ';
        }
    }

    return strHexString;
}
