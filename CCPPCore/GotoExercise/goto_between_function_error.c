/*************************************************
- File name: goto_between_function_error.c
- Author: libin180956  Version: -       Date: 2018-05-31 11:31:07
- Description:
    goto语句被当作破坏结构化程序的典型代表，在结构化程序设计年代，goto语句就像洪水猛兽一样，
    程序员都唯恐避之不及；可后来在微软的一些例子程序中经常把goto语句用来处理出错，当出错时，
    goto到函数要退出的一个label那里进行资源释放等操作。那么，goto语句是不是只可以用于出错处理，
    其他地方都不可以用了呢？下列关于使用goto语句的原则可以供参考。
    1) 使用goto语句只能goto到同一函数内，而不能从一个函数里goto到另外一个函数里。
    2) 使用goto语句在同一函数内进行goto时，goto的起点应是函数内一段小功能的结束处，
       goto的目的label处应是函数内另外一段小功能的开始处。
    3) 不能从一段复杂的执行状态中的位置goto到另外一个位置，比如，从多重嵌套的循环判断中跳出去就是不允许的。
    4）应该避免向两个方向跳转。这样最容易导致*面条代码*。
- Others:         // 其它内容的说明
- Function List:  // 主要函数列表，每条记录应包括函数名及功能简要说明
   1. ....
- History:        // 修改历史记录列表，每条修改记录应包括修改日期、修改
                  // 者及修改内容简述
    1. Date:
       Author:
       Modification:
    2. ...

*************************************************/

#include <stdio.h>

void foo();

int main(int argc, char *argv[])
{
    int count = 0;

LABEL1:
    printf("-------MAIN:ENTER-------------\n");
    count++;
    printf("-------MAIN:COUNT(%d)----------\n", count);
    //goto LABEL1; // OK
    foo();
    printf("------- MAIN:EXIT ------------\n");
    return 0;
}

void foo()
{
    int i = 0;

LABEL2:
    printf("-------FOO:ENTER-------------\n");
    ++i;
    printf("-------FOO:i(%d)----------\n", i);
    //goto LABEL1; // error C2094: 标签“LABEL1”未定义  /*只能跳转函数内LABEL*/
    //goto LABEL2; // OK
    printf("------- FOO:EXIT ------------\n");
}
