
#ifndef KERNEL_MULTI_BOOT_INC_
#define KERNEL_MULTI_BOOT_INC_




enum class MBTagType_t : uint32_t
{
    End            = 0,
    CommandLine    = 1,
    BootLoaderName = 2,
    TypeModule     = 3,
    BasicMemInfo   = 4,
    BootDevice     = 5,
    MemMap         = 6,
    Vbe            = 7,
    FrameBuffer    = 8,
    ElfSections    = 9,
    Apm            = 10,
    Efi32          = 11,
    Efi64          = 12,
    SmBios         = 13,
    AcpiOld        = 14,
    AcpiNew        = 15,
    Network        = 16,
    EfiMap         = 17,
    EfiBs          = 18,
    Efi32IH        = 19,
    Efi64IH        = 20,
    LoadBaseAddr   = 21
};



struct MBTag_t
{
    MBTagType_t type;
    uint32_t size;
};



struct MBString_t : public MBTag_t
{
    char string[0];
};



struct MBMemInfo_t : public MBTag_t
{
    uint32_t memLower;
    uint32_t memUpper;
};



struct MBBootDevice_t : public MBTag_t
{
    uint32_t biosDevice;
    uint32_t partition;
    uint32_t subPartition;
};



struct MBMemMapEntry_t
{
    uint64_t address;
    uint64_t length;
    uint32_t type;

    uint32_t reserved;
};



struct MBMemMap_t : public MBTag_t
{
    uint32_t count;
    uint32_t version;
    MBMemMapEntry_t entries[0];
};



struct MBColor_t
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};



enum class MBFBType_t : uint8_t
{
    Indexed = 0,
    Rgb = 1,
    EgaText = 2
};



struct MBFrameBuffer_t : public MBTag_t
{
    uint64_t address;

    uint32_t pitch;
    uint32_t with;
    uint32_t height;

    uint8_t bitsPerPixel;
    MBFBType_t type;

    uint16_t reserved;

    union
    {
        struct
        {
            uint16_t count;
            MBColor_t colors[0];
        };

        struct
        {
            uint8_t redFieldPosition;
            uint8_t redMaskSize;

            uint8_t greenFieldPosition;
            uint8_t greenMaskSize;

            uint8_t blueFieldPosition;
            uint8_t blueMaskSize;
        };
    };
};



struct MBApm : public MBTag_t
{
    uint16_t version;
    uint16_t cseg;
    uint32_t offset;
    uint16_t cseg16;
    uint16_t dseg;
    uint16_t flags;
    uint16_t csegLen;
    uint16_t cseg16Len;
    uint16_t dsegLen;
};



struct MBAcpiOld_t : public MBTag_t
{
    uint8_t rsdp[0];
};



constexpr uint32_t MB_ExpectedMagic = 0x36d76289;



extern const uint32_t MB_Magic;



extern const void* MB_Info;




void Print(const PrintInfo_t& info, MBTagType_t type);
void Print(const PrintInfo_t& info, const MBTag_t* tagPtr);




#endif
