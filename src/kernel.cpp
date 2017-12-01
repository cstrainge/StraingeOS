
#include "kernelDefs.h"
#include "string.h"
#include "printing.h"
#include "multiBoot.h"
#include "vgaColor.h"
#include "terminal.h"



// TODO: Look at print bug, ending a print with a number is BAD.
Terminal_t screen;



static void WalkTags(const void* startPtr)
{
    const char* nextPtr = reinterpret_cast<const char*>(startPtr);


    size_t size = *(size_t *) startPtr;

    Print(screen, BC_LGry, " Announced size:", size, nl, nl);
    nextPtr += 8;


    const MBTag_t* tagPtr = reinterpret_cast<const MBTag_t*>(nextPtr);

    size_t index = 0;

    do
    {
        Print(screen, BC_LGry, " Tag", index, ":", tagPtr);

        switch (tagPtr->type)
        {
            case MBTagType_t::CommandLine:
            case MBTagType_t::BootLoaderName:
                {
                    auto strPtr = reinterpret_cast<const MBString_t*>(tagPtr);
                    Print(screen, BC_LGry, PrintSeperator_t::None,
                          FC_Blu, " : \"", strPtr->string, "\"");
                }
                break;

            case MBTagType_t::BasicMemInfo:
                {
                    auto memPtr = reinterpret_cast<const MBMemInfo_t*>(tagPtr);
                    Print(screen, BC_LGry, PrintSeperator_t::None, " : ", Hex,
                          "Low ", FC_Blu, "0x", memPtr->memLower, FC_DGry,
                          ", High ", FC_Blu, "0x", memPtr->memUpper, FC_DGry, ".");
                }
                break;

            case MBTagType_t::MemMap:
                {
                    auto memPtr = reinterpret_cast<const MBMemMap_t*>(tagPtr);

                    Print(screen, BC_LGry, PrintSeperator_t::None, " : ",
                          "version ", FC_Blu, memPtr->version, FC_DGry,
                          ", count ", FC_Blu, memPtr->count, FC_DGry,
                          ".");

                    /*for (size_t i = 0; i < memPtr->count; ++i)
                    {
                        auto& entry = memPtr->entries[i];

                        Print(screen, BC_LGry, PrintSeperator_t::None, "    ",
                              i, Hex, ": type: ", entry.type,
                              " - addr: ", (uint32_t)entry.address,
                              ", len: ", (uint32_t)entry.length, ".", nl);
                    }*/
                }
                break;

            case MBTagType_t::FrameBuffer:
                {
                    auto framePtr = reinterpret_cast<const MBFrameBuffer_t*>(tagPtr);

                    Print(screen, BC_LGry, PrintSeperator_t::None, " : ",
                          "pitch ", FC_Blu, framePtr->pitch, FC_DGry,
                          ", width ", FC_Blu, framePtr->with, FC_DGry,
                          ", height ", FC_Blu, framePtr->height, FC_DGry,
                          ", bpp ", FC_Blu, framePtr->bitsPerPixel, FC_DGry,
                          ", type ", FC_Blu, static_cast<uint8_t>(framePtr->type), FC_DGry,
                          ".");
                }
                break;

            case MBTagType_t::BootDevice:
                {
                    auto bootPtr = reinterpret_cast<const MBBootDevice_t*>(tagPtr);

                    Print(screen, BC_LGry, PrintSeperator_t::None, " : ",
                          "device: ", FC_Blu, Hex, bootPtr->biosDevice, FC_DGry,
                          ", part: ", FC_Blu, bootPtr->partition, FC_DGry,
                          ", sub: ", FC_Blu, bootPtr->subPartition, FC_DGry, ".");
                }
                break;

            default:
                break;
        }

        Print(screen, nl);

        nextPtr += (tagPtr->size + 7) & ~7;
        tagPtr = reinterpret_cast<const MBTag_t*>(nextPtr);
        ++index;

        if (index > 10)
        {
            break;
        }
    }
    while (tagPtr->type != MBTagType_t::End);

    Print(screen, BC_LGry, " EOL");
}



extern "C" void KernelMain(void)
{
    screen.Clear(VgaColorValue_t::LightGrey);

    Print(screen, BC_LGry, PrintSeperator_t::None,
          nl,
          FC_Yel, " Strainge", FC_Red, "OS", FC_DGry, " kernel booted.", nl,
          nl,
          FC_DGry, " Multi-Boot magic: ", FC_Blu, Hex, "0x", MB_Magic, nl,
          FC_DGry, " Multi-Boot info:  ", FC_Blu, Hex, MB_Info, nl,
          nl);

    if (MB_Magic != MB_ExpectedMagic)
    {
        Print(screen, BC_LGry, FC_Red, PrintSeperator_t::None,
              " Multi-boot detection failed, expected value: 0x", Hex, MB_ExpectedMagic);

        return;
    }

    if (reinterpret_cast<size_t>(MB_Info) & 7)
    {
        Print(screen, BC_LGry, FC_Red, "Unaligned Multi-Boot information pointer.");
        return;
    }


    //


    Print(screen, BC_LGry, FC_DGry, " Multi-boot detection success.", nl,
          nl);

    WalkTags(MB_Info);
}
