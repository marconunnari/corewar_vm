#include "corewar_vm.h"

/*
** parse the option -dump or -d followed by a number
*/
void		parse_dump(char **argv, int *i, t_vm *vm)
{
	vm->dump = 0;
	if (ft_strequ(argv[*i], "-d") || ft_strequ(argv[*i], "-dump"))
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

/*
** parse the option -a
*/
void		parse_aff(char **argv, int *i, t_vm *vm)
{
	vm->affiche = 0;
	if (ft_strequ(argv[*i], "-a"))
	{
		vm->affiche = 1;
		*i += 1;
	}
}

/*
** parse the option -v followed by a number
*/
void		parse_verbosity(char **argv, int *i, t_vm *vm)
{
	vm->verbosity = 0;
	if (ft_strequ(argv[*i], "-v"))
	{
		*i += 1;
		if (ft_isuintmax(argv[*i]))
			vm->verbosity = ft_atouimax(argv[*i]);
		else
			ft_err(1, "option -v must be followed by a positive number");
		*i += 1;
	}
}

/*
** TODO: parsing the options independently by the order
*/
void		parse_args(char **argv, t_vm *vm)
{
	int		i;

	i = 0;
	parse_dump(argv, &i, vm);
	parse_aff(argv, &i, vm);
	parse_verbosity(argv, &i, vm);
	parse_players(argv, &i, vm);
}
