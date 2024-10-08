// Dorje Pradhan
// Functions for PA 1

#include <stdint.h> 

const int_32 MAX_ASCII = 127;

// Milestone 1

int32_t is_ascii(char str[])
{
    int_32 index = 0;

    while (str[index] != 0)
    {
        if (str[index] > MAX_ASCII)
        {
            return 0;
        }

        index += 1;
    }

    return 1;
}

int32_t capitalize_ascii(char str[])
{
    int32_t index = 0;
    int32_t numCap = 0;

    while (str[index] != 0)
    {
        if (str[index] > 'a' && str[index] < 'z')
        {
            str[index] = str[index] - 32;
            numCap += 1;
        }

        index += 1;
    }

    return numCap;
}