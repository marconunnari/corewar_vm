#include "corewar_vm.h"

/*
** check that the first 4 four bytes of the executable file are
** equals to the 4 bytes of the magic number (COREWAR_EXEC_MAGIC in op.h)
** of corewar executables
*/
void		check_magic(char *filename)
{
	int	fd;
	byte	buff[4];
	int	ret;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		perror(filename);
		exit(0);
	}
	ret = read(fd, buff, 4);
	if (ret < 4)
		ft_err(1, "%s: not a corewar eecutable", filename);
	if (buff[0] != (COREWAR_EXEC_MAGIC_0))
		ft_err(1, "%s: not a corewar eecutable", filename);
	if (buff[1] != (COREWAR_EXEC_MAGIC_1))
		ft_err(1, "%s: not a corewar eecutable", filename);
	if (buff[2] != (COREWAR_EXEC_MAGIC_2))
		ft_err(1, "%s: not a corewar eecutable", filename);
	if (buff[3] != (COREWAR_EXEC_MAGIC_3))
		ft_err(1, "%s: not a corewar eecutable", filename);
	if (close(fd) == -1)
	{
		perror(filename);
		exit(0);
	}
}
