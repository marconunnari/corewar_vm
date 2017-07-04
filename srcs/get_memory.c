#include "corewar_vm.h"

uint8_t		memory[MEM_SIZE];

/*
** get one byte of memory at index
** considering that memory is circular
*/
uint8_t		get_uint8_at(int i)
{
	return (memory[i % MEM_SIZE]);
}

/*
** get two bytes of memory at index
** considering that memory is circular
*/
uint16_t		get_uint16_at(int i)
{
	uint16_t	res;

	res = memory[i % MEM_SIZE] << 8 | memory[(i + 1) % MEM_SIZE];
	return (res);
}

/*
** get four bytes of memory at index
** considering that memory is circular
*/
uint32_t		get_uint32_at(int i)
{
	uint16_t	res;

	res = memory[i % MEM_SIZE] << 24 | memory[(i + 1) % MEM_SIZE] << 16 |
		memory[(i + 2) % MEM_SIZE] << 8 | memory[(i + 3) % MEM_SIZE];
	return (res);
}
