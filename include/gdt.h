#ifndef GDT_H_
#define GDT_H_

struct gdtEntry_t{
    unsigned short limitLow;        //段限长0-15位
    unsigned short baseLow;         //基地址0-15位
    unsigned char baseMiddle;       //基地址16-23位
    unsigned char access;           //TYPE4位 + S + DPL +P
    unsigned char granularity;      //段限长16-19位 + AVL + 保留1位 + D/B + G
    unsigned char baseHigh;         //基地址24-31位
} __attribute__((packed));

struct gdtPtr_t{
    unsigned short limit;           //全局描述符表限长
    unsigned int base;              //全局描述符基地址
} __attribute__((packed));

//初始化全局描述符表
void initGdt();

//GDT加载到GDTR
extern void gdtFlush(unsigned int);

#endif