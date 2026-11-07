int main(int argc, char **argv)
{
    char line[256];
    FILE *f;
    int max = 10;
    int n = 0;
    char *name;

    if (argc == 4 && strcmp(argv[1], "-n") == 0)
    {
        max = atoi(argv[2]);
        name = argv[3];
    }
    else if (argc == 2)
        name = argv[1];
    else
    {
        printf("usage: head [-n N] FILE\n");
        return 1;
    }

    f = fopen(fullpath(name), "r");
    if (f == NULL)
    {
        printf("head: %s: not found\n", name);
        return 1;
    }
    while (n < max && fgets(line, sizeof(line), f) != NULL)
    {
        printf("%s", line);
        n++;
    }
    fclose(f);
    return 0;
}
