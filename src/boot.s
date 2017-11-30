
# --------------------------------------------------------------------------------------------------
#  Core bootstrap code.  Based off of http://wiki.osdev.org/Bare_Bones
# --------------------------------------------------------------------------------------------------


# --------------------------------------------------------------------------------------------------
#  The multi-boot 2 header.  Used so GRUB can successfuly load our Kernel.  We also use this
#  structure to inform GRUB or any multi-boot compliant bootloader that we want additional
#  information.
# --------------------------------------------------------------------------------------------------

.section .multiboot
.align 8



.set MB_MAGIC,          0xe85250d6
.set MB_ARCH,           0
.set MB_LENGTH,         (mb_header_end - mb_header)
.set MB_CHECKSUM,       -(MB_MAGIC + MB_ARCH + MB_LENGTH)

.set MB_TAG_MEMORY_MAP, 6
.set MB_TAG_END,        0



mb_header:      # Multi-boot 2 header.
                .long MB_MAGIC
                .long MB_ARCH
                .long MB_LENGTH
                .long MB_CHECKSUM

                # List of tags to request extra information from the boot loader.
mb_mm_tag:      .long MB_TAG_MEMORY_MAP
                .long mb_mm_tag_end - mb_mm_tag # Size.
                .long # Entry size.
                .long # Entry version.
mb_mm_tag_end:

                # End tag.
                .short MB_TAG_END
                .short 0
                .short 8
mb_header_end:



# --------------------------------------------------------------------------------------------------
#  Reserve space for a 2 MB stack.
# --------------------------------------------------------------------------------------------------
.section .bss
.align 16

stackBottom: .skip 0x4000
stackTop:



# --------------------------------------------------------------------------------------------------
#  The actual start code, call into our Kernels main C function.
# --------------------------------------------------------------------------------------------------

.section .text

.global _start
.type _start, @function




_start:         # Setup the expected stack register, and call our main function.
                mov         $stackTop, %esp

                # Save our multi-boot info.
                mov         %eax, MB_Magic
                mov         %ebx, MB_Info

                # Call all of the pre-init functions.
                call        _init

                # Now call the Kernel's main function.
                call        KernelMain

                # Make sure that all of our C++ destructors get called.
                subl        $4, %esp
                movl        $0x00, (%esp)
                call        __cxa_finalize

                # Call all of the remaining cleanup functions.
                call        _fini

                # Finally, go into an infiinite loop until the machine is shutdown/reset.
                cli
halt_loop:      hlt
                jmp halt_loop



.size _start, . - _start



# --------------------------------------------------------------------------------------------------
#  The actual start code, call into our Kernels main C function.
# --------------------------------------------------------------------------------------------------
.section .data
.align 4

.global MB_Magic, MB_Info


MB_Magic: .long 0
MB_Info:  .long 0
