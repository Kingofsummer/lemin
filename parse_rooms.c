#include "lem_in.h"

int			parse_rooms(t_lemin *lem)
{
	char	*line;

	
	while (get_next_line(0, &line) == 1 && !valid_link(lem, line))
	{
	
		// printf("|%s|\n", line);
		if (*line == '#')
		{
			if ((ft_strstr(line, "##start") || ft_strstr(line, "##end")))
			{
				ft_strdel(&line);
				start_end_room(lem);
				free_split(lem->valid_room);
				continue ;
			}
			else 
			{
				ft_strdel(&line);
				continue ;
			}
		}
		// if(!ft_strchr(line, ' ') &&  !valid_room(lem, line))
		// 	ft_error("INVALID ROOM");
		if (ft_strchr(line, ' ') && valid_room(lem, line) == 1)
		{
			create_room(lem, line);
			ft_strdel(&line);
		}

		free_split(lem->valid_room);
	}

	// system("leaks lem-in");
	lem->links = (t_jlist**)ft_memalloc(sizeof(t_jlist) * (lem->sum + 1));
	lem->links[lem->sum] = NULL;
		
	if(check_start_end(lem) == 0)
	{
		if(lem->check < 2)
			ft_error("NO START OR END ROOM");
		else if(lem->check > 2)
			ft_error("START OR END ALREADY EXIST");
	}
	
	// print_rooms(lem);
	if(line == NULL)
		ft_error("da");
	free_split(lem->valid_link);
	
	if(valid_link(lem, line))
	{
		parse_links(lem, line);
	}
	return (0);
}
int		check_start_end(t_lemin *lem)
{
	t_room *tmp;

	tmp = lem->rooms;
	while(tmp)
	{
		if(tmp->type == 1 || tmp->type == 2)
			lem->check++;
		tmp = tmp->next;
	}
	if(lem->check == 2)
		return (1);
	return (0);
}

void	start_end_room(t_lemin *lem)
{
	char	*line;
	int		type;

	
	if (ft_strcmp(line, "##start") == 0)
		lem->type = 1;
	else if (ft_strcmp(line, "##end") == 0)
		lem->type = 2;
	
	while( get_next_line(0, &line))
	{
		if(*line == '#')
		{
			ft_strdel(&line);
			continue;
		}
		if (valid_room(lem, line) == 1)
		{
			create_room(lem, line);
			lem->type = 0;
			ft_strdel(&line);
			break;
		}
		else
		{
			ft_strdel(&line);
			ft_error("INVALID ROOM");
		}
	}
}

void	create_room(t_lemin *lem, char *line)
{
	t_room			*new;
	static t_room	*last;
	new = (t_room *)ft_memalloc(sizeof(t_room));
	if (lem->rooms == NULL)
	{
		last = new;
		lem->rooms = new;
	}
	else
	{
		last->next = new;
		last = new;
	}
	if (plagiat_coord(lem) == 42 )
		ft_error("THE SAME COORDS");
	else
		fill_room(new, lem);
	lem->sum++;
}

void	fill_room(t_room *new, t_lemin *lem)
{
	if (plagiat_name(lem) == 42)
		ft_error("THE SAME NAME of ROOMS");
	new->name = ft_strdup(lem->valid_room[0]);
	new->x = ft_atoi(lem->valid_room[1]);
	new->y = ft_atoi(lem->valid_room[2]);
	new->type = lem->type;
}

int			valid_room(t_lemin *lem, char *line)
{
	if(ft_strchr(line, '-'))
		ft_error("INVALID ROOM");
	lem->valid_room = ft_strsplit(line, ' ');
	if (count(line, ' ') == 2)
	{
		if (is_digitstr(lem->valid_room[1]) && is_digitstr(lem->valid_room[2]))
		{
			if (lem->valid_room[1][0] != 'L' && lem->valid_room[2][0] != 'L')
			{
				return (1);
			}
		}
		else
			ft_error("INVALID COORD");
	}
	else
		ft_error("INVALID ROOM");
	return (0);
}

int		plagiat_name(t_lemin *lem)
{

	t_room  *tmp;

	tmp = lem->rooms;
 	
	while(tmp && tmp->name)
	{
		if (ft_strcmp(tmp->name, lem->valid_room[0]) == 0)
			return (42);
		tmp = tmp->next;
	}
	return (0);
}

int		plagiat_coord(t_lemin *lem)
{
	t_room  *tmp;

	tmp = lem->rooms;
	while (tmp)
	{
		if (tmp->x == ft_atoi(lem->valid_room[1]) && tmp->y == ft_atoi(lem->valid_room[2]))
			return (42);
		tmp = tmp->next;
	}
	return (0);

}
