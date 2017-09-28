/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 23:31:16 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 23:33:40 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

void		print_memory(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("%s%#.4x : ", i == 0 ? "0x" : "", i);
		ft_printf("%02x ", vm->memory[i]);
		if (i % 64 == 63)
			ft_putchar('\n');
		i++;
	}
}

void		print_usage(void)
{
	ft_printf("usage: corewar [-d nbr_cycles] ");
	ft_printfnl("[-a] <[-n number] champion1.cor> <..>");
	exit(0);
}

void		print_intro(t_vm *vm)
{
	int			i;
	t_player	player;

	ft_printfnl("Introducing contestants...");
	i = 0;
	while (i < vm->players_nbr)
	{
		player = vm->players[i];
		ft_printfnl("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !",
				player.number, player.size, player.name, player.comment);
		i++;
	}
}

void		print_winner(t_vm *vm)
{
	ft_printfnl("Contestant %d, \"%s\", has won !",
			-vm->last_alive, get_player_name(vm, vm->last_alive));
}
