#include "so_long.h"

void put_nbr(int n)
{
    char    c;

    if (n < 0)
    {
        write(1, "-", 1);
        if (n == -2147483648)
        {
            write(1, "2147483648", 10);
            return;
        }
        n = -n;
    }
    if (n >= 10)
        put_nbr(n / 10);
    c = (n % 10) + '0';
    write(1, &c, 1);
}

int ft_strlen_custom(const char *s)
{
    int len;

    len = 0;
    while (s[len])
        len++;
    return (len);
}