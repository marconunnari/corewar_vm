#include "corewar_vm.h"

int	main(int argc, char **argv)
{
	char	*filename;
	int	fd;
	char	player_name[PROG_NAME_LENGTH + 1];

	filename = argv[argc - 1];
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		perror(filename);
		exit(0);
	}
	check_magic(filename, fd);
	ft_printfnl("This is a corewar executable!!");
	get_player_name(filename, fd, player_name);
	ft_printfnl("Player name: %s", player_name);
	if (close(fd) == -1)
	{
		perror(filename);
		exit(0);
	}
}
