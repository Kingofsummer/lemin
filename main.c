/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedoren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 15:35:19 by afedoren          #+#    #+#             */
/*   Updated: 2018/10/13 15:35:22 by afedoren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_rooms(t_lemin *tool)
{
	t_room		*room;

	room = tool->rooms;
	printf("\n  Rooms:\n------------\n");
	while (room)
	{
		printf("%s -> level: %d, coords [%d, %d] visit %d",
			room->name,  room->level, room->x,
			room->y, room->visited);
		if (room->type == 1)
			printf(" -> START");
		else if (room->type == 2)
			printf(" -> END");
		room = room->next;
		printf("\n");
	}
	printf("------------\n");
}

int		main(int ac, char **av)
{
	char	*line;
	t_lemin	lem;
	t_text *tmp;
	line = NULL;
	// int fd = open(av[1], O_RDONLY);
	// dup2(fd, STDIN_FILENO);
	ft_bzero(&lem, sizeof(t_lemin));
	
	parse_ants(&lem);
	
	parse_rooms(&lem);
	// free(line);


		// exit(1);
	main_searcher(&lem);
	system("leaks lem-in");
	exit(1);

	// ft_strdel(&line);
	

	// exit(1);
	
	return (0);
}
