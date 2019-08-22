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
#define DEFAULT_FORMAT  0x00
#define OCTAL_FORMAT    0x01
#define HEX_FORMAT      0x02

#define ASCII_MIN       0x37
#define ASCII_MAX       0xFF
#define IS_ASCII(A)     (A) >= ASCII_MIN && (A) <= ASCII_MAX

uint32_t getLine(uint8_t *, uint32_t);
uint32_t printLine(uint8_t *, uint32_t, uint8_t);
void usage(void);

int main(int argc, char **argv)
{
    uint8_t buffer[MAXLEN];
    uint32_t len;
    uint8_t format;
    FILE *in_file, *out_file;

    format = DEFAULT_FORMAT;
    in_file = out_file = NULL;

    while (--argc > 0) {
        ++argv;

        if (**argv == '-' && (strlen(*argv) == 2)) {
            switch(*(*argv+1)) {
                case 'w':
                    if (argc > 0) {
                        if ((out_file = fopen(*++argv, "w")) != NULL)
                            --argc;
                        break;
                    }
                    else {
                        printf("ERROR: no output file selected\n");
                        usage();
                        return -1;
                    }
                case 'r':
                    if (argc > 0) {
                        if ((in_file = fopen(*++argv, "r")) != NULL)
                            --argc;
                        break;
                    }
                    else {
                        printf("ERROR: no input file selected\n");
                        usage();
                        return -1;
                    }
                case 'h':
                    usage();
                    return 0;
                case 'x':
                    format |= HEX_FORMAT;
                    break;
                case 'o':
                    format |= OCTAL_FORMAT;
                    break;
                default:
                    printf("ERROR: invalid input %s\n", *argv);
                    usage();
                    return -1;
            }
        }
        else if (strncmp(*argv, "--", 2) == 0) {
            if (!strcmp(*argv, "--read")) {
                if (argc > 0) {
                    if ((in_file = fopen(*++argv, "r")) != NULL)
                        --argc;
                }
                else {
                    printf("ERROR: no input file selected\n");
                    usage();
                    return -1;
                }
            }
            else if (!strcmp(*argv, "--write")){
                if (argc > 0) {
                    if ((out_file = fopen(*++argv, "w")) != NULL)
                        --argc;
                }
                else {
                    printf("ERROR: no output file selected\n");
                    usage();
                    return -1;
                }
            }
            else if (!strcmp(*argv, "--hex"))
                format |= HEX_FORMAT;
            
            else if (!strcmp(*argv, "--octal"))
                format |= OCTAL_FORMAT;
            
            else if (!strcmp(*argv, "--help")) {
                usage();
                return 0;
            }
            else {
                printf("ERROR: invalid command line input: %s\n", *argv);
                usage();
                return -1;
            }
        }
        else {
            printf("ERROR: invalid command line input: %s\n", *argv);
            usage();
            return -1;
        }

        if (format & HEX_FORMAT && format & OCTAL_FORMAT) {
            printf("ERROR: cannot specify both octal and decimal formats\n");
            usage();
            return -1;
        }
    }

    while ((len = getLine(buffer, MAXLEN)))
        printLine(buffer, len, format);
    
    if (in_file != NULL)
        fclose(in_file);
    
    if (out_file != NULL)
        fclose(out_file);

    return 0;
}

/* usage: print command line options, and usage instructions */
void usage(void)
{
    printf("\n");
    printf("usage: Ex_7_2 [-r][--read] [FILE] [-w][--write] [FILE] [-x][--hex] [-o][--octal] [-h][--help]\n");
    printf("Process arbitrary user input.\n");
    printf("\noptional arguments:\n");
    printf(" -r, --read   [FILE]  Get input from file\n");
    printf(" -w, --write  [FILE]  Write output to file\n");
    printf(" -x, --hex            Convert non-graphic characters to hexadecimal\n");
    printf(" -o, --octal          Convert non-graphic characters to octal\n");
    printf(" -h, --help           Show this help message and exit\n");
    printf("\n");
}

/* getLine: get single line from input */
uint32_t getLine(uint8_t *buffer, uint32_t len)
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
uint32_t printLine(uint8_t *line, uint32_t len, uint8_t format)
{
    while (len) {
        if (IS_ASCII(*line))
            printf("%c", *line);
        else
            printf("0x%x", *line);
        ++line;
        --len;
    }
    printf("\n");

    return 0;
}
