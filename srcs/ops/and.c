/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 21:01:10 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 21:47:48 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

static int		get_val(t_vm *vm, t_process *process, t_arg_type arg_type, int arg)
{
	int		val;

	val = 0;
	if (arg_type == T_DIR)
		val = arg;
	else if (arg_type == T_IND)
		val = get_int32_at(vm, process->pc + arg);
	else if (arg_type == T_REG)
	{
		if (!is_reg_valid_mod(arg, process))
			return (0);
		val = get_reg_val(process, arg);
	}
	return (val);
}

void			and(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		val1;
	int		val2;
	int		res;
	int		reg;

	val1 = get_val(vm, process, op->args_types[0], args[0]);
	if (process->reg_invalid)
		return ;
	val2 = get_val(vm, process, op->args_types[1], args[1]);
	if (process->reg_invalid)
		return ;
	res = val1 & val2;
	reg = args[2];
	if (!is_reg_valid(reg))
		return ;
	set_reg_val(process, reg, res);
	process->carry = res == 0;
	if ((vm->verbosity & 4) == 4)
		ft_printfnl("P%5d | and %d %d r%d", process->number,
				val1, val2, args[2]);
}
