#include <stdio.h>

int main(void)
{
    /* 练习1：先原样编译运行这个文件，确认能看到下面这行输出
       终端执行（Mac/Linux）：
         cd m00_编译运行流程
         gcc 练习.c -o lx && ./lx
       Windows (PowerShell)：
         cd m00_编译运行流程
         gcc 练习.c -o lx.exe ; .\lx.exe
    */
    printf("我开始学C语言了！\n");

    /* 练习2：把下面的出生年份改成你自己的，
       存盘后【重新编译再运行】，体会"改完源码必须重编" */
    int birthYear = 2006;          // TODO: 改成你的出生年份
    printf("我出生于 %d 年。\n", birthYear);

    /* 练习3：在下面自己加一行 printf，打印任意一句话
       格式照抄上面，记得结尾 \n 和分号 ; */
    // TODO: 在这里写一行 printf


    return 0;
}
