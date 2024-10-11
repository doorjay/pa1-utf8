// Dorje Pradhan
// Functions for PA 1

#include <stdint.h> 
#include <stdio.h>
#include <string.h>

const int32_t MAX_ASCII = 127;

// Milestone 1 -----------------------------------------------------------------------------

int32_t is_ascii(char str[])
{
    int32_t index = 0;

    while (str[index] != 0)
    {
        if (str[index] > MAX_ASCII || str[index] < 0)
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

// Milestone 2 -----------------------------------------------------------------------------

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
        // add the length of each char and progress by that length
        strLen += width_from_start_byte(str[index]);
        index += 1;
    }

    return strLen;
}

int32_t codepoint_index_to_byte_index(char str[], int32_t cpi)
{
    if (str == NULL || cpi < 0)
    {
        return -1;
    }
    if (cpi == 0)
    {
        return 0;
    }

    int32_t byte_index = 0;
    int32_t cpi_count = 0;
    while (str[byte_index] != '\0')
    {
        // add byte value to index for each cpi
        byte_index += width_from_start_byte(str[byte_index]);
        cpi_count += 1;

        if (cpi_count == cpi)
        {
            return byte_index;
        }
    }

    // if gone through entire string without finding index
    return -1;
}

void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[])
{
    // Ensure indices are valid
    if (cpi_start < 0 || cpi_start >= cpi_end)
    {
        result[0] = '\0';  // Return an empty result for invalid input
        return;
    }

    // Get the actual number of code points in the string
    int32_t total_codepoints = utf8_strlen(str);

    // If cpi_end exceeds the total number of code points, clamp it to the end of the string
    if (cpi_end > total_codepoints)
    {
        cpi_end = total_codepoints;
    }

    int32_t byte_start = codepoint_index_to_byte_index(str, cpi_start);
    int32_t byte_end = codepoint_index_to_byte_index(str, cpi_end);
    int32_t result_index = 0;

    // Extract substring from byte_start to byte_end
    while (byte_start < byte_end && str[byte_start] != '\0')
    {
        result[result_index] = str[byte_start];
        result_index += 1;
        byte_start += 1;
    }

    result[result_index] = '\0';  // Null-terminate the result
}

// Milestone 3 -----------------------------------------------------------------------------

int32_t codepoint_at(char str[], int32_t cpi)
{
    int32_t byte_index = codepoint_index_to_byte_index(str, cpi);
    if (byte_index == -1)
    {
        return -1;
    }

    int8_t char_length = width_from_start_byte(str[byte_index]);
    int32_t decimal_value = 0;


    switch (char_length)
    {
        case 1:  // Single byte (ASCII)
            decimal_value = str[byte_index];
            break;

        case 2:  // 2-byte character: extract 5 bits from the first byte and 6 bits from the second byte.
            decimal_value = (str[byte_index] & 0b00011111) << 6;  // Extract 5 bits from first byte (0b110xxxxx).
            decimal_value |= (str[byte_index + 1] & 0b00111111);  // Extract 6 bits from second byte (0b10xxxxxx).
            break;

        case 3:  // 3-byte character: extract 4 bits from the first byte, 6 bits from the second and third bytes.
            decimal_value = (str[byte_index] & 0b00001111) << 12;  // Extract 4 bits from first byte (0b1110xxxx).
            decimal_value |= (str[byte_index + 1] & 0b00111111) << 6;  // Extract 6 bits from second byte.
            decimal_value |= (str[byte_index + 2] & 0b00111111);  // Extract 6 bits from third byte.
            break;

        case 4:  // 4-byte character: extract 3 bits from the first byte, 6 bits from the next three bytes.
            decimal_value = (str[byte_index] & 0b00000111) << 18;  // Extract 3 bits from first byte (0b11110xxx).
            decimal_value |= (str[byte_index + 1] & 0b00111111) << 12;  // Extract 6 bits from second byte.
            decimal_value |= (str[byte_index + 2] & 0b00111111) << 6;  // Extract 6 bits from third byte.
            decimal_value |= (str[byte_index + 3] & 0b00111111);  // Extract 6 bits from fourth byte.
            break;

        default:
            return -1;
    }

    return decimal_value;
}

char is_animal_emoji_at(char str[], int32_t cpi)
{
    int32_t code_point = codepoint_at(str, cpi);

    // emoji bounds
    int32_t lower_first_bound = 0x1F400;  // 🐀 (Rat)
    int32_t upper_first_bound = 0x1F43F;  // 🐿 (Chipmunk)
    int32_t lower_second_bound = 0x1F980; // 🦀 (Crab)
    int32_t upper_second_bound = 0x1F9AE; // 🦮 (Guide Dog)

    if ((code_point >= lower_first_bound && code_point <= upper_first_bound) || 
        (code_point >= lower_second_bound && code_point <= upper_second_bound))
    {
        return 1;
    }

    return 0;
}



/*
int main()
{
    char str[] = "abcd";

    printf("The string abcd is a series of ascii chars %d \n", is_ascii(str));

    printf("Before capitalizing: %s\n", str);
    int numberOfCaps = capitalize_ascii(str);
    printf("After capitalizing: %s \nNumber of letters capitalized: %d \n", str, numberOfCaps);

    char hey[] = "🦀🦮🦮🦀🦀🦮🦮";
    printf("\nExpecting: -1 \nGot: %d \n", width_from_start_byte(hey[1]));
    printf("Expecting: 4 \nGot: %d \n", width_from_start_byte(hey[4]));
    printf("Expecting: -1 \nGot: %d \n", width_from_start_byte(hey[2]));

    char joesph[] = "Joséph";
    printf("\nLength of Joséph \nExpecting: 7 \nGot: %d \n", utf8_strlen("🦀🦮🦮🦀🦀🦮🦮"));

    printf("\nCodepoint index is %d byte index %d\n", 3, codepoint_index_to_byte_index("🦀🦮🦮🦀🦀🦮🦮", 3));
    
    char result[17];
    utf8_substring("🦀🦮🦮🦀🦀🦮🦮", 3, 7, result);
    printf("\nString: 🦀🦮🦮🦀🦀🦮🦮\nSubstring: %s \n", result); // these emoji are 4 bytes long

    printf("\nCodepoint at %d in %s is %d\n", 4, joesph, codepoint_at(joesph, 4)); // 'p' is the 4th codepoint

    printf("\nIs 🦮 an animal?\n%s \n", (is_animal_emoji_at("🦮", 0)) ? "Yes!" : "No!" );
    printf("Is 🦂 an animal?\n%s \n", (is_animal_emoji_at("🦂", 0)) ? "Yes!" : "No!" );
    printf("Is Jeff an animal?\n%s \n", (is_animal_emoji_at("Jeff", 0)) ? "Yes!" : "No!" );
}
*/