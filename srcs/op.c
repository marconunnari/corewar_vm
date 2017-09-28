/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/09/28 23:17:07 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, {0, 0, 0}, live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, {0, 0, 0}, ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, {0, 0, 0}, st},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, {0, 0, 0}, add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0,
		{0, 0, 0}, sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, {0, 0, 0}, and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, {0, 0, 0}, or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, {0, 0, 0}, xor},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, {0, 0, 0}, zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, {0, 0, 0}, ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, {0, 0, 0}, sti},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, {0, 0, 0}, fork_op},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0,
		{0, 0, 0}, lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, {0, 0, 0}, lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, {0, 0, 0}, lfork_op},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, {0, 0, 0}, aff},
	{0, 0, {0}, 0, 0, 0, 0, 0, {0, 0, 0}, NULL}
};

/*
** get the operation from the operations array
*/

t_op			*get_op(uint8_t opcode)
{
	int			i;

	i = 0;
	while (g_op_tab[i].mnemonic)
	{
		if (g_op_tab[i].opcode == opcode)
		{
			return (&g_op_tab[i]);
		}
		i++;
	}
	return (NULL);
}
