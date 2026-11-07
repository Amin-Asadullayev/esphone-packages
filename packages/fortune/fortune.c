int main()
{
    char lines[32][128];
    int count = 0;
    FILE *f = fopen(fullpath("/pkg/fortune/sayings.txt"), "r");

    if (f == NULL)
    {
        printf("fortune: sayings.txt is missing - reinstall with 'pkg install fortune'\n");
        return 1;
    }
    while (count < 32 && fgets(lines[count], 128, f) != NULL)
        count++;
    fclose(f);

    if (count == 0)
        return 1;
    srand(micros());
    printf("%s", lines[rand() % count]);
    return 0;
}
