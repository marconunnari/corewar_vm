#include "corewar_vm.h"

t_process			*new_process(int player_number, uint16_t pc, char carry)
{
	static int	process_number;
	t_process	*process;

	process = (t_process*)malloc(sizeof(t_process));
	process->registries[0] = -player_number;
	process->pc = pc;
	process->carry = carry;
	process->wait = -1;
	process->lives = 0;
	process->number = ++process_number;
	return (process);
}

/*
** load the players in memory
** create a process for each player and add it to the stack of processes
*/
void				init_players(t_vm *vm)
{
	int			i;
	uint8_t		buf[CHAMP_MAX_SIZE];
	t_process	*process;
	t_player	player;

	ft_bzero(vm->memory, MEM_SIZE);
	i = 0;
	vm->processes = NULL;
	while (i < vm->players_nbr)
	{
		player = vm->players[i];
		lseek(player.fd, 4, SEEK_CUR);
		read(player.fd, buf, CHAMP_MAX_SIZE);
		set_buf(vm, (MEM_SIZE / vm->players_nbr) * i, buf, CHAMP_MAX_SIZE);
		close(player.fd);
		process = new_process(player.number,
				(MEM_SIZE / vm->players_nbr) * i, 0);
		ft_lstaddnew(&vm->processes, process, sizeof(t_process));
		ft_bzero(buf, CHAMP_MAX_SIZE);
		i++;
	}
}

/*
** set [size] bytes of memory to [size] bytes of [buf]
** starting at index [idx] of memory
*/
void			set_buf(t_vm *vm, int idx, uint8_t *buf, int size)
{
	int			i;

	i = 0;
	while (i < size)
	{
		vm->memory[(idx + i) % MEM_SIZE] = buf[i];
		i++;
	}
}
