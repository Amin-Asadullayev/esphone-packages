int ignore_case = 0;

int contains(char *hay, char *needle)
{
    int hn = strlen(hay);
    int nn = strlen(needle);
    int i;
    int j;

    for (i = 0; i + nn <= hn; i++)
    {
        for (j = 0; j < nn; j++)
        {
            if (ignore_case ? tolower(hay[i + j]) != tolower(needle[j]) : hay[i + j] != needle[j])
                break;
        }
        if (j == nn)
            return 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    char line[256];
    FILE *f;
    int numbers = 0;
    int first = 1;
    int found = 0;
    int lineno_ = 0;
    int i;
    char *word;

    while (first < argc && argv[first][0] == '-')
    {
        if (strcmp(argv[first], "-i") == 0)
            ignore_case = 1;
        else if (strcmp(argv[first], "-n") == 0)
            numbers = 1;
        else
            break;
        first++;
    }
    if (argc - first < 2)
    {
        printf("usage: grep [-i] [-n] WORD FILE...\n");
        return 2;
    }
    word = argv[first];

    for (i = first + 1; i < argc; i++)
    {
        f = fopen(fullpath(argv[i]), "r");
        if (f == NULL)
        {
            printf("grep: %s: not found\n", argv[i]);
            continue;
        }
        lineno_ = 0;
        while (fgets(line, sizeof(line), f) != NULL)
        {
            lineno_++;
            if (!contains(line, word))
                continue;
            found = 1;
            if (argc - first > 2)
                printf("%s:", argv[i]);
            if (numbers)
                printf("%d:", lineno_);
            printf("%s", line);
            if (line[strlen(line) - 1] != '\n')
                printf("\n");
        }
        fclose(f);
    }
    return found ? 0 : 1;
}
