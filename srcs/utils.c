#include "corewar_vm.h"

char	*get_player_name(t_vm *vm, int player_nbr)
{
	int			i;
	t_player	*players;

	i = 0;
	players = vm->players;
	while (i < vm->players_nbr)
	{
		if (players[i].number == player_nbr)
			return (players[i].name);
		i++;
	}
	return (NULL);
}
