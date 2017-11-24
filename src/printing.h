
#ifndef KERNEL_PRINTING_INC_
#define KERNEL_PRINTING_INC_




// -------------------------------------------------------------------------------------------------
// Definitions for the formatting options.
// -------------------------------------------------------------------------------------------------



enum class Align_t
{
    Left,
    Right,
    Center
};



enum class NumRadix_t
{
    Bin,
    Dec,
    Hex
};



struct NumFmt_t
{
    static const NumRadix_t defaultRadix = NumRadix_t::Dec;
    static const Align_t defaultAlignment = Align_t::Left;
    static const size_t defaultPadding = 0;
    static const char_t defaultPadChar = ' ';

    NumRadix_t radix;
    Align_t alignment;
    size_t padding;
    char_t padChar;


    inline NumFmt_t(size_t newPadding = defaultPadding,
                    char_t newPadChar = defaultPadChar,
                    Align_t newAlignment = defaultAlignment)
    : radix(defaultRadix),
      alignment(newAlignment),
      padding(newPadding),
      padChar(newPadChar)
    {
    }



    inline NumFmt_t(NumRadix_t newRadix,
                    size_t newPadding = defaultPadding,
                    char_t newPadChar = defaultPadChar,
                    Align_t newAlignment = defaultAlignment)
    : radix(newRadix),
      alignment(newAlignment),
      padding(newPadding),
      padChar(newPadChar)
    {
    }
};



struct StrFmt_t
{
    static const Align_t defaultAlignment = Align_t::Left;
    static const size_t defaultPadding = 0;
    static const char_t defaultPadChar = ' ';

    Align_t alignment;
    size_t padding;
    char_t padChar;

    inline StrFmt_t(size_t newPadding = defaultPadding,
                    char_t newPadChar = defaultPadChar,
                    Align_t newAlignment = defaultAlignment)
    : alignment(newAlignment),
      padding(newPadding),
      padChar(newPadChar)
    {
    }
};



enum class FColor_t
{
    Black        = 0x00,
    Blue         = 0x01,
    Green        = 0x02,
    Cyan         = 0x03,
    Red          = 0x04,
    Magenta      = 0x05,
    Brown        = 0x06,
    LightGrey    = 0x07,
    DarkGrey     = 0x08,
    LightBlue    = 0x09,
    LightGreen   = 0x0a,
    LightCyan    = 0x0b,
    LightRed     = 0x0c,
    LightMagenta = 0x0d,
    Yellow       = 0x0e,
    White        = 0x0f
};



enum class BColor_t
{
    Black        = 0x00,
    Blue         = 0x10,
    Green        = 0x20,
    Cyan         = 0x30,
    Red          = 0x40,
    Magenta      = 0x50,
    Brown        = 0x60,
    LightGrey    = 0x70,
    DarkGrey     = 0x80,
    LightBlue    = 0x90,
    LightGreen   = 0xa0,
    LightCyan    = 0xb0,
    LightRed     = 0xc0,
    LightMagenta = 0xd0,
    Yellow       = 0xe0,
    White        = 0xf0
};



enum class PrintSeperator_t : uint8_t
{
    None           = 0x00,

    NewLine        = 0x01,
    Comma          = 0x02,
    Colon          = 0x03,
    SemiColon      = 0x04,

    Space          = 0x10,

    CommaSpace     = 0x12,
    ColonSpace     = 0x13,
    SemiColonSpace = 0x14
};



inline bool operator ==(uint8_t value, PrintSeperator_t sepValue)
{
    return static_cast<uint8_t>(sepValue) == value;
}



class PrintAdapter_t;



constexpr auto nl = "\n";



struct PrintInfo_t
{
    PrintAdapter_t& adapter;

    FColor_t foreColor = FColor_t::DarkGrey;
    BColor_t backColor = BColor_t::Black;

    NumFmt_t numFormat = NumFmt_t();
    StrFmt_t strFormat = StrFmt_t();

    PrintSeperator_t seperator = PrintSeperator_t::Space;

    PrintInfo_t(PrintAdapter_t& newAdapter);

    PrintInfo_t(const PrintInfo_t& printInfo, FColor_t newColor);
    PrintInfo_t(const PrintInfo_t& printInfo, BColor_t newColor);
    PrintInfo_t(const PrintInfo_t& printInfo, const NumFmt_t& newFormat);
    PrintInfo_t(const PrintInfo_t& printInfo, const StrFmt_t& newFormat);
    PrintInfo_t(const PrintInfo_t& printInfo, PrintSeperator_t newSeperator);

    protected:
        PrintInfo_t(const PrintInfo_t& printInfo);

