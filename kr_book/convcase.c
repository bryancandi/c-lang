/* Exercise 7-1
 * caseconv: convert input to either lower or upper case depending
 * on the name the program is invoked with, as found in argv[0]
 *
 * ./lower - the program will convert input to lower case
 * ./upper - the program will convert input to upper case
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int c;
    char *filename = strrchr(argv[0], '/'); // Unix path

    if (filename == NULL)
    {
        filename = strrchr(argv[0], '\\'); // Windows path
    }
    if (filename != NULL)
    {
        filename++; // skip over slash or backslash
    }
    else
    {
        filename = argv[0]; // no path in argv[0], use it as-is
    }

    char *dot = strrchr(filename, '.');
    if (dot && strcmp(dot, ".exe") == 0) // Windows: strip ".exe" from filename
    {
        *dot = '\0';
    }

    if (strcmp(filename, "lower") == 0)
    {
        while ((c = getchar()) != EOF)
        {
            putchar(tolower(c));
        }    
    }
    else if (strcmp(filename, "upper") == 0)
    {
        while ((c = getchar()) != EOF)
        {
            putchar(toupper(c));
        }
    }
    else
    {
        printf("Program must be invoked with filename 'lower' or 'upper'\nCurrent filename: %s\n", filename);
    }
    return 0;
}
