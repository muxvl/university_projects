#define MAXLINE 100
int main()
{
    char line[MAXLINE];
    int c = 0;
    int max = 0;
    char *buffer;
    char *start;
    gets(line);
    buffer = line;
    start = line;
    while (*buffer != '\0')
    {
        if ((*buffer != ' ') && (*buffer != '.') && (*buffer != ','))
        {
            c++;
            if (c > max)
            {
                max = c;
                start = (buffer - max + 1);
            }
        }
        else
            c = 0;
        buffer++;
    }

    while (*start != '\0')
    {
        *start = *(start + max);
        start++;
    }

    puts(line);
    return 0;
}
