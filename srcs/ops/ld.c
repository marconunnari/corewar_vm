#include "corewar_vm.h"

void		ld(t_list *processes, t_process *process, t_op *op, int *args)
{
	int		val;
	int		reg;

	(void)processes;
	val = args[0];
	if (op->args_types[0] == T_IND)
		val = get_uint32_at(process->pc + val);
	reg = args[1];
	if (is_reg_valid(reg))
		set_reg_val(process, reg, val);
}
