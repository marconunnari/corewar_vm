#include "corewar_vm.h"

void		lldi(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		idx1;
	int		idx2;
	int		val;
	int		reg;

	if (op->args_types[0] == T_DIR)
		idx1 = args[0];
	else if (op->args_types[0] == T_IND)
		idx1 = get_uint16_at(vm, (process->pc + args[0]));
	else if (op->args_types[0] == T_REG)
	{
		if (!is_reg_valid(args[0]))
			return ;
		idx1 = get_reg_val(process, args[0]);
	}
	idx2 = 0;
	if (op->args_types[1] == T_DIR)
		idx2 = args[1];
	else if (op->args_types[1] == T_IND)
		idx2 = get_uint16_at(vm, (process->pc + args[1]));
	val = get_uint32_at(vm, (process->pc + (idx1 + idx2)));
	reg = args[2];
	if (is_reg_valid(reg))
		set_reg_val(process, reg, val);
	process->carry = val == 0;
}
