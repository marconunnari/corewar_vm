/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 23:08:20 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 23:09:36 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** check if the current os is little endian:
** if the first byte of the int 1 is 1, it is little endian
** 1 in little endian:
** +----+----+----+----+
** |0x01|0x00|0x00|0x00|
** +----+----+----+----+
** 1 in big endian:
** +----+----+----+----+
** |0x00|0x00|0x00|0x01|
** +----+----+----+----+
*/

int			is_little_endian(void)
{
	uint32_t	i;
	char		*c;

	i = 1;
	c = (char*)&i;
	if (*c == 1)
		return (1);
	else
		return (0);
}

/*
** reverse the endiannes:
** put the last byte in first, the first in the last and so on
*/

void		reverse_endian(int size, uint8_t *value)
{
	int			i;
	uint8_t		tmp[32];

	i = 0;
	while (i < size)
	{
		tmp[i] = value[size - i - 1];
		i++;
	}
	i = 0;
	while (i < size)
	{
		value[i] = tmp[i];
		i++;
	}
}
