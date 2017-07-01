#include "corewar_vm.h"

extern t_op		g_op_tab[17];

void			get_args_types(uint8_t encod, uint8_t *types)
{
	types[0] = (encod & (3 << 6)) >> 6;
	types[1] = (encod & (3 << 4)) >> 4;
	types[2] = (encod & (3 << 2)) >> 2;
	types[3] = 0;
}

void			parse_operations(char *filename, int fd)
{
	int			ret;
	uint8_t		buf1;
//	uint16_t	buf2;
//	uint32_t	buf4;
	uint8_t		types[MAX_ARGS_NUMBER];
	int			i;
	int			j;

	lseek(fd, 4, SEEK_CUR);
	ret = read(fd, &buf1, 1);
	if (ret < 1)
		ft_err(1, "%s: error in parsing operations", filename);
	i = 0;
	while (g_op_tab[i].name)
	{
		if (g_op_tab[i].code == buf1)
		{
			ft_printf("%s ", g_op_tab[i].name);
			if (g_op_tab[i].types_encod)
			{
				ret = read(fd, &buf1, 1);
				if (ret < 1)
					ft_err(1, "%s: error in parsing operations", filename);
				get_args_types(buf1, types);
				j = 0;
				while (types[j])
					ft_printf("%02b ", types[j++]);
			}
		}
		i++;
	}
}
