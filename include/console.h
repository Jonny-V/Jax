#ifndef CONSOLE_H_
#define CONSOLE_H_

enum colorType{
  black=0,
  blue=1,
  green=2,
  cyan=3,           //青
  red=4,
  magenta=5,        //品红
  brown=6,          
  lightGren=7,      //白
  darkGren=8,       //灰
  lightBlue=9,      
  lightGreen=10,
  lightCyan=11,
  lightRed=12,
  lightMagenta=13,  //浅品红
  lightBrown=14,    //黄
  white=15          //亮白
};

//清屏操作
void consoleClear();

//屏幕打印一个带颜色的字符
void consolePrintChar(char c, enum colorType backColor, enum colorType foreColor);

//屏幕打印一个以 \0 结尾的字符串,默认黑底白字
void consolePrintString(const char *str);

//屏幕打印一个以 \0 结尾的带颜色的字符串
void consolePrintStringWithColor(const char *str, enum colorType backColor, enum colorType foreColor);

//屏幕打印一个十六进制的整型数
void consolePrintHex(unsigned int n, enum colorType backColor, enum colorType foreColor);

//屏幕打印一个十进制的整型数
void consolePrintDec(unsigned int n, enum colorType backColor, enum colorType foreColor);


#endif