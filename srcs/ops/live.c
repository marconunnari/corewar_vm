#include "corewar_vm.h"

void		live(t_vm *vm, t_process *process, t_op *op, int *args)
{
	(void)op;
	(void)process;
	(void)vm;
	//TODO: if (get_player(vm, player_nbr))
	ft_printfnl("A process shows that player %d (champion_name) is alive", args[0]);
	vm->last_alive = args[0];
}
