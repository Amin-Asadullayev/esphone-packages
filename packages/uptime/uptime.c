int main()
{
    unsigned int s = millis() / 1000;
    int days = s / 86400;
    int hours = (s / 3600) % 24;
    int mins = (s / 60) % 60;

    printf("up ");
    if (days > 0)
        printf("%d day(s), ", days);
    printf("%02d:%02d:%02d, %u bytes free\n", hours, mins, s % 60, free_heap());
    return 0;
}
