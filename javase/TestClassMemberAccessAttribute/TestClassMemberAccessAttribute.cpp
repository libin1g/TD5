/*
 * @(#) TestClassMemberAccessAttribute.cpp        Version: -    Date: 2018-06-12 09:52:25
 *
 * Copyright (C), 2018, Def Tech. Co., Ltd.
 *
 * Description:     ///< 描述本文件的内容、功能、内容各部分之间的关系
 *                  ///< 及本文件与其他文件关系等
 * Others:          ///< 其它内容的说明
 * Function List:   ///< 主要函数及其功能
 *   1. --------
 * History:        ///< 历史修改记录
 *   <author>  <time>   <version >   <desc>
 * 1. libin180956  2018.06.12  1.0   build this moudle
 */

#include <iostream>

class A {
    public:
        void bar() {
            std::cout << "A::bar() called." << std::endl;
            foo();
            this->foo();
        }
    private:
        virtual void foo()
        {
            std::cout << "A::foo() called." << std::endl;
        }
};

class A1 : public A {
    private:
        void foo()
        {
            std::cout << "A1::foo() called." << std::endl;
        }
};


int main(int argc, char *argv[])
{
    A1 a1;
    //a1.foo(); // error C2248: “A1::foo”: 无法访问 private 成员(在“A1”类中声明)
    A &a = a1;
    a.bar();

    return 0;
}
