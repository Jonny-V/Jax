ENTRY(start)
SECTIONS
{
	. = 0x100000;

	PROVIDE(kernelStart = .);
	.text :
	{
		*(.text)
		. = ALIGN(4096);
	}
	.data :
	{
		*(.data)
		*(.rodata)
		. = ALIGN(4096);
	}
	.bss :
	{
		*(.bss)
		. = ALIGN(4096);
	}
	.stab :
	{
		*(.stab)
		. = ALIGN(4096);
	}
	.stabstr :
	{
		*(.stabstr)
	 	. = ALIGN(4096);
	}
	PROVIDE(kernelEnd = .);
	
	/DISCARD/ : { *(.comment) *(.eh_frame) }
}

