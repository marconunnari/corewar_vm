/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 23:13:23 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 23:14:14 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** this function execute an operation, advance the pc
** of the process and set the operation to be scheduled
*/

void			exec_op(t_vm *vm, t_process *process, t_op *op)
{
	int			args_sizes;
	int			args_valid;
	int32_t		args[MAX_ARGS_NUMBER];

	args_valid = get_op_args(vm, op, process->pc + 1, args);
	args_sizes = get_args_sizes(vm, process, op);
	if (args_valid)
		op->run(vm, process, op, args);
	if (op->opcode != 9)
		advance_pc(vm, process, args_sizes);
	process->wait = 0;
}

/*
** This function executes a cycle of code.
** Iterates over each process and see if it has to wait,
** execute or schedule
*/

void			do_cycle(t_vm *vm)
{
	t_list		*processes;
	t_process	*process;
	t_op		*op;

	processes = vm->processes;
	while (processes)
	{
		process = (t_process*)processes->content;
		if (process->wait == 0)
		{
			op = get_op(get_int8_at(vm, process->pc));
			if (op)
			{
				process->op = op;
				process->wait = op->cycles - 1;
			}
			else
				increase_pc(process, 1);
		}
		else if (process->wait == 1)
			exec_op(vm, process, process->op);
		else
			process->wait--;
		processes = processes->next;
	}
}

/*
** execute the code in the virtual machine according to the rules of
** the game. This is where take place the loop of execution.
*/

void			exec(t_vm *vm)
{
	uintmax_t	cycle;
	int			cycle_to_die;

	cycle = 1;
	cycle_to_die = CYCLE_TO_DIE;
	while (1)
	{
		if (cycle_to_die <= 0)
			check_up(vm, &cycle_to_die);
		if (vm->processes == NULL)
			break ;
		if (vm->dump && cycle == vm->dump_cycle + 1)
			dump(vm);
		if ((vm->verbosity & 2) == 2)
			ft_printfnl("It is now cycle %ju", cycle);
		cycle_to_die--;
		do_cycle(vm);
		cycle++;
	}
}
