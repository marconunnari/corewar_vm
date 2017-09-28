/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 16:47:13 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/28 23:23:17 by mnunnari         ###   ########.fr       */
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

typedef struct s_op			t_op;
typedef struct s_vm			t_vm;
typedef struct s_player		t_player;
typedef struct s_process	t_process;
typedef void	(*t_oprun)(t_vm *vm, t_process *process, t_op*, int*);

struct			s_op
{
	char		*mnemonic;
	uint8_t		args_nbr;
	t_arg_type	possible_args_types[3];
	uint8_t		opcode;
	uint32_t	cycles;
	char		*comment;
	uint8_t		types_encod;
	uint8_t		indexes;
	t_arg_type	args_types[3];
	t_oprun		run;
};

struct			s_process
{
	int			registries[REG_NUMBER];
	uint16_t	pc;
	char		carry;
	int			wait;
	int			lives;
	int			number;
	t_op		*op;
	uint8_t		reg_invalid;
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
	uint8_t		dump;
	uintmax_t	dump_cycle;
	uint8_t		affiche;
	uint8_t		verbosity;
};

int				is_little_endian();
void			reverse_endian(int size, uint8_t *value);

int				get_address(int index);
void			set_buf(t_vm *vm, int idx, uint8_t *buf, int size);
void			set_int(t_vm *vm, int i, int val);
int8_t			get_int8_at(t_vm *vm, int i);
int16_t			get_int16_at(t_vm *vm, int i);
int32_t			get_int32_at(t_vm *vm, int i);

void			print_usage();
void			print_intro(t_vm *vm);
void			print_winner(t_vm *vm);
void			print_processes(t_vm *vm);
void			print_op(t_op *op, int *args, t_process *process);
void			print_memory();
void			dump(t_vm *vm);

void			parse_args(char **argv, t_vm *vm);
t_player		parse_player(char *filename);
void			parse_players(char **argv, int *i, t_vm *vm);

char			*get_player_name(t_vm *vm, int player_nbr);
t_op			*get_op(uint8_t opcode);
int				is_arg_type_valid(t_arg_type arg_type, t_arg_type correct);
t_arg_type		get_arg_type(uint8_t encod, int i);
uint8_t			get_arg_size(t_arg_type arg_type, char are_indexes);
int				get_op_args(t_vm *vm, t_op *op, int idx, int32_t *args);
int				get_args_sizes(t_vm *vm, t_process *process, t_op *op);
void			advance_pc(t_vm *vm, t_process *process, int diff_pc);
t_process		*new_process(int player_number, uint16_t pc, char carry);
void			init_players(t_vm *vm);
void			increase_pc(t_process *process, int quantity);
void			check_up(t_vm *vm, int *cycle_to_die);
void			exec(t_vm *vm);

void			st(t_vm *vm, t_process *process, t_op *op, int *args);
void			sti(t_vm *vm, t_process *process, t_op *op, int *args);
void			ld(t_vm *vm, t_process *process, t_op *op, int *args);
void			ldi(t_vm *vm, t_process *process, t_op *op, int *args);
void			lld(t_vm *vm, t_process *process, t_op *op, int *args);
void			lldi(t_vm *vm, t_process *process, t_op *op, int *args);
void			aff(t_vm *vm, t_process *process, t_op *op, int *args);
void			xor(t_vm *vm, t_process *process, t_op *op, int *args);
void			or(t_vm *vm, t_process *process, t_op *op, int *args);
void			and(t_vm *vm, t_process *process, t_op *op, int *args);
void			zjmp(t_vm *vm, t_process *process, t_op *op, int *args);
void			fork_op(t_vm *vm, t_process *process, t_op *op, int *args);
void			lfork_op(t_vm *vm, t_process *process, t_op *op, int *args);
void			add(t_vm *vm, t_process *process, t_op *op, int *args);
void			sub(t_vm *vm, t_process *process, t_op *op, int *args);
void			live(t_vm *vm, t_process *process, t_op *op, int *args);

int				is_reg_valid(int reg);
int				is_reg_valid_mod(int reg, t_process *process);
int				get_reg_val(t_process *process, int reg);
void			set_reg_val(t_process *process, int reg, int val);
int				parse_arg(t_arg_type type, int val, int *arg,
				t_process *process);
#endif
