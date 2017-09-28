/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 20:59:11 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 20:59:12 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void		aff(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int	reg;

	(void)op;
	reg = args[0];
	if (!is_reg_valid(reg))
		return ;
	if (vm->affiche)
		ft_printfnl("Aff: %c", get_reg_val(process, reg) % 256);
}
