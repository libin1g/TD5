/*
 * @(#) ReferenceExercise.cpp        Version: -    Date: 2018-06-08 08:45:43
 *
 *
 *
 * Description:  引用类型必须被初始化
 *
 * Others:          ///< 其它内容的说明
 * Function List:   ///< 主要函数及其功能
 *   1. --------
 * History:        ///< 历史修改记录
 *   <author>  <time>   <version >   <desc>
 * 1. libin180956  2018.06.08  1.0   build this moudle
 */

#include <iostream>

void foo(const int &r = 99)
{
    std::cout << "foo# param [in] const int &r = " << r << std::endl;
    std::cout << "#void foo(const int &r = 99) called#" << std::endl;
}

/*
 * 函数形参带缺省值引发对重载函数的调用不明确
 *
ReferenceExercise.cpp(44) : error C2668: “foo”: 对重载函数的调用不明确
        ReferenceExercise.cpp(30): 可能是“void foo(void)”
        ReferenceExercise.cpp(18): 或       “void foo(const int &)”
        尝试匹配参数列表“(void)”时
*/
//void foo(void)
void foo(char)
{
    std::cout << "#void foo() called#" << std::endl;
}

int main(int argc, char **argv)
{
    int a = 0;
    int b = 1;
    std::cout << "int a = " << a << "\t int b = " << b << std::endl;
    int &ra = a;
    std::cout << "int ra = " << ra << std::endl;

    foo(60);
    foo('a');

    return 0;
}

