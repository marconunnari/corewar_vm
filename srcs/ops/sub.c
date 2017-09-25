#include "corewar_vm.h"

void		sub(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		val1;
	int		val2;
	int		res;
	int		reg;

	(void)op;
	(void)vm;
	if (!is_reg_valid(args[0]))
		return ;
	val1 = get_reg_val(process, args[0]);
	if (!is_reg_valid(args[1]))
		return ;
	val2 = get_reg_val(process, args[1]);
	res = val1 - val2;
	reg = args[2];
	if (!is_reg_valid(reg))
		return ;
	set_reg_val(process, reg, res);
	process->carry = res == 0;
}
