#include "so_long.h"

void map_dimentioner(char *filename, int *a, int *b)
{
    int     fd;
    int     i;
    int     j;
    int     line_count;
    char    *tmp;
    
    line_count = 1;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        exit(1);
    tmp = get_next_line(fd);
    if (!tmp)
        exit(1);
    i = ft_strlen(tmp);
    j = i;
    free(tmp);
    while (1)
    {
        tmp = get_next_line(fd);
        if (!tmp)
            break;
        i = ft_strlen(tmp);
        if (i != j)
        {
            free(tmp);
            perror("Map Error");
            exit(1);
        }
        j = i;
        line_count++;
        free(tmp);
    }
    close(fd);
    *a = line_count;
    *b = i; 
}

void freer(char **map, int i)
{
    int k = 0;
    while (k < i)
    {
        free(map[k]);
        k++;
    }
    free(map);
}

char **read_map_with_error_handle(char *filename)
{
    int     fd;
    char    **map_fill;
    int     max_i;
    int     max_j;
    int     i;

    map_dimentioner(filename, &max_i, &max_j);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        exit(1);

    map_fill = malloc(sizeof(char *) * (max_i + 1));
    if (!map_fill)
        exit(2);

    i = 0;
    while (i < max_i)
    {
        map_fill[i] = get_next_line(fd);
        if (!map_fill[i])
        {
            freer(map_fill, i);
            close(fd);
            exit(3);
        }
        i++;
    }
    map_fill[i] = NULL;
    close(fd);
    return (map_fill);
}

int main(int argc, char **argv)
{
    char    **map;
    int     i = 0;

    if (argc != 2)
    {
        write(1, "Usage: ./so_long map.ber\n", 26);
        return (1);
    }
    if (open(argv[1], O_RDONLY) == -1)
    {
        write(1, "Error Opening map.ber\n", 23);
        return (1);
    }
    map = read_map_with_error_handle(argv[1]);

    freer(map, i);
    return (0);
}
