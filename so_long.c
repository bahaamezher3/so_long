#include "so_long.h"

int check_file_access(char *filename)
{
    int fd;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);
    close(fd);
    return (1);
}

int get_clean_length(char *line)
{
    int len;
    
    len = ft_strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r' || line[len - 1] == ' ' || line[len - 1] == '\t'))
    {
        line[len - 1] = '\0';
        len--;
    }
    return (len);
}

void map_dimentioner(char *filename, int *a, int *b)
{
    int     fd;
    int     len;
    int     expected_len;
    int     line_count;
    char    *tmp;
    
    line_count = 0;
    expected_len = -1;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        exit(1);
    
    while (1)
    {
        tmp = get_next_line(fd);
        if (!tmp)
            break;
        len = get_clean_length(tmp);
        if (len == 0)
        {
            free(tmp);
            continue;
        }
        if (expected_len == -1)
            expected_len = len;
        else if (len != expected_len)
        {
            write(2, "Map Error: Inconsistent line length\n", 37);
            free(tmp);
            close(fd);
            exit(1);
        }
        line_count++;
        free(tmp);
    }
    close(fd);
    if (line_count == 0 || expected_len <= 0)
    {
        write(2, "Map Error: Empty or invalid map\n", 32);
        exit(1);
    }
    *a = line_count;
    *b = expected_len; 
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
    char    *tmp;
    int     len;

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
        tmp = get_next_line(fd);
        if (!tmp)
        {
            freer(map_fill, i);
            close(fd);
            exit(3);
        }
        len = get_clean_length(tmp);
        if (len == 0)
        {
            free(tmp);
            continue;
        }
        map_fill[i] = tmp;
        i++;
    }
    map_fill[i] = NULL;
    close(fd);
    return (map_fill);
}

int main(int argc, char **argv)
{
    char    **map;
    int     max_i;
    int     max_j;

    if (argc != 2)
    {
        write(1, "Usage: ./so_long map.ber\n", 26);
        return (1);
    }
    
    if (!check_file_access(argv[1]))
    {
        write(1, "Error Opening map.ber\n", 23);
        return (1);
    }

    map_dimentioner(argv[1], &max_i, &max_j);
    map = read_map_with_error_handle(argv[1]);
    if (!map)
    {
        write(2, "Error: Failed to load map\n", 26);
        return (1);
    }

    if (check_path(map, max_i, max_j))
        write(1, "VALID MAP\n", 11);
    else
        write(1, "INVALID MAP\n", 13);
    freer(map, max_i);
    return (0);
}