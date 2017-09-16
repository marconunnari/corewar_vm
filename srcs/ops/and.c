#include "corewar_vm.h"

void		and(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		val1;
	int		val2;
	int		res;
	int		reg;

	(void)vm;
	(void)op;
	if (op->args_types[0] == T_DIR)
		val1 = args[0];
	if (op->args_types[0] == T_REG)
	{
		if (!is_reg_valid(args[0]))
			return ;
		val1 = get_reg_val(process, args[0]);
	}
	if (op->args_types[1] == T_DIR)
		val2 = args[1];
	if (op->args_types[1] == T_REG)
	{
		if (!is_reg_valid(args[1]))
			return ;
		val2 = get_reg_val(process, args[1]);
	}
	res = val1 & val2;
	ft_printf("val1 %d \n", val1);
	ft_printf("val2 %d \n", val2);
	ft_printf("res %d \n", res);
	reg = args[2];
	if (!is_reg_valid(reg))
		return ;
	set_reg_val(process, reg, res);
	process->carry = res == 0;
}
