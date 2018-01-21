#ifndef PMM_H_
#define PMM_H_

#include "multiboot.h"
#include "debug.h"

//线程栈大小
#define STACK_SIZE 8192

//支持最大的物理内存 512MB
#define PMM_MAX_SIZE 0x20000000

//物理内存页框大小 4KB
#define PMM_PAGE_SIZE 0x1000

//最多支持物理页个数
#define PAGE_MAX_SIZE (PMM_MAX_SIZE / PMM_PAGE_SIZE)

//页掩码按照4096对齐地址
#define PHY_PAGE_MASK 0xFFFFF000

//内核起始和结束内存位置
extern unsigned char kernelStart[];
extern unsigned char kernelEnd[];

//动态分配的物理内存页总数
extern unsigned int phyPageCount;

//打印物理内存布局
void showMemoryMap();

//初始化物理内存管理
void initPmm();

//返回一个物理页的地址
unsigned int pmmAllocPage();

//释放一个物理页
void pmmFreePage(unsigned int page);

#endif   //include PMM_H_