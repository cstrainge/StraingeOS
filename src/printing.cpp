
#include "kernelDefs.h"
#include "string.h"
#include "printing.h"



// -------------------------------------------------------------------------------------------------
// .
// -------------------------------------------------------------------------------------------------



PrintAdapter_t::PrintAdapter_t()
{
}



PrintAdapter_t::~PrintAdapter_t()
{
}



// -------------------------------------------------------------------------------------------------
// .
// -------------------------------------------------------------------------------------------------



PrintInfo_t::PrintInfo_t(PrintAdapter_t& newAdapter)
: adapter(newAdapter)
{
}



PrintInfo_t::PrintInfo_t(const PrintInfo_t& printInfo, FColor_t newColor)
: PrintInfo_t(printInfo)
{
    foreColor = newColor;
}



PrintInfo_t::PrintInfo_t(const PrintInfo_t& printInfo, BColor_t newColor)
: PrintInfo_t(printInfo)
{
    backColor = newColor;
}



PrintInfo_t::PrintInfo_t(const PrintInfo_t& printInfo, const NumFmt_t& newFormat)
: PrintInfo_t(printInfo)
{
    numFormat = newFormat;
}



PrintInfo_t::PrintInfo_t(const PrintInfo_t& printInfo, const StrFmt_t& newFormat)
: PrintInfo_t(printInfo)
{
    strFormat = newFormat;
}



PrintInfo_t::PrintInfo_t(const PrintInfo_t& printInfo, PrintSeperator_t newSeperator)
: PrintInfo_t(printInfo)
{
    seperator = newSeperator;
}



PrintInfo_t::PrintInfo_t(const PrintInfo_t& printInfo)
: adapter(printInfo.adapter),
  foreColor(printInfo.foreColor),
  backColor(printInfo.backColor),
  numFormat(printInfo.numFormat),
  strFormat(printInfo.strFormat),
  seperator(printInfo.seperator)
{
}



// -------------------------------------------------------------------------------------------------
// .
// -------------------------------------------------------------------------------------------------



static void Pad(const PrintInfo_t& info, size_t neededChars)
{
    char_t padStr[neededChars + 1] = "";

    for (size_t i = 0; i <= neededChars; ++i)
    {
        padStr[i] = info.numFormat.padChar;
    }

    info.adapter.WriteString(info, padStr);
}



void Print(const PrintInfo_t& info, const char* string)
{
    info.adapter.WriteString(info, string);
}



template <size_t byteSize, typename Value_t>
static inline void PrintIntValue(const PrintInfo_t& info, Value_t value)
{
    ssize_t maxChars = 20;

    char_t buffer[20] = "";
    ssize_t usedChars = 0;

    int base = 0;

    switch (info.numFormat.radix)
    {
        case NumRadix_t::Dec:
            //usedChars = IntToString(buffer, value);
            base = 10;
            break;

        case NumRadix_t::Hex:
            //usedChars = IntToHexString(buffer, value);
            maxChars = byteSize * 2;
            base = 16;
            break;

        case NumRadix_t::Bin:
            //usedChars = IntToBinaryString(buffer, value);
            maxChars = byteSize * 8;
            base = 2;
            break;
    }

    usedChars = IntToString(base, buffer, value);

    ssize_t strBase = 0;

    if (usedChars > maxChars)
    {
        strBase = usedChars - maxChars;
        usedChars = maxChars;
    }

    ssize_t padChars = info.numFormat.padding - usedChars;

    if (padChars <= 0)
    {
        info.adapter.WriteString(info, &buffer[strBase]);
    }
    else
    {
        switch (info.numFormat.alignment)
        {
            case Align_t::Left:
                info.adapter.WriteString(info, &buffer[strBase]);
                Pad(info, padChars);
                break;

            case Align_t::Center:
                {
                    ssize_t before = padChars / 2;
                    ssize_t after = before;

                    if ((padChars % 2) != 0)
                    {
                        after += 1;
                    }

                    Pad(info, before);
                    info.adapter.WriteString(info, &buffer[strBase]);
                    Pad(info, after);
                }
                break;

            case Align_t::Right:
                Pad(info, padChars);
                info.adapter.WriteString(info, &buffer[strBase]);
                break;
        }
    }
}



void Print(const PrintInfo_t& info, uint8_t value)
{
    PrintIntValue<1, uint32_t>(info, value);
}



void Print(const PrintInfo_t& info, int8_t value)
{
    PrintIntValue<1, int32_t>(info, value);
}



void Print(const PrintInfo_t& info, uint16_t value)
{
    PrintIntValue<2, uint32_t>(info, value);
}



void Print(const PrintInfo_t& info, int16_t value)
{
    PrintIntValue<2, uint32_t>(info, value);
}



void Print(const PrintInfo_t& info, uint32_t value)
{
    PrintIntValue<4, uint32_t>(info, value);
}



void Print(const PrintInfo_t& info, int32_t value)
{
    PrintIntValue<4, uint32_t>(info, value);
}



void Print(const PrintInfo_t& /*info*/, float32_t /*value*/)
{
}



void Print(const PrintInfo_t& /*info*/, float64_t /*value*/)
{
}



void Print(const PrintInfo_t& /*info*/, void* /*value*/)
{
}



void Print(const PrintInfo_t& info, const Version_t& version)
{
    Print(info, PrintSeperator_t::None,
                NumFmt_t(NumRadix_t::Dec),
                version.major, ".", version.minor, ".", version.mod);
}
