
#ifndef KERNEL_TERMINAL_INC_
#define KERNEL_TERMINAL_INC_



class Terminal_t
{
    private:
        size_t width;
        size_t height;

        size_t x;
        size_t y;

        uint16_t* bufferPtr;

    public:
        Terminal_t();
        Terminal_t(const Terminal_t& term) = delete;
        Terminal_t(Terminal_t&& term) = delete;

        virtual ~Terminal_t()
        {
        }

    public:
        Terminal_t& operator =(const Terminal_t& term) = delete;
        Terminal_t& operator =(Terminal_t&& term) = delete;

    public:
        void Clear(VgaColorValue_t clearColor);

    public:
        void WriteChar(unsigned char character, VgaColor_t color);
        void WriteString(const char* string, VgaColor_t color);

    public:
        void IncLine();
        void IncColumn();

    public:
        class TerminalPrintAdapter_t : public PrintAdapter_t
        {
            public:
                Terminal_t& terminal;

            public:
                TerminalPrintAdapter_t(Terminal_t& newTerminal)
                : PrintAdapter_t(),
                  terminal(newTerminal)
                {
                }

                ~TerminalPrintAdapter_t() override
                {
                }

            public:
                void WriteString(const PrintInfo_t& info, const char_t* string) override
                {
                    auto intColor = static_cast<uint8_t>(info.backColor) >> 4;

                    auto fg = static_cast<VgaColorValue_t>(info.foreColor);
                    auto bg = static_cast<VgaColorValue_t>(intColor);

                    auto color = VgaColor_t(fg, bg);

                    terminal.WriteString(string, color);
                }
        };
};



template <typename... Args_t>
inline void Print(Terminal_t& terminal, Args_t... args)
{
    Terminal_t::TerminalPrintAdapter_t adapter(terminal);

    Print(PrintInfo_t(adapter), args...);
}




#endif
