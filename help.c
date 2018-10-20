#include "lem_in.h"

void		ft_error(char *str)
{
	ft_putstr(str);
	exit(0);
}

void		ft_make_zero_struct(t_lemin *lem)
{
	lem->ants = 0;
	lem->rooms = NULL;
	lem->type = 0;
}

int			count(char *line, char sign)
{
	int		i;

	i = 0;
	while (*line)
	{
		if (*line == sign)
			i++;
		line++;
	}
	if (i == 2)
		return (2);
	return (0);
}

int			count_l(char *line, char sign)
{
	int		i;

	i = 0;
	while (*line)
	{
		if (*line == sign)
			i++;
		line++;
	}
	if (i == 1)
		return (1);
	return (0);
}