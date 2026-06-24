/* ============================================================
 * M10 debug —— 指针进阶与链表实战 Debug
 * ------------------------------------------------------------
 * 链表和动态内存是考研大题的高频考点，也是 bug 重灾区。
 * 每个场景模拟一道"改错题"——代码里有故意隐患，
 * 你需要找出问题并修复。
 *
 * 编译运行：
 *   gcc debug.c -o debug
 *   ./debug
 *
 * 约 2/3 的 bug 不会导致编译报错，但运行结果不对或内存泄漏。
 * 用 valgrind 检测内存泄漏：
 *   valgrind --leak-check=full ./debug
 * （Mac 上可以用 `leaks -atExit -- ./debug`）
 * ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- 链表节点定义（考研标准结构） ---- */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* ---- 辅助函数：创建新节点 ---- */
Node *create_node(int data)
{
    Node *new = (Node *)malloc(sizeof(Node));
    if (new == NULL) {
        printf("   内存分配失败！\n");
        return NULL;
    }
    new->data = data;
    new->next = NULL;
    return new;
}

/* ---- 辅助函数：打印链表 ---- */
void print_list(Node *head)
{
    printf("   链表: ");
    for (Node *p = head; p != NULL; p = p->next) {
        printf("%d -> ", p->data);
    }
    printf("NULL\n");
}

/* ---- 辅助函数：释放链表 ---- */
void free_list(Node *head)
{
    Node *p = head;
    while (p != NULL) {
        Node *next = p->next;
        free(p);
        p = next;
    }
}


/* ============================================================
 * Bug 1：忘记检查 malloc 返回值
 * malloc 可能失败返回 NULL，直接解引用 NULL 会崩。
 * ============================================================ */
Node *bug1_create(void)
{
    Node *head = (Node *)malloc(sizeof(Node));
    // BUG：没有检查 malloc 是否成功
    head->data = 1;     // 如果 malloc 返回 NULL，这里崩
    head->next = NULL;

    // FIX: 在 malloc 后加
    // if (head == NULL) { printf("malloc 失败\n"); return NULL; }

    return head;
}


/* ============================================================
 * Bug 2：链表插入 —— 头插时没更新外部指针
 * 在头部插入新节点后，main 里的 head 指针没变！
 * ============================================================ */
void bug2_insert_head(Node *head, int data)
{
    // BUG：这里想头插，但 head 是副本
    Node *new = create_node(data);
    new->next = head;      // 新节点指向旧头
    head = new;            // 只改了局部 head，外面的没变
    // ⚠️ 函数结束，新节点泄漏了（没人指向它）
}

// ✅ 正确版：接收 Node **，才能改外面的 head
void insert_head_ok(Node **head, int data)
{
    Node *new = create_node(data);
    new->next = *head;
    *head = new;
}


/* ============================================================
 * Bug 3：链表删除 —— 丢了下一个节点
 * 删除节点时，忘记保存 next 指针就 free，后续访问崩溃。
 * ============================================================ */
void bug3_delete_wrong(Node *head, int target)
{
    // BUG：遍历时先 free 再 next，但 next 已经没了
    Node *p = head;
    while (p != NULL && p->data == target) {
        free(p);            // ❌ 先 free 了 p
        p = p->next;        // 再试图访问 p->next，此时 p 已释放！
    }
}

// ✅ 正确版：先保存 next，再 free
void delete_ok(Node *head, int target)
{
    Node *p = head;
    while (p != NULL) {
        Node *next = p->next;   // 先保存
        if (p->data == target) {
            free(p);            // 再释放
        }
        p = next;
    }
}


/* ============================================================
 * Bug 4：内存泄漏 —— 有 malloc 没 free
 * 每次调用都分配内存但不释放，程序跑久了内存越用越多。
 * ============================================================ */
void bug4_leak(void)
{
    for (int i = 0; i < 5; i++) {
        Node *n = (Node *)malloc(sizeof(Node));
        n->data = i;
        n->next = NULL;
        // BUG：没有 free(n)，每次循环泄漏 sizeof(Node) 字节
    }
}

