#include "corewar_vm.h"

/*
** reset the variable cycle to die according to the rules of the game
*/
void		reset_cycle_to_die(int *cycle_to_die, int total_lives)
{
	static int		decreases;
	static int		checkups_without_decrease;

	if (total_lives >= NBR_LIVE || checkups_without_decrease == MAX_CHECKS)
	{
		decreases++;
		*cycle_to_die = CYCLE_TO_DIE - (CYCLE_DELTA * decreases);
		checkups_without_decrease = 0;
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
int		is_process_dead(void *content, void *param)
{
	t_process	*process;

	(void)param;
	process = (t_process*)content;
	return (process->lives == 0);
}

/*
** remove the deads processes
** reset the the cycle_to_die variable according to the rules of the game
**
*/
void		check_up(t_vm *vm, int *cycle_to_die)
{
	t_list		*current;
	t_process	*process;
	int		total_lives;

	ft_lstremoveif(&vm->processes, NULL, is_process_dead, NULL);
	total_lives = 0;
	current = vm->processes;
	while (current) {
		process = (t_process*)current->content;
		total_lives += process->lives;
		process->lives = 0;
		current = current->next;
	}
	reset_cycle_to_die(cycle_to_die, total_lives);
}
