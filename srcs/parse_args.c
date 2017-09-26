#include "corewar_vm.h"

/*
** parse the option -dump or -d followed by a number
*/
int			parse_dump(char **argv, int *i, t_vm *vm)
{
	if (ft_strequ(argv[*i], "-d") || ft_strequ(argv[*i], "-dump"))
	{
		*i += 1;
		vm->dump = 1;
		if (ft_isuintmax(argv[*i]))
			vm->dump_cycle = ft_atouimax(argv[*i]);
		else
			ft_err(1, "option -d must be followed by a positive number");
		*i += 1;
		return (1);
	}
	return (0);
}

/*
** parse the option -a
*/
int			parse_aff(char **argv, int *i, t_vm *vm)
{
	if (ft_strequ(argv[*i], "-a"))
	{
		vm->affiche = 1;
		*i += 1;
		return (1);
	}
	return (0);
}

/*
** parse the option -v followed by a number
*/
int			parse_verbosity(char **argv, int *i, t_vm *vm)
{
	if (ft_strequ(argv[*i], "-v"))
	{
		*i += 1;
		if (ft_isuintmax(argv[*i]))
			vm->verbosity = ft_atouimax(argv[*i]);
		else
			ft_err(1, "option -v must be followed by a positive number");
		*i += 1;
		return (1);
	}
	return (0);
}

/*
** TODO: parsing the options independently by the order
*/
void		parse_args(char **argv, t_vm *vm)
{
	int			opt;
	int			i;

	i = 0;
	opt = 1;
	vm->verbosity = 0;
	vm->dump = 0;
	vm->affiche = 0;
	while (opt)
	{
		opt = 0;
		if (parse_dump(argv, &i, vm))
			opt = 1;
		if (parse_aff(argv, &i, vm))
			opt = 1;
		if (parse_verbosity(argv, &i, vm))
			opt = 1;
	}
	parse_players(argv, &i, vm);
}
