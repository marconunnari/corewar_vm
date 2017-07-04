#include "corewar_vm.h"

extern uint8_t	memory[MEM_SIZE];

void		sti(t_list *processes, t_op *op, int *args)
{
	int	reg;
	int	idx1;
	int	idx2;

	reg = args[0];
	if (!is_reg_valid(reg))
		return ;
	idx1 = args[1];
	if (op->args_types[1] == T_IND)
		idx1 = get_uint32_at(idx1);
	if (op->args_types[1] == T_REG)
	{
		if (!is_reg_valid(idx1))
			return ;
		idx1 = get_reg_val_first(processes, idx1);
	}
	idx2 = args[2];
	if (op->args_types[2] == T_REG)
	{
		if (!is_reg_valid(idx2))
			return ;
		idx1 = get_reg_val_first(processes, idx2);
	}
	set_uint32(idx1 + idx2, get_reg_val_first(processes, reg));
}
