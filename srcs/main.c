#include "corewar_vm.h"

void	pexit(char *filename)
{
	perror(filename);
	exit(0);
}

int		main(int argc, char **argv)
{
	int		i;
	t_player	player;

	i = 1;
	while (i < argc)
	{
		player = parse_player(argv[i]);
		ft_printfnl("player '%s' fat |%u| that say '%s'",
				player.name, player.size, player.comment);
		load(player);
		i++;
	}
}
