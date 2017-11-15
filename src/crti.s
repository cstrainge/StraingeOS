
# --------------------------------------------------------------------------------------------------
# CRT pre init/shutdown code.  Based off of http://wiki.osdev.org/Calling_Global_Constructors
# --------------------------------------------------------------------------------------------------

.section .init

.global _init
.type _init, @function


_init:          push        %ebp
                movl        %esp, %ebp
                # GCC will flesh out the contents of this function.



.section .fini

.global _fini
.type _fini, @function


_fini:          push        %ebp
                movl        %esp, %ebp
                # GCC will also fill out this function.
