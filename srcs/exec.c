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

void			start_waiting(t_vm *vm, t_process *process)
{
	t_op	*op;

	op = get_op(get_uint8_at(vm, process->pc));
	if (op)
		process->wait = op->cycles - 2;
}

void			exec_op(t_vm *vm, t_process *process)
{
	t_op		*op;
	int32_t			args[MAX_ARGS_NUMBER];

	op = get_op(get_uint8_at(vm, process->pc));
	if (op)
	{
		get_op_args(vm, op, process->pc + 1, args);
		//print_op(op, args);
		if (op->run)
			op->run(vm, process, op, args);
		process->pc++;
		increase_pc(process, op);
	}
	else
		process->pc++;
	process->wait = -1;
}

void			do_cycle(t_vm *vm)
{
	t_list		*processes;
	t_process	*process;

	processes = vm->processes;
	while(processes)
	{
		process = (t_process*)processes->content;
		if (process->wait == -1)
			start_waiting(vm, process);
		else if (process->wait == 0)
			exec_op(vm, process);
		else
			process->wait--;
		processes = processes->next;
	}
}

void			exec(t_vm *vm)
{
	uintmax_t	cycle;

	cycle = 1;
	while (1)
	{
//		ft_printfnl("cycle %ju", cycle);
		do_cycle(vm);
		if (cycle == MEM_SIZE)
			break;
		cycle++;
	}
}
