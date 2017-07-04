#include "corewar_vm.h"

void		aff(t_list *processes, t_process *process, t_op *op, int *args)
{
	int	reg;

	(void)op;
	(void)processes;
	reg = args[0];
	if (is_reg_valid(reg))
		ft_printfnl("%c", get_reg_val(process, reg) % 256);
}
