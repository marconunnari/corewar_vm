#include "corewar_vm.h"

extern uint8_t	memory[MEM_SIZE];

void		sti(t_process *process, t_op *op, int *args)
{
	int	reg;
	int	idx1;
	int	idx2;

	reg = args[0];
	if (reg < 1 || reg > 16)
		return ;
	idx1 = args[1];
	if (op->args_types[1] == T_IND)
		idx1 = get_uint32_at(idx1);
	idx2 = args[2];
	if (op->args_types[2] == T_REG)
	{
		if (idx2 < 1 || idx2 > 16)
			return ;
		idx2 = process->registries[idx2 - 1];
	}
	ft_memcpy(&process->registries[reg - 1],
		&memory[(idx1 + idx2) / MEM_SIZE], REG_SIZE);
}
