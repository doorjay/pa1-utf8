#include "functions.c"
#include <stdio.h> 

int main()
{
    puts("Enter a UTF-8 encoded string: ");
    char str[100];
    fgets(str, 100, stdin);

    // Remove the newline character from the input string (if it exists)
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    printf("Valid ASCII: %s \n", (is_ascii(str)) ? "true" : "false");

    char upcaseStr[100];
    int32_t index = 0;
    while (str[index] != 0)
    {
        upcaseStr[index] = str[index];
        index += 1;
    }

    int32_t numCap = capitalize_ascii(upcaseStr);
    printf("Uppercased ASCII: %s \n", upcaseStr);

    printf("Length in bytes: %ld \n", strlen(str));
    printf("Number of code points: %d \n", utf8_strlen(str));

    printf("Bytes per code point: ");
    index = 0;
    while (str[index] != 0)
    {
        int32_t bytes = width_from_start_byte(str[index]);
        printf("%d ", bytes);
        index += bytes;
    }
    printf("\n");

    char substring[25];
    utf8_substring(str, 0, 5, substring);
    printf("Substring of the first 6 code points: %s \n", substring);

    printf("Code points as decimal numbers: ");
    int32_t str_len = utf8_strlen(str);
    for (index = 0; index < str_len; index += 1)
    {
        printf("%d ", codepoint_at(str, index));
    }
    printf("\n");


    index = 0;

    printf("Animal emojis: ");
    while (index < str_len)
    {
        // Check if this code point is an animal emoji
        if (is_animal_emoji_at(str, index))
        {
            // Find the byte index of this emoji
            int32_t byte_index = codepoint_index_to_byte_index(str, index);
            int8_t char_length = width_from_start_byte(str[byte_index]);

            // Print the entire multi-byte emoji
            for (int i = 0; i < char_length; ++i)
            {
                printf("%c", str[byte_index + i]);
            }
            printf(" ");  // Add a space after the emoji
        }

        // Increment the index to move to the next code point
        index += 1;
    }

    printf("\n");
    
}