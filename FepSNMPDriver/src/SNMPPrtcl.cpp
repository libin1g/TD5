#include "SNMPPrtcl.h"

namespace MACS_SCADA_SUD
{
    std::string CSNMPPrtcl::s_strClassName = "CSNMPPrtcl";


    std::string CSNMPPrtcl::GetClassName()
    {
        return s_strClassName;
    }


    OpcUa_Int32 CSNMPPrtcl::BuildRequest(OpcUa_Byte *pByteData, OpcUa_Int32 nDataLen)
    {

        return 0;
    }


    bool CSNMPPrtcl::ExtractPacket(OpcUa_Byte *pPacketBuf, OpcUa_Int32 *pPacketLen)
    {

        return 0;
    }


    void CSNMPPrtcl::ProcessRcvdPacket(OpcUa_Byte *pPacketBuf, OpcUa_Int32 nPacketLen, bool bFromLocal)
    {

    }


}