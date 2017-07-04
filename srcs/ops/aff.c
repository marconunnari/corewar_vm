#include "corewar_vm.h"

void		aff(t_process *process, t_op *op, int *args)
{
	int	reg;

	(void)op;
	reg = args[0];
	if (reg < 1 || reg > 16)
		return ;
	ft_printf("%c", process->registries[reg - 1] % 256);
}
