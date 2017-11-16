
// -------------------------------------------------------------------------------------------------
//  Essential C++ support code, from http://wiki.osdev.org/C%2B%2B
// -------------------------------------------------------------------------------------------------

#include "kernelDefs.h"




// -------------------------------------------------------------------------------------------------
// Operator new/delete and virtual method handling.
// -------------------------------------------------------------------------------------------------

extern "C" void __cxa_pure_virtual()
{
    // Is this a panic situation?
}


void operator delete(void*)
{
    //
}




// -------------------------------------------------------------------------------------------------
//  Code to handle global value destructors.
// -------------------------------------------------------------------------------------------------

typedef void (*DestructorFunc_t)(void*);


struct ExitFuncEntry_t
{
    DestructorFunc_t destructorPtr;
    void* objectPtr;
    void* dsoHandlePtr;
};



static const size_t ExitTableCount = 128;
static ExitFuncEntry_t ExitTable[ExitTableCount] = { { nullptr, nullptr, nullptr} };

static size_t ExitTableIndex = 0;




extern "C" int __cxa_atexit(DestructorFunc_t destructorPtr, void* objectPtr, void* dsoHandlePtr)
{
    if (ExitTableIndex >= ExitTableCount)
    {
        return -1;
    }

    auto& newEntry = ExitTable[ExitTableIndex];

    newEntry.destructorPtr = destructorPtr;
    newEntry.objectPtr = objectPtr;
    newEntry.dsoHandlePtr = dsoHandlePtr;

    return 0;
}


extern "C" void __cxa_finalize(void* f)
{
    for (ssize_t index = ExitTableIndex; index >= 0; --index)
    {
        auto& entry = ExitTable[index];

        if (   ((f == nullptr) || (entry.destructorPtr == f))
            && (entry.destructorPtr != nullptr))
        {
            entry.destructorPtr(entry.objectPtr);
        }
    }
}
