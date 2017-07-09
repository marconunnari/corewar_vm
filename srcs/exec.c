#include "corewar_vm.h"

void			exec_op(t_vm *vm, t_process *process, t_op *op)
{
	int32_t			args[MAX_ARGS_NUMBER];

	get_op_args(vm, op, process->pc + 1, args);
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
}

void			exec(t_vm *vm)
{
	uintmax_t	cycle;
	int		cycle_to_die;

	cycle = 1;
	cycle_to_die = CYCLE_TO_DIE;
	while (1)
	{
		//ft_printfnl("cycle_to_die %d", cycle_to_die);
		//ft_printfnl("cycle %ju", cycle);
		cycle_to_die--;
		if (cycle_to_die <= 0)
			check_up(vm, &cycle_to_die);
		if (vm->processes == NULL)
			break;
		do_cycle(vm);
		if (vm->dump && cycle == vm->dump_cycle + 1)
			dump(vm);
		cycle++;
	}
}
