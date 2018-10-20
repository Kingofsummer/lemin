#include "lem_in.h"

int		parse_ants(t_lemin *lem)
{
	char	*line;
	
	line = NULL;
	if (!get_next_line(0, &line))
		ft_error("CANNT READ FROM FILE");

	while (1)
	{
		if (*line == '#')
		{
			if(ft_strstr(line, "##start") || ft_strstr(line, "##end"))
				ft_error("START OR END BEFORE ANTS");
			ft_strdel(&line);
			get_next_line(0, &line);
			continue ;
		}
		if (*line != '#' && !is_digitstr(line))
			ft_error("TRASH");
		if (!is_digitstr(line) || ft_strstr(line, "##"))
		{
			ft_strdel(&line);
			ft_error("NO ANTS");
		}
		
		if (is_digitstr(line))
		{
			lem->ants = ft_atoi(line);
			if (lem->ants == 0)
				ft_error("BAD NUMBER OF ANTS");
			break;
		}
	}

	free (line);
	return (0);
}
