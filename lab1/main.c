// 声明外部的串口输出函数
void uart_putc(char c);

// C 语言入口函数
void main() {
    // 任务：在QEMU中输出 "Hello OS"
    char *s = "Hello OS\n";
    while (*s) {
        uart_putc(*s++);
    }

    // 进入死循环，防止程序结束
    while (1);
}