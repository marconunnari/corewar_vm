#include "corewar_vm.h"

void		live(t_vm *vm, t_process *process, t_op *op, int *args)
{
	int		player_nbr;
	char	*player_name;

	(void)op;
	process->lives++;
	player_nbr = args[0];
	if ((player_name = get_player_name(vm, player_nbr)))
	{
		if ((vm->verbosity & 1) == 1)
		{
			/*/
			ft_putstr("A process shows that player ");
			ft_putnbr(-player_nbr);
			ft_putstr(" (\"");
			ft_putstr(player_name);
			ft_putstr("\") is alive.\n");
			/*/

			ft_putstr("Player ");
			ft_putnbr(-player_nbr);
			ft_putstr(" (");
			ft_putstr(player_name);
			ft_putstr(") is said to be alive\n");
		}
		//ft_printfnl("A process shows that player %d (\"%s\") is alive.",
		//		-player_nbr, player_name);
		vm->last_alive = player_nbr;
	}
}
