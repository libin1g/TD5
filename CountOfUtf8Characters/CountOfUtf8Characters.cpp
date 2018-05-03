#include <iostream>
#include <fstream>
#include <string>


size_t LengthOfString(const char* pstr)
{
    size_t BytesOfCharacter(char firstByteOfCharacter);
    size_t nCount = 0;
    for (nCount = 0; *pstr; nCount++)
    {
        pstr += BytesOfCharacter(*pstr);
    }
    return nCount;
}

size_t BytesOfCharacter(char firstByteOfCharacter)
{
    size_t nCount = 0;
    for (nCount = 0; firstByteOfCharacter & 0x80; nCount++)
    {
        firstByteOfCharacter <<= 1; 
    }
    if (nCount > 6 || nCount < 2 )
    {
        nCount = 1;
    }
    return nCount;
}


int main(int argc, char* argv[])
{
    std::ifstream ifs;
    for (int i = 1; i < argc; ++i)
    {
        ifs.open(*(argv + i), std::ios::binary);
        if (ifs.rdstate() & std::ios::failbit)
        {
            std::cerr << "Failed to open file "
                << "'" 
                << *(argv + i) 
                << "'"
                << std::endl;
            continue;
        }

        ifs.seekg(0, std::ios::end);
        size_t fileSize = ifs.tellg();
        std::cout << i << " " << "File: " << *(argv + i) << " " 
            << "Size: " << fileSize / 1024 << "KB" << std::endl;
        ifs.seekg(std::ios::beg);

        char buf[64];
        size_t countOfCharecters = 0;
        size_t byteRead = 0;
        std::string str;
        while (ifs.good())
        {
            memset(buf, 0, sizeof(buf));
            ifs.read(buf, sizeof(buf));
            byteRead += ifs.gcount();
            float f = byteRead * 1.0f / fileSize * 1.0f;
            std::cout << "\r";
            std::cout << "Process[" << byteRead 
                << "/" << fileSize << "] " << std::flush;
            for (int i = 0; i < f * 40; ++i)
            {
                std::cout << "#" << std::flush;
            }
            std::cout << int(f * 100) << "%" << std::flush;

            for (int i = 0; i < sizeof(buf); ++i)
            {
                str.push_back(buf[i]);
                if (buf[i] == '\0')
                {
                    countOfCharecters += LengthOfString(str.c_str());
                    str.clear();
                }
            }
        }
        std::cout << std::endl;
        std::cout << "Total " << countOfCharecters << " characters " << std::endl;
        ifs.close();
    }

    if (argc < 2)
    {
        std::cout << "\tUsage:  CountOfUtf8Characters <file1> <file2> ..."  << std::endl
            << "\t用法:  CountOfUtf8Characters <文件1> <文件2> ..." << std::endl;
    }

    return 0;
}
