#include "corewar_vm.h"

void		live(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		player_nbr;
	char	*player_name;

	(void)op;
	process->lives++;
	player_nbr = args[0];
	if ((player_name = get_player_name(vm, player_nbr)))
	{
		ft_printfnl("A process shows that player %d (\"%s\") is alive.",
				-player_nbr, player_name);
		vm->last_alive = player_nbr;
	}
}
