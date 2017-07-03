#include "corewar_vm.h"

uint8_t		memory[MEM_SIZE];

/*
** get memory at index
** considering that memory is circular
*/
uint8_t		get_memory_at(int i)
{
	return (memory[i % MEM_SIZE]);
}

t_process	*new_process(uint8_t *player_number, uint16_t pc, char carry)
{
	t_process	*process;

	process = (t_process*)malloc(sizeof(t_process));
	ft_memcpy(process->registries[0], player_number, REG_SIZE);
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
int		get_players(int argc, char **argv, t_player *players)
{
	int		i;
	t_player	player;

	i = 1;
	while (i < argc)
	{
		player = parse_player(argv[i]);
		player.number = i;
		ft_printfnl("player n. %d called '%s' fat |%u| that say '%s'",
			player.number, player.name, player.size, player.comment);
		players[i - 1] = player;
		i++;
	}
	if (i - 1 > MAX_PLAYERS)
		ft_err(1, "Too many players");
	return(i - 1);
}

/*
** load the players in memory
** create a process for each player and add it to the processes stack
*/
void		init_players(t_player *players, int players_nbr, t_list **processes)
{
	int		i;
	t_process	*process;
	t_player	player;

	i = 0;
	while (i < players_nbr)
	{
		player = players[i];
		lseek(player.fd, 4, SEEK_CUR);
		read(player.fd, &memory[(MEM_SIZE / players_nbr) * i], CHAMP_MAX_SIZE);
		if (close(player.fd) == -1)
			pexit(player.filename);
		process = new_process((uint8_t *)&player.number,
				(MEM_SIZE / players_nbr) * i, 0);
		ft_lstaddnew(processes, process, sizeof(t_process));
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_player	players[MAX_PLAYERS];
	int		players_nbr;
	t_list		*processes;

	players_nbr = get_players(argc, argv, players);
	processes = NULL;
	init_players(players, players_nbr, &processes);
	exec(processes);
}
