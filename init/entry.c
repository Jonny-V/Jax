#include "types.h"
#include "common.h"
#include "console.h"

int kern_entry()
{
  consoleClear(); 
  consolePrintString("Hello,Jax!\n");
  consolePrintStringWithColor("Version:0.0.2\n",black,magenta);
  consolePrintStringWithColor("This is created by Jonny\n", black, red);

  char c, s[20]; 
  int a=-1234;
  strcpy(s, "Hello,World"); 
  c='\x41'; 
  printk("a=%d\n", a);//按照十进制整数格式输出，显示 a=1234
  printk("a=%d%%\n", a);//输出%号 结果 a=1234%
  printk("a=%6d\n", a);//输出6位十进制整数 左边补空格，显示 a= 1234
  printk("a=%06d\n", a);//输出6位十进制整数 左边补0，显示 a=001234
  printk("a=%2d\n", a);//a超过2位，按实际输出 a=1234
  printk("a=%-6d\n", a);///输出6位十进制整数 右边补空格，显示 a=1234
  printkWithColor(black,red,"s[]=%s\n", s);//输出数组字符串s[]=Hello,World
  printkWithColor(black,magenta,"s[]=%6.9s\n", s);//输出最多9个字符的字符串 s[]=Hello,Wor
  return 0;
}