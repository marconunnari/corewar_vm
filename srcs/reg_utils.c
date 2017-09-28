#include "corewar_vm.h"

/*
** check that the register index is between 1 and REG_NUMBER
**
*/
int		is_reg_valid(int reg)
{
	if (reg < 1 || reg > REG_NUMBER)
	{
		//ft_printfnl("reg invalid %d", reg);
		return (0);
	}
	return (1);
}

int		is_reg_valid_mod(int reg, t_process *process)
{
	if (reg < 1 || reg > REG_NUMBER)
	{
		//ft_printfnl("reg invalid %d", reg);
		process->reg_invalid = 1;
		return (0);
	}
	process->reg_invalid = 0;
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
** set the register [reg] of the process to the value [val]
*/
void		set_reg_val(t_process *process, int reg, int val)
{
	process->registries[reg - 1] = val;
}
