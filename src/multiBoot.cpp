
#include "kernelDefs.h"
#include "string.h"
#include "printing.h"
#include "multiBoot.h"





void Print(const PrintInfo_t& info, MBTagType_t type)
{
    const char* strPtr = "UNKNOWN";

    switch (type)
    {
        case MBTagType_t::End:            strPtr = "End";            break;
        case MBTagType_t::CommandLine:    strPtr = "CommandLine";    break;
        case MBTagType_t::BootLoaderName: strPtr = "BootLoaderName"; break;
        case MBTagType_t::TypeModule:     strPtr = "TypeModule";     break;
        case MBTagType_t::BasicMemInfo:   strPtr = "BasicMemInfo";   break;
        case MBTagType_t::BootDevice:     strPtr = "BootDevice";     break;
        case MBTagType_t::MemMap:         strPtr = "MemMap";         break;
        case MBTagType_t::Vbe:            strPtr = "Vbe";            break;
        case MBTagType_t::FrameBuffer:    strPtr = "FrameBuffer";    break;
        case MBTagType_t::ElfSections:    strPtr = "ElfSections";    break;
        case MBTagType_t::Apm:            strPtr = "Apm";            break;
        case MBTagType_t::Efi32:          strPtr = "Efi32";          break;
        case MBTagType_t::Efi64:          strPtr = "Efi64";          break;
        case MBTagType_t::SmBios:         strPtr = "SmBios";         break;
        case MBTagType_t::AcpiOld:        strPtr = "AcpiOld";        break;
        case MBTagType_t::AcpiNew:        strPtr = "AcpiNew";        break;
        case MBTagType_t::Network:        strPtr = "Network";        break;
        case MBTagType_t::EfiMap:         strPtr = "EfiMap";         break;
        case MBTagType_t::EfiBs:          strPtr = "EfiBs";          break;
        case MBTagType_t::Efi32IH:        strPtr = "Efi32IH";        break;
        case MBTagType_t::Efi64IH:        strPtr = "Efi64IH";        break;
        case MBTagType_t::LoadBaseAddr:   strPtr = "LoadBaseAddr";   break;
    }

    Print(info, strPtr);
}



void Print(const PrintInfo_t& info, const MBTag_t* tagPtr)
{
    Print(info, PrintSeperator_t::None,
          tagPtr->type, "<", static_cast<uint32_t>(tagPtr->type), "> ",
          tagPtr->size);
}
