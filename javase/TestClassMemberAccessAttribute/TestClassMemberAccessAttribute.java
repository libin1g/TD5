/*
 * @(#) TestClassMemberAccessAttribute.java        Version: -    Date: 2018-06-12 09:31:57
 *
 * Copyright (C), 2018, Def Tech. Co., Ltd.
 *
 * Description:     本例列举类成员的访控属性
 *                  ///< 描述本文件的内容、功能、内容各部分之间的关系
 *                  ///< 及本文件与其他文件关系等
 * Others:          ///< 其它内容的说明
 *        NOTE1: 派生类重写基类虚函数时缩小了虚函数的访控属性，编译器告error
 *        NOTE2: 派生类重写基类虚函数时扩大了虚函数的访控属性，编译通过
 * Function List:   ///< 主要函数及其功能
 *   1. --------
 * History:        ///< 历史修改记录
 *   <author>  <time>   <version >   <desc>
 * 1. libin180956  2018.06.12  1.0   build this moudle
 */

public class TestClassMemberAccessAttribute {
    public static void main(String [] args) {
        A base = new A1();
        base.foo();
        base.bar();
    }
}


class A {
    public void foo() {
        System.out.println("A#foo() called");
    }

    public void bar() {
        System.out.println("A#bar() called");
    }
}

class A1 extends A {

    /*
    */
    private void foo() {
        System.out.println("A1#foo() called");
    }

    protected void bar() {
        System.out.println("A1#bar() called");
    }
}
