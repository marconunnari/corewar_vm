#include "corewar_vm.h"

uint8_t		memory[MEM_SIZE];

void		pexit(char *filename)
{
	perror(filename);
	exit(0);
}

/*
** get memory at index
** considering that memory is circular
*/
uint8_t		get_memory_at(int i)
{
	return (memory[i % MEM_SIZE]);
}

t_process	new_process(uint8_t *r1, uint16_t pc, char carry)
{
	t_process	process;

	ft_memcpy(process.registries[0], r1, REG_SIZE);
	process.pc = pc;
	process.carry = carry;
	return (process);
}

int		main(int argc, char **argv)
{
	t_player	player;
	t_process	process;

	player = parse_player(argv[argc - 1]);
	player.number = -2;
	ft_printfnl("player n. %d called '%s' fat |%u| that say '%s'",
		player.number, player.name, player.size, player.comment);
	process = new_process((uint8_t *)&player.number, 0, 0);
	exec_process(&process);
}
