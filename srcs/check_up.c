/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 23:09:48 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 23:11:01 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** reset the variable cycle to die according to the rules of the game
*/

void		reset_cycle_to_die(t_vm *vm, int *cycle_to_die, int total_lives)
{
	static int		decreases;
	static int		checkups_without_decrease;

	if (total_lives >= NBR_LIVE || checkups_without_decrease == MAX_CHECKS - 1)
	{
		decreases++;
		*cycle_to_die = CYCLE_TO_DIE - (CYCLE_DELTA * decreases);
		checkups_without_decrease = 0;
		if ((vm->verbosity & 2) == 2)
			ft_printfnl("Cycle to die is now %d", *cycle_to_die);
	}
	else
	{
		*cycle_to_die = CYCLE_TO_DIE - (CYCLE_DELTA * decreases);
		checkups_without_decrease++;
	}
}

/*
** function passes as parameter to ft_lstremoveif
** to removing deads objects
*/

int			is_process_dead(void *content, void *param)
{
	t_process	*process;
	t_vm		*vm;

	vm = (t_vm*)param;
	process = (t_process*)content;
	if ((vm->verbosity & 8) == 8 && process->lives == 0)
		ft_printfnl("Process %d is dead", process->number);
	return (process->lives == 0);
}

void		free_process(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

/*
** remove the deads processes
** reset the the cycle_to_die variable according to the rules of the game
*/

void		check_up(t_vm *vm, int *cycle_to_die)
{
	t_list		*current;
	t_process	*process;
	int			total_lives;

	ft_lstremoveif(&vm->processes, free_process, is_process_dead, vm);
	total_lives = 0;
	current = vm->processes;
	while (current)
	{
		process = (t_process*)current->content;
		total_lives += process->lives;
		process->lives = 0;
		current = current->next;
	}
	reset_cycle_to_die(vm, cycle_to_die, total_lives);
}
