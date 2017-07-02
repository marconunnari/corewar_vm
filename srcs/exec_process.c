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

void			print_op(t_op *op, int *args)
{
	int			i;
	
	ft_printf("%s", op->mnemonic);
	i = 0;
	while (i < op->args_nbr)
		ft_printf(" %d", args[i++]);
	ft_putchar('\n');
}

/*
** execute one process
*/
void			exec_process(t_process *process)
{
	t_op		*op;
	int32_t			args[MAX_ARGS_NUMBER];

	while (process->pc < MEM_SIZE / 2)
	{
		op = get_op(get_memory_at(process->pc++));
		if (!op)
		{
			process->pc++;
			continue;
		}
		get_op_args(op, process, args);
		print_op(op, args);
	}
}
