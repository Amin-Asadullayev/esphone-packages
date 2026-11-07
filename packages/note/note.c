int main(int argc, char **argv)
{
    char line[200];
    char path[64];
    FILE *f;
    int i;
    int n = 0;

    strcpy(path, fullpath("/pkg/note/notes.txt"));

    if (argc >= 3 && strcmp(argv[1], "add") == 0)
    {
        f = fopen(path, "a");
        if (f == NULL)
        {
            printf("note: can't write %s\n", path);
            return 1;
        }
        for (i = 2; i < argc; i++)
            fprintf(f, i > 2 ? " %s" : "%s", argv[i]);
        fprintf(f, "\n");
        fclose(f);
        printf("Saved.\n");
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "clear") == 0)
    {
        remove(path);
        printf("All notes deleted.\n");
        return 0;
    }

    if (argc != 1)
    {
        printf("usage: note | note add TEXT... | note clear\n");
        return 1;
    }

    f = fopen(path, "r");
    while (f != NULL && fgets(line, sizeof(line), f) != NULL)
        printf("%2d. %s", ++n, line);
    if (f != NULL)
        fclose(f);
    if (n == 0)
        printf("No notes yet - try: note add buy milk\n");
    return 0;
}
