#include <stdio.h>
#include <malloc/malloc.h>
#include <stdlib.h>
#define MAXLINE 100
int words(char line[])
{
    int i = 0;
    int count = 0;
    int flag = 0;
    while (line[i] == ' ' && line[i] != '\0')
    {
        i++;
        flag = 0;
    }
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && flag == 0)
        {
            flag = 1;
            count++;
        }
        else if (line[i] == ' ')
            flag = 0;
        3 i++;
    }
    return count;
}
int main(void)
{

    FILE *fpin;
    FILE *fpout;

    char *line_ptr;
    int count;
    int max_count = 0;
    int i;
    int j = 1;
    int num_str = 0;

    fpin = fopen("text.txt", "rt");
    fpout = fopen("result.txt", "wt");

    if (fpin == NULL)
    {
        return 255;
    }

    if (fpout == NULL)
    {
        return 200;
    }

    line_ptr = (char *)calloc(MAXLINE, sizeof(char));

    while (!feof(fpin))
    {
        fgets(line_ptr, MAXLINE, fpin);
        num_str++;
        count = words(line_ptr);

 if (count > max_count
 max_count = count;
    }

    rewind(fpin);

    for (i = 0; i < num_str; i++)
    {
        while (!feof(fpin))
        {
            4 fgets(line_ptr, MAXLINE, fpin);
            count = words(line_ptr);

            if (count == j)
                fputs(line_ptr, fpout);
        }

        rewind(fpin);
        j++;
    }

    fclose(fpin);
    fclose(fpout);

    printf("Конец программы.\n");

    return 0;
}