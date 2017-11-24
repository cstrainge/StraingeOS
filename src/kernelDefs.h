
#ifndef KERNEL_DEFS_INC_
#define KERNEL_DEFS_INC_



using uint8_t   = unsigned char;
using  int8_t   = char;

using uint16_t  = unsigned short;
using  int16_t  = short;

using uint32_t  = unsigned int;
using  int32_t  = int;

using float32_t = float;
using float64_t = double;


using size_t    = uint32_t;
using ssize_t   = int32_t;

using char_t    =  int8_t;



struct Version_t
{
    uint16_t major;
    uint16_t minor;
    uint16_t mod;
};



#endif
