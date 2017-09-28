/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 23:31:32 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 23:34:25 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void		print_processes(t_vm *vm)
{
	t_list		*processes;
	t_process	*process;

	processes = vm->processes;
	while (processes)
	{
		process = (t_process*)processes->content;
		ft_printfnl("process: pc %d lives %d",
				process->pc, process->lives);
		processes = processes->next;
	}
}

void		dump(t_vm *vm)
{
	print_memory(vm);
	exit(0);
}

void		print_op(t_op *op, int *args, t_process *process)
{
	int			i;

	ft_printf("P%5d | %s", process->number, op->mnemonic);
	i = 0;
	while (i < op->args_nbr)
		ft_printf(" %d", args[i++]);
	ft_putchar('\n');
}
