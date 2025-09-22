#include <stdarg.h>
void uart_putc(char c);
void uart_flush(); // 新增的声明
// ...
// 声明 uart_putc，因为 printf 需要调用它来输出单个字符
void uart_putc(char c);

// 内部使用的静态函数，用于打印无符号整数
static void print_uint(unsigned long long n, int base) {
    static char digits[] = "0123456789abcdef";
    char buf[32];
    int i = 0;

    if (n == 0) {
        uart_putc('0');
        return;
    }

    while (n > 0) {
        buf[i++] = digits[n % base];
        n /= base;
    }

    while (--i >= 0) {
        uart_putc(buf[i]);
    }
}

// 内部使用的静态函数，用于打印有符号整数
static void print_int(long long n, int base) {
    if (n < 0) {
        uart_putc('-');
        print_uint((unsigned long long)-n, base);
    } else {
        print_uint((unsigned long long)n, base);
    }
}

// 新的核心函数 vprintf，它接收一个 va_list
void vprintf(const char *fmt, va_list args) {
    while (*fmt) {
        if (*fmt != '%') {
            uart_putc(*fmt);
        } else {
            fmt++;
            switch (*fmt) {
                // ... (这里的 switch case 内容完全不变) ...
                case 'd':
                    print_int(va_arg(args, int), 10);
                    break;
                case 'x':
                    print_uint(va_arg(args, unsigned int), 16);
                    break;
                case 's': {
                    char *s = va_arg(args, char *);
                    if (!s) s = "(null)";
                    while (*s) uart_putc(*s++);
                    break;
                }
                case 'c':
                    uart_putc((char)va_arg(args, int));
                    break;
                case '%':
                    uart_putc('%');
                    break;
                default:
                    // 如果遇到不认识的格式，比如 %y, %z
                    // 就把 '%' 和那个字符都打印出来
                    uart_putc('%');
                    uart_putc(*fmt);
                    break;
            }
        }
        fmt++;
    }
}

// 旧的 printf 函数现在变成 vprintf 的一个包装器
void printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

// 清屏函数
void clear_screen(void) {
    printf("\033[2J\033[H");
}

typedef enum {
    COLOR_RESET = 0,
    COLOR_RED = 31,
    COLOR_GREEN = 32,
    COLOR_YELLOW = 33,
    COLOR_BLUE = 34
} term_color_t;

// 将光标移动到 (x, y) 坐标 (1-indexed)
void goto_xy(int x, int y) {
    // 发送 ANSI 命令 \033[<y>;<x>H
    printf("\033[%d;%dH", y, x);
}

// 清除当前行
void clear_line(void) {
    // 发送 ANSI 命令 \033[2K
    printf("\033[2K");
}

// 以指定颜色进行格式化输出
void printf_color(term_color_t color, const char *fmt, ...) {
    va_list args;
    
    // 1. 设置颜色
    printf("\033[%dm", color);
    
    // 2. 使用 vprintf 打印内容
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    
    // 3. 恢复默认颜色，以免影响后续输出
    printf("\033[%dm", COLOR_RESET);
}