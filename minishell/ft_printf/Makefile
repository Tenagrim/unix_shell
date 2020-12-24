NAME=libftprintf.a
LIBFT_O = libft/*.o
LIBFT = libft/libft.a
SRC_DIR = src/
OBJ_DIR = src/
HEADER = includes/ft_printf.h	includes/get_next_line.h	includes/libft.h
SRC_FILES =  	ft_format_output_char.c ft_format_output_digit.c \
		ft_format_output_str.c ft_get_attr.c ft_get_conv.c \
		ft_get_flags.c ft_get_precision.c ft_get_size.c ft_get_width.c \
		ft_ifchar.c ft_ifdigit.c ft_ifstr.c ft_itoa_base.c \
		ft_itoa_base_h.c ft_itoa_base_hh.c ft_itoa_base_l.c \
		ft_itoa_base_ll.c ft_itoa_base_u.c ft_itoa_base_uh.c \
		ft_itoa_base_uhh.c ft_itoa_base_ul.c ft_itoa_base_ull.c \
		ft_min.c ft_new_attr.c ft_print_conv.c ft_printf.c \
		ft_pow.c ft_dtoa.c ft_format_output_float.c \
		ft_iffloat.c ft_max.c ft_ifptr.c ft_abs.c \
		ft_format_output_ptr.c ft_str_len.c
		get_next_line.c \
		get_next_line_utils.c \
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ_FILES = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
CC= gcc
FLAGS = -Wall -Wextra -Werror -I includes

all : $(NAME)

$(LIBFT) :
	@echo "COMPILING LIBFT"
	$(MAKE) -C libft
	cp $(LIBFT) ./$(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ_FILES) $(HEADER) $(LIBFT)
	ar rc $(NAME) $(OBJ_FILES)

clean :
	make clean -C libft
	rm -f $(OBJ_FILES)

bonus : $(NAME)
	@echo "Compiling bonuses..."
	@echo "..."
	@echo "..."
	@echo "Done"

fclean : clean
	make fclean -C libft
	rm -f $(NAME)

re : fclean all




