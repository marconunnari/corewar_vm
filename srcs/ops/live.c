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

void		live(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		player_nbr;
	char	*player_name;

	(void)op;
	(void)process;
	player_nbr = args[0];
	if ((player_name = get_player_name(vm, player_nbr)))
		ft_printfnl("A process shows that player %d (%s) is alive",
				player_nbr, player_name);
	vm->last_alive = args[0];
}
