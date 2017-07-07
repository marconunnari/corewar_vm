#include "corewar_vm.h"

void		zjmp(t_vm *vm, t_process *process, t_op *op, int *args)
{
	(void)op;
	(void)vm;
	if (process->carry)
		increase_pc(process, args[0] - T_DIR - 1);
}
