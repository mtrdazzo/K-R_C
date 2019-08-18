/*
 *
 * Exercise 7-2
 * 
 * Write a program that will print arbitrary input in a sensible way. As a minimum, it should print 
 * non-graphic characters in octal or hexadecimal according to a local custom, and break long text
 * lines.
 * 
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAXLEN 1000
#define LETTER_a        0x61
#define LETTER_z        0x7A
#define LETTER_A        0x41
#define LETTER_Z        0x5A
#define NUM_0           0x30
#define NUM_9           0X39

#define IS_LOWERCASE(A) (A) >= LETTER_a && (A) <= LETTER_z
#define IS_UPPERCASE(A) (A) >= LETTER_A && (A) <= LETTER_Z
#define IS_NUM(A)       (A) >= NUM_0 && (A) <= NUM_9
#define IS_ALPHA(A)     (IS_LOWERCASE(A)) || (IS_UPPERCASE(A))
#define IS_ALPHA_NUM(A) (IS_ALPHA(A)) || (IS_NUM(A))

uint32_t getLine(char *, uint32_t);
uint32_t printLine(char *, uint32_t, char);
void usage(void);

int main(int argc, char **argv)
{
    usage();
    return 0;
    char buffer[MAXLEN];
    uint32_t len;
    char format;

    if (argc > 1)
    {
        if (!strcmp(*(argv+1), "-o"))
            format = 'o';
        else if (!strcmp(*(argv+1), "-x"))
            format = 'x';
        else if (!strcmp(*(argv+1), "-c"))
            format = 'c';
        else
        {
            printf("Incorrect format argument: %s\n", *(argv+1));
            return -1;
        }
    }
    else
        format = 'c';

    while ((len = getLine(buffer, MAXLEN)))
        printLine(buffer, len, format);
    return 0;
}

/* usage: print command line options, and usage instructions */
void usage(void)
{
    printf("\n");
    printf("usage: Ex_7_2 options\n");
    printf("Process arbitrary user input.\n");
    printf("\noptional arguments:\n");
    printf(" -f, --file   [FILE]        Get input from file\n");
    printf(" -t, --output [OUTPUT FILE] Send output to file\n");
    printf(" -x, --hex                  Convert non-graphic characters to hexadecimal\n");
    printf(" -o, --octal                Convert non-graphic characters to octal\n");
    printf(" -h, --help                 Show this help message and exit\n");
    printf("\n");
}

/* getLine: get single line from input */
uint32_t getLine(char *buffer, uint32_t len)
{
    uint8_t c;

    while ((len-1) && (c = getchar()) != EOF && c != '\n') {
        *buffer++ = c;
        --len;
    }
    *buffer = '\0';
    
    return MAXLEN - len;
}

/* printLine: print single line from input */
uint32_t printLine(char *line, uint32_t len, char format)
{
    while (len) {
        if (IS_ALPHA_NUM(*line))
            printf("%c", *line);
        else
            printf("0x%x", *line);
        ++line;
        --len;
    }
    printf("\n");

    return 0;
}
