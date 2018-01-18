#ifndef DEBUG_H_
#define DEBUG_H_

#include "vargs.h"
#include "console.h"
#include "elf.h"
#include "types.h"

void printk(const char *format, ...);

void printkWithColor(enum colorType backColor, enum colorType foreColor, const char *format, ...);

#define assert(x, info)         \
        do {                    \
            if(!(x))            \
            {                   \
                panic(info);    \
            }                   \
        } while(0)

//编译器静态检测
#define staticAssert(x)         \
        switch(x)               \
        {                       \
            case 0:             \
            case (x): ;         \
        }

//初始化debug信息
void initDebug();

//打印当前函数调用栈信息
void panic(const char *msg);

//打印当前的段寄存器值
void printCurrentStatus();

#endif      //INCLUDE DEBUG_H_