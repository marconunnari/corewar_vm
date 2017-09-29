#include "corewar_vm.h"

static void	print(t_vm *vm, t_process *process, t_op *op, int *args)
{
	ft_printfnl("P%5d | lld %d r%d", process->number,
			op->args_types[0] == T_DIR ? args[0] :
				get_int16_at(vm, process->pc + args[0]),
			args[1]);
}

void		lld(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		val;
	int		reg;

	val = args[0];
	if (op->args_types[0] == T_IND)
		val = get_int16_at(vm, process->pc + args[0]);
	reg = args[1];
	if (!is_reg_valid(reg))
		return;
	set_reg_val(process, reg, val);
	process->carry = val == 0;
	if ((vm->verbosity & 4) == 4)
		print(vm, process, op, args);
}
