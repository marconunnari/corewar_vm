/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 23:20:49 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 23:29:30 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

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
	else if (enc == DIR_CODE)
		return (T_DIR);
	else if (enc == IND_CODE)
		return (T_IND);
	else
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
** get arg based on arg type
*/

int32_t			get_arg(t_vm *vm, int *idx, t_arg_type arg_type,
						char are_indexes)
{
	uint8_t		size;
	int8_t		arg1;
	int16_t		arg2;
	int32_t		arg4;

	arg4 = 0;
	size = get_arg_size(arg_type, are_indexes);
	if (size == 1)
	{
		arg1 = get_int8_at(vm, *idx);
		arg4 = arg1;
	}
	else if (size == 2)
	{
		arg2 = get_int16_at(vm, *idx);
		arg4 = arg2;
	}
	else if (size == 4)
	{
		arg4 = get_int32_at(vm, *idx);
	}
	*idx += size;
	return (arg4);
}

void			get_op_args_types(t_vm *vm, t_op *op, int idx)
{
	uint8_t			i;
	uint8_t			encod;
	t_arg_type		arg_type;

	encod = 0;
	if (op->types_encod)
		encod = get_int8_at(vm, idx);
	i = 0;
	while (i < op->args_nbr)
	{
		if (op->types_encod)
		{
			arg_type = get_arg_type(encod, i);
			op->args_types[i] = arg_type;
		}
		else
			op->args_types[i] = op->possible_args_types[i];
		i++;
	}
}

/*
** get the arguments of one operation
** put the arguments into the args array
*/

int				get_op_args(t_vm *vm, t_op *op, int idx, int32_t *args)
{
	uint8_t			i;

	get_op_args_types(vm, op, idx);
	if (op->types_encod)
		idx++;
	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		if (i < op->args_nbr)
			args[i] = get_arg(vm, &idx, op->args_types[i], op->indexes);
		else
			args[i] = 0;
		i++;
	}
	return (1);
}
