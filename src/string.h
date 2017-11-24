
#ifndef KERNEL_STRING_INC_
#define KERNEL_STRING_INC_



size_t StringLength(const char_t* stringPtr);




void ReverseString(char_t* stringPtr, size_t size);



template <size_t stringSize>
inline void ReverseString(char_t (&string)[stringSize])
{
    ReverseString(string, stringSize);
}



size_t StringCopy(char_t* destPtr, size_t destSize, const char_t* sourcePtr);



template <size_t stringSize>
inline size_t StringCopy(char_t (&destPtr)[stringSize], const char_t* sourcePtr)
{
    return StringCopy(destPtr, stringSize, sourcePtr);
}



size_t IntToString(size_t base, char_t* destPtr, size_t destSize, uint32_t number);
size_t IntToString(size_t base, char_t* destPtr, size_t destSize, int32_t number);




template <size_t stringSize>
inline size_t IntToString(size_t base, char_t (&destPtr)[stringSize], uint32_t number)
{
    return IntToString(base, destPtr, stringSize, number);
}



template <size_t stringSize>
inline size_t IntToString(size_t base, char_t (&destPtr)[stringSize], int32_t number)
{
    return IntToString(base, destPtr, stringSize, number);
}



#endif
