#include "common.h"
#include "types.h"
#include "string.h"
#include "elf.h"

struct elf_t elfFromMultiboot(struct multiboot_t *mb)
{
    int i;
    struct elf_t elf;
    struct elfSectionHeader_t *sh = (struct elfSectionHeader_t *)mb->addr;

    unsigned int shstrtab = sh[mb->shndx].addr;
    for(i = 0; i< mb->num; i++)
    {
        const char *name = (const char *)(shstrtab + sh[i].name);
        if( strcmp(name, ".strtab") == 0)
        {
            elf.strtab = (const char *)sh[i].addr;
            elf.strtabSize = sh[i].size;
        }
        if( strcmp(name, ".symtab") == 0)
        {
            elf.symtab = (struct elfSymbol_t *)sh[i].addr;
            elf.symtabSize = sh[i].size;
        }
    }
    return elf;
}

const char *elfCheckSymbol(unsigned int addr, struct elf_t *elf)
{
    int i;
    for(i = 0; i < (elf->symtabSize / sizeof(struct elfSymbol_t)); i++)
    {
        if(ELF32_ST_TYPE(elf->symtab[i].info) != 0x2)
            continue;
        if((addr >= elf->symtab[i].value) && (addr < (elf->symtab[i].value + elf->symtab[i].size)))
            return (const char *)((unsigned int)elf->strtab + elf->symtab[i].name);
    }
    return NULL;
}