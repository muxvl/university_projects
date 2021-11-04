#include <stdio.h>
#define MAXLINE 1024
int main(void)
{
    FILE *fpin, *fp_glas, *fp_sogl;
    //char *ptr;
    char line[MAXLINE];

    fpin = fopen("text.txt", "rt");
    if (fpin == NULL)
        return 70;

    fp_glas = fopen("glas.txt", "wt");
    if (fp_glas == NULL)
        return 70;
    fp_sogl = fopen("sogl.txt", "wt");
    if (fp_sogl == NULL)
        return 70;

    while (!feof(fpin))
    {
        fgets(line, MAXLINE, fpin);

        if ((line[0] == 'A') || (line[0] == 'a') || (line[0] == 'O') ||
            (line[0] == 'o') || (line[0] == 'E') || (line[0] == 'e') || (line[0] == 'U') || (line[0] == 'u') || (line[0] == 'I') || (line[0] == 'i') ||
            (line[0] == 'Y') || (line[0] == 'y'))
            fputs(line, fp_glas);
        else
            fputs(line, fp_sogl);
    }

    fclose(fpin);
    fclose(fp_glas);
    fclose(fp_sogl);

    return 0;
}