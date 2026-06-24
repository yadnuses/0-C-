<div align="center">

# 🚀 0-C- 0基础上手C语言

### 练习驱动 · 喂饭级讲义

*从「Hello World」到「链表大题」，一条龙打通考研 C 语言*

<br>

[![新手上手指南](https://img.shields.io/badge/📖_新手上手指南-点这里开始-2A9D8F?style=for-the-badge)](https://hcne37wbg3ch.feishu.cn/docx/C1BgdlfLSoWXGNxKDUKcbuOynEf?from=from_copylink)

<br>

[![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![Compiler](https://img.shields.io/badge/Compiler-gcc-FF6C37?style=for-the-badge&logo=gnu&logoColor=white)](https://gcc.gnu.org/)
[![Exam](https://img.shields.io/badge/考研-408-E63946?style=for-the-badge)](#)
[![Level](https://img.shields.io/badge/难度-零基础友好-2A9D8F?style=for-the-badge)](#)

![Platform](https://img.shields.io/badge/Windows-0078D6?style=flat-square&logo=windows&logoColor=white)
![Platform](https://img.shields.io/badge/macOS-000000?style=flat-square&logo=apple&logoColor=white)
![Platform](https://img.shields.io/badge/Linux-FCC624?style=flat-square&logo=linux&logoColor=black)
![Modules](https://img.shields.io/badge/模块-13_个-blueviolet?style=flat-square)
![Style](https://img.shields.io/badge/风格-喂饭级-ff69b4?style=flat-square)

</div>

---

## ✨ 这套课程哪里不一样

<table>
<tr>
<td width="33%" align="center">

### 🍚 喂饭级讲解
每个概念**从零讲起**，生活类比 + 逐字拆解，不假设你有任何基础。

</td>
<td width="33%" align="center">

### ✍️ 练习驱动
每个模块配 `TODO` 练习，**只给思路不给答案**，逼你亲手敲、亲眼看结果。

</td>
<td width="33%" align="center">

### 🎯 对齐 408
专门标注**真题里的另一种形式**，考点 ⭐、易错坑 ⚠️ 一眼可见。

</td>
</tr>
</table>

---

## 📂 课程结构

每个模块是一个独立文件夹，里面有三类文件：

| 文件 | 作用 |
|:---|:---|
| 📖 `讲义.md` | 这一模块的知识点 + 考点 + 易错坑 |
| 🔬 `demo.c` | 写好的示例代码，编译运行看效果 |
| 📝 `练习.c` | 带 `TODO` 的题目，自己填空 / 补全 |

> 🧭 **学习四步法**：`读讲义` → `跑 demo` → `做练习` → `错题复盘`

---

## ⚡ 快速开始

> 💡 **第一次用？** 先打开 [`m00_编译运行流程/讲义.md`](m00_编译运行流程/讲义.md)，里面有 Windows / macOS / Linux 三平台的 **gcc 环境安装步骤**。

环境装好后，进任意模块文件夹执行：

<details open>
<summary><b>🍎 macOS / 🐧 Linux</b></summary>

```bash
cd m01_变量与输入输出            # 进入模块
gcc demo.c -o demo && ./demo     # 编译并运行 demo
gcc 练习.c -o lianxi && ./lianxi # 编译并运行你的练习
```
</details>

<details>
<summary><b>🪟 Windows（PowerShell）</b></summary>

```powershell
cd m01_变量与输入输出
gcc demo.c -o demo.exe ; .\demo.exe       # 编译并运行 demo
gcc 练习.c -o lianxi.exe ; .\lianxi.exe   # 编译并运行你的练习
```
</details>

> `gcc 源文件.c -o 输出名` 是编译；运行时 macOS/Linux 用 `./输出名`，Windows 用 `.\输出名.exe`。

---

## 🗺️ 课程大纲

> 按**考点权重**排序，⭐ 越多越爱考，🔴 表示难度高、需重点攻克。

| 模块 | 章节 | 核心内容 | 考点权重 | 难度 |
|:---:|:---:|:---|:---:|:---:|
| **M0** | §1.2 | 编译运行流程 + 环境搭建 | ⭐ | 🟢 |
| **M1** | 第1-2章 | 程序结构、变量、`printf`/`scanf`、运算符 | ⭐⭐ | 🟢 |
| **M2** | 第3章 | 分支：`if`/`else`/`switch`、关系与逻辑运算 | ⭐⭐⭐ | 🟢 |
| **M3** | 第4章 | 循环：`for`/`while`/`do-while`、break/continue | ⭐⭐⭐ | 🟡 |
| **M4** | 第5章 | 函数：定义/调用/传参、作用域、递归入门 | ⭐⭐⭐ | 🟡 |
| **M5** | 第6章 | 🔥 **数据类型陷阱**：补码、类型转换、表达式求值 | ⭐⭐⭐⭐ | 🔴 |
| **M6** | 第7章 | 数组：一维/二维、字符串基础 | ⭐⭐⭐ | 🟡 |
| **M7** | 第8章 | 🔥 **指针**：地址、解引用、指针与数组、传址 | ⭐⭐⭐⭐⭐ | 🔴 |
| **M8** | 第9章 | 结构体：`struct`、结构数组、成员访问 | ⭐⭐⭐ | 🟡 |
| **M9** | 第10章 | 程序结构：递归（汉诺塔）、宏、多文件 | ⭐⭐⭐ | 🟡 |
| **M10** | 第11章 | 🔥 **指针进阶 + 链表**：动态内存、字符指针 | ⭐⭐⭐⭐⭐ | 🔴 |
| **M11** | 第12章 | 文件读写：`fopen`/`fscanf`/`fwrite` | ⭐⭐ | 🟡 |
| **M12** | 附录A | 语法总复习 + 真题模拟 | ⭐⭐⭐⭐ | 🔴 |

---

## 🐯 三个「拦路虎」

> 考研 C 语言失分集中在这三处，到了要放慢节奏、多做题。

```
┌─────────────────────────────────────────────────────────┐
│  M5  数据类型陷阱   补码、类型转换、-1 的存储 —— 选择题高频坑   │
│  M7  指针          C 语言的命门，理解它之后全盘皆通          │
│  M10 链表          指针实战，大题常考，必须画箭头图          │
└─────────────────────────────────────────────────────────┘
```

---

## 🏷️ 标记约定

| 符号 | 含义 | | 符号 | 含义 |
|:---:|:---|---|:---:|:---|
| ⭐ | 考点（选择 / 填空） | | 📝 | 配套练习题 |
| ⚠️ | 易错坑（改错题常出） | | 🎯 | 真题 / 模拟题 |

---


<div align="center">

**参考资料**：翁恺《C语言程序设计》 · 何钦铭 / 颜晖教材 · 2025 计算机学科专业基础考试大纲


</div>
