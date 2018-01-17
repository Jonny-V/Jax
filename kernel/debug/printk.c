#include "vargs.h"
#include "console.h"
#include "string.h"
#include "debug.h"

//格式字符
#define ZEROPAD   1       //垫零
#define SIGN      2       //
#define PLUS      4       //加号
#define SPACE     8       //正值输出' '，否则输出'0'
#define LEFT      16      //左对齐，右边填充空格
#define SPECIAL   32      //0x
#define SMALL     64      //十六进制中全部采用小写字母

//求余数
#define div(n,base) ({\
  int __res;\
  __asm__("divl %4":"=a" (n),"=d" (__res):"0" (n),"1" (0),"r" (base));\
  __res; })

#define is_digit(c) ((c) >= '0' && (c) <= '9')

//将数字字符串转换为整型数
static inline int strToInt(const char **s)
{
  int i = 0;
  while(is_digit(**s))
  {
    i = i*10 + *((*s)++) - '0';
  }
  return i;
}

/*打印数字类型的变量,返回打印内容的长度
str是将数字转换为相应的格式字符串
num为需要打印的数字
base为基本进制，提供八进制 十进制 十六进制
size为打印的宽度
precision为打印精度
printType为打印格式
*/
static char *printNumber(char *str, int num, int base, int size, int precision, int printType)
{
  char temp[36];
  const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char c, sign;
  int i;

  if( base < 2 || base >36)
    return 0;

  c = (printType & ZEROPAD) ? '0' : ' ';
  if (printType & SMALL)
    digits = "0123456789abcdefghijklmnopqrstuvwxyz";
  if(printType & LEFT)
    printType &= ~ZEROPAD;
  if(printType & SIGN && num < 0)
  {
    sign = '-';
    num = -num;
  }
  else
    sign = (printType & PLUS) ? '+' : ((printType & SPACE) ? ' ' : 0);
  if(sign)
    --size;
  if(printType & SPECIAL)
  {
    if( base == 16)
      size -= 2;
    else if (base == 8)
      --size;
  }

  //先将数字转为相应的字符串
  i = 0;
  if(num == 0)
    temp[i++] = '0';
  else
  {
    while(num != 0)
      temp[i++] = digits[div(num,base)];
  }

  if(i > precision)
    precision = i;
  size -= precision;

  if(!(printType & (ZEROPAD + LEFT)))
    while( size-- > 0)
      *str++ = ' ';
  if(sign)
    *str++ = sign;
  if(base == 8)
    *str++ = 'o';
  else if(base == 16)
  {
    *str++ = '0';
    *str++ = 'x';
  }
  if(!(printType & LEFT))
    while( size-- > 0)
      *str++ = c;

  while (i < precision--) 
  {
		*str++ = '0';
	}

  while(i-- > 0)
    *str++ = temp[i];
  while(size-- > 0)
    *str++ = ' ';

  return str;
}

static int vsPrintf(char *buff, const char *format, va_list args)
{
  char *str;
  char *strTemp;
  int printWidth;     //打印宽度
  int precision;      //精度位数
  int flag;
  int len;
  int i;
  int *ip;

  for( str = buff; *format; ++format)
  {
    if( *format != '%')
    {
      *str++ = *format;
      continue;
    }

    //获取输出标志
    flag = 0;
    repeat:
      ++format;       //跳过%号
      switch(*format)
      {
        case '-':     //结果左对齐，右边填空格
          flag |= LEFT;
          goto repeat;
        case '+':     //输出符号(正号或负号)
          flag |= PLUS;
          goto repeat;
        case '0':     //垫零，满足宽度
          flag |= ZEROPAD;
          goto repeat;
        case ' ':     //输出值为正时冠以空格，为负时冠以负号
          flag |= SPACE;
          goto repeat;
        case '#':     //八进制输出o，十六进制输出0x
          flag |= SPECIAL;
          goto repeat;
      }

    //获取输出宽度
    printWidth = -1;
    if(is_digit(*format))
      printWidth = strToInt((const char **)&format);
    else if(*format == '*')
    {
       printWidth =  va_arg(args, int);
       if(printWidth < 0)   //负数表示左对齐
       {
         printWidth = -printWidth;
         flag |= LEFT;
       }
    }

    //获取精度
    precision = -1;
    if(*format == '.')
    {
      ++format;
      if(is_digit(*format))
        precision = strToInt(&format);
      else if(*format == '*')
      {
        precision = va_arg(args, int);
      }
      if(precision < 0)
        precision = 0;
    }

    if( *format == 'h' || *format == 'l' || *format == 'L')
      ++format;
    
    switch(*format)
    {
      //输出字符
      case 'c':
        if(!(flag & LEFT))
          while( --printWidth > 0)
            *str++ = ' ';
        *str++ = (unsigned char)va_arg(args, int);
        while( --printWidth > 0)
            *str++ = ' ';
        break;

      //输出字符串 
      case 's':
        strTemp = va_arg(args, char *);
        len = strlen(strTemp);
        if( precision < 0 )
          precision = len;
        else if( len > precision )
          len = precision;

        if(!(flag & LEFT))
          while( --printWidth > 0 )
            *str++ = ' ';
        for( i=0; i< len; i++)
          *str++ = *strTemp++;
        while( len < --printWidth )
          *str++ = ' ';
        break;
      
      //输出八进制
      case 'o':
        str = printNumber(str, va_arg(args, unsigned long), 8, printWidth, precision, flag);
        break;
      
      //输出指针地址
      case 'p':
        if( printWidth == -1)
        {
          printWidth = 8;
          flag |= ZEROPAD;
        }
        str = printNumber(str, (unsigned long)va_arg(args, void *), 16, printWidth, precision, flag);

        break;
      
      //输出十六进制，以小写字母表示
      case 'x':
        flag |= SMALL;

      //输出十六进制，以大写字母表示
      case 'X':
        str = printNumber(str, va_arg(args, unsigned long), 16, printWidth, precision, flag);
        break;

      //输出十进制
      case 'd':
      case 'i':
        flag |= SIGN;
      case 'u':
        str = printNumber(str, va_arg(args, unsigned long), 10, printWidth, precision, flag);
        break;
      
      //输出二进制
      case 'b':
        str = printNumber(str, va_arg(args, unsigned long), 2, printWidth, precision, flag);
        break;

      //字符位置
      case 'n':
        ip = va_arg(args, int *);
        *ip = (str - buff);
        break;
      
      default:
        if(*format != '%')
          *str++ = '%';
        if(*format)
          *str++ = *format;
        else
          --format;
        break;

    }
  }

  *str = '\0';
  return (str - buff);
}

void printk(const char *format, ...)
{
  static char buff[1024];
  va_list args;

  va_start(args, format);
  int i = vsPrintf(buff, format, args);
  va_end(args);

  buff[i]='\0';
  consolePrintString(buff);
}

void printkWithColor(enum colorType backColor, enum colorType foreColor, const char *format, ...)
{
  static char buff[1024];
  va_list args;

  va_start(args, format);
  int i = vsPrintf(buff, format, args);
  va_end(args);

  buff[i]='\0';
  consolePrintStringWithColor(buff, backColor, foreColor);
}