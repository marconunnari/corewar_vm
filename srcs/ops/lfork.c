#include "corewar_vm.h"

void		lfork_op(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int			i;
	t_process	*new_proc;

	(void)op;
	new_proc = new_process(0, 0, 0);
	i = 0;
	while (i < REG_NUMBER)
	{
		new_proc->registries[i] = process->registries[i];
		i++;
	}
	new_proc->pc = get_address((process->pc) + args[0]);
	new_proc->carry = process->carry;
	new_proc->lives = process->lives;
	ft_lstaddnew(&vm->processes, new_proc, sizeof(t_process));
}
