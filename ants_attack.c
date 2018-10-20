#include "lem_in.h"

void ants_attack(t_lemin *lem)
{
	t_room 				*index;
	t_anttool			*tool;
	tool = (t_anttool*)malloc(sizeof(t_anttool));
	make_to_zero(tool);
	arr_init(lem, tool);
	tool->j = lem->size;
	write(1, "\n", 1);
	while (tool->arr[tool->j - 1] < lem->ants)
	{
		tool->i = -1;
		make_one_step(tool);
		if (tool->arr[tool->j - 1] == lem->ants)
			break ;
		tool->m = tool->j;
		main_loop_ants(lem, tool , index);
		if (tool->j > 1)
			printf("\n");
	}
	free(tool);
}

void	main_loop_ants(t_lemin *lem, t_anttool *tool, t_room *index)
{
	while (tool->m > 0)
	{
		tool->m--;
		if (tool->arr[tool->m] >= 0 && tool->arr[tool->m] < lem->ants)
		{
			index = find_index(lem, tool->m);
			printf("L%d-%s ", tool->arr[tool->m] + 1, index->name);
		}
	}
}

void	make_to_zero(t_anttool *tool)
{
	tool->j =0;
	tool->i =0;
	tool->m =0;
	tool->init_j = 0;
	tool->init_d = -1;
}

void make_one_step(t_anttool *tool)
{
	int a;
	int b;

	a = tool->i;
	b = tool->j;
	while (a < b)
	{
		a++;
		tool->arr[a]++;
	}
	tool->i = a;
	tool->j = b;
}

t_room *find_index(t_lemin *lem, int m)
{
	t_room *tmp;
	t_room *ptr;
	
	ptr = lem->road;
	
	while(ptr)
	{
		if (ptr->index_room == m )
		{
			tmp = ptr;
			return (tmp);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

 void		arr_init(t_lemin *lem, t_anttool *tool)
{
	int						*arr;
	int						a;
	int						b;

	a = tool->init_j;
	b = tool->init_d;
	arr = (int *)ft_memalloc(sizeof(int) * lem->size);
	while (a <= lem->size)
	{
		arr[a] = b;
		b--;
		a++;
	}
	
	tool->arr = arr;
	ft_memdel((void **)&arr);
}
