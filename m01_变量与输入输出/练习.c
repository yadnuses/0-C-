#include <stdio.h>

int main(void)
{
    /* 练习1：声明一个变量 myAge 存你的年龄，并打印
       提示：先 int myAge = ...; 再用 printf 配 %d 打印整数 */
    // TODO: 在这里写代码


    /* 练习2：读入两个整数 a 和 b，输出 和、差、积、商、余数
       提示：
         - 一次读两个：scanf("%d %d", &a, &b);  变量前别忘了 &
         - 五个结果分别用 a+b、a-b、a*b、a/b、a%b
         - ⚠️ a/b 是整数除法（结果取整）；a%b 是取余，两边必须是整数 */
    int a, b;
    printf("请输入两个整数(用空格隔开): ");
    // TODO: 用 scanf 读入 a 和 b

    // TODO: 分别打印 a+b, a-b, a*b, a/b, a%b


    /* 练习3：体会整数除法 vs 浮点除法
       提示：打印 5/2 的结果（用 %d）和 5.0/2 的结果（用 %.1f），观察差别 */
    // TODO: 在这里写代码


    return 0;
}
