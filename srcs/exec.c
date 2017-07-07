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

void			exec(t_vm *vm)
{
	uintmax_t	cycle;

	cycle = 1;
	while (1)
	{
		//ft_printfnl("cycle %ju", cycle);
		do_cycle(vm);
		if (vm->dump && cycle == vm->dump_cycle + 1)
		{
			print_memory(vm);
			exit(0);
		}
		if (cycle == 20482)
			break;
		cycle++;
	}
}
