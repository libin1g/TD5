/*
 * @(#) FactoryRegister.cpp        Version: -    Date: 2019-03-27 17:56:56
 *
 * Copyright (C), 2019, HollySys Co., Ltd. All rights reserved.
 *
 * Description:     向PrtclFactory/DeviceFactory/DriverFactory注册驱动实现类
 *
 * Others:          ///< 其它内容的说明
 * Function List:   ///< 主要函数及其功能
 *   1. --------
 * History:        ///< 历史修改记录
 *   <author>  <time>   <version >   <desc>
 * 1. libin  2019.03.27  1.0   build this moudle
 */

#include "SNMPDriver.h"
#include "SNMPDevice.h"
#include "SNMPPrtcl.h"

namespace MACS_SCADA_SUD
{
    extern "C" MACS_DLL_EXPORT int InitDll()
    {
        GENERIC_REGISTER_CLASS(CIOPrtclParserBase, CSNMPPrtcl, &g_DrvPrtclFactory);
        GENERIC_REGISTER_CLASS(CIODeviceBase, CSNMPDevice, &g_DrvDeviceFactory);
        GENERIC_REGISTER_CLASS(CIODriverBase, CSNMPDriver, &g_IODriverFactory);

        return 0;
    }

    extern "C" MACS_DLL_EXPORT int UnInitDll()
    {
        GENERIC_UNREGISTER_CLASS(CIOPrtclParserBase, CSNMPPrtcl, &g_DrvPrtclFactory);
        GENERIC_UNREGISTER_CLASS(CIODeviceBase, CSNMPDevice, &g_DrvDeviceFactory);
        GENERIC_UNREGISTER_CLASS(CIODriverBase, CSNMPDriver, &g_IODriverFactory);

        return 0;
    }

}
