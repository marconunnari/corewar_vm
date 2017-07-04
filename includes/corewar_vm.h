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

typedef struct	s_op		t_op;
typedef struct	s_process	t_process;
typedef			void(*t_oprun)(t_list*, t_op*, int*);

struct	s_op
{
	char		*mnemonic;
	uint8_t		args_nbr;
	t_arg_type	args_types[3];
	uint8_t		opcode;
	uint32_t	cycles;
	char		*comment;
	uint8_t		types_encod;
	uint8_t		indexes;
	t_oprun		run;
};

struct	s_process
{
	int		registries[REG_NUMBER]; //TODO: consider REG_SIZE?!
	uint16_t	pc;
	char		carry;
	int		wait;
};

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

void			set_uint32(int i, uint32_t val);
uint8_t			get_uint8_at(int i);
uint16_t			get_uint16_at(int i);
uint32_t			get_uint32_at(int i);

void			print_memory();
void			pexit(char *filename);

t_player		parse_player(char *filename);

void			get_op_args(t_op *op, t_process *process, int32_t *args);
void			exec(t_list *processes);

void			sti(t_list *processes, t_op *op, int *args);
void			ld(t_list *processes, t_op *op, int *args);
void			aff(t_list *processes, t_op *op, int *args);

int				is_reg_valid(int reg);
int				get_reg_val(t_process *process, int reg);
int				get_reg_val_first(t_list *processes, int reg);
void				set_reg_val(t_process *process, int reg, int val);
void				set_reg_val_first(t_list *processes, int reg, int val);
#endif
