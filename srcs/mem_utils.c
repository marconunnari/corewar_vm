#include "corewar_vm.h"

int		get_address(int index)
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
uint8_t		get_uint8_at(t_vm *vm, int i)
{
	return (vm->memory[get_address(i)]);
}

/*
** get two bytes of memory at index
** considering that memory is circular
*/
uint16_t		get_uint16_at(t_vm *vm, int i)
{
	uint16_t	res;

	res = vm->memory[get_address(i)] << 8 |
		vm->memory[get_address(i + 1)];
	return (res);
}

/*
** get four bytes of memory at index
** considering that memory is circular
*/
uint32_t		get_uint32_at(t_vm *vm, int i)
{
	uint32_t	res;

	res = 	vm->memory[get_address(i + 3)] |
			vm->memory[get_address(i + 2)] << 8 |
			vm->memory[get_address(i + 1)] << 16 |
			vm->memory[get_address(i + 0)] << 24;
	return (res);
}

/*
** set four bytes of memory starting at index [i] to the four bytes of [val]
*/
void			set_uint32(t_vm *vm, int i, uint32_t val)
{
	if (is_little_endian())
		reverse_endian(sizeof(val), (uint8_t*)&val);
	ft_memcpy(&vm->memory[get_address(i)], &val, 4);
}
