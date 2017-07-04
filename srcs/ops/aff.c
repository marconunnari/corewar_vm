#include "corewar_vm.h"

void		aff(t_list *processes, t_op *op, int *args)
{
	int	reg;

	(void)op;
	reg = args[0];
	if (is_reg_valid(reg))
		ft_printfnl("%c", get_reg_val_first(processes, reg) % 256);
}
