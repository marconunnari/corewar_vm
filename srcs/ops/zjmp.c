#include "corewar_vm.h"

void		zjmp(t_list *processes, t_process *process, t_op *op, int *args)
{
	(void)op;
	(void)processes;
	if (process->carry)
		process->pc += args[0] - T_DIR - 1;
}
