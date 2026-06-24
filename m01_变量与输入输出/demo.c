#include <stdio.h>

int main(void)
{
    /* 1. 变量声明与赋值 */
    int age = 20;
    double price = 3.14;
    char grade = 'A';

    /* 2. printf 占位符配对 */
    printf("我 %d 岁，价格 %.2f，等级 %c\n", age, price, grade);

    /* 3. scanf 输入（注意 &） */
    int n;
    printf("请输入一个整数: ");
    scanf("%d", &n);
    printf("你输入的是 %d，它的平方是 %d\n", n, n * n);

    /* 4. 整数除法陷阱 */
    printf("5 / 2   = %d  (整数除法，结果取整)\n", 5 / 2);
    printf("5.0 / 2 = %.1f  (有小数参与，结果才是小数)\n", 5.0 / 2);
    printf("7 %% 3   = %d  (取余数)\n", 7 % 3);

    return 0;
}
