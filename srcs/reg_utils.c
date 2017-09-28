/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 23:34:34 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 23:34:52 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** check that the register index is between 1 and REG_NUMBER
*/

int		is_reg_valid(int reg)
{
	if (reg < 1 || reg > REG_NUMBER)
	{
		return (0);
	}
	return (1);
}

int		is_reg_valid_mod(int reg, t_process *process)
{
	if (reg < 1 || reg > REG_NUMBER)
	{
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

void	set_reg_val(t_process *process, int reg, int val)
{
	process->registries[reg - 1] = val;
}
