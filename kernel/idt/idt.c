#include "idt.h"
#include "common.h"
#include "string.h"
#include "debug.h"

//中断描述符表
struct idtEntry_t idtEntry[256];

//IDTR
struct idtPtr_t idtPtr;

//中断处理函数的指针数组
interruptHander_t interruptHander[256];

void registerInterruptHander(unsigned char n, interruptHander_t h)
{
	interruptHander[n] = h;
}

void isrHander(struct ptRegs_t *regs)
{
    if(interruptHander[regs->intNo])
        interruptHander[regs->intNo](regs);
    else
        printkWithColor(black, blue, "Unhandled interrupt: %d\n", regs->intNo);

}

void irqHander(struct ptRegs_t *regs)
{
	if(regs->intNo >= 40)
		writeByte(0xA0, 0x20);
	writeByte(0x20, 0x20);

	if(interruptHander[regs->intNo])
		interruptHander[regs->intNo](regs);
	else
		printkWithColor(black, blue, "Unhandled interrupt: %d\n", regs->intNo);
}

//设置中断描述符
static idtSetGate(unsigned char num, unsigned int base, unsigned short selector, unsigned char flags)
{
    idtEntry[num].baseLow = base & 0xFFFF;
    idtEntry[num].baseHigh = (base >> 16) & 0xFFFF;
    idtEntry[num].selector = selector;
    idtEntry[num].flags = flags;
    idtEntry[num].zero = 0;
}

//声明加载IDTR函数
extern void idtFlush(unsigned int);

void initIdt()
{
	//两片级联的8259A芯片 主片端口0x20 0x21 从片端口0xA0 0xA1
	//初始化主从片
	writeByte(0x20, 0x11);
	writeByte(0xA0, 0x11);
	//设置主片IRQ从32号开始
	writeByte(0x21, 0x20);
	//设置从片IRQ从40号开始
	writeByte(0xA1, 0x28);
	//设置主片IR2引脚连接从片
	writeByte(0x21, 0x04);
	writeByte(0xA1, 0x02);
	//设置主从片按照8086方式工作
	writeByte(0x21, 0x01);
	writeByte(0xA1, 0x01);
	//设置主从片允许中断
	writeByte(0x21, 0x00);
	writeByte(0xA1, 0x00);

    bzero((unsigned char *)&interruptHander, sizeof(interruptHander_t) * 256);
    idtPtr.limit = sizeof(struct idtEntry_t) * 256 - 1;
    idtPtr.base = (unsigned int)&idtEntry;

    bzero((unsigned char *)&idtEntry, sizeof(struct idtEntry_t) * 256);

    // 0-32:  用于 CPU 的中断处理
	idtSetGate( 0, (unsigned int)isr0,  0x08, 0x8E);
	idtSetGate( 1, (unsigned int)isr1,  0x08, 0x8E);
	idtSetGate( 2, (unsigned int)isr2,  0x08, 0x8E);
	idtSetGate( 3, (unsigned int)isr3,  0x08, 0x8E);
	idtSetGate( 4, (unsigned int)isr4,  0x08, 0x8E);
	idtSetGate( 5, (unsigned int)isr5,  0x08, 0x8E);
	idtSetGate( 6, (unsigned int)isr6,  0x08, 0x8E);
	idtSetGate( 7, (unsigned int)isr7,  0x08, 0x8E);
	idtSetGate( 8, (unsigned int)isr8,  0x08, 0x8E);
	idtSetGate( 9, (unsigned int)isr9,  0x08, 0x8E);
	idtSetGate(10, (unsigned int)isr10, 0x08, 0x8E);
	idtSetGate(11, (unsigned int)isr11, 0x08, 0x8E);
	idtSetGate(12, (unsigned int)isr12, 0x08, 0x8E);
	idtSetGate(13, (unsigned int)isr13, 0x08, 0x8E);
	idtSetGate(14, (unsigned int)isr14, 0x08, 0x8E);
	idtSetGate(15, (unsigned int)isr15, 0x08, 0x8E);
	idtSetGate(16, (unsigned int)isr16, 0x08, 0x8E);
	idtSetGate(17, (unsigned int)isr17, 0x08, 0x8E);
	idtSetGate(18, (unsigned int)isr18, 0x08, 0x8E);
	idtSetGate(19, (unsigned int)isr19, 0x08, 0x8E);
	idtSetGate(20, (unsigned int)isr20, 0x08, 0x8E);
	idtSetGate(21, (unsigned int)isr21, 0x08, 0x8E);
	idtSetGate(22, (unsigned int)isr22, 0x08, 0x8E);
	idtSetGate(23, (unsigned int)isr23, 0x08, 0x8E);
	idtSetGate(24, (unsigned int)isr24, 0x08, 0x8E);
	idtSetGate(25, (unsigned int)isr25, 0x08, 0x8E);
	idtSetGate(26, (unsigned int)isr26, 0x08, 0x8E);
	idtSetGate(27, (unsigned int)isr27, 0x08, 0x8E);
	idtSetGate(28, (unsigned int)isr28, 0x08, 0x8E);
	idtSetGate(29, (unsigned int)isr29, 0x08, 0x8E);
	idtSetGate(30, (unsigned int)isr30, 0x08, 0x8E);
	idtSetGate(31, (unsigned int)isr31, 0x08, 0x8E);

	//interrupt request
	idtSetGate(32, (unsigned int)irq0, 0x08, 0x8E);
	idtSetGate(33, (unsigned int)irq1, 0x08, 0x8E);
	idtSetGate(34, (unsigned int)irq2, 0x08, 0x8E);
	idtSetGate(35, (unsigned int)irq3, 0x08, 0x8E);
	idtSetGate(36, (unsigned int)irq4, 0x08, 0x8E);
	idtSetGate(37, (unsigned int)irq5, 0x08, 0x8E);
	idtSetGate(38, (unsigned int)irq6, 0x08, 0x8E);
	idtSetGate(39, (unsigned int)irq7, 0x08, 0x8E);
	idtSetGate(40, (unsigned int)irq8, 0x08, 0x8E);
	idtSetGate(41, (unsigned int)irq9, 0x08, 0x8E);
	idtSetGate(42, (unsigned int)irq10, 0x08, 0x8E);
	idtSetGate(43, (unsigned int)irq11, 0x08, 0x8E);
	idtSetGate(44, (unsigned int)irq12, 0x08, 0x8E);
	idtSetGate(45, (unsigned int)irq13, 0x08, 0x8E);
	idtSetGate(46, (unsigned int)irq14, 0x08, 0x8E);
	idtSetGate(47, (unsigned int)irq15, 0x08, 0x8E);

	// 255 将来用于实现系统调用
	idtSetGate(255, (unsigned int)isr255, 0x08, 0x8E);

    idtFlush((unsigned int)&idtPtr);
}


