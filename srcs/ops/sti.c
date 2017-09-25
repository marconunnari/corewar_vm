#include "corewar_vm.h"

void		sti(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		reg;
	int		idx1;
	int		idx2;
	int		idx;

	reg = args[0];
	if (!is_reg_valid(reg))
		return ;
	idx1 = 0;
	if (op->args_types[1] == T_DIR)
		idx1 = args[1];
	else if (op->args_types[1] == T_IND)
		idx1 = get_uint32_at(vm, process->pc + (args[1] % IDX_MOD));
	else if (op->args_types[1] == T_REG)
	{
		if (!is_reg_valid(args[1]))
			return ;
		idx1 = get_reg_val(process, args[1]);
	}
	idx2 = 0;
	if (op->args_types[2] == T_DIR)
		idx2 = args[2];
	else if (op->args_types[2] == T_IND)
		idx2 = get_uint32_at(vm, process->pc + (args[2] % IDX_MOD));
	idx = idx1 + idx2;
	set_uint32(vm, process->pc + (idx % IDX_MOD), get_reg_val(process, reg));
}
