
#include "kernelDefs.h"
#include "multiBoot.h"
#include "string.h"
#include "printing.h"
#include "vgaColor.h"
#include "terminal.h"



Terminal_t screen;



extern "C" void KernelMain(void)
{
    screen.Clear(VgaColorValue_t::LightGrey);

    Print(screen, BC_LGry, PrintSeperator_t::None,
          nl,
          FC_Yel, " Strainge", FC_Red, "OS", FC_DGry, " kernel booted.", nl,
          nl,
          FC_DGry, " Multi-Boot magic: ", FC_Blu, Hex, MB_Magic, nl,
          FC_DGry, " Multi-Boot info:  ", FC_Blu, Hex, MB_Info, nl,
          nl);

    if (MB_Magic != MB_ExpectedMagic)
    {
        Print(screen, BC_LGry, FC_Red, PrintSeperator_t::None,
              " Multi-boot detection failed, expected value: 0x", Hex, MB_ExpectedMagic);

        return;
    }


    void* testPtr = (void*)KernelMain;

    Print(screen, BC_LGry, FC_DGry, " Multi-boot detection success.", nl, testPtr,
          nl);
}
