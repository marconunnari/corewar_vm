#include "corewar_vm.h"

void		st(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		reg;
	int		idx;
	int		val;

	reg = args[0];
	if (!is_reg_valid(reg))
		return ;
	val = get_reg_val(process, reg);
	if (op->args_types[1] == T_IND) {
		idx = args[1];
		set_int(vm, process->pc + (idx % IDX_MOD), val);
	} else if (op->args_types[1] == T_REG) {
		reg = args[1];
		if (is_reg_valid(reg))
			set_reg_val(process, reg, val);
	}
}
