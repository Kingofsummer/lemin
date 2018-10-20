#include "lem_in.h"
void			free_split(char **arr)
{
	int		i;

	i = 0;

	while (arr[i])
	{
		ft_memdel((void **)&arr[i]);
		i++;
	}
	free(arr);
}

int			valid_link(t_lemin *lem, char *line)
{
	if(count(line, ' ') == 2 && count_l(line, '-') == 1)
		ft_error("INVALID COORD");

    if (ft_strchr(line, '-'))
	{

        lem->valid_link = ft_strsplit(line, '-');

		if(count_l(line, '-') != 1)
			ft_error("INVALID LINK");
		if(ft_strcmp(lem->valid_link[0],lem->valid_link[1]) == 0)
			ft_error("THE SAME COORDs IN LINK");
		if (count_l(line, '-') == 1 )
		{

            if (plagiat_link(lem) == 1)
			{
				return (1);
			}
			else if(plagiat_link(lem) != 1 && *line != '#')
			{
				free_split(lem->valid_link);
				ft_error("INVALID ROOM IN LINK");
			}
			return(1);
		}
	}
	return (0);
}

int		plagiat_link(t_lemin *lem)
{
	t_room	*tmp;
	int		check;

	check = 0;
	tmp = lem->rooms;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, lem->valid_link[0]) == 0)
			check++;
		if (ft_strcmp(tmp->name, lem->valid_link[1]) == 0)
			check++;
		tmp = tmp->next;
	}
	return (check == 2 ? 1 : 0);
}

int		parse_links(t_lemin *lem, char *line)
{

	while (1 )
	{
		if (ft_strchr(line, '#'))
		{
			if (ft_strstr(line, "##start") || ft_strstr(line, "##end"))
			{
				ft_strdel(&line);
				ft_error("FOUND ROOM in LINKS");
			}
			else if (*line == '#')
			{
				ft_strdel(&line);
				get_next_line(0, &line);
				if(!line)
					break;
				continue ;
			}
		}
		free_split(lem->valid_link);

		if (valid_link(lem, line))
		{
			add_first(lem);

			add_second(lem);

			ft_strdel(&line);
			get_next_line(0, &line);
			if(!line)
				break;
		}

		// free_split(lem->valid_link);
		// printf("%s %s\n", lem->valid_link[0],lem->valid_link[1]);
	}
	system("leaks lemin");

	return (0);
}
 
void	add_first(t_lemin *lem)
{
	int i;

	if (in_arr(lem) == 0)
	{
		make_new_link(lem);
		add_to_link(lem);
		lem->i_room++;
	}
	else if (in_arr(lem) == 1)
	{
		add_to_link_tmp(lem);
	}
}

void	add_to_link(t_lemin *lem)
{
	t_jlist *to_add;
	t_jlist *pos;

	to_add = (t_jlist*)ft_memalloc(sizeof(t_jlist));
	pos = lem->links[lem->i_room]->next;
	to_add->room = looking_for_1(lem);
	lem->links[lem->i_room]->next = to_add;
	to_add->next = pos;
}

void	add_to_link_tmp(t_lemin *lem)
{
	t_jlist *to_add;
	t_jlist *pos;

	to_add = (t_jlist*)ft_memalloc(sizeof(t_jlist));
	pos = lem->links[lem->i_room_tmp]->next;
	to_add->room = looking_for_1(lem);
	if(check_the_same(lem, to_add) == 1)
	{
		free(to_add);
		ft_error("SAME LINKS");
		return ;
	}
	lem->links[lem->i_room_tmp]->next = to_add;
	to_add->next = pos;
}

int check_the_same(t_lemin *lem, t_jlist *to_add)
{
	int i;
	t_jlist *tmp;

	i = lem->i_room_tmp;
	tmp = lem->links[i];
	while(tmp)
	{
		if(ft_strcmp(tmp->room->name, to_add->room->name) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	print_al(t_lemin *lem)
{
	int			i = 0;
	t_jlist	*temp;

	printf("----------\n");
	while (lem->links[i])
	{
		temp = lem->links[i];
		while (temp)
		{
			printf("%s -> ", temp->room->name);
			temp = temp->next;
		}
		printf(" ...\n");
		i++;
	}
	printf("----------\n");
}

int		in_arr(t_lemin *lem)
{
	int		i;

	i = 0;
	lem->i_room_tmp = 0;
	while (lem->links[i])
	{ 
		if (ft_strcmp(lem->links[i]->room->name, lem->valid_link[0]) == 0)
		{
			lem->i_room_tmp = i;
			return (1);
		}
		i++;
	}
	return (0);
}

void	make_new_link(t_lemin *lem)
{
	t_jlist *new;

		new = (t_jlist*)malloc(sizeof(t_jlist));
		new->room = looking_for_rname(lem);
		lem->links[lem->i_room] = new;
		new->next = NULL;
}

t_room	*looking_for_1(t_lemin *lem)
{
	t_room	*tmp;

	tmp = lem->rooms;

	while (tmp)
	{
		if (ft_strcmp(tmp->name, lem->valid_link[1]) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

t_room	*looking_for_rname(t_lemin *lem)
{
	t_room  *tmp;

	tmp = lem->rooms;

	while (tmp)
	{
		if(ft_strcmp(tmp->name, lem->valid_link[0]) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	ft_error("INVALID LINKING ROOM");
	return (0);
}