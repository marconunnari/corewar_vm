#include "corewar_vm.h"

extern uint8_t	memory[MEM_SIZE];

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
		ft_err(1, "%s: not a corewar eecutable", player->filename);
	if (is_little_endian())
		reverse_endian((int)sizeof(buf), (uint8_t*)&buf);
	if (buf != COREWAR_EXEC_MAGIC)
		ft_err(1, "%s: not a corewar eecutable", player->filename);
}

/*
** get the player name from the file:
** the number of bytes of player name is defined in op.h
*/
void		get_player_name(t_player *player)
{
	int		ret;

	ret = read(player->fd, player->name, PROG_NAME_LENGTH);
	if (ret < PROG_NAME_LENGTH)
		ft_err(1, "%s: no player name", player->filename);
	player->name[ret] = 0;
}

/*
** get the player size from the file:
** this is defined by the 4 bytes after player name
*/
void		get_player_size(t_player *player)
{
	int	ret;

	lseek(player->fd, 4, SEEK_CUR);
	ret = read(player->fd, &player->size, 4);
	if (ret < 4)
		ft_err(1, "%s: no player size", player->filename);
	if (is_little_endian())
		reverse_endian((int)sizeof(player->size), (uint8_t*)&player->size);
}

/*
** get the player comment from the file:
** the number of bytes of player comment is defined in op.h
*/
void		get_player_comment(t_player *player)
{
	int	ret;

	ret = read(player->fd, player->comment, COMMENT_LENGTH);
	if (ret < COMMENT_LENGTH)
		ft_err(1, "%s: no player comment", player->filename);
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
		pexit(player.filename);
	check_magic(&player);
	get_player_name(&player);
	get_player_size(&player);
	get_player_comment(&player);
	lseek(player.fd, 4, SEEK_CUR);
	read(player.fd, memory, CHAMP_MAX_SIZE);
	if (close(player.fd) == -1)
		pexit(player.filename);
	return (player);
}
