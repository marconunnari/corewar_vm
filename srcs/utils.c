/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 23:35:07 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 23:35:22 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

int		is_arg_type_valid(t_arg_type arg_type, t_arg_type arg_type_correct)
{
	int		valid;

	valid = (arg_type && (arg_type_correct & arg_type) == arg_type);
	return (valid);
}

/*
** get player name based on player number
*/

char	*get_player_name(t_vm *vm, int player_nbr)
{
	int			i;
	t_player	*players;

	i = 0;
	player_nbr = -player_nbr;
	players = vm->players;
	while (i < vm->players_nbr)
	{
		if (players[i].number == player_nbr)
			return (players[i].name);
		i++;
	}
	return (NULL);
}

/*
** increase the pc of the current process of quantity
** considering the cicularity of memory
*/

void	increase_pc(t_process *process, int quantity)
{
	process->pc = get_address(process->pc + quantity);
}

int		arg_type_valid(t_arg_type type)
{
	int		res;

	res = (type == T_DIR || type == T_IND || type == T_REG);
	return (res);
}
