/*
 * kernel/kernel.ld
 *
 * Copyright (C) 2024 Wuhan University
 */

OUTPUT_ARCH(riscv)
ENTRY(_start)

BASE_ADDRESS = 0x80000000;

SECTIONS
{
    . = BASE_ADDRESS;

    .text : {
        *(.text.entry)
        *(.text .text.*)
    }

    .rodata : {
        *(.rodata .rodata.*)
    }
    
    .data : {
        *(.data .data.*)
    }

    .bss : {
        *(.bss .bss.*)
    }

    /* 在程序末尾定义栈顶位置 */
    . = ALIGN(16);
    stack_bottom = .;
    . = . + 4096; /* 4K 栈空间 */
    stack_top = .;
    
    end = .;
}

