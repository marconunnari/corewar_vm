#include "corewar_vm.h"

/*
** this function execute an operation, advance the pc
** of the process and set the operation to be scheduled
*/
void			exec_op(t_vm *vm, t_process *process, t_op *op)
{
	int32_t			args[MAX_ARGS_NUMBER];

	get_op_args(vm, op, process->pc + 1, args);
	if (op->run)
		op->run(vm, process, op, args);
	advance_pc(process, op);
	process->wait = 0;
}

/*
** This function executes a cycle of code.
** Itereates over each process and see if it has to wait,
** execute or schedule
*/
void			do_cycle(t_vm *vm)
{
	t_list		*processes;
	t_process	*process;
	t_op	*op;

	processes = vm->processes;
	while(processes)
	{
		process = (t_process*)processes->content;

		if (process->wait == 0)
		{
			op = get_op(get_uint8_at(vm, process->pc));
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

		/*
		op = get_op(get_uint8_at(vm, process->pc));
		if (op)
		{
			if (process->wait == 0)
				process->wait = op->cycles - 1;
			else if (process->wait == 1)
				exec_op(vm, process, op);
			else
				process->wait--;
		}
		else
		{
			increase_pc(process, 1);
		}
		*/

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
	int		cycle_to_die;

	cycle = 1;
	cycle_to_die = CYCLE_TO_DIE;
	while (1)
	{
		if (cycle_to_die <= 0)
			check_up(vm, &cycle_to_die);
		if (vm->processes == NULL)
			break;
		if (vm->dump && cycle == vm->dump_cycle + 1)
			dump(vm);
		if ((vm->verbosity & 2) == 2)
			ft_printfnl("It is now cycle %ju", cycle);
		cycle_to_die--;
		do_cycle(vm);
		cycle++;
	}
}
