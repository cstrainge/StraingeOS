
#ifndef _TERMINAL_INC_
#define _TERMINAL_INC_



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
};



#endif
