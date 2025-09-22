#
# Makefile for the minimal OS
#
# Copyright (C) 2024 Wuhan University
#

# 工具链前缀
TOOLPREFIX = riscv64-unknown-elf-

CC = $(TOOLPREFIX)gcc
LD = $(TOOLPREFIX)ld
OBJDUMP = $(TOOLPREFIX)objdump

# 编译和链接选项
CFLAGS = -Wall -Werror -O2 -fno-pic -ffreestanding -nostdlib -mcmodel=medany
LDFLAGS = -T kernel/kernel.ld

# 目标文件
TARGET = kernel.elf
OBJS = kernel/entry.o kernel/main.o kernel/uart.o kernel/printf.o

# 默认目标: 编译所有
all: $(TARGET)

# 链接规则: 将所有 .o 文件链接成最终的 .elf 可执行文件
$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS)

# 编译规则: 将 C 源文件编译成 .o 目标文件
kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# 编译规则: 将汇编源文件编译成 .o 目标文件
kernel/%.o: kernel/%.S
	$(CC) $(CFLAGS) -c $< -o $@

# 清理规则: 删除编译生成的文件
clean:
	rm -f $(TARGET) $(OBJS)

# QEMU 运行规则
qemu: $(TARGET)
	@echo "--- Starting QEMU ---"
	@qemu-system-riscv64 -machine virt -nographic -bios none -kernel $(TARGET)
	@echo "\n--- QEMU finished ---"

# GDB 调试规则
qemu-gdb: $(TARGET)
	@echo "--- Starting QEMU for GDB ---"
	@qemu-system-riscv64 -machine virt -nographic -bios none -kernel $(TARGET) -s -S
