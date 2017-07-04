#include "corewar_vm.h"

uint8_t		memory[MEM_SIZE];

void		pexit(char *filename)
{
	perror(filename);
	exit(0);
}

void		print_memory()
{
	int	i;

	while (i < MEM_SIZE)
	{
		if (i % 32 == 0)
			ft_printf("%#06x:", i);
		ft_printf(" %02x", memory[i]);
		if (i % 32 == 31)
			ft_putchar('\n');
		i++;
	}
}