#include "corewar_vm.h"

static void	print(t_process *process, int *args)
{
	ft_printfnl("P%5d | zjmp %d %s", process->number, args[0],
			process->carry?"OK":"FAILED");
}

void		zjmp(t_vm *vm, t_process *process, t_op *op, int *args)
{
	(void)op;
	(void)vm;
	if (process->carry)
		process->pc = get_address((process->pc - 3) + (args[0] % IDX_MOD));
	if ((vm->verbosity & 4) == 4)
		print(process, args);
}
