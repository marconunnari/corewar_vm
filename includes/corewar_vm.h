/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 16:47:13 by mnunnari          #+#    #+#             */
/*   Updated: 2017/06/30 16:52:52 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
# define COREWAR_VM_H

# include "op.h"
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

typedef unsigned char	byte;

void		check_magic(char *filename, int fd);
void		get_player_name(char *filename, int fd, char *player_name);
#endif
