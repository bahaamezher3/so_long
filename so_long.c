#include "so_long.h"

int	main(int argc, char **argv)
{
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
}