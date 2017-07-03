#include "corewar_vm.h"

extern t_op		g_op_tab[17];
extern uint8_t	memory[MEM_SIZE];

/*
** get the operation from the operations array
*/
t_op			*get_op(uint8_t opcode)
{
	int			i;

	i = 0;
	while (g_op_tab[i].mnemonic)
	{
		if (g_op_tab[i].opcode == opcode)
			return (&g_op_tab[i]);
		i++;
	}
	return (NULL);
}

void			exec_op(t_op *op, int *args)
{
	int			i;

	ft_printf("%s", op->mnemonic);
	i = 0;
	while (i < op->args_nbr)
		ft_printf(" %d", args[i++]);
	ft_putchar('\n');
}

void			boh(t_list *processes)
{
	t_process	*process;
	t_op		*op;
	int32_t			args[MAX_ARGS_NUMBER];

	while(processes)
	{
		process = (t_process*)processes->content;
		if (process->wait == -1)
		{
			op = get_op(get_memory_at(process->pc));
			if (op)
				process->wait = op->cycles - 2;
		}
		else if (process->wait == 0)
		{
			op = get_op(get_memory_at(process->pc++));
			if (op)
			{
				get_op_args(op, process, args);
				exec_op(op, args);
			}
			else
				process->pc++;
			process->wait = -1;
		}
		else
			process->wait--;
		processes = processes->next;
	}
}

void			exec(t_list *processes)
{
	uintmax_t	cycle;

	cycle = 1;
	while (1)
	{
		ft_printfnl("cycle %ju", cycle);
		boh(processes);
		if (cycle == MEM_SIZE)
			break;
		cycle++;
	}
}
