/*
 * @(#) SNMPDriver.cpp        Version: -    Date: 2019-03-27 18:23:00
 *
 * Copyright (C), 2019, HollySys Co., Ltd. All rights reserved.
 *
 * Description:     ///< 描述本文件的内容、功能、内容各部分之间的关系
 *                  ///< 及本文件与其他文件关系等
 * Others:          ///< 其它内容的说明
 * Function List:   ///< 主要函数及其功能
 *   1. --------
 * History:        ///< 历史修改记录
 *   <author>  <time>   <version >   <desc>
 * 1. libin  2019.03.27  1.0   build this moudle
 */

#include "SNMPDriver.h"

namespace MACS_SCADA_SUD
{
    std::string CSNMPDriver::s_strClassName = "CSNMPDriver";


    std::string CSNMPDriver::GetClassName()
    {
        return s_strClassName;
    }


    /**
     *  ///< Brief description which ends at this dot.
     * <p> ///< Details description follow here, 1st line.
     *     ///< Details description follow here, 2st line.
     *
     * @param   [in]     ///< 输入参数说明, 包括每个参数的作用和
     *                   ///< 取值范围，以及各参数间关系
     * @param   [out]    ///< 输出参数说明
     * @param   [in,out] ///< 输入输出参数说明
     * @return           ///< 函数返回值说明
     *
     * @see class
     * @see #prop|func
     * @see class#prop|func
     *
     * @author libin  2019.03.27
     * @version 1.0
     *
     */
    OpcUa_Int32 CSNMPDriver::OpenChannel()
    {

        return 0;
    }


    OpcUa_Int32 CSNMPDriver::StartWork(void)
    {
        return 0;
    }

}
