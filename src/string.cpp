
#include "kernelDefs.h"
#include "string.h"



size_t StringLength(const char_t* stringPtr)
{
    size_t i = 0;

    while (*stringPtr)
    {
        ++i;
        ++stringPtr;
    }

    return i;
}



void ReverseString(char_t* stringPtr, size_t size)
{
    for (size_t start = 0, end = size - 1; start < end; ++start, --end)
    {
        char first = stringPtr[start];

        stringPtr[start] = stringPtr[end];
        stringPtr[end] = first;
    }
}



size_t StringCopy(char_t* destPtr, size_t destSize, const char_t* sourcePtr)
{
    size_t newSize = destSize - 1;

    for (size_t i = 0; i <= newSize; ++i)
    {
        destPtr[i] = sourcePtr[i];

        if (sourcePtr[i] == 0)
        {
            return i;
        }
    }

    destPtr[destSize] = 0;
    return newSize;
}



size_t IntToString(size_t base, char_t* destPtr, size_t destSize, uint32_t number)
{
    size_t count = 0;

    if (number == 0)
    {
        destPtr[0] = '0';
        destPtr[1] = 0;
        count = 1;
    }
    else
    {
        while (   (number > 0)
               && (count < destSize))
        {
            size_t remain = number % base;
            number = number / base;

            destPtr[count] = (remain > 9) ? ('a' + (remain - 10)) : ('0' + remain);
            ++count;
        }

        destPtr[count] = 0;
        ReverseString(destPtr, count);
    }

    return count;
}



size_t IntToString(size_t base, char_t* destPtr, size_t destSize, int32_t number)
{
    size_t mod = 0;
    char* newPtr = destPtr;

    if (   (number < 0)
        && (base == 10))
    {
        destPtr[0] = '-';
        number = -number;
        mod = 1;
        newPtr = &destPtr[1];
    }

    return IntToString(base, newPtr, destSize - mod, static_cast<uint32_t>(number)) + mod;
}
