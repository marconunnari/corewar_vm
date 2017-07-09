#include "corewar_vm.h"

void		sti(t_vm *vm, t_process *process, t_op *op, int *args)
{
	//sti r1, %:live, %1
	int		reg;
	int		idx;

	(void)op;
	reg = args[0];
	if (!is_reg_valid(reg))
		return ;
	idx = args[1] + args[2];
	set_uint32(vm, process->pc + (idx % IDX_MOD), get_reg_val(process, reg));

}
