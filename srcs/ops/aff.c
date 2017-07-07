#include "corewar_vm.h"

void		aff(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int	reg;

	(void)vm;
	(void)op;
	reg = args[0];
	if (is_reg_valid(reg) && vm->affiche)
		ft_printfnl("Aff: %c", get_reg_val(process, reg) % 256);
}
