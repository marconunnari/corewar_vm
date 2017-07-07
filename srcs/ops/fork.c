#include "corewar_vm.h"

void		fork_op(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int			i;
	t_process	*new_process;

	(void)op;
	new_process = (t_process*)malloc(sizeof(t_process));
	i = 0;
	while (i < REG_NUMBER)
	{
		new_process->registries[i] = process->registries[i];
		i++;
	}
	new_process->pc = (process->pc + (args[0] % IDX_MOD)) % MEM_SIZE;
	new_process->carry = process->carry;
	new_process->wait = -1;
	ft_lstaddnew(&vm->processes, new_process, sizeof(t_process));
}
