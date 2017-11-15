
#ifndef _VGA_COLOR_INC_
#define _VGA_COLOR_INC_



enum class VgaColorValue_t : uint8_t
{
    Black        =  0,
    Blue         =  1,
    Green        =  2,
    Cyan         =  3,
    Red          =  4,
    Magenta      =  5,
    Brown        =  6,
    LightGrey    =  7,
    DarkGrey     =  8,
    LightBlue    =  9,
    LightGreen   = 10,
    LightCyan    = 11,
    LightRed     = 12,
    LightMagenta = 13,
    Yellow       = 14,
    White        = 15
};



struct VgaColor_t
{
    uint8_t value;

    inline VgaColor_t(VgaColorValue_t fg, VgaColorValue_t bg)
    {
        value = (((uint8_t)bg) << 4) | ((uint8_t)fg);
    }

    inline VgaColorValue_t Fg() const
    {
        return (VgaColorValue_t)(value & 0x0F);
    }

    inline VgaColorValue_t Bg() const
    {
        return (VgaColorValue_t)((value & 0xF0) >> 4);
    }
};



struct VgaCharacter_t
{
    uint16_t value;

    inline VgaCharacter_t(uint8_t character, VgaColor_t color)
    {
        value = ((uint16_t)color.value << 8) | character;
    }

    inline VgaCharacter_t(uint8_t character, VgaColorValue_t fg, VgaColorValue_t bg)
    {
        value = (VgaColor_t(fg, bg).value << 8) | character;
    }
};



#endif
