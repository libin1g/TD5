#include "SNMPDevice.h"

namespace MACS_SCADA_SUD
{
    std::string CSNMPDevice::s_strClassName = "CSNMPDevice";
    
    std::string CSNMPDevice::GetClassName()
    {
        return s_strClassName;
    }
    
    
    OpcUa_Int32 CSNMPDevice::Init()
    {
        return 0;
    }
    
    
    void CSNMPDevice::SetInitValue()
    {
    
    }

}