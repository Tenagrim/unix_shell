.PHONY: clean fclean re bonus all
NAME=minishell
HEADER=includes/*.h
PRINTF = libftprintf.a
MLX = mlx/libmlx.a
SRC_DIR = src/
OBJ_DIR = src/
SRC_FILES = $(shell ls -1 src | grep "\.c")
INC=/usr/include
INCLIB=$(INC)/../lib
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ_FILES = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
FLAGS = -Wall -Wextra  -Iincludes/ -O0 -g #FIXME add -Werror
CC= gcc $(FLAGS)

all :  $(NAME)

$(PRINTF) : ft_printf/libftprintf.a
	$(MAKE) -C ft_printf
	cp ft_printf/libftprintf.a .

%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

$(NAME) :  $(PRINTF) $(OBJ_FILES) $(HEADER)
	$(CC) -o $(NAME) $(OBJ_FILES) $(PRINTF)

clean :
	make clean -C ft_printf
	rm -f $(OBJ_FILES)

fclean : clean
	make fclean -C ft_printf
	rm -f $(NAME)
	rm -f $(PRINTF)

re : fclean all

