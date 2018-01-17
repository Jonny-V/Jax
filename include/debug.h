#ifndef DEBUG_H_
#define DEBUG_H_

#include "vargs.h"
#include "console.h"

void printk(const char *format, ...);

void printkWithColor(enum colorType backColor, enum colorType foreColor, const char *format, ...);

#endif      //INCLUDE DEBUG_H_