#include "corewar_vm.h"

void		ld(t_process *process, t_op *op, int *args)
{
	int	val;
	int	reg;

	val = args[0];
	if (op->args_types[0] == T_IND)
		val = get_uint32_at(val);
	reg = args[1];
	if (reg < 1 || reg > 16)
		return ;
	ft_memcpy(&process->registries[reg - 1], &val, REG_SIZE);
}
