#ifndef MULTIBOOT_H_
#define MULTIBOOT_H_

struct multiboot_t{
    unsigned int flags;                 //Multiboot version

    //get memory info from boot
    unsigned int memLower;              //the size of low mem
    unsigned int memUpper;              //the size of up mem
    unsigned int bootDevice;            //boot device
    unsigned int cmdline;               //the cmdline from kernel
    unsigned int modsCount;
    unsigned int modsAddr;

    //the head form of section about ELF
    unsigned int num;
    unsigned int size;
    unsigned int addr;
    unsigned int shndx;

    //The infomation about the buffer
    unsigned int mmapLength;
    unsigned int mmapAddr;

    unsigned int drivesLength;
    unsigned int drivesAddr;
    unsigned int configTable;
    unsigned int bootLoaderName;
    unsigned int apmTable;              //apm table
    unsigned int vbeControlInfo;
    unsigned int vbeModeInfo;
    unsigned int vbeMode;
    unsigned int vbeInterfaceSeg;
    unsigned int vbeInterfaceOff;
    unsigned int vbeInterfaceLen;
} __attribute__ ((packed));

struct mmapEntry_t{
    unsigned int size;                  //not include itself
    unsigned int baseAddrLow;
    unsigned int baseAddrHigh;
    unsigned int lengthLow;
    unsigned int lengthHigh;
    unsigned int type;
} __attribute__ ((packed));

extern struct multiboot_t *glbMbootPtr;

#endif  //include MULTIBOOT_H_