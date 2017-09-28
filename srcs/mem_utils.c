/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 23:14:35 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 23:15:25 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int			get_address(int index)
{
	index %= MEM_SIZE;
	if (index < 0)
		index += MEM_SIZE;
	return (index);
}

/*
** get one byte of memory at index
** considering that memory is circular
*/

int8_t		get_int8_at(t_vm *vm, int i)
{
	return (vm->memory[get_address(i)]);
}

/*
** get two bytes of memory at index
** considering that memory is circular
*/

int16_t		get_int16_at(t_vm *vm, int i)
{
	int16_t	res;

	res = vm->memory[get_address(i)] << 8 |
		vm->memory[get_address(i + 1)];
	return (res);
}

/*
** get four bytes of memory at index
** considering that memory is circular
*/

int32_t		get_int32_at(t_vm *vm, int i)
{
	int32_t	res;

	res = vm->memory[get_address(i + 3)] |
			vm->memory[get_address(i + 2)] << 8 |
			vm->memory[get_address(i + 1)] << 16 |
			vm->memory[get_address(i + 0)] << 24;
	return (res);
}

void		set_int(t_vm *vm, int i, int val)
{
	if (is_little_endian())
		reverse_endian(sizeof(val), (uint8_t*)&val);
	vm->memory[get_address(i + 0)] = (val & 0x000000FF) >> 0;
	vm->memory[get_address(i + 1)] = (val & 0x0000FF00) >> 8;
	vm->memory[get_address(i + 2)] = (val & 0x00FF0000) >> 16;
	vm->memory[get_address(i + 3)] = (val & 0xFF000000) >> 24;
}
