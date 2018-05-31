/*************************************************

- File name: GotoExercise.java
- Author: libin  Version: -       Date: 2018-05-31 20:20:13
- Description:
        1. java没有goto语句，并且将goto作为其保留字
        2. java允许break/continue带有label，以支持必要的原本goto语句才能实现的跳转(跳转只能识别函数内定义的label)
        3. 因为break只能用在switch/while/do...while/for块语句中
        4. 因为continue只能用在while/do...while/for块语句中
        5. 所以只能给switch/while/do...while/for块语句定义label

- Others:
- Function List:
    1. --------
- History:        // 历史修改记录
    <author>  <time>   <version >   <desc>
  1.libin  2018.05.31  1.0   build this moudle
*************************************************/

public class GotoExercise {

    public static void main(String[] args) {

        /*立即跳出label所标记的循环*/
        BreakTheOuterLoop();

        /*立即进入label所标记的循环的下一轮循环*/
        ContinueTheOuterLoop();

        /*立即跳出label所标记的switch语句块*/
        BreakToSwitchOuter(0);

    }


    public static void BreakTheOuterLoop() {
        System.out.println("\n----------BreakTheOuterLoop Enter----------");
        /* This is the outer loop marked by LABEL1 */
        int i = 0;
LABEL1: while (i < 5) {
            System.out.print("In while loop, loop variable i = " + i + '\n');
            /* This is the inner loop */
            for (int j = 0; j < 50; ++j) {
                System.out.print("In for loop, loop variable j = " + j + '\n');
                if (j > 6) {
                    /* 从LABEL1所标记的循环跳出*/
                    System.out.print("In for loop, break the outer loop marked by LABEL1.\n");
                    break LABEL1;
                }
            }
            ++i;
        }
        System.out.println("----------BreakTheOuterLoop Exit----------");
    }


    public static void ContinueTheOuterLoop() {
        System.out.println("\n**********ContinueTheOuterLoop Enter**********");
        /* This is the outer loop marked by LABEL2 */
LABEL2: for (int i = 0; i < 5; ++i) {
            System.out.print("In outer for loop, loop variable i = " + i + '\n');
            /* This is the inner loop */
            for (int j = 0; j < 50; ++j) {
                System.out.print("In inner for loop, loop variable j = " + j + '\n');
                if (j > 6) {
                    /* 让LABEL2所标记的循环进入下一轮循环*/
                    System.out.print("In inner for loop, continue the outer for loop marked by LABEL2.\n");
                    continue LABEL2;
                }
            }
        }
        System.out.println("**********ContinueTheOuterLoop Exit**********");
    }


    public static void BreakToSwitchOuter(int n) {

        System.out.println("\n##########BreakToSwitchOuter Enter##########");
        /* This is the outer switch marked by LABEL3 */
LABEL3:switch (n) {
            case 0:
            case 1:
                {
                    System.out.println("In outer switch block, n = " + n);
                    int m = n + 1;
                    /* This is the inner switch */
                    switch (m) {
                        case 1:
                            System.out.println("In inner switch block, m = " + m);
                            /* 从LABEL3所标记的switch语句块跳出*/
                            System.out.println("In inner switch block, break the outer switch marked by LABEL3.");
                            break LABEL3;
                        default:
                            System.out.println("In inner switch block, default switch.");
                            /* 从当前的switch语句块跳出*/
                            break;
                    }
                }
            case 2:
                System.out.println("In outer switch block, n = " + n);
                /* 从当前的switch语句块跳出*/
                break;
            default:
                System.out.println("In outer switch block, default switch.");
                /* 从当前的switch语句块跳出*/
                break;
        }

        System.out.println("##########BreakToSwitchOuter Exit##########");
    }

}
