#ifndef TEA_H
#define TEA_H

#include <string>
#include <fstream>

#include <winsock2.h>

using namespace std;

// TEA operates on two 32-bit unsigned integers 
// (could be derived from a 64-bit data block) and uses a 128-bit(16-byte) key. 
const unsigned short BYTES_OF_KEY = 16;
const unsigned short BYTES_OF_DATA_BLOCK = 8;

typedef unsigned char byte;
typedef unsigned int uint32;

class TEA 
{
public:
    TEA(const byte *key, int nRound = 32, bool bNetByte = false);
    ~TEA();
    TEA(const TEA &rhs);
    TEA& operator=(const TEA &rhs);
    void SetKey(const byte *key);
    const byte* Key() const;
    bool IsValid() const;
    void Encrypt(const byte *in, byte *out);
    void Decrypt(const byte *in, byte *out);
    static ofstream& LogStream()
    {
        if (!m_ofsp)
        {
            m_ofsp = new ofstream("TEA.log", ios::ate | ios::app);
        }
        return *m_ofsp;
    }

private:
    void Encrypt(const uint32 *in, uint32 *out, uint32 *k);
    void Decrypt(const uint32 *in, uint32 *out, uint32 *k);
    uint32 NetToHost(uint32 netlong) { return m_bNetByte ? ntohl(netlong) : netlong; }
    uint32 HostToNet(uint32 hostlong) { return m_bNetByte ? htonl(hostlong) : hostlong; }
    static std::string BytesToHexString(const byte aBytes[] , int nSize);

private:
    int m_nRound; //iteration round to encrypt or decrypt
    bool m_bNetByte; //whether input bytes come from network
    byte m_key[BYTES_OF_KEY]; //encrypt or decrypt key

    static ofstream* m_ofsp;
};

#endif //TEA_H