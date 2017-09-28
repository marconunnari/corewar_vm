/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 22:05:41 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 22:59:59 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

static int		get_idx(t_vm *vm, t_process *process, t_arg_type type, int arg)
{
	int		idx;

	process->reg_invalid = 0;
	idx = 0;
	if (type == T_DIR)
		idx = arg;
	else if (type == T_IND)
		idx = get_int16_at(vm, (process->pc + (arg % IDX_MOD)));
	else if (type == T_REG)
	{
		if (!is_reg_valid_mod(arg, process))
			return (0);
		idx = get_reg_val(process, arg);
	}
	return (idx);
}

void			ldi(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		idx1;
	int		idx2;
	int		val;
	int		reg;

	idx1 = get_idx(vm, process, op->args_types[0], args[0]);
	if (process->reg_invalid)
		return ;
	idx2 = get_idx(vm, process, op->args_types[1], args[1]);
	if (process->reg_invalid)
		return ;
	val = get_int32_at(vm, (process->pc + ((idx1 + idx2) % IDX_MOD)));
	reg = args[2];
	if (!is_reg_valid(reg))
		return ;
	set_reg_val(process, reg, val);
	if ((vm->verbosity & 4) == 4)
		ft_printfnl("P%5d | ldi %d %d r%d", process->number,
				idx1, idx2, args[2]);
	if ((vm->verbosity & 4) == 4)
		ft_printfnl("       | -> load from %d + %d = %d (with pc and mod %d)",
				idx1, idx2, idx1 + idx2,
				process->pc + ((idx1 + idx2) % IDX_MOD));
}
