#include "corewar_vm.h"

void		st(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		reg;
	int		idx;

	(void)op;
	reg = args[0];
	if (!is_reg_valid(reg))
		return ;
	idx = args[1];
	set_uint32(vm, process->pc + (idx % IDX_MOD), get_reg_val(process, reg));
}
