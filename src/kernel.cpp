
#include "kernelDefs.h"
#include "string.h"
#include "printing.h"
#include "vgaColor.h"
#include "terminal.h"




Terminal_t screen;




extern "C" void kernelMain(void)
{
    screen.Clear(VgaColorValue_t::LightGrey);

    Print(screen,
          BColor_t::LightGrey,
          nl,
          FColor_t::Yellow,   " Strainge",
          FColor_t::Red,      "OS",
          FColor_t::DarkGrey, "Kernel booted.", nl,
          nl,
          FColor_t::LightBlue, " Greetings and hello world.");
}
