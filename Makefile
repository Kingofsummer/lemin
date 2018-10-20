NAME = lem-in
# FLAGS = -Wall -Wextra -Werror
LIB = libft.a
SRC = main.c ft_isdigitstr.c parse_ants.c parse_rooms.c help.c parse_links.c parse_links_v_2_0.c searcher.c ants_attack.c
OBJ = $(SRC:.c=.o)
all: $(NAME)

$(NAME): $(OBJ)
	@cd ./libft && make && mv $(LIB) ..
	@gcc $(OBJ) $(LIB) $(FLAGS) -o $(NAME)
	@echo " \x1B[36m MAKE for LEM_IN DONE \033[0m"
	@echo " \x1B[36m ----------------------\033[0m"
%.o: %.c
	@gcc $(FLAGS) -c $<
clean:
	@rm -rf $(OBJ)
	@make clean -C libft
fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB)
	@make fclean -C libft
re: fclean all
