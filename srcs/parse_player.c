#include "corewar_vm.h"

/*
** check that the first 4 four bytes of the executable file are
** equals to the 4 bytes of the magic number
** of corewar executables (COREWAR_EXEC_MAGIC in op.h)
*/
void		check_magic(char *filename, int fd)
{
	t_uint	buf;
	int	ret;

	ret = read(fd, &buf, 4);
	if (ret < 4)
		ft_err(1, "%s: not a corewar eecutable", filename);
	if (is_little_endian())
		reverse_endian(sizeof(t_uint), (t_byte*)&buf);
	if (buf != COREWAR_EXEC_MAGIC)
		ft_err(1, "%s: not a corewar eecutable", filename);
}

/*
** get the player name from the file:
** the number of bytes of player name is defined in op.h
*/
void		get_player_name(char *filename, int fd, char *player_name)
{
	int	ret;
	char	buf[PROG_NAME_LENGTH + 1];

	ret = read(fd, buf, PROG_NAME_LENGTH);
	if (ret < PROG_NAME_LENGTH)
		ft_err(1, "%s: no player name", filename);
	buf[ret] = 0;
	ft_strcpy(player_name, buf);
}

/*
** get the player size from the file:
** this is defined by the 4 bytes after player name
*/
void		get_player_size(char *filename, int fd, t_luint *player_size)
{
	t_luint	buf;
	int	ret;

	ret = read(fd, &buf, 8);
	if (ret < 8)
		ft_err(1, "%s: no player size", filename);
	if (is_little_endian())
		reverse_endian(sizeof(t_luint), (t_byte*)&buf);
	*player_size = buf;
}

/*
** get the player comment from the file:
** the number of bytes of player comment is defined in op.h
*/
void		get_player_comment(char *filename, int fd, char *player_comment)
{
	int	ret;
	char	buf[COMMENT_LENGTH + 1];

	ret = read(fd, buf, COMMENT_LENGTH);
	if (ret < COMMENT_LENGTH)
		ft_err(1, "%s: no player comment", filename);
	buf[ret] = 0;
	ft_strcpy(player_comment, buf);
}
