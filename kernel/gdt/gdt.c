#include "gdt.h"
#include "string.h"

//全局描述符长度
#define GDT_LENGTH 5

//全局描述符表
struct gdtEntry_t gdtEntry[GDT_LENGTH];

//全局描述符表地址，即入口
struct gdtPtr_t gdtPtr;

static void gdtSetGate(int num, unsigned int base, unsigned int limit, unsigned char access, unsigned char gran)
{
    gdtEntry[num].baseLow = (base & 0xFFFF);
    gdtEntry[num].baseMiddle = (base >> 16) & 0xFF;
    gdtEntry[num].baseHigh = (base >> 24) & 0xFF;

    gdtEntry[num].limitLow = (limit & 0xFFFF);
    gdtEntry[num].granularity = (limit >> 16) & 0x0F;

    gdtEntry[num].granularity |= (gran & 0xF0);

    gdtEntry[num].access = access; 
}

//内核栈地址
extern unsigned int stack;

void initGdt()
{
    gdtPtr.base = (unsigned int)&gdtEntry;
    gdtPtr.limit = sizeof(struct gdtEntry_t) * GDT_LENGTH - 1;

    gdtSetGate(0, 0, 0, 0, 0);                      //第一个描述符必须为0
    gdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);       //内核模式代码段
    gdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);       //内核模式数据段
    gdtSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);       //用户模式代码段
    gdtSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);       //用户模式数据段

    gdtFlush((unsigned int)&gdtPtr);
}
