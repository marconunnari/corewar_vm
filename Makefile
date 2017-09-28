# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/09 14:31:16 by mnunnari          #+#    #+#              #
#    Updated: 2017/09/28 23:31:53 by mnunnari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=corewar_vm
GCC=gcc -Wall -Wextra -Werror -g #TODO: remove -g
INCLUDES= -Iincludes -Ilibft/includes
LIBFT=libft/libft.a
LFT=-Llibft -lft
DOBJS=objs
DSRCS=srcs
HEADER=includes/corewar_vm.h

SRCS_FILES= main op parse_player endian exec get_op_args mem_utils \
		parse_args init_players utils check_up parse_players reg_utils \
		ops/st ops/sti ops/ld ops/aff ops/xor ops/zjmp ops/add \
		ops/live ops/fork ops/sub ops/or ops/and ops/lfork \
		ops/lld ops/ldi ops/lldi advance_pc output1 output2 #new#

SRCS = $(addprefix $(DSRCS)/, $(addsuffix .c, $(SRCS_FILES)))
OBJS = $(SRCS:$(DSRCS)/%.c=$(DOBJS)/%.o)

all: $(NAME)

$(DOBJS):
	mkdir -p $(DOBJS)
	mkdir -p $(DOBJS)/ops

dolibft:
	make -C libft

$(OBJS): $(DOBJS)/%.o: $(DSRCS)/%.c $(HEADER)
	$(GCC) $(INCLUDES) -c $< -o $@

$(NAME): dolibft $(DOBJS) $(OBJS) $(HEADER)
	$(GCC) -o $(NAME) $(OBJS) $(LFT)

clean:
	make clean -C libft
	rm -rf $(DOBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
