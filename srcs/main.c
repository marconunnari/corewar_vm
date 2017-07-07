#include "corewar_vm.h"

int		main(int argc, char **argv)
{
	t_vm		vm;

	if (argc == 1)
		print_usage();
	parse_args(argv + 1, &vm);
	if (vm.players_nbr == 0)
		print_usage();
	print_intro(&vm);
	init_players(&vm);
	exec(&vm);
	print_winner(&vm);
}
