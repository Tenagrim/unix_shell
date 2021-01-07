.PHONY: clean fclean re bonus all
NAME=minishell
HEADER_FILES=\
env.h\
exec_args.h\
libft.h\
minishell.h\
semantic.h\
token.h
HEADER=$(addprefix includes/,$(HEADER_FILES))
PRINTF = libftprintf.a
SRC_DIR = src/
OBJ_DIR = src/
SEMANTIC_FILES = \
arguments.c\
char.c\
error.c\
free.c\
helpful.c\
init.c\
make.c\
print.c\
subprocessor.c\
subprocessor2.c\
token.c
ENV_FILES=\
find.c\
free.c\
helpful.c\
init.c\
native.c\
print.c\
var.c
TOKEN_FILES=\
buffer.c\
buffer2.c\
buffer3.c\
char.c\
char2.c\
error.c\
free.c\
helpful.c\
init.c\
make.c\
print.c\
processor.c\
state.c\
subprocessor.c\
subprocessor2.c\
token.c
EXEC_FILES=\
cd_builtin.c\
copy_env.c\
echo_builtin.c\
env_builtin.c\
exec_commands.c\
exec_redirected.c\
exit_builtin.c\
export_builtin.c\
find_file_in_dir.c\
find_path.c\
get_exec_func.c\
get_last_code.c\
inc_shlvl.c\
is_dir.c\
main.c\
print_env.c\
print_error.c\
print_error1.c\
print_error2.c\
print_error3.c\
pwd_builtin.c\
replace_exec_path.c\
signal_handler.c\
unset_builtin.c\
write_prompt.c
SRC_FILES = \
$(EXEC_FILES)\
$(addprefix token/,$(TOKEN_FILES))\
$(addprefix semantic/,$(SEMANTIC_FILES))\
$(addprefix env/,$(ENV_FILES))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
CFLAGS = -Wall -Wextra -Werror -Iincludes/

all: $(NAME)

ft_printf/libftprintf.a:
	$(MAKE) -C ft_printf

$(PRINTF) : ft_printf/libftprintf.a
	cp ft_printf/libftprintf.a .

$(SRC): $(HEADER)
	touch $@

$(NAME): $(PRINTF) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(PRINTF)

clean :
	make clean -C ft_printf
	rm -f $(OBJ)

fclean : clean
	make fclean -C ft_printf
	rm -f $(NAME)
	rm -f $(PRINTF)

re : fclean all

