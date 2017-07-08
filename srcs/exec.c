#include "corewar_vm.h"

void			print_op(t_op *op, int *args)
{
	int			i;

	ft_printf("%s", op->mnemonic);
	i = 0;
	while (i < op->args_nbr)
		ft_printf(" %d", args[i++]);
	ft_putchar('\n');
}

void			exec_op(t_vm *vm, t_process *process, t_op *op)
{
	int32_t			args[MAX_ARGS_NUMBER];

	get_op_args(vm, op, process->pc + 1, args);
	//print_op(op, args);
	if (op->run)
		op->run(vm, process, op, args);
	increase_pc(process, 1);
	advance_pc(process, op);
	process->wait = -1;
}

void			do_cycle(t_vm *vm)
{
	t_list		*processes;
	t_process	*process;
	t_op	*op;

	processes = vm->processes;
	while(processes)
	{
		process = (t_process*)processes->content;
	//	ft_printfnl("process pc %d wait %d", process->pc, process->wait);
		op = get_op(get_uint8_at(vm, process->pc));
		if (op)
		{
			if (process->wait == -1)
				process->wait = op->cycles - 2;
			else if (process->wait == 0)
				exec_op(vm, process, op);
			else
				process->wait--;
		}
		else
		{
			increase_pc(process, 1);
		}
		processes = processes->next;
	}
	//ft_printfnl("");
}

void            dump(t_vm *vm)
{
    print_memory(vm);
    exit(0);
}

void            reset_cycle_to_die(int *cycle_to_die, int total_lives)
{
    static int      decreases;
    static int      checkups_without_decrease;

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

int             is_process_dead(void *content, void *param)
{
    t_process   *process;

    (void)param;
    process = (t_process*)content;
    return (process->lives == 0);
}

void            check_up(t_vm *vm, int *cycle_to_die)
{
    t_list      *current;
    t_process   *process;
    int         total_lives; 

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

void			exec(t_vm *vm)
{
	uintmax_t	cycle;
    int         cycle_to_die;

	cycle = 1;
    cycle_to_die = CYCLE_TO_DIE;
	while (1)
	{
        //ft_printfnl("cycle_to_die %d", cycle_to_die);
		//ft_printfnl("cycle %ju", cycle);
    	do_cycle(vm);
		if (vm->dump && cycle == vm->dump_cycle + 1)
            dump(vm);
		if (cycle_to_die < 1)
            break;
		if (cycle_to_die == 1)
			check_up(vm, &cycle_to_die);
        else
            cycle_to_die--;
		cycle++;
	}
}
