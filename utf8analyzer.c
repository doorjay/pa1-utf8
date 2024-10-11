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

    printf("Animal emojis: ");

    index = 0;
    while (index < str_len)
    {
        int32_t char_length = width_from_start_byte(str[index]);
        if (is_animal_emoji_at(str, index))
        {
            for (int32_t i = 0; i < char_length; i += 1)
            {
                printf("%c", str[index + i]);
            }

            printf(" "); // space between emojis
        }
        
        index += char_length; // move by char length
    }
    printf("\n");
    
}