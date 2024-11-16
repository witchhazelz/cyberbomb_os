//declare 'kernel_main' label as being external to this file bc its the name of the main c function in kernel.c 

'kernel.c'
.extern kernal_main

//declare the 'start' label as global for linker
.global start

//bootloader and grub need to know basic info about kernel
//so we gotta give grub info using multiboot

//to define a valid multiboot header, we need to hardcode some constants into the executable
.set MB_MAGIC, 0x1BADB002
.set MB_FLAGS, (1<<0)|(1<< 1)
//calculate checksum that inclused all prev values

.set MB_CHECKSUM, (0-(MB_MAGIC + MB_FLAGS))

//start section of executable that will contain multiboot header

.section .multiboot
.align 4 //following data is aligned on a multiple of 4 bytes

.long MB_MAGIC
.long MB_FLAGS
//use checksum we calculated

.long MB_CHECKSUM

//this section contains data initialized to zeroes when kernel is loaded
.section .bss
//c code needs a stack to run, allocate 4096 bytes to our stack we can expand later
.align 16
stack_bottom:
.skip 4096 //reserves stack
stack_top:
//contains actual assembly code to be run when kernel loads
.section .text
//here is start label

start:
//well we need an environment first...so we need to set up our stack and we're like, done- stack grows downward btw
mov $stack_top, $esp //set the stack pointer to the top of the stack

//call main c function
call kernal_main

//if the kernels c code ever returns, woo how mysterious.. we can just hang the cpu lmao
hang:
cli
hlt
jmp hang
//kabaam we r done, if it didnt work, loop around and try 
