#include "corewar_vm.h"

/*
** check that the register index is between 1 and REG_NUMBER
**
*/
int		is_reg_valid(int reg)
{
	if (reg < 1 || reg > REG_NUMBER)
		return (0);
	return (1);
}

/*
** return the value of register [reg] of the process
*/
int		get_reg_val(t_process *process, int reg)
{
	return (process->registries[reg - 1]);
}

/*
** return the value of register [reg] of the first process in the stack
*/
int		get_reg_val_first(t_list *processes, int reg)
{
	t_process	*process;

	process = (t_process*)processes->content;
	return (get_reg_val(process, reg));
}

/*
** set the register [reg] of the process to the value [val]
*/
void		set_reg_val(t_process *process, int reg, int val)
{
	process->registries[reg - 1] = val;
}

/*
** set the register [reg] of the first process of the stack to the value [val]
*/
void		set_reg_val_first(t_list *processes, int reg, int val)
{
	t_process	*process;

	process = (t_process*)processes->content;
	set_reg_val(process, reg, val);
}
