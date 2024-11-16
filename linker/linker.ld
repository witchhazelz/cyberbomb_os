/*the bootloader will start execution at the symbol designated as the entry point. in this case, thats start (defined in start.s)
*/
ENTRY(start)

/* tell link part of compiler where many sections of kernel will be put into final kernel executable*/
sections{
	/*begin putting sections at 1M, a good place for kernels to be loaded by bootloader
	/because memory below 1m is reserved for other x86 things so we cant use it lol*/
	. = 1M;
	/*align all sections in the executable at multiples of 4k, will be useful when we add paging*/
	/* first put multiboot header, required to be near start of executable otherwisr the bootloader wont find it
	*/
	/*multiboot header is READONLY data, so we can put it in a '.rodata' section */
	.rodata BLOCK(4K): ALIGN(4K)
	{
		*(.multiboot)
	}
	/*Executable code*/
	.text BLOCK(4K): ALIGN (4K)
	{
		*(.text)
	}
	/*rodata (initialized)*/
	.data BLOCK(4K): ALIGN (4K)
	{
		*(.data)
	}
	/*read-write data (uninitialized) and stack*/
	.bss BLOCK(4K): ALIGN (4K)
	{
		*(COMMON)
		*(.bss)
	}
}
