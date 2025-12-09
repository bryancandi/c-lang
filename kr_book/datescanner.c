/* Sample 7.4
 * read input lines containing dates formatted as:
 * 25 Dec 2025
 * mm/dd/yyyy
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 100

int main(void)
{
    char buffer[BUFFER];
    int day, month, year;
    char monthname[20];

    while (fgets(buffer, BUFFER, stdin))
    {
        buffer[strcspn(buffer, "\n")] = '\0'; // remove trailing newline
        if (sscanf(buffer, "%d %s %d", &day, monthname, &year) == 3)
        {
            printf("valid: %s\n", buffer); // 25 Dec 2025 date form
        }
        else if (sscanf(buffer, "%d/%d/%d", &month, &day, &year) == 3)
        {
            printf("valid: %s\n", buffer); // mm/dd/yyyy date form
        }
        else
        {
            printf("invalid: %s\n", buffer); // invalid form
        }
    }
    return 0;
}