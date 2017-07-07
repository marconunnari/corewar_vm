#include "corewar_vm.h"

t_process	*new_process(int player_number, uint16_t pc, char carry)
{
	t_process	*process;

	process = (t_process*)malloc(sizeof(t_process));
	process->registries[0] = player_number;
	process->pc = pc;
	process->carry = carry;
	process->wait = -1;
	return (process);
}

/*
** load the players in memory
** create a process for each player and add it to the stack of processes
*/
void		init_players(t_vm *vm)
{
	int		i;
	uint8_t	buf[CHAMP_MAX_SIZE];
	t_process	*process;
	t_player	player;

	ft_bzero(vm->memory, MEM_SIZE);
	i = 0;
	vm->processes = NULL;
	while (i < vm->players_nbr)
	{
		player = vm->players[i];
		lseek(player.fd, 4, SEEK_CUR);
		read(player.fd, buf, CHAMP_MAX_SIZE);
		set_buf(vm, (MEM_SIZE / vm->players_nbr) * i, buf, CHAMP_MAX_SIZE);
		close(player.fd);
		process = new_process(player.number,
				(MEM_SIZE / vm->players_nbr) * i, 0);
		ft_lstaddnew(&vm->processes, process, sizeof(t_process));
		i++;
	}
}

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
