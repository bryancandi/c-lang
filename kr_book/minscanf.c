/* Exercise 7-4
 * minscanf: minimal private version of scanf
 */

#include <stdarg.h>
#include <stdio.h>

#define BUFFER 100

void minscanf(char *fmt, ...);

int main(void)
{
    int n;
    double f;
    char s[BUFFER];

    printf("Enter an integer, a double, and a string (eg: 10 10.5 hello):\n");
    minscanf("%d %f %s", &n, &f, s);
    printf("n = %d, f = %f, s = %s\n", n, f, s);

    return 0;
}

void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p;
    int *ip;
    double *dp;
    char *sp;

    va_start(ap, fmt);
    for (p = fmt; *p; p++)
    {
        if (*p != '%') // ignore literal characters in input
        {
            continue;
        }
        switch (*++p)
        {
        case 'd':
            ip = va_arg(ap, int *);
            scanf("%d", ip);
            break;
        case 'f':
            dp = va_arg(ap, double *);
            scanf("%lf", dp);
            break;
        case 's':
            sp = va_arg(ap, char *);
            scanf("%s", sp);
            break;
        }
    }
    va_end(ap);
}
