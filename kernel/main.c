// 声明所有我们将要使用的外部函数
void printf(const char *fmt, ...);
void clear_screen(void);
void goto_xy(int x, int y);
void clear_line(void);
void uart_flush(); // 新增的声明

// 定义颜色枚举 (与 printf.c 中保持一致)
typedef enum {
    COLOR_RESET = 0,
    COLOR_RED = 31,
    COLOR_GREEN = 32,
    COLOR_YELLOW = 33,
    COLOR_BLUE = 34
} term_color_t;

void printf_color(term_color_t color, const char *fmt, ...);

// C 语言入口函数
void main() {
    // 步骤 1: 初始清屏和基础 printf 测试
    clear_screen();

    printf("--- Basic printf Tests ---\n");
    printf("Hello from printf!\n");
    printf("====================\n");
    
    // --- 基础测试 ---
    printf("1. Testing integer: %d\n", 42);
    printf("2. Testing negative: %d\n", -123);
    printf("3. Testing zero: %d\n", 0);
    printf("4. Testing hex: 0x%x\n", 0xABC);
    printf("5. Testing string: %s\n", "This is a test string.");
    printf("6. Testing char: %c\n", 'X');
    printf("7. Testing percent: %%\n");

    // --- 边界测试 ---
    int int_min = -2147483648;
    printf("8. INT_MIN: %d\n", int_min);
    printf("9. NULL string: %s\n", (char*)0);
    
    printf("\nBasic tests passed!\n");


    // 步骤 2: 在下方追加高级功能演示
    // ------------------------------------------
    printf("\n--- Advanced Terminal Functions Demo ---\n");

    // 演示 printf_color
    printf("This line is default color.\n");
    printf_color(COLOR_GREEN, "This line is green.\n");
    printf_color(COLOR_RED, "And this line is red.\n");
    printf_color(COLOR_BLUE, "This one is blue!\n");
    printf("Color is now back to default.\n");
    
    // 演示 goto_xy 和 clear_line
    printf("\nDemonstrating clear_line in 3 seconds...\n");

    // 定位到下一行行首，准备演示
    int demo_line = 23; // 假设我们想在第23行演示
    goto_xy(1, demo_line); 
    printf("This entire line will be cleared soon...");
    
    // 添加一个延迟，以便能看到效果
    for (volatile int i = 0; i < 30000000; i++);

    goto_xy(1, demo_line); // 回到行首
    clear_line();   // 清除整行
    printf_color(COLOR_YELLOW, "Line cleared and this new text is written!");

    // 将光标移动到屏幕末尾
    goto_xy(1, 25);
    printf("\nAll demos finished.\n");


        // --- 步骤 3: 错误恢复与性能测试 ---
    printf("\n--- Error Recovery & Performance Tests ---\n");

    // 1. 错误恢复测试: 测试未知的格式说明符
    printf("Testing unknown format specifier %%z: ");
    printf("Hello %z World!\n", 12345);

    // 2. 性能测试: 大量输出
    printf("Starting performance test (1000 lines of output)...\n");

    // 添加一个延迟，以便能看到开始的消息
    for (volatile int i = 0; i < 10000000; i++);

    //int start_time = 0; // 伪代码: 我们还没有时钟，所以无法精确计时
    for (int i = 0; i < 1000; i++) {
        printf("Line %d: The quick brown fox jumps over the lazy dog. 0x%x\n", i, i * 37);
    }
    //int end_time = 0; // 伪代码

    printf("\nPerformance test finished.\n");


    // 将光标移动到屏幕末尾
    goto_xy(1, 25);
    printf("\nAll demos finished.\n");
     uart_flush(); 
    // 进入死循环, 防止程序跑飞
    while (1);
}