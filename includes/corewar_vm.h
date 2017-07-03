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
# include <inttypes.h>

typedef struct	s_op
{
	char		*mnemonic;
	uint8_t		args_nbr;
	t_arg_type	args_types[3];
	uint8_t		opcode;
	uint32_t	cycles;
	char		*comment;
	uint8_t		types_encod;
	uint8_t		indexes;
}				t_op;

typedef struct	s_process
{
	uint8_t		registries[REG_NUMBER][REG_SIZE];
	uint16_t	pc;
	char		carry;
	int		wait;
}				t_process;

typedef struct	s_player
{
	char		*filename;
	int			fd;
	char		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	uint32_t	size;
	int			number;
}				t_player;

int				is_little_endian();
void			reverse_endian(int size, uint8_t *value);

uint8_t			get_memory_at(int i);

void			print_memory();
void			pexit(char *filename);

t_player		parse_player(char *filename);

void			get_op_args(t_op *op, t_process *process, int32_t *args);
void			exec(t_list *processes);
#endif
