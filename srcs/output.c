#include "corewar_vm.h"

void		print_memory(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0)
			ft_printf("%#06x:", i);
		ft_printf(" %02x", vm->memory[i]);
		if (i % 32 == 31)
			ft_putchar('\n');
		i++;
	}
}

void		print_usage()
{
	ft_printfnl("usage: corewar [-dump nbr_cycles] [[-n number] champion1.cor]");
	exit(0);
}

void		print_intro(t_vm *vm)
{
	int			i;
	t_player	player;

	ft_printfnl("Introducing contestants...");
	i = 0;
	while (i < vm->players_nbr)
	{
		player = vm->players[i];
		ft_printfnl("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !",
				player.number, player.size, player.name, player.comment);
		i++;
	}
}
