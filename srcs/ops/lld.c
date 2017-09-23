#include "corewar_vm.h"

void		lld(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		val;
	int		reg;

	val = args[0];
	if (op->args_types[0] == T_IND)
		val = get_uint32_at(vm, (process->pc + args[0]));
	reg = args[1];
	if (is_reg_valid(reg))
		set_reg_val(process, reg, val);
	process->carry = val == 0;
}