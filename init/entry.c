#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "pmm.h"

int kern_entry()
{
  initDebug();
  initGdt();
  initIdt();
  printk("initIdt success\n");
  
  consoleClear();
  printk("Hello,Jax\n");

  printk("kernel Strat: %08X, kernel End: %08X, Used: %dKB\n",
          kernelStart, kernelEnd,
          (kernelEnd - kernelStart + 1023) / 1024);

  showMemoryMap();
  initPmm();

  printkWithColor(black, red, "\nThe Count of Physical Memory Page is: %u\n\n", phyPageCount);

	unsigned  allc_addr = NULL;
	printkWithColor(black, lightBrown, "Test Physical Memory Alloc :\n");
	allc_addr = pmmAllocPage();
	printkWithColor(black, lightBrown, "Alloc Physical Addr: %08X\n", allc_addr);
	allc_addr = pmmAllocPage();
	printkWithColor(black, lightBrown, "Alloc Physical Addr: %08X\n", allc_addr);
	allc_addr = pmmAllocPage();
	printkWithColor(black, lightBrown, "Alloc Physical Addr: %08X\n", allc_addr);
	allc_addr = pmmAllocPage();
	printkWithColor(black, lightBrown, "Alloc Physical Addr: %08X\n", allc_addr);

  //initTimer(200);

  //asm volatile("sti");
  

  //panic("Test");

  return 0;
}