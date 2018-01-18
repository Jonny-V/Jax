#include "debug.h"

static void printStackTrace();
static struct elf_t kernelElf;

void initDebug()
{
    kernelElf = elfFromMultiboot(glbMbootPtr);
}

void printCurrentStatus()
{
    static int round = 0;
    unsigned short reg1, reg2, reg3, reg4;
    asm volatile (  "mov %%cs, %0;"
                    "mov %%ds, %1;"
                    "mov %%es, %2;"
                    "mov %%ss, %3;"
                    : "=m"(reg1), "=m"(reg2), "=m"(reg3), "=m"(reg4));
    
    //打印当前的运行级别
    printk("%d: @ring %d\n", round, reg1 & 0x3);
    printk("%d: cs = %x\n", round, reg1);
    printk("%d: ds = %x\n", round, reg2);
    printk("%d: es = %x\n", round, reg3);
    printk("%d: ss = %x\n", round, reg4);
    ++round;
}

void panic(const char *msg)
{
    printk("***** System panic: %s *****\n", msg);
    printStackTrace();
    printk("****************************\n");
    while(1);
}

void printStackTrace()
{
    /*
    unsigned int *ebp, *eip;
    asm volatile ("mov %%ebp, %0" : "=r" (ebp));
    while(ebp)
    {
        eip = ebp + 1;
        printk("    [%X] %s\n", *eip, elfCheckSymbol(*eip, &kernelElf));
        ebp = (unsigned int *) *ebp;
    }
    */
    unsigned int *ebp, *eip;

	asm volatile ("mov %%ebp, %0" : "=r" (ebp));
	while (ebp) {
		eip = ebp + 1;
		printk("   [0x%x] %s\n", *eip, elfCheckSymbol(*eip, &kernelElf));
		ebp = (unsigned int *)*ebp;
    }
}