/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 16:47:13 by mnunnari          #+#    #+#             */
/*   Updated: 2017/07/05 20:32:53 by mnunnari         ###   ########.fr       */
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
typedef struct	s_vm		t_vm;
typedef struct	s_player	t_player;
typedef struct	s_process	t_process;
typedef			void(*t_oprun)(t_vm *vm, t_process *process, t_op*, int*);

struct			s_op
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

struct			s_process
{
	int			registries[REG_NUMBER]; //TODO: consider REG_SIZE?!
	uint16_t	pc;
	char		carry;
	int			wait;
};

struct			s_player
{
	char		*filename;
	int			fd;
	char		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	uint32_t	size;
	int			number;
};

struct			s_vm
{
	t_player	players[MAX_PLAYERS];
	int			players_nbr;
	uint8_t		memory[MEM_SIZE];
	t_list		*processes;
	int			last_alive;
};

int				is_little_endian();
void			reverse_endian(int size, uint8_t *value);

void			set_uint32(t_vm *vm, int i, uint32_t val);
uint8_t			get_uint8_at(t_vm *vm, int i);
uint16_t		get_uint16_at(t_vm *vm, int i);
uint32_t		get_uint32_at(t_vm *vm, int i);

void			print_memory();

t_player		parse_player(char *filename);

t_op			*get_op(uint8_t opcode);
void			get_op_args(t_vm *vm, t_op *op, int idx, int32_t *args);
void			increase_pc(t_process *process, t_op *op);
void			exec(t_vm *vm);

void			st(t_vm *vm, t_process *process, t_op *op, int *args);
void			sti(t_vm *vm, t_process *process, t_op *op, int *args);
void			ld(t_vm *vm, t_process *process, t_op *op, int *args);
void			aff(t_vm *vm, t_process *process, t_op *op, int *args);
void			xor(t_vm *vm, t_process *process, t_op *op, int *args);
void			zjmp(t_vm *vm, t_process *process, t_op *op, int *args);
void			add(t_vm *vm, t_process *process, t_op *op, int *args);
void			live(t_vm *vm, t_process *process, t_op *op, int *args);

int				is_reg_valid(int reg);
int				get_reg_val(t_process *process, int reg);
void			set_reg_val(t_process *process, int reg, int val);
int				parse_arg(t_arg_type type, int val, int *arg, t_process *process);
#endif
