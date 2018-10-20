#include "lem_in.h"

void        add_second(t_lemin *lem)
{
	int     i;

	if (in_arr_second(lem) == 0)
	{   
		make_new_link1(lem);
		add_to_link_1(lem);
		lem->i_room++;
	}
	else if (in_arr_second(lem) == 1)
	{
		add_to_link_tmp1(lem);
	}
}

int         in_arr_second(t_lemin *lem)
{
	int i;

	i = 0;
	while (lem->links[i])
	{
		if (ft_strcmp(lem->links[i]->room->name, lem->valid_link[1]) == 0)
		{
			lem->i_room_tmp = i;
			return (1);
		}
		i++;
	}
	return (0);
}

void	make_new_link1(t_lemin *lem)
{
	t_jlist *new;

		new = (t_jlist*)malloc(sizeof(t_jlist));
		new->room = looking_for_rname1(lem);
		lem->links[lem->i_room] = new;
		new->next = NULL;
}

void    add_to_link_1(t_lemin *lem)
{
	t_jlist *to_add;
	t_jlist *pos;

	to_add = (t_jlist*)malloc(sizeof(t_jlist));
	pos = lem->links[lem->i_room]->next;
	to_add->room = looking_for_2(lem);
	lem->links[lem->i_room]->next = to_add;
	to_add->next = pos;
}

t_room    *looking_for_2(t_lemin *lem)
{
	t_room  *tmp;

	tmp = lem->rooms;
   
	while (tmp)
	{
		if(ft_strcmp(tmp->name, lem->valid_link[0]) == 0)
			return (tmp);
		tmp = tmp->next;
	}
return (0);
}

t_room    *looking_for_rname1(t_lemin *lem)
{
	t_room  *tmp;

	tmp = lem->rooms;
   
	while (tmp)
	{
		if(ft_strcmp(tmp->name, lem->valid_link[1]) == 0)
			return (tmp);
		tmp = tmp->next;
	}
return (0);
}
void    add_to_link_tmp1(t_lemin *lem)
{
	t_jlist *to_add;
	t_jlist *pos;
  
	to_add = (t_jlist*)malloc(sizeof(t_jlist));
	pos = lem->links[lem->i_room_tmp]->next;
	to_add->room = looking_for_2(lem);
	if(check_the_same_1(lem, to_add) == 1)
	{
		free(to_add);
		ft_error("SAME LINKS");
		return ;
	}
	lem->links[lem->i_room_tmp]->next = to_add;
	to_add->next = pos;
}

int check_the_same_1(t_lemin *lem, t_jlist *to_add)
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