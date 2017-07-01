#include "corewar_vm.h"

uint8_t		memory[MEM_SIZE];

void		pexit(char *filename)
{
	perror(filename);
	exit(0);
}

int		main(int argc, char **argv)
{
	t_player	player;
	uint32_t	i;

	player = parse_player(argv[argc - 1]);
	ft_printfnl("player '%s' fat |%u| that say '%s'",
		player.name, player.size, player.comment);
	i = 0;
	while (i < player.size)
	{
		ft_printf("%02x ", memory[i]);
		if (i % 16 == 15)
			ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}
