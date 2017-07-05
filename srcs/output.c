#include "corewar_vm.h"

void		print_memory(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0)
			ft_printf("%#06x:", i);
		ft_printf(" %02x", vm->memory[i]);
		if (i % 32 == 31)
			ft_putchar('\n');
		i++;
	}
}
