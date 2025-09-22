/*
 * kernel/uart.c
 * Manages the UART output with a buffer to improve performance.
 */

// 定义 UART 硬件寄存器地址
#define UART_BASE 0x10000000L
#define UART_THR (volatile unsigned char *)(UART_BASE + 0x00)

// 定义缓冲区大小
#define UART_BUF_SIZE 128
static char uart_buf[UART_BUF_SIZE];
// `buf_idx` 指向缓冲区中下一个空闲的位置
static int buf_idx = 0;

// 内部函数：刷新缓冲区，将所有内容发送到硬件
void uart_flush() {
    if (buf_idx == 0) {
        return; // 缓冲区是空的，无需操作
    }

    for (int i = 0; i < buf_idx; i++) {
        *UART_THR = uart_buf[i];
    }
    
    // 发送完毕，重置缓冲区索引
    buf_idx = 0;
}

// 公共函数：输出一个字符（现在是写入缓冲区）
void uart_putc(char c) {
    // 将字符存入缓冲区
    uart_buf[buf_idx++] = c;

    // 如果缓冲区满了，或者遇到换行符，就刷新缓冲区
    if (buf_idx >= UART_BUF_SIZE || c == '\n') {
        uart_flush();
    }
}