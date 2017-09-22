#include "corewar_vm.h"

/*
** get one byte of memory at index
** considering that memory is circular
*/
uint8_t		get_uint8_at(t_vm *vm, int i)
{
	return (vm->memory[i % MEM_SIZE]);
}

/*
** get two bytes of memory at index
** considering that memory is circular
*/
uint16_t		get_uint16_at(t_vm *vm, int i)
{
	uint16_t	res;

	res = vm->memory[i % MEM_SIZE] << 8 | vm->memory[(i + 1) % MEM_SIZE];
	return (res);
}

/*
** get four bytes of memory at index
** considering that memory is circular
*/
uint32_t		get_uint32_at(t_vm *vm, int i)
{
	uint32_t	res;

	res = 	vm->memory[(i + 3) % MEM_SIZE] |
			vm->memory[(i + 2) % MEM_SIZE] << 8 |
			vm->memory[(i + 1) % MEM_SIZE] << 16 |
			vm->memory[(i + 0) % MEM_SIZE] << 24;
	return (res);
}

/*
** set four bytes of memory starting at index [i] to the four bytes of [val]
*/
void			set_uint32(t_vm *vm, int i, uint32_t val)
{
	if (is_little_endian())
		reverse_endian(sizeof(val), (uint8_t*)&val);
	ft_memcpy(&vm->memory[i % MEM_SIZE], &val, 4);
}
