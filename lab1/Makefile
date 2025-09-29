# 工具链前缀
RISCV_TOOLCHAIN_PREFIX := riscv64-unknown-elf-

# 编译器和链接器
CC := $(RISCV_TOOLCHAIN_PREFIX)gcc
LD := $(RISCV_TOOLCHAIN_PREFIX)ld
OBJCOPY := $(RISCV_TOOLCHAIN_PREFIX)objcopy

# QEMU 模拟器
QEMU := qemu-system-riscv64

# 源文件和对象文件
SRCS := entry.S main.c uart.c
OBJS := $(patsubst %.S, %.o, $(filter %.S, $(SRCS)))
OBJS += $(patsubst %.c, %.o, $(filter %.c, $(SRCS)))

# 编译和链接选项
CFLAGS := -nostdlib -nostdinc -fno-builtin -mcmodel=medany -g
LDFLAGS := -T kernel.ld

# 目标文件名
TARGET := kernel.elf

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	$(QEMU) -machine virt -nographic -bios none -kernel $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)