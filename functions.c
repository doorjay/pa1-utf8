// Dorje Pradhan
// Functions for PA 1

#include <stdint.h> 
#include <stdio.h>
#include <string.h>

const int32_t MAX_ASCII = 127;

// Milestone 1 ---------------------------------------------------------

int32_t is_ascii(char str[])
{
    int32_t index = 0;

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
        if (str[index] >= 'a' && str[index] <= 'z')
        {
            str[index] = str[index] - 32;
            numCap += 1;
        }

        index += 1;
    }

    return numCap;
}

// Milestone 2 ---------------------------------------------------------

int8_t width_from_start_byte(char start_byte)
{
    if ((start_byte & 0b10000000) == 0b00000000)
    {
        return 1;        // ascii
    }
    else if ((start_byte & 0b11000000) == 0b11000000)
    {
        if ((start_byte & 0b11110000) == 0b11110000)
        {
            return 4;   // 4 byte
        }
        else if ((start_byte & 0b11100000) == 0b11100000)
        {
            return 3;   // 3 byte
        }
        else
        {
            return 2;   // 2 byte
        }
    }

    // continuation byte
    return -1;
}

int32_t utf8_strlen(char str[])
{
    int32_t index = 0;
    int32_t strLen = 0;
    while (str[index] != 0)
    {
        strLen += width_from_start_byte(str[index]);
        index += 1;
    }

    return strLen;
}

int32_t codepoint_index_to_byte_index(char str[], int32_t cpi)
{
    return strlen(str) - utf8_strlen(str) + cpi;
}




int main()
{
    char str[] = "abcd";

    printf("The string abcd is a series of ascii chars %d \n", is_ascii(str));

    printf("Before capitalizing: %s\n", str);
    int numberOfCaps = capitalize_ascii(str);
    printf("After capitalizing: %s \nNumber of letters capitalized: %d \n", str, numberOfCaps);

    char hey[] = "Héy";
    printf("\nExpecting: 2 \nGot: %d \n", width_from_start_byte(hey[1]));
    printf("Expecting: 1 \nGot: %d \n", width_from_start_byte(hey[0]));
    printf("Expecting: -1 \nGot: %d \n", width_from_start_byte(hey[2]));

    char Joseph[] = "Joséph";
    printf("\nLength of Joséph \nExpecting: 6 \nGot: %d \n", utf8_strlen(Joseph));

    printf("\nCodepoint index %d is byte index %d\n", 4, codepoint_index_to_byte_index("Josééph", 4));
    
}