/* Exercise 7-9
 * isupper: return 1 if c is an uppercase ASCII letter ('A'–'Z'), otherwise 0
 * isupper_macro: macro version of isupper
 * The standard library provides its own isupper in <ctype.h>
 */

#include <stdio.h>
#include <string.h>

#define isupper_macro(c) (((c) >= 'A' && (c) <= 'Z') ? 1 : 0)

int isupper(char c);

int main(void)
{
    const char *p = "This Is A String";
    int n = strlen(p);

    printf("Function:\t");
    for (int i = 0; i < n; i++)
    {
        if (isupper(p[i]))
        {
            printf("%c ", p[i]);
        }
    }
    printf("\nMacro   :\t");
    for (int i = 0; i < n; i++)
    {
        if (isupper_macro(p[i]))
        {
            printf("%c ", p[i]);
        }
    }
    return 0;
}

int isupper(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
