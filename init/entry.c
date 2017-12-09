#include "types.h"
#include "common.h"
#include "console.h"

int kern_entry()
{
  consoleClear(); 
  consolePrintString("Hello,Jax!");
  consolePrintStringWithColor("Version:0.0.1\n",black,magenta);
  consolePrintStringWithColor("This is created by Jonny\n", black, red);
  consolePrintDec(123,black,cyan);
  consolePrintChar('\n',black,white);
  consolePrintHex(245,black,green);
  return 0;
}