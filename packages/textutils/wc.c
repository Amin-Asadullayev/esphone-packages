int main(int argc, char **argv)
{
    FILE *f;
    int c;
    int i;
    int lines;
    int words;
    int bytes;
    int inword;

    if (argc < 2)
    {
        printf("usage: wc FILE...\n");
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        f = fopen(fullpath(argv[i]), "r");
        if (f == NULL)
        {
            printf("wc: %s: not found\n", argv[i]);
            continue;
        }
        lines = 0;
        words = 0;
        bytes = 0;
        inword = 0;
        while ((c = fgetc(f)) != EOF)
        {
            bytes++;
            if (c == '\n')
                lines++;
            if (isspace(c))
                inword = 0;
            else if (!inword)
            {
                inword = 1;
                words++;
            }
        }
        fclose(f);
        printf("%6d %6d %7d %s\n", lines, words, bytes, argv[i]);
    }
    return 0;
}
