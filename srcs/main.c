#include "corewar_vm.h"

int	main(int argc, char **argv)
{
	char		*filename;
	int		fd;
	char		player_name[PROG_NAME_LENGTH + 1];
	t_luint		player_size;
	char		player_comment[COMMENT_LENGTH + 1];

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
	get_player_size(filename, fd, &player_size);
	ft_printfnl("Player size: %lu", player_size);
	get_player_comment(filename, fd, player_comment);
	ft_printfnl("Player comment: %s", player_comment);
	if (close(fd) == -1)
	{
		perror(filename);
		exit(0);
	}
	
}
