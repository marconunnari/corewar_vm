#include "corewar_vm.h"

/*
** check that the first 4 four bytes of the executable file are
** equals to the 4 bytes of the magic number (COREWAR_EXEC_MAGIC in op.h)
** of corewar executables
*/
void		check_magic(char *filename, int fd)
{
	byte	buf[4];
	int	ret;

	ret = read(fd, buf, 4);
	if (ret < 4)
		ft_err(1, "%s: not a corewar eecutable", filename);
	if (buf[0] != (COREWAR_EXEC_MAGIC_0))
		ft_err(1, "%s: not a corewar eecutable", filename);
	if (buf[1] != (COREWAR_EXEC_MAGIC_1))
		ft_err(1, "%s: not a corewar eecutable", filename);
	if (buf[2] != (COREWAR_EXEC_MAGIC_2))
		ft_err(1, "%s: not a corewar eecutable", filename);
	if (buf[3] != (COREWAR_EXEC_MAGIC_3))
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
