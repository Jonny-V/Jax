#include "common.h"

inline unsigned char readByte(unsigned short port)
{
  unsigned char ret;
  asm volatile( "inb %1, %0" : "=a"(ret) : "dN"(port));
  return ret;
}

inline void writeByte(unsigned short port, unsigned char value)
{
  asm volatile( "outb %1, %0" : : "dN" (port), "a" (value));
}

inline unsigned short readWord(unsigned short port)
{
  unsigned short ret;
  asm volatile( "inb %1, %0" : "=a"(ret) : "dN"(port));
  return ret;
}

inline void writeWord(unsigned short port, unsigned short value)
{
  asm volatile( "outb %1, %0" : : "dN"(port), "a"(value));
}