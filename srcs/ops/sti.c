/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 22:17:10 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 23:05:05 by mnunnari         ###   ########.fr       */
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
		idx = get_int32_at(vm, process->pc + (arg % IDX_MOD));
	else if (type == T_REG)
	{
		if (!is_reg_valid_mod(arg, process))
			return (0);
		idx = get_reg_val(process, arg);
	}
	return (idx);
}

void			sti(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		reg;
	int		idx1;
	int		idx2;
	int		idx;

	reg = args[0];
	if (!is_reg_valid(reg))
		return ;
	idx1 = get_idx(vm, process, op->args_types[1], args[1]);
	if (process->reg_invalid)
		return ;
	idx2 = get_idx(vm, process, op->args_types[2], args[2]);
	if (process->reg_invalid)
		return ;
	idx = idx1 + idx2;
	set_int(vm, process->pc + (idx % IDX_MOD), get_reg_val(process, reg));
	if ((vm->verbosity & 4) == 4)
		ft_printfnl("P%5d | sti r%d %d %d", process->number, args[0],
					idx1, idx2);
	if ((vm->verbosity & 4) == 4)
		ft_printfnl("       | -> store to %d + %d = %d (with pc and mod %d)",
			idx1, idx2, idx, process->pc + (idx % IDX_MOD));
}
