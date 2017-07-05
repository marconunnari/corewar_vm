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
** get players files from command line, parse them and fill
** the array of players.
** return the number of players
*/
void		get_players(int argc, char **argv, t_vm *vm)
{
	int		i;
	t_player	player;

	i = 0;
	if (argc > MAX_PLAYERS)
		ft_err(1, "Too many players");
	while (i < argc)
	{
		player = parse_player(argv[i]);
		player.number = i + 1;
		ft_printfnl("player n. %d called '%s' fat |%u| that say '%s'",
			player.number, player.name, player.size, player.comment);
		vm->players[i] = player;
		i++;
	}
	vm->players_nbr = i;
}

/*
** load the players in memory
** create a process for each player and add it to the stack of processes
*/
void		init_players(t_vm *vm)
{
	int		i;
	t_process	*process;
	t_player	player;

	i = 0;
	while (i < vm->players_nbr)
	{
		player = vm->players[i];
		lseek(player.fd, 4, SEEK_CUR);
		read(player.fd, &vm->memory[(MEM_SIZE / vm->players_nbr) * i], CHAMP_MAX_SIZE);
		if (close(player.fd) == -1)
		{
			perror(player.filename);
			exit(0);
		}
		process = new_process(player.number,
				(MEM_SIZE / vm->players_nbr) * i, 0);
		ft_lstaddnew(&vm->processes, process, sizeof(t_process));
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_vm		vm;

	get_players(--argc, ++argv, &vm);
	vm.processes = NULL;
	init_players(&vm);
	exec(&vm);
	print_memory(&vm);
	ft_printfnl("last alive %d", vm.last_alive);
}