void bug4_leak_fixed(void)
{
    for (int i = 0; i < 5; i++) {
        Node *n = (Node *)malloc(sizeof(Node));
        n->data = i;
        n->next = NULL;
        printf("    第 %d 个节点地址: %p，已 free\n", i, (void *)n);
        free(n);    // ✅ 用完就释放
    }
}


/* ============================================================
 * Bug 5：悬空指针 —— use-after-free
 * 释放内存后还继续用，读的是垃圾值或崩。
 * ============================================================ */
void bug5_dangling(void)
{
    int *p = (int *)malloc(sizeof(int));
    *p = 42;
    printf("  free 前: %d\n", *p);

    free(p);        // 释放

    // BUG：释放后还在用
    printf("  free 后: %d（悬空指针！可能是垃圾值）\n", *p);

    // ⚠️ 释放后 p 指向的内存可能已被分配给其他数据，
    //   继续用轻则取值不对，重则覆盖其他数据导致诡异 bug。
    // FIX: free 后将 p 置 NULL
    p = NULL;
}


/* ============================================================
 * Bug 6：double free —— 重复释放同一块内存
 * 两次 free 同一块内存，运行时崩溃（或触发 abort）。
 * ============================================================ */
void bug6_double_free(void)
{
    int *p = (int *)malloc(sizeof(int));
    *p = 100;
    free(p);
    // BUG：第二次 free，未定义行为
    // free(p);    // ❌ double free，取消注释看效果

    printf("  double free 已注释掉，取消注释试试。\n");
}


/* ============================================================
 * Bug 7（链表）：插入到有序链表 —— 漏了一种情况
 * 在有序链表中插入新节点，要考虑三种情况：
 *   ① 插在头部
 *   ② 插在中间
 *   ③ 插在尾部
 * 下面这个版本漏了第①种。
 * ============================================================ */
Node *bug7_insert_sorted(Node *head, int data)
{
    Node *new = create_node(data);
    if (head == NULL) return new;

    // BUG：如果 data 比 head->data 还小，应该插在头部
    //   但下面的循环从 head 开始找，如果 data < head->data，
    //   循环不会进入，最终插在尾部——错了！

    Node *p = head;
    while (p->next != NULL && p->next->data < data) {
        p = p->next;
    }
    new->next = p->next;
    p->next = new;

    return head;    // BUG: 如果新节点应该成为新头，返回的 head 不对
}

// ✅ 正确版
Node *insert_sorted_ok(Node *head, int data)
{
    Node *new = create_node(data);

    // 情况①：插在头部（链表为空或新节点最小）
    if (head == NULL || data < head->data) {
        new->next = head;
        return new;
    }

    // 情况②③：插在中间或尾部
    Node *p = head;
    while (p->next != NULL && p->next->data < data) {
        p = p->next;
    }
    new->next = p->next;
    p->next = new;

    return head;
}


/* ============================================================
 * Bug 8：strdup 用完后没 free（字符串内存泄漏）
 * strdup 内部调用了 malloc，用完必须 free。
 * ============================================================ */
void bug8_strdup_leak(void)
{
    char *s = strdup("hello malloc");
    printf("  strdup: %s\n", s);
    // BUG：strdup 内部调用了 malloc，但这里没有 free(s)
    // free(s);  // ✅ 应该加这行
}


/* ============================================================
 * Bug 9（链表挑战）：反转链表 —— 丢失了对后续节点的引用
 * 考研大题常见考点。下面这个实现少写了一行。
 * ============================================================ */
Node *bug9_reverse(Node *head)
{
    Node *prev = NULL;
    Node *curr = head;
    Node *next = NULL;

    while (curr != NULL) {
        next = curr->next;      // 保存下一个
        curr->next = prev;      // 反转当前节点
        // BUG：这里少了一步往前推进
        // prev = curr;         // ✅ 应该加这行
        // curr = next;         // ✅ 应该加这行
    }

    return prev;    // 由于 prev 没更新，这里返回的是 NULL
}


