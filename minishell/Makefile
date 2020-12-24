.PHONY: clean fclean re bonus all
NAME=cub3d
HEADER=includes/cub3d.h includes/draw_sprite_args.h includes/ft_printf.h \
	   includes/get_next_line.h includes/keys_lin.h includes/keys_mac.h \
	   includes/libft.h includes/mlx.h includes/raycast_args.h
PRINTF = libftprintf.a
MLX = mlx/libmlx.a
SRC_DIR = src/
OBJ_DIR = src/
SRC_FILES = 		exit_game.c			ft_update_window.c \
clear_file.c			exit_hook.c			get_player_pos.c \
clear_game.c			find_line.c			init_game.c \
clear_img.c			ft_clear_split.c		init_map.c \
clear_map.c			ft_copy_intpair.c		init_mlx.c \
clear_mlx.c			ft_count_splitted.c		key_press.c \
clear_player.c			ft_default_settings.c		key_release.c \
clear_settings.c		ft_get_map_from_file.c		load_texture.c \
clear_sprites.c			ft_get_settings.c		load_textures.c \
clear_textures.c		ft_main_loop.c			main.c \
clear_window.c			ft_new_floatpair.c		parse_colors.c \
controls.c			ft_new_intpair.c		parse_map.c \
draw_floor_ceil.c		ft_new_player.c			parse_res.c \
draw_line.c			ft_print_file.c			parse_tex_paths.c \
draw_map.c			ft_print_map.c			raycast_im.c \
draw_pixel.c			ft_read_file.c			raycast_utils.c \
draw_rectangle.c		ft_sort_sprites.c		save_bmp.c \
draw_sprites.c			ft_sprtadd_front.c		screenshot.c \
draw_textured_rectangle.c	ft_sprtnew.c			validate_map.c \
error_map_line.c		ft_sptradd_sorted.c  check_filename.c \
get_next_line.c get_next_line_utils.c
INC=/usr/include
INCLIB=$(INC)/../lib
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))  \
	  gnl/get_next_line.c gnl/get_next_line_utils.c check_filename.c
OBJ_FILES = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
LIBS_MAC = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm
FLAGS = -Wall -Wextra -Werror  -Iincludes/ -O2
CC= gcc $(FLAGS)           # mac   CC
#CC= gcc $(FLAGS) -I$(INC) # linux CC

all :  $(NAME)

$(PRINTF) :
	$(MAKE) -C ft_printf
	mv ft_printf/libftprintf.a .

%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

$(MLX):
				$(MAKE) -C mlx
				cp mlx/mlx.h includes/mlx.h

$(NAME) : $(MLX)  $(PRINTF) $(OBJ_FILES) $(HEADER)
	$(CC) -o $(NAME) $(OBJ_FILES) $(PRINTF) $(LIBS_MAC) $(MLX)

clean :
	make clean -C ft_printf
	rm -f $(OBJ_FILES)

fclean : clean
	make fclean -C ft_printf
	make clean -C mlx
	rm -f $(NAME)
	rm -f $(PRINTF)

re : fclean all


#$(CC) -o $(NAME) $(SRC_FILES) $(LIBFT) $(PRINTF) $(LIBS)

#$(CC) -o $(NAME) $(SRC_FILES) $(LIBFT) $(MLX_LIN) $(PRINTF) -Lminilibx/ -lmlx -L /usr/lib -lXext -lX11 -lm -lbsd

