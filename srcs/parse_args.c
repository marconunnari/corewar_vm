#include "corewar_vm.h"

int		is_unique(int player_nbr, t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->players_nbr)
	{
		if (vm->players[i].number == player_nbr)
			return (0);
		i++;
	}
	return (1);
}

int			parse_player_nbr(char **argv, int *i, t_vm *vm)
{
	int			player_nbr;

	*i += 1;
	if (!argv[*i])
		print_usage();
	if (!ft_isint(argv[*i]))
		ft_err(1, "option -n must be followed by an integer");
	player_nbr = ft_atoi(argv[*i]);
	*i += 1;
	if (!is_unique(player_nbr, vm))
		ft_err(1, "each player number must be unique");
	return (player_nbr);
}

int			get_next_nbr(t_vm *vm)
{
	static int		nbr;

	nbr++;
	while (!is_unique(nbr, vm))
		nbr++;
	return (nbr);
}

void		parse_players(char **argv, int *i, t_vm *vm)
{
	t_player	player;
	int			player_nbr;

	vm->players_nbr = 0;
	while (argv[*i])
	{
		if (ft_strequ(argv[*i], "-n"))
			player_nbr = parse_player_nbr(argv, i, vm);
		else
			player_nbr = get_next_nbr(vm);
		if (!argv[*i])
			print_usage();
		player = parse_player(argv[*i]);
		player.number = player_nbr;
		vm->players[vm->players_nbr] = player;
		vm->last_alive = player.number;
		vm->players_nbr++;
		if (vm->players_nbr > MAX_PLAYERS)
			ft_err(1, "Too many players");
		*i += 1;
	}
}

void		parse_dump(char **argv, int *i, t_vm *vm)
{
	vm->dump = 0;
	if (ft_strequ(argv[*i], "-d"))
	{
		*i += 1;
		vm->dump = 1;
		if (ft_isuintmax(argv[*i]))
			vm->dump_cycle = ft_atouimax(argv[*i]);
		else
			ft_err(1, "option -d must be followed by a positive number");
		*i += 1;
	}
}

void		parse_aff(char **argv, int *i, t_vm *vm)
{
	vm->affiche = 0;
	if (ft_strequ(argv[*i], "-a"))
	{
		vm->affiche = 1;
		*i += 1;
	}
}
void		parse_args(char **argv, t_vm *vm)
{
	int		i;

	i = 0;
	parse_dump(argv, &i, vm);
	parse_aff(argv, &i, vm);
	parse_players(argv, &i, vm);
}
