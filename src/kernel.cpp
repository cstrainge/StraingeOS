
#include <stddef.h>
#include <stdint.h>
#include "vgaColor.h"
#include "terminal.h"




Terminal_t screen;




extern "C" void kernelMain(void)
{
    auto background = VgaColorValue_t::LightGrey;

    auto greyText = VgaColor_t(VgaColorValue_t::DarkGrey, background);
    auto blueText = VgaColor_t(VgaColorValue_t::LightBlue, background);
    auto yellow = VgaColor_t(VgaColorValue_t::Yellow, background);
    auto red = VgaColor_t(VgaColorValue_t::Red, background);

    screen.Clear(background);

    screen.WriteString("\n Strainge", yellow);
    screen.WriteString("OS", red);
    screen.WriteString(" Kernel booted.\n\n", greyText);
    screen.WriteString(" Greetings and hello world.", blueText);
}
