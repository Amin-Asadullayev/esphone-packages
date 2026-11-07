int main(int argc, char **argv)
{
    char city[64];
    char url[200];
    char *buf;
    char *p;
    char *q;
    FILE *f;
    int status;
    int i;

    city[0] = '\0';
    if (argc > 1)
    {
        strncpy(city, argv[1], sizeof(city) - 1);
        city[sizeof(city) - 1] = '\0';
    }
    else
    {
        f = fopen(fullpath("/pkg/weather/city.txt"), "r");
        if (f != NULL)
        {
            if (fgets(city, sizeof(city), f) == NULL)
                city[0] = '\0';
            fclose(f);
        }
        city[strcspn(city, "\r\n")] = '\0';
    }
    if (city[0] == '\0')
    {
        printf("usage: weather CITY  (or put a city in /pkg/weather/city.txt)\n");
        return 1;
    }
    if (!net_status())
    {
        printf("weather: not connected - use 'wifi connect' first\n");
        return 1;
    }

    for (i = 0; city[i] != '\0'; i++)
    {
        if (city[i] == ' ')
            city[i] = '+';
    }

    sprintf(url, "https://wttr.in/%s?m&format=%%l:+%%C+%%t+%%w", city);

    buf = malloc(512);
    status = http_get(url, buf, 512);
    if (status < 0)
    {
        printf("weather: %s\n", http_error());
        return 1;
    }
    if (status != 200)
    {
        printf("weather: wttr.in returned HTTP %d\n", status);
        return 1;
    }

    q = buf;
    for (p = buf; *p != '\0'; p++)
    {
        if ((*p & 0x80) == 0)
            *q++ = *p;
    }
    *q = '\0';
    printf("%s\n", buf);
    free(buf);
    return 0;
}
