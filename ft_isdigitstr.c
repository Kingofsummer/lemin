#include "lem_in.h"
int	is_digitstr(char *str)
{
	if(!str)
		return (0);
	while (*str && *str != ' ')
		if (!ft_isdigit(*(str++)))
			return(0);
	return (1);
}
