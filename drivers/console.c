#include "console.h"

//VGA 显示缓冲点内存起点地址 0xB8000
static unsigned short *displayBuffer = (unsigned short *)0xB8000;

//光标
static unsigned char cursorX = 0;
static unsigned char cursorY = 0;

//设置光标位置
static void cursorSet(unsigned char x, unsigned char y)
{
  cursorX = x;
  cursorY = y;
}
//光标移动
static void cursorMove()
{
  //屏幕80字节宽
  unsigned short cursorLocation = cursorY*80 + cursorX;
  
  writeByte(0x3D4, 14);
  writeByte(0x3D5, cursorLocation >> 8);    //发送高八位
  writeByte(0x3D4, 15);
  writeByte(0x3D5, cursorLocation);         //发送低八位
}

//清除屏幕
void consoleClear()
{
  unsigned char black1 = (unsigned char)black;
  unsigned char white1= (unsigned char)white;
  unsigned char color = (black1 << 4) | (white1 & 0x0F);
  unsigned short blank = (0x20) | (color << 8); //0x20 是空白符的ANSI值
  for(int i = 0*80; i < 80*25; i++)
    displayBuffer[i] = blank;

  cursorSet(0,0);
  cursorMove();
}

//屏幕滚动
void consoleScroll()
{
  unsigned char color = ((unsigned char)black << 4) | ((unsigned char)white & 0x0F);
  unsigned short blank = (0x20) | (color << 8);

  if( cursorY > 25)
  {
    int i = 0;
    for(i = 0*80; i < 80*24; i++)
      displayBuffer[i] = displayBuffer[i+80];
    for(i =24*80; i< 80*25; i++)
      displayBuffer[i] = blank;
    cursorY = 24;
    //cursorMove();
  }
}

void consolePrintChar(char c, enum colorType backColor, enum colorType foreColor)
{
  //unsigned char color = (unsigned short)(((unsigned char)backColor << 4) | ((unsigned char)foreColor & 0x0F));
  unsigned char black1 = (unsigned char)backColor;
  unsigned char white1= (unsigned char)foreColor;
  unsigned char color = (black1 << 4) | (white1 & 0x0F);
  unsigned short cursorLocation = cursorY * 80 + cursorX;
  
  if( c == 0x08 && cursorX)
  {
    cursorX--;
  }
  else if( c == 0x09)
  {
    cursorX = (cursorX + 8) & ~(8-1);
  }
  else if( c == '\r')
  {
    cursorX = 0;
  }
  else if( c == '\n')
  {
    cursorY++;
    cursorX = 0;
  }
  else if( c >= ' ')
  {
    displayBuffer[cursorLocation] = c | (color << 8);
    cursorX++;
  }

  if(cursorX >= 80)
  {
    cursorX = 0;
    cursorY++;
  }

  consoleScroll();
  cursorMove();
}

//屏幕打印一个以 \0 结尾的字符串,默认黑底白字
void consolePrintString(const char *str)
{
  while( *str ){
    consolePrintChar( *str++, black, white);
  }
}

//屏幕打印一个以 \0 结尾的带颜色的字符串
void consolePrintStringWithColor(const char *str, enum colorType backColor, enum colorType foreColor)
{
  while( *str ){
    consolePrintChar( *str++, backColor, foreColor);
  }
}

//屏幕打印一个十六进制的正整型数
void consolePrintHex(unsigned int n, enum colorType backColor, enum colorType foreColor)
{
  consolePrintStringWithColor("0x", backColor, foreColor);
  
  int nTemp;
  char noZero = 1;
  for(int i =28; i >=0; i-=4)
  {
    nTemp = ( n>>i ) & 0x0F;
    if( nTemp == 0 && noZero !=0 )
      continue;
  noZero = 0;
  if( nTemp >= 0xA)
    consolePrintChar( nTemp-0xA+'a', backColor, foreColor);
  else
    consolePrintChar( nTemp+'0', backColor ,foreColor);
  } 
}

//屏幕打印一个十进制的正整型数
void consolePrintDec(unsigned int n, enum colorType backColor, enum colorType foreColor)
{
  if( n==0 )
    consolePrintChar('0', backColor, foreColor);
  
  char cReverse[32];
  unsigned int nTemp = n;
  unsigned char i = 0;
  while( nTemp > 0)
  {
    cReverse[i++] = nTemp % 10 + '0';
    nTemp /= 10;
  }
  cReverse[i] = '\0'; //对字符串进行补‘\0’操作
  //对数组进行首尾颠倒
  unsigned char j = 0;
  char cNormal[32];
  cNormal[i--] = '\0';
  while( cReverse[j] )
  {
    cNormal[i--] = cReverse[j++];
  }

  consolePrintStringWithColor(cNormal, backColor, foreColor);
}