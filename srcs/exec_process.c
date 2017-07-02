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

/*
** get the arg type from the
** encoding byte and the index of the arg
*/
t_arg_type		get_arg_type(uint8_t encod, int i)
{
	uint8_t		enc;

	enc = (encod & (3 << (6 - i * 2))) >> (6 - i * 2);
	if (enc == REG_CODE)
		return (T_REG);
	if (enc == DIR_CODE)
		return (T_DIR);
	if (enc == IND_CODE)
		return (T_IND);
	return (0);
}

/*
** get arg size base on arg type
*/
uint8_t			get_arg_size(t_arg_type arg_type, char are_indexes)
{
	if (arg_type == T_IND)
		return (IND_SIZE);
	if (arg_type == T_DIR && are_indexes)
		return (IND_SIZE);
	if (arg_type == T_DIR && !are_indexes)
		return (DIR_SIZE);
	if (arg_type == T_REG)
		return (1);
	return (0);
}

/*
** get arg and increase the pc base on arg type
*/
void			get_arg(t_process *process, t_arg_type arg_type, char are_indexes, uint8_t *arg)
{
	uint8_t		i;
	uint8_t		size;

	size = get_arg_size(arg_type, are_indexes);
	i = 0;
	while (i < size)
	{
		arg[i] = get_memory_at(++process->pc);
		i++;
	}
}

/*
** get the arguments of one operation
** increase the pc of the process
** put the argument int the args array
*/
void			get_args(t_op *op, t_process *process, uint8_t **args)
{
	uint8_t		i;
	uint8_t		encod;

	encod = 0;
	if (op->types_encod)
		encod = get_memory_at(++process->pc);
	i = 0;
	while (i < op->args_nbr)
	{
		if (encod)
			op->args_types[i] = get_arg_type(encod, i);
		i++;
	}
	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		if (i < op->args_nbr)
			get_arg(process, op->args_types[i], op->indexes, args[i]);
		else
			args[i] = 0;
		i++;
	}
}

void			print_arg(uint8_t *arg)
{
	(void)arg;
}

/*
** execute one process
*/
void			exec_process(t_process *process)
{
	int			i;
	t_op		*op;
	uint8_t			args[MAX_ARGS_NUMBER][4];

	while (process->pc < MEM_SIZE / 2)
	{
		op = get_op(get_memory_at(process->pc));
		if (op)
		{
			get_args(op, process, (uint8_t**)args);
			ft_printf("%s", op->mnemonic);
			i = 0;
			while (i < op->args_nbr)
				print_arg(args[i++]);
			ft_putchar('\n');
		}
		process->pc++;
	}
}
