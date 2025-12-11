/* Exercise 7-8 (with extra features)
 * paginate (v2): print files with pagination
 * Each file starts on a new page with its filename and a running page number
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define CHARS_PER_LINE 80 // set char count per line
#define LINES_PER_PAGE 50 // set line count per page

void filecopy(FILE *, FILE *, const char *filename);

int main(int argc, char *argv[])
{
    FILE *fp;
    char *prog = argv[0]; // program name for error output

    if (argc < 2)
    {
        fprintf(stderr, "%s: must provide at least one file to read\n", prog);
        exit(1);
    }

    while (--argc > 0)
    {
        if ((fp = fopen(*++argv, "r")) == NULL)
        {
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(2);
        }
        else
        {
            filecopy(fp, stdout, *argv);
            fclose(fp);
        }
    }

    if (ferror(stdout))
    {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(3);
    }
    exit(0);
}

// filecopy: copy file ifp to file ofp, paginate files
void filecopy(FILE *ifp, FILE *ofp, const char *filename)
{
    int c;
    int charnum = 0;
    int linenum = 0;
    int pagenum = 1;
    // int wordlen = 0;

    // print header for first page
    fprintf(ofp, "File: %s\t\tPage: %d\n\n", filename, pagenum);

    while ((c = getc(ifp)) != EOF)
    {
        charnum++;
        putc(c, ofp);

        if (c == '\n')
        {
            charnum = 0; // reset for next line
            linenum++;
        }
        else if (charnum >= CHARS_PER_LINE)
        {
            int nc = getc(ifp); // read ahead to next char

            if (nc == EOF)
            {
                putc('\n', ofp);
                linenum++;
                break;
            }
            if (isalpha(c) && isalpha(nc)) // inside a word
            {
                charnum++;
                putc(nc, ofp);
                // finish printing the word on the current line
                int d;
                while ((d = getc(ifp)) != EOF && isalpha(d))
                {
                    charnum++;
                    putc(d, ofp);
                }
                // also include punctuation on current line if attached to a word
                if (d == '.' || d == ',' || d == ';' || d == ':' || d == '!' || d == '?')
                {
                    charnum++;
                    putc(d, ofp);
                }
                charnum = 0;
                linenum++;
                putc('\n', ofp);
            }
            else // newline starting with nc
            {
                charnum = 1;
                linenum++;
                putc('\n', ofp);

                if (!isspace(nc))
                {
                    putc(nc, ofp);
                }
                // else skip the space
            }
        }
        if (linenum >= LINES_PER_PAGE)
        {
            linenum = 0; // reset for next page
            pagenum++;
            putc('\f', ofp); // form feed: starts a new page for printer or visual separation
            fprintf(ofp, "File: %s\t\tPage: %d\n\n", filename, pagenum);
        }
    }
}
