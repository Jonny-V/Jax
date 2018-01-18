#ifndef ELF_H_
#define ELF_H_

#include "multiboot.h"

#define ELF32_ST_TYPE(i) ((i) & 0xf)

struct elfSectionHeader_t{
    unsigned int name;
    unsigned int type;
    unsigned int flags;
    unsigned int addr;
    unsigned int offset;
    unsigned int size;
    unsigned int link;
    unsigned int info;
    unsigned int addrAlign;
    unsigned int entSize;
} __attribute__ ((packed));

struct elfSymbol_t{
    unsigned int name;
    unsigned int value;
    unsigned int size;
    unsigned char info;
    unsigned char other;
    unsigned short shndx;
} __attribute__ ((packed));

struct elf_t{
    struct elfSymbol_t *symtab;
    unsigned int symtabSize;
    const char *strtab;
    unsigned int strtabSize;
};

//get ELF info from multiboot_t
struct elf_t elfFromMultiboot(struct multiboot_t *mb);
//check ELF info
const char *elfCheckSymbol(unsigned int addr, struct elf_t *elf);

#endif  //include ELF_H_