/* ============================================================
 * Bug 10（挑战）：遍历链表时修改链表
 * 遍历过程中删除了当前节点，但继续用当前节点的 next。
 * ============================================================ */
void bug10_delete_while_iterating(Node *head, int target)
{
    Node *p = head;
    while (p != NULL) {
        if (p->data == target) {
            // BUG：删了 p 后，p->next 已经非法，但循环末尾 p = p->next
            //   实际应该先保存 next，删掉 p，再让 p = next
            free(p);
        }
        p = p->next;    // ❌ 如果上面 free(p) 了，这里访问已释放的内存
    }
}


/* ---- main：逐一跑 bug 场景 ---- */
int main(void)
{
    printf("========================================\n");
    printf("  M10 指针进阶与链表 — Debug 实战\n");
    printf("========================================\n\n");

    /* Bug 1：检查 malloc */
    printf("=== Bug 1: 未检查 malloc ===\n");
    Node *h1 = bug1_create();
    printf("  创建成功: head->data = %d\n", h1->data);
    free(h1);

    /* Bug 2：头插法 */
    printf("\n=== Bug 2: 头插没更新指针 ===\n");
    Node *h2 = create_node(1);
    bug2_insert_head(h2, 0);       // BUG：想头插 0，但没插进去
    print_list(h2);                 // 看头插生效了吗？

    // 正确做法
    Node *h2_ok = create_node(1);
    insert_head_ok(&h2_ok, 0);
    print_list(h2_ok);
    free_list(h2_ok);

    /* Bug 3：删除丢 next */
    printf("\n=== Bug 3: 内存泄漏 ===\n");
    bug4_leak();
    bug4_leak_fixed();
    printf("  用 leaks 或 valgrind 检测上面有没有泄漏。\n");

    /* Bug 5：悬空指针 */
    printf("\n=== Bug 5: 悬空指针 ===\n");
    bug5_dangling();

    /* Bug 6：double free */
    printf("\n=== Bug 6: double free ===\n");
    bug6_double_free();

    /* Bug 7：有序插入 */
    printf("\n=== Bug 7: 有序插入 ===\n");
    Node *h7 = NULL;
    h7 = insert_sorted_ok(h7, 5);
    h7 = insert_sorted_ok(h7, 3);
    h7 = insert_sorted_ok(h7, 8);
    h7 = insert_sorted_ok(h7, 1);
    printf("  有序插入预期: 1 -> 3 -> 5 -> 8 -> NULL\n");
    print_list(h7);
    free_list(h7);

    /* Bug 8：strdup 泄漏 */
    printf("\n=== Bug 8: strdup 泄漏 ===\n");
    bug8_strdup_leak();

    /* Bug 9：反转链表 */
    printf("\n=== Bug 9: 反转链表 ===\n");
    Node *h9 = NULL;
    for (int i = 1; i <= 4; i++) {
        insert_head_ok(&h9, i);   // 构建 4->3->2->1
    }
    printf("  原链表: 4 -> 3 -> 2 -> 1 -> NULL\n");
    printf("  ⚠️ bug9_reverse 有 bug（curr 永远不会推进），\n");
    printf("     运行会死循环，这里不执行它。\n");
    printf("     去看代码，补上两行修复再取消注释验证。\n");
    // 正确版本展示：
    printf("  反转函数正确代码的调用效果：\n");
    // 这里直接演示正确反转逻辑（不调用 bug9_reverse）
    Node *prev = NULL, *curr = h9, *next;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    printf("  反转后: ");
    print_list(prev);

    printf("\n========================================\n");
    printf("  Debug 完毕\n");
    printf("========================================\n");
    printf("\n提示：\n");
    printf("  1. 注释掉 Bug 9 的修复行上的注释，看看反转是否正常。\n");
    printf("  2. 用 `leaks -atExit -- ./debug` 检查内存泄漏。\n");
    printf("  3. 每个 bug 都亲手改一遍，然后重新编译验证。\n");

    return 0;
}
