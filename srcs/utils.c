#include "corewar_vm.h"

/*
** get player name based on player number
*/
char	*get_player_name(t_vm *vm, int player_nbr)
{
	int			i;
	t_player	*players;

	i = 0;
	player_nbr = -player_nbr;
	players = vm->players;
	while (i < vm->players_nbr)
	{
		if (players[i].number == player_nbr)
			return (players[i].name);
		i++;
	}
	return (NULL);
}

/*
** increase the pc of the current process of quantity
** considering the cicularity of memory
*/
void	increase_pc(t_process *process, int quantity)
{
	process->pc = get_address(process->pc + quantity);
}