        PrintInfo_t(PrintInfo_t&& printInfo) = delete;
        PrintInfo_t&operator =(const PrintInfo_t& printInfo) = delete;
        PrintInfo_t&operator =(PrintInfo_t&& printInfo) = delete;
};



class PrintAdapter_t
{
    protected:
        PrintAdapter_t();

    public:
        virtual ~PrintAdapter_t();

    public:
        virtual void WriteString(const PrintInfo_t& info, const char_t* string) = 0;
};



// -------------------------------------------------------------------------------------------------
// Collection of print adapters for our standard types, and a default handler for unspecialized
// values.
// -------------------------------------------------------------------------------------------------



template <typename Data_t>
inline void Print(const PrintInfo_t& info, Data_t)
{
    // TODO: Investigate compile time introspection to do something more interesting here?
    info.adapter.WriteString(info, "<UNKNOWN-DATA-TYPE>");
}



void Print(const PrintInfo_t& info, const char* string);
void Print(const PrintInfo_t& info, uint8_t value);
void Print(const PrintInfo_t& info, int8_t value);
void Print(const PrintInfo_t& info, uint16_t value);
void Print(const PrintInfo_t& info, int16_t value);
void Print(const PrintInfo_t& info, uint32_t value);
void Print(const PrintInfo_t& info, int32_t value);
void Print(const PrintInfo_t& info, float32_t value);
void Print(const PrintInfo_t& info, float64_t value);
void Print(const PrintInfo_t& info, void* value);
void Print(const PrintInfo_t& info, const Version_t& version);



// -------------------------------------------------------------------------------------------------
// .
// -------------------------------------------------------------------------------------------------



inline PrintSeperator_t BaseValue(PrintSeperator_t value)
{
    auto baseValue = static_cast<uint8_t>(value) & 0x0f;
    return static_cast<PrintSeperator_t>(baseValue);
}



inline bool IncludeSpace(PrintSeperator_t value)
{
    static const uint8_t spaceFlag = static_cast<uint8_t>(PrintSeperator_t::Space);

    auto flags = static_cast<uint8_t>(value) & 0xf0;
    return (flags & spaceFlag) == spaceFlag;
}



template <typename Data_t, typename... Args_t>
inline void Print(const PrintInfo_t& info, Data_t data, Args_t... args)
{
    Print(info, data);

    switch (BaseValue(info.seperator))
    {
        case PrintSeperator_t::NewLine:   Print(info, "\n"); break;
        case PrintSeperator_t::Comma:     Print(info, ",");  break;
        case PrintSeperator_t::Colon:     Print(info, ":");  break;
        case PrintSeperator_t::SemiColon: Print(info, ";");  break;

        default:
        case PrintSeperator_t::None:                         break;
    }

    if (IncludeSpace(info.seperator))
    {
        info.adapter.WriteString(info, " ");
    }

    Print(info, args...);
}



template <typename... Args_t>
inline void Print(const PrintInfo_t& info, FColor_t foreColor, Args_t... args)
{
    Print(PrintInfo_t(info, foreColor), args...);
}



template <typename... Args_t>
inline void Print(const PrintInfo_t& info, BColor_t backColor, Args_t... args)
{
    Print(PrintInfo_t(info, backColor), args...);
}



template <typename... Args_t>
inline void Print(const PrintInfo_t& info, const NumFmt_t& numFormat, Args_t... args)
{
    Print(PrintInfo_t(info, numFormat), args...);
}



template <typename... Args_t>
inline void Print(const PrintInfo_t& info, const StrFmt_t& strFormat, Args_t... args)
{
    Print(PrintInfo_t(info, strFormat), args...);
}



template <typename... Args_t>
inline void Print(const PrintInfo_t& info, PrintSeperator_t seperator, Args_t... args)
{
    Print(PrintInfo_t(info, seperator), args...);
}



template <typename... Args_t>
inline void Print(const PrintInfo_t& info, Args_t... args)
{
    Print(info, args...);
}



class StringAdapter_t : public PrintAdapter_t
{
    public:
        char_t* bufferPtr;
        size_t size;

        size_t position = 0;

    public:
        inline StringAdapter_t(char_t* newBufferPtr, size_t newSize)
        : bufferPtr(newBufferPtr),
          size(newSize)
        {
        }

        inline ~StringAdapter_t() override
        {
        }

    public:
        void WriteString(const PrintInfo_t& /*info*/, const char_t* string) override
        {
            if (position >= (size - 1))
            {
                return;
            }

            size_t copied = StringCopy(&bufferPtr[position], size - position, string);
            position += copied;
        }
};



template <typename... Args_t>
inline size_t PrintToString(char_t* bufferPtr, size_t size, Args_t... args)
{
    StringAdapter_t adapter(bufferPtr, size);

    Print(PrintInfo_t(adapter), args...);
    return adapter.position;
}



#endif
