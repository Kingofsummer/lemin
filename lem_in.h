#ifndef LEM_IN_H
# define LEM_IN_H

#include "libft/libft.h"


typedef struct  s_room
{
	char            *name;
	int             x;
	int             y;
	int             type;
	int             level;
	int             visited;
	int				index_room;
	struct s_room	*next;
}					t_room;

typedef struct		s_jlist
{
	t_room			*room;
	struct s_jlist	*next;
}					t_jlist;

typedef struct		s_queue
{
	t_room			*room;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_text
{
	char			*str;
	struct s_text	*next;
}					t_text;
typedef struct		s_lemin
{
	int         ants;

	char        **valid_room;
	char        **valid_link;
	int         type;
	t_room		*rooms;

	t_jlist     **links;

	t_queue     *first;
	t_queue		*last;

	int			ochered_size;

	int			len_line;
	int			sum;
	int			i_room;
	int			i_room_tmp;
	int			j;
	int			size;
	t_room		*start;
	t_room		*end;
	t_room		*road;
	t_jlist		*tmp;
	char		**all;

	int			check;
	int			check_s;
	int			check_e;
}				t_lemin;

typedef struct	s_anttool
{
	int		j;
	int		i;
	int		m;
	int		init_j;
	int		init_d;
	int		*arr;
}				t_anttool;

int         is_digitstr(char *str);
int         parse_ants(t_lemin *lem);
void        ft_error(char *str);
void        ft_make_zero_struct(t_lemin *lem);
int         parse_rooms(t_lemin *lem);
int         valid_room(t_lemin *lem, char *line);
int         count(char *line, char sign);
void        create_room(t_lemin *lem, char *line);
void        fill_room(t_room *new, t_lemin *lem);
void        start_end_room(t_lemin *lem);
int         plagiat_coord(t_lemin *lem);
int         plagiat_name(t_lemin *lem);
int         valid_link(t_lemin *lem, char *line);
int         count_l(char *line, char sign);
int         plagiat_link(t_lemin *lem);
int         parse_links(t_lemin *lem, char *line);
void        add_first(t_lemin *lem);
int         in_arr(t_lemin *lem);
t_room         *looking_for_rname(t_lemin *lem);
void        make_new_link(t_lemin *lem);
void        add_to_link(t_lemin *lem);
t_room      *looking_for_1(t_lemin *lem);
void	    print_al(t_lemin *lem);
void		free_split(char **arr);
void        add_to_link_tmp(t_lemin *lem);
int         in_arr_second(t_lemin *lem);
void        add_second(t_lemin *lem);
t_room      *looking_for_2(t_lemin *lem);
void        make_new_link1(t_lemin *lem);
t_room      *looking_for_rname1(t_lemin *lem);
void        add_to_link_tmp1(t_lemin *lem);
void        add_to_link_1(t_lemin *lem);
void        main_searcher(t_lemin *lem);
void        add_node(t_lemin *lem, t_jlist *links);
void        find_start_end_room(t_lemin *lem);

void	print_al_queue(t_lemin *lem);
void        find_links_and_add(t_room *vertex, t_lemin *lem, t_queue *ochered);

int         v_ocherede( t_jlist  *tmp);
void        add_in_ochered(t_jlist *tmp, t_lemin *lem,  t_room *vertex);
t_room      *dell_from_queue(t_lemin *lem, t_room *vertex);
void	print_al1(t_lemin *lem);
void	add_to_road(t_room *ants_road, t_lemin *lem);
t_jlist	*searching_links(t_room *tmp, t_lemin *lem);
void	make_ants_road(t_room *tmp, t_lemin *lem);
void ants_attack(t_lemin *lem);
void		arr_init(t_lemin *lem, t_anttool *tool);
 t_room *find_index(t_lemin *lem, int m);
 void indexing(t_lemin *lem);
 int		*add_one_to_all(int i, int j, int *arr);
 void	make_to_zero(t_anttool *tool);
 void 	make_one_step(t_anttool *tool);
 void 	main_loop_ants(t_lemin *lem, t_anttool *tool, t_room *index);
 void text(t_lemin *lem, char *str);

void			print_rooms(t_lemin *tool);
int		check_start_end(t_lemin *lem);
int check_the_same(t_lemin *lem, t_jlist *to_add);
int check_the_same_1(t_lemin *lem, t_jlist *to_add);
int check_in_jlist_start(t_lemin *lem);
int check_in_jlist_end(t_lemin *lem);
int check_visited(t_jlist *tmp);
int check_visited_tmp(t_lemin *lem);
#endif