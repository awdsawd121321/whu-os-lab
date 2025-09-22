#
# kernel/entry.S
#
# Copyright (C) 2024 Wuhan University
#

.section .text.entry
.globl _start
_start:
    # 设置栈指针 sp
    # 我们预留 4096 字节的栈空间
    # stack_top 符号将在链接脚本中定义
    la sp, stack_top

    # 跳转到 C 语言的 main 函数
    call main

    # 如果 main 函数返回, 则进入死循环
loop:
    j loop
