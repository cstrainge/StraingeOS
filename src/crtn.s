
# --------------------------------------------------------------------------------------------------
# CRT pre init/shutdown code.  Based off of http://wiki.osdev.org/Calling_Global_Constructors
# --------------------------------------------------------------------------------------------------

.section .init
                /* GCC will flesh out the contents of this function. */
                popl        %ebp
                ret


.section .fini
                /* GCC will also fill out this function. */
                popl        %ebp
                ret
