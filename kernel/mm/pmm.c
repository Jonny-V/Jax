#include "pmm.h"

static unsigned int pmmStack[PAGE_MAX_SIZE + 1];
static unsigned int pmmStackTop;

unsigned int phyPageCount;

void showMemoryMap()
{
    unsigned int mmapAddr = glbMbootPtr->mmapAddr;
    unsigned int mmapLength = glbMbootPtr->mmapLength;

    printk("*******Memory map: *******\n");

    struct mmapEntry_t *mmap = (struct mmapEntry_t *)mmapAddr;
    for(; (unsigned int)mmap <= mmapAddr + mmapLength; mmap++)
    {
        printk("baseAddr = %X%08X, Length = %X%08X, type = %X\n",
                mmap->baseAddrHigh, mmap->baseAddrLow,
                mmap->lengthHigh, mmap->lengthLow,
                mmap->type);
    }
    printk("**************************\n");

}

void initPmm()
{
    struct mmapEntry_t *mmapStartAddr = (struct mmapEntry_t *)glbMbootPtr->mmapAddr;
    struct mmapEntry_t *mmapEndAddr = mmapStartAddr + glbMbootPtr->mmapLength;
    struct mmapEntry_t *mmapEntry;
    for(mmapEntry = mmapStartAddr; mmapEntry < mmapEndAddr; mmapEntry++)
    {
        if(mmapEntry->type == 1 && mmapEntry->baseAddrLow == 0x100000)
        {
            unsigned int pageAddr = mmapEntry->baseAddrLow + (unsigned int)(kernelEnd - kernelStart);
            unsigned int length = mmapEntry->baseAddrLow + mmapEntry->lengthLow;

            while(pageAddr < length && pageAddr <= PMM_MAX_SIZE)
            {
                pmmFreePage(pageAddr);
                pageAddr += PMM_PAGE_SIZE;
                phyPageCount++;
            }
        }
    }
}

unsigned int pmmAllocPage()
{
    assert(pmmStackTop != 0, "out of memory");
    unsigned int page = pmmStack[pmmStackTop--];
    return page;
}

void pmmFreePage(unsigned int page)
{
    assert(pmmStackTop != PAGE_MAX_SIZE, "out of pmm Stack");
    pmmStack[++pmmStackTop] = page;
}