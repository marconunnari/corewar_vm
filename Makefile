# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/09 14:31:16 by mnunnari          #+#    #+#              #
#    Updated: 2017/06/30 16:46:06 by mnunnari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=corewar_vm
GCC=gcc -Wall -Wextra -Werror
INCLUDES= -Iincludes -Ilibft/includes
LIBFT=libft/libft.a
LFT=-Llibft -lft
DOBJS=objs
DSRCS=srcs
HEADER=includes/corewar_vm.h

SRCS_FILES= main parse_player endian #new#

SRCS = $(addprefix $(DSRCS)/, $(addsuffix .c, $(SRCS_FILES)))
OBJS = $(SRCS:$(DSRCS)/%.c=$(DOBJS)/%.o)

all: $(NAME)

$(DOBJS):
	mkdir -p $(DOBJS)

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
