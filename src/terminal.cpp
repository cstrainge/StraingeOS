
#include "kernelDefs.h"
#include "vgaColor.h"
#include "terminal.h"




Terminal_t::Terminal_t()
:   width(80),
    height(25),
    x(0),
    y(0),
    bufferPtr((uint16_t*)0xB8000)
{
}



void Terminal_t::Clear(VgaColorValue_t clearColor)
{
    const VgaCharacter_t fillCharacter = VgaCharacter_t(' ', clearColor, clearColor);

    x = 0;
    y = 0;

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            const size_t index = y * width + x;
            bufferPtr[index] = fillCharacter.value;
        }
    }
}




void Terminal_t::WriteChar(unsigned char character, VgaColor_t color)
{
    const size_t index = y * width + x;

    bufferPtr[index] = VgaCharacter_t(character, color).value;
    IncColumn();
}



void Terminal_t::WriteString(const char* string, VgaColor_t color)
{
    for (size_t i = 0; string[i] != 0; ++i)
    {
        char next = string[i];

        switch (next)
        {
            case '\n':
                IncLine();
                break;

            case '\t':
                WriteString("    ", color);
                break;

            default:
                WriteChar(string[i], color);
                break;
        }
    }
}



void Terminal_t::IncLine()
{
    x = 0;
    ++y;

    if (y > height)
    {
        y = 0;
    }
}



void Terminal_t::IncColumn()
{
    ++x;

    if (x > width)
    {
        IncLine();
    }
}
