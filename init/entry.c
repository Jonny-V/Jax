#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"

int kern_entry()
{
  initDebug();
  initGdt();
  initIdt();
  printk("initIdt success\n");
  
  consoleClear();
  printk("Hello,Jax\n");

  initTimer(200);

  asm volatile("sti");
  

  //panic("Test");

  return 0;
}