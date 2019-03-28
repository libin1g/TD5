/*
 * @(#) SNMPPrtcl.h        Version: -    Date: 2019-03-27 17:23:38
 *
 * Copyright (C), 2019, HollySys Co., Ltd. All rights reserved.
 *
 * Description:     ///< 用于详细说明此程序文件完成的主要功能，与其他模块
 *                  ///< 或函数的接口，输出值、取值范围、含义及参数间的控
 *                  ///< 制、顺序、独立或依赖等关系
 * Others:          ///< 其它内容的说明
 * Function List:   ///< 主要函数列表，每条记录应包括函数名及功能简要说明
 *  1. ....
 * History:        ///< 修改历史记录列表，每条修改记录应包括修改日期、修改
 *                 ///< 者及修改内容简述
 *   1. Date:
 *      Author:
 *      Modification:
 *   2. ...
 */

#ifndef SNMPPRTCL_H
#define SNMPPRTCL_H

#include "common_def.h"
#include "RTDB/Server/DBDriverFrame/IOPrtclParser.h"

namespace MACS_SCADA_SUD
{
    class FEPSNMPDRIVER_API CSNMPPrtcl : public CIOPrtclParser
    {
        public:
            std::string GetClassName();
            virtual OpcUa_Int32 BuildRequest(OpcUa_Byte *pByteData, OpcUa_Int32 nDataLen);
            virtual bool ExtractPacket(OpcUa_Byte *pPacketBuf, OpcUa_Int32 *pPacketLen);
            virtual void ProcessRcvdPacket(OpcUa_Byte *pPacketBuf, OpcUa_Int32 nPacketLen, bool bFromLocal);

        public:
            static std::string s_strClassName;
    };

}

#endif // SNMPPRTCL_H

