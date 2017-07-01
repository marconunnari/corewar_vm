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

typedef unsigned char	t_byte;
typedef unsigned int	t_uint;
typedef unsigned long	t_luint;

int		is_little_endian();
void		reverse_endian(const long long int size, t_byte *value);

void		check_magic(char *filename, int fd);
void		get_player_name(char *filename, int fd, char *player_name);
void		get_player_size(char *filename, int fd, t_luint *player_size);
void		get_player_comment(char *filename, int fd, char *player_comment);
#endif
