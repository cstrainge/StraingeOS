
#include "kernelDefs.h"
#include "string.h"
#include "printing.h"
#include "vgaColor.h"
#include "terminal.h"




static const uint32_t MBExpectedMagic = 0x36d76289;



Terminal_t screen;




extern "C" void KernelMain(uint32_t magic, void* infoPtr)
{
    screen.Clear(VgaColorValue_t::LightGrey);

    Print(screen, BC_LGry,
          nl,
          FC_Yel, "Strainge", FC_Red, "OS", FC_DGry, "Kernel booted.", nl,
          nl,
          FC_DGry, "Multi-Boot magic:", FC_Blu, Hex, magic, nl,
          FC_DGry, "Multi-Boot info: ", FC_Blu, Hex, (uint32_t)infoPtr, nl,
          nl);

    if (magic != MBExpectedMagic)
    {
        Print(screen, BC_LGry, FC_Red, " Multi-boot detection failed, expected value:",
              Hex, MBExpectedMagic);

        return;
    }


    Print(screen, BC_LGry, FC_Grn, " Multi-boot detection success.", nl,
          nl);
}
