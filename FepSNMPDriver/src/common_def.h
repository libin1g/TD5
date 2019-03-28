/*
 * @(#) common_def.h        Version: -    Date: 2019-03-27 16:13:06
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
#ifndef COMMON_DEF_H
#define COMMON_DEF_H

#include "RTDB/Server/DBDriverFrame/IODriverH.h"

#ifdef FEPSNMPDRIVER_EXPORTS
#define FEPSNMPDRIVER_API MACS_DLL_EXPORT
#else
#define FEPSNMPDRIVER_API MACS_DLL_IMPORT
#endif

namespace MACS_SCADA_SUD
{

}

#endif //COMMON_DEF_H