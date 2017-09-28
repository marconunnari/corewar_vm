/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_pc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 23:21:38 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 23:24:09 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int			get_args_sizes(t_vm *vm, t_process *process, t_op *op)
{
	int			i;
	int			res;
	uint8_t		encod;

	res = 1;
	encod = 0;
	if (op->types_encod)
	{
		encod = get_int8_at(vm, process->pc + 1);
		res++;
	}
	i = 0;
	while (i < op->args_nbr)
	{
		if (op->types_encod)
			res += get_arg_size(get_arg_type(encod, i), op->indexes);
		else
			res += get_arg_size(op->args_types[i], op->indexes);
		i++;
	}
	return (res);
}

/*
** advance the pc of the process based on the sizes of the arguments
*/

void		advance_pc(t_vm *vm, t_process *process, int diff_pc)
{
	int		i;
	int		old_pc;

	old_pc = process->pc;
	increase_pc(process, diff_pc);
	if ((vm->verbosity & 16) == 16)
	{
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ",
				diff_pc, old_pc, old_pc + diff_pc);
		i = 0;
		while (i < diff_pc)
			ft_printf("%.2x ", vm->memory[get_address(old_pc + i++)]);
		ft_putchar('\n');
	}
}
