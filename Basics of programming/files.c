#include <stdio.h>
#define MAXLINE 1024
int main(void)
{
    FILE *fpin, *fpout;
    char line[MAXLINE];
    int c = 0;
    int max = 0;
    char *ptr, *start;

    fpin = fopen("text.txt", "rt");
    if (fpin == NULL)
        return 78;

    fpout = fopen("result.txt", "wt");
    if (fpin == NULL)
        return 76;

    while (!feof(fpin))
    {
        start = fgets(line, MAXLINE, fpin);
        ptr = start;

        if (ptr == NULL)
            break;

        while (*ptr != '\0')
        {
            3 if ((*ptr != ' ') && (*ptr != '.') && (*ptr != ','))
            {
                c++;
                if (c > max)
                {
                    max = c;
                    start = (ptr - max + 1);
                }
            }
            else c = 0;
            ptr++;
        }

        while (*start != '\0')
        {
            *start = *(start + max);
            start++;
        }
        c = 0;
        max = 0;
        fputs(line, fpout);
    }
    fclose(fpin);
    fclose(fpout);

    fclose(fpin);
    fclose(fpout);

    return 0;
}