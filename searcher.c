#include "lem_in.h"

void find_start_end_room(t_lemin *lem)
{
	t_room *tmp;

	tmp = lem->rooms;

	while (tmp)
	{
		if (tmp->type == 1)
			lem->start = tmp;
		else if (tmp->type == 2)
			lem->end = tmp;
		tmp = tmp->next;
	}
}
void	print_al1(t_lemin *lem)
{
	int			i = 0;
	t_jlist	*temp;

	printf("----------\n");
	while (lem->links[i])
	{
		temp = lem->links[i];
		while (temp)
		{
			printf("%s[%d] -> ", temp->room->name, temp->room->level);
			temp = temp->next;
		}
		printf(" ...\n");
		i++;
	}
	printf("----------\n"); 
}

int check_in_jlist_start(t_lemin *lem)
{
	int		i;
	t_jlist	*temp;

	i = 0;
	while(lem->links[i])
	{
		if(ft_strcmp(lem->start->name, lem->links[i]->room->name) == 0)
			return (1);
		temp = lem->links[i];
		while(temp)
		{
			if(ft_strcmp(temp->room->name, lem->start->name) == 0)
				return (1);
			temp = temp->next;
		}
		i++;
	}
	return (0);
}
int check_visited(t_jlist *tmp)
{
	while(tmp)
	{
		if(tmp->room->visited == 0)
			return(1);
		tmp = tmp->next;
	}
	return (0);
}

int check_in_jlist_end(t_lemin *lem)
{
	int		i;
	t_jlist	*temp;

	i = 0;
	while(lem->links[i])
	{
		if(ft_strcmp(lem->end->name, lem->links[i]->room->name) == 0)
			return (1);
		temp = lem->links[i];
		while(temp)
		{
			if(ft_strcmp(temp->room->name, lem->end->name) == 0)
				return (1);
			temp = temp->next;
		}
		i++;
	}
	return (0);
}

static	void	init_que(t_lemin *lem, t_queue *ochered, t_room *vertex)
{
	lem->ochered_size = 0;
	find_start_end_room(lem);

	ochered->room = lem->start;
	ochered->next = NULL;
	ochered->room->visited = 1;
	ochered->room->level = 1;
	lem->first = ochered;
	lem->last = ochered;
	lem->ochered_size = 1;
}

void		find_links_and_add(t_room *vertex, t_lemin *lem, t_queue *ochered)
{
	int		i;
	t_jlist	*tmp;
	tmp = NULL;

	i = 0;
	while (lem->links[i])
	{
		
		if (ft_strcmp(lem->links[i]->room->name, vertex->name) == 0)
			tmp = lem->links[i];
		if (lem->links[i]->room->type == 2)
			lem->j = i;
		i++;
	}
	
	while (tmp)
	{
		if (tmp->room->visited == 0)
			add_in_ochered(tmp, lem, vertex);
		tmp = tmp->next;
	}
}


void		main_searcher(t_lemin *lem)
{
	
	t_queue	*ochered;
	t_room	*vertex;
	t_room	*ants_road;
	
	
	ochered = (t_queue*)ft_memalloc(sizeof(t_queue));
	
	init_que(lem, ochered, vertex);
	vertex = lem->start;
		
	if(check_in_jlist_start(lem) == 0 || check_in_jlist_end(lem) == 0)
		ft_error("NOT ENOUGH LINKS TO FIND AN ANTS ROAD");
	else
	find_links_and_add(vertex, lem, ochered);
	
	while (lem->ochered_size >= 0)
	{
		if(lem->ochered_size == 1)
			ft_error("NOT ENOUGH LINKS TO FIND ANTS ROAD");
		print_al_queue(lem);
		vertex = dell_from_queue(lem, vertex);
		if (vertex->type == 2)
			break;
		find_links_and_add(vertex, lem, ochered);
	}

		print_rooms(lem);	
	// free_non_visited(lem);
		
	add_to_road(ants_road, lem);
	
		// exit(1);
	

}


void	make_ants_road(t_room *tmp, t_lemin *lem)
{
	t_room *road;
	t_room *head;

	road = tmp;
	if (!lem->road)
	{
		lem->road = road;
		road->next = NULL;
	}
	else
	{
		head = lem->road;
		lem->road = road;
		road->next = head;
	}

}

void	add_to_road(t_room *ants_road, t_lemin *lem)
{
	
	int	max;
	int index;
	index = 0;

	max = 999;

	t_room *tmp;
	t_jlist *tmp_final;
	tmp = lem->end;
	while (1)
	{
		if (tmp->name != lem->start->name)
		{
			make_ants_road(tmp, lem);
			lem->size++;
		}
		if (tmp == lem->start)
			break ;
		
		tmp_final = searching_links(tmp, lem);
	
		while(tmp_final)
		{
			if(tmp_final->room->level > 0 && tmp_final->room->level < max)
			{
				max = tmp_final->room->level;
				tmp = tmp_final->room;
			}
			tmp_final = tmp_final->next;	
		}
	}
	// tmp = lem->road;
	// while (tmp)
	// {
	// 	printf("%s->", tmp->name);
	// 	tmp = tmp->next;
	// }
	// printf("\n");
	
	indexing(lem);
	ants_attack(lem);
			// system("leaks lem-in");		
	// exit(1);
}

void indexing(t_lemin *lem)
{
	t_room	*ptr;
	ptr = lem->road;
	int	index;
	index = 0;
	
	while(ptr)
	{
		ptr->index_room = index;
		ptr = ptr->next;
		index++;
	}
}

 t_jlist	*searching_links(t_room *tmp, t_lemin *lem)
 {
	int i;
	i = 0;
	t_jlist *tmp_final;

	while(lem->links[i])
	{
		if (ft_strcmp(lem->links[i]->room->name, tmp->name) == 0)
		{
			tmp_final = lem->links[i];
			return (tmp_final);
		}
		i++;
	}
	return (NULL);
 }



t_room		*dell_from_queue(t_lemin *lem, t_room *vertex)
{
	t_queue	*temp;

	if (temp)
	{
		temp = lem->first;
		lem->first = lem->first->next;
		free(temp);
		lem->ochered_size--;
	}
	return (lem->first->room);
}

void add_in_ochered(t_jlist *tmp, t_lemin *lem, t_room *vertex)
{
	t_queue *new;

	new = (t_queue *)ft_memalloc(sizeof(t_queue));
	new->room = tmp->room;
	new->room->visited = 1;
	new->room->level = vertex->level + 1;
	lem->last->next = new;
	new->next = NULL;
	lem->last = new;
	lem->ochered_size++;
}


void	print_al_queue(t_lemin *lem)
{
	t_queue	*temp;
	temp = lem->first;
	printf("----------\n");
	while(temp)
	{
		printf("%s[%d] -> ", temp->room->name, temp->room->level);
		temp = temp->next;
	}
	printf("\n----------\n");
}

