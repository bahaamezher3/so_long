#include "so_long.h"

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void map_dimentioner(char *filename, int *a, int *b)
{
	int		fd;
	int		i;
	int		j;
	int		line_Count;
	
	line_Count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(1);
	i = ft_strlen(get_next_line(fd));
	j = i;
	while (i = ft_strlen(get_next_line(fd)))
	{
		if(i != j)
		{
			perror("Map Error");
			exit(1);
		}
		j = i;
		line_Count++;
	}
	*a = line_Count;
	*b = i; 
}

char **read_map_with_error_handle(char *filename)
{
	int		fd;
	char	**map_fill;
	int		max_i;
	int		max_j;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(1);
	max_i = 0;
	max_j = 0;
	map_dimentioner(filename, &max_i, &max_j);

}

int	main(int argc, char **argv)
{
	char	**map;

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
}