/*
 * @(#) SwapVariable.java        Version: -    Date: 2018-06-09 18:19:06
 *
 * Copyright (C), 2018, Def Tech. Co., Ltd.
 *
 * Description:     java没有类类型变量，看似类类型变量实则都是引用类型, java没有显式的类类型变量.
 *
 *    从c++代码被编译输出汇编码后可以看出:
 *    非引用类型变量用本身唯一代表一个数据存储区; 引用类型变量用本身唯一代表被引用者所代表的存储区;
 *    变量本身就是所代表的存储区的起始地址, 地址值在运行期初始化时或编译期被指定，一旦地址确定则不可更改.
 *
 *    指针类型的变量, 简称"指针", 指针变量唯一代表的数据存储区存储着指针所指变量的地址, 访问指针所指的变量要经过解引用运算.

 *
 *    java和c++类似又有不同:
 *    java中非引用类型的变量用本身唯一代表一个数据存储区, 变量本身就是所代表的存储区的起始地址. 地址值在运行期初始化时被指定，一旦地址确定则不可更改.
 *    java中引用类型的变量用本身唯一代表被引用者所代表的存储区, 变量本身就是所代表的存储区的起始地址. 地址值在运行期被初始化为null，并且允许更改.
 *
 *    java 弃用了c++的指针概念, 没有解引用运算
 *
 *
 *    至此， java的数据类型可以总结如下:
 *                                    /定点数byte/short/int/long
 *                                   | 浮点数float/double
 *                     --基本数据类型+ 布尔类型boolean
 *                   |              |
 *     java数据类型 -+              \字符类型char
 *                   \
 *                    --引用类型 (32bit虚拟机引用类型size为4byte,64bit虚拟机引用类型size为8byte)
 *
 *
 * Others:          ///< 其它内容的说明
 * Function List:   ///< 主要函数及其功能
 *   1. --------
 * History:        ///< 历史修改记录
 *   <author>  <time>   <version >   <desc>
 * 1. libin  2018.06.09  1.0   build this moudle
 */


import java.lang.reflect.Field;

/**
 *  反射特性可以实现简单的数据交换(swap).
 *
 * <p>C++中经典的swap案例利用了C++的引用/指针达到了数据交换目的, 但是
 * java没有指针类型变量，不支持指针解引用, 而且java的引用也与C++不同，
 * 实现数据调换需求只能依靠java的反射特性.
 *
 *
 * @author libin  2018.06.10
 * @version 1.0
 *
 */
public class SwapVariable {
    public static void main(String [] args) {
        int a = 100;
        int b = 900;
        System.out.println("Swap int:");
        System.out.println("Before SwapInt, a = " + a + ", b = " + b);
        SwapInt(a, b);
        System.out.println(" After SwapInt, a = " + a + ", b = " + b);
        System.out.println();

        System.out.println("Swap Integer:");
        Integer oa = 100;
        Integer ob = 900;
        System.out.println("Before SwapInteger, oa = " + oa + ", ob = " + ob);
        SwapInteger(oa, ob);
        System.out.println(" After SwapInteger, oa = " + oa + ", ob = " + ob);
        System.out.println();

        System.out.println("Swap String:");
        String stra = "AAAAA";
        String strb = "BBBBB";
        System.out.println("Before SwapString, stra = " + stra + ", strb = " + strb);
        SwapString(stra, strb);
        System.out.println(" After SwapString, stra = " + stra + ", strb = " + strb);
        System.out.println();


        System.out.println("Swap Integer by reflect:");
        oa = 100;
        ob = 900;
        System.out.println("Before SwapIntegerByReflect, oa = " + oa + ", ob = " + ob);
        SwapIntegerByReflect(oa, ob);
        System.out.println(" After SwapIntegerByReflect, oa = " + oa + ", ob = " + ob);
    }


    public static void SwapInt(int x, int y) {
        System.out.println("1: x = " + x + ", y = " + y);
        int z = x;
        x = y;
        y = z;
        System.out.println("2: x = " + x + ", y = " + y);
    }


    public static void SwapInteger(Integer ox, Integer oy) {
        if (ox == null || oy == null) {
            System.out.println("=====Null Pointer Exception=====");
            return;
        }

        System.out.println("1: ox = " + ox + ", oy = " + oy);
        Integer oz = ox;
        ox = oy;
        oy = oz;
        System.out.println("2: ox = " + ox + ", oy = " + oy);
    }


    public static void SwapString(String strx, String stry) {
        if (strx != null && stry != null) {
            System.out.println("1: strx = " + strx + ", stry = " + stry);
            String strz = strx;
            strx = stry;
            stry = strz;
            System.out.println("1: strx = " + strx + ", stry = " + stry);
        }
        else {
            System.out.println("=====Null Pointer Exception=====");
        }
    }


    /**
     *  Swap data by reflect.
     * <p> ///< This is an example, please try
     *     ///< swap String object later.
     *
     * @param   ox [in,out]
     * @param   oy [in,out]
     *
     * @author libin  2018.06.10
     * @version 1.0
     *
     */
    public static void SwapIntegerByReflect(Integer ox, Integer oy) {
        if (ox != null && oy != null) {
            Class<Integer> integerClass = (Class<Integer>)ox.getClass();
            try {
                Field value = integerClass.getDeclaredField("value");
                value.setAccessible(true);
                //Integer oz = ox; // ERROR; 此语句造成oz引用ox，导致value.setInt(oy, oz);等效于value.setInt(oy, ox);
                int oz = ox;
                value.setInt(ox, oy);
                value.setInt(oy, oz);
            }
            catch (NoSuchFieldException e) {
                e.printStackTrace();
            }
            catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        }
        else {
            System.out.println("=====Null Pointer Exception=====");
        }
    }

}

