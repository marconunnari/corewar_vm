/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 23:36:06 by mnunnari          #+#    #+#             */
/*   Updated: 2017/09/29 20:33:08 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar_vm.h"

/*
** check that the first 4 four bytes of the executable file are
** equals to the 4 bytes of the magic number
** of corewar executables (COREWAR_EXEC_MAGIC in op.h)
*/

void		check_magic(t_player *player)
{
	uint32_t	buf;
	int			ret;

	ret = read(player->fd, &buf, 4);
	if (ret < 4)
		ft_err(1, "Error: %s: not a corewar executable", player->filename);
	if (is_little_endian())
		reverse_endian((int)sizeof(buf), (uint8_t*)&buf);
	if (buf != COREWAR_EXEC_MAGIC)
		ft_err(1, "Error: %s: not a corewar executable", player->filename);
}

/*
** get the player name from the file:
** the number of bytes of player name is defined in op.h
*/

void		parse_player_name(t_player *player)
{
	int		ret;

	ret = read(player->fd, player->name, PROG_NAME_LENGTH);
	if (ret < PROG_NAME_LENGTH)
		ft_err(1, "Error: %s: no player name", player->filename);
	player->name[ret] = 0;
}

/*
** get the player size from the file:
** this is defined by the 4 bytes after player name
*/

void		parse_player_size(t_player *player)
{
	int	ret;

	lseek(player->fd, 4, SEEK_CUR);
	ret = read(player->fd, &player->size, 4);
	if (ret < 4)
		ft_err(1, "Error: %s: no player size", player->filename);
	if (is_little_endian())
		reverse_endian((int)sizeof(player->size), (uint8_t*)&player->size);
	if (player->size > CHAMP_MAX_SIZE)
		ft_err(1, "Error: %s: file too large (%d bytes > %d bytes)",
				player->filename, player->size, CHAMP_MAX_SIZE);
}

/*
** get the player comment from the file:
** the number of bytes of player comment is defined in op.h
*/

void		parse_player_comment(t_player *player)
{
	int	ret;

	ret = read(player->fd, player->comment, COMMENT_LENGTH);
	if (ret < COMMENT_LENGTH)
		ft_err(1, "Error: %s: no player comment", player->filename);
	player->comment[ret] = '\0';
}

/*
** check and get name, comment and size of the player specified
** from the filename passed as command line
** then load the player in memory
*/

t_player	parse_player(char *filename)
{
	t_player	player;

	player.filename = filename;
	if ((player.fd = open(player.filename, O_RDONLY)) == -1)
	{
		perror(filename);
		exit(0);
	}
	check_magic(&player);
	parse_player_name(&player);
	parse_player_size(&player);
	parse_player_comment(&player);
	return (player);
}
