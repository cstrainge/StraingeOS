
// -------------------------------------------------------------------------------------------------
// Core bootstrap code.  Based off of http://wiki.osdev.org/Bare_Bones
// -------------------------------------------------------------------------------------------------


.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

// -------------------------------------------------------------------------------------------------
// The multi-boot header.  Used so GRUB can successfuly load our Kernel.
// -------------------------------------------------------------------------------------------------

.section .multiboot
.align 4


.long MAGIC      /* The UBoot magic! */
.long FLAGS      /* We want things aligned to pages, and be provided a memory map. */
.long CHECKSUM   /* Another magic value computed to confirm to the bootloader that this kernel is
                     real. */



// -------------------------------------------------------------------------------------------------
// Reserve space for a 16k stack.
// -------------------------------------------------------------------------------------------------
.section .bss
.align 16

stackBottom: .skip 16384
stackTop:



// -------------------------------------------------------------------------------------------------
// The actual start code, call into our Kernels main C function.
// -------------------------------------------------------------------------------------------------

.section .text

.global _start
.type _start, @function

                // Setup the expected stack register, and call our main function.
_start:         mov         $stackTop, %esp
                call        kernelMain

                // If main ever returns simply go into an infinite loop.
                cli
1:              hlt
                jmp 1b

.size _start, . - _start
