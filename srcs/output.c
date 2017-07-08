#include "corewar_vm.h"

void		print_memory(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("%s%#.4x : ", i == 0 ? "0x" : "",  i);
		ft_printf("%02x ", vm->memory[i]);
		if (i % 64 == 63)
			ft_putchar('\n');
		i++;
	}
}

void		print_usage()
{
	ft_printfnl("usage: corewar [-d nbr_cycles] [-a] <[-n number] champion1.cor> <..>");
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

void		print_winner(t_vm *vm)
{
	ft_printfnl("Contestant %d, \"%s\", has won !",
			vm->last_alive, get_player_name(vm, vm->last_alive));
}

void		print_processes(t_list *processes)
{
	int		i;

	i = 0;
	while (processes)
	{
		ft_printfnl("process %d pc %d", i++,
				((t_process*)processes->content)->pc);
		processes = processes->next;
	}
	ft_putchar('\n');
}

void		dump(t_vm *vm)
{
	print_memory(vm);
	exit(0);
}

void			print_op(t_op *op, int *args)
{
	int			i;

	ft_printf("%s", op->mnemonic);
	i = 0;
	while (i < op->args_nbr)
		ft_printf(" %d", args[i++]);
	ft_putchar('\n');
}


