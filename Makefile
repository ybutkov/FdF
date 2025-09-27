NAME = fdf
NAME_C = fdf.c

BUILD_DIR =	build
LIB_INCLUDE = -Iincludes
MinilibX = MinilibX

CC = cc
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined $(LIB_INCLUDE)
# CFLAGS = -Wall -Wextra -Werror -g -O3 $(LIB_INCLUDE) -I$(MinilibX)
CFLAGS = -Wall -Wextra -Werror -g -O0 -fsanitize=address,undefined $(LIB_INCLUDE) -I$(MinilibX)


LFLAGS = -L$(MinilibX) -lmlx -L$(MinilibX)/lib -lXext -lX11 -lm

C_FDF_FILES = parcer/get_next_line.c \
			parcer/parcer.c \
			base_stack/stack_base_basic.c \
			base_stack/stack_base_core.c \
			base_stack/stack_base_operations.c \
			draw_func/put_pixel.c \
			draw_func/draw_line.c \
			draw_func/draw_circle.c \
			draw_func/draw_rectangle.c \
			map_op/map_core.c \
			app_op/app_core.c \
			events/hooks.c \
			events/mouse_hooks.c \
			utils/error.c \
			utils/ft_calloc.c \
			utils/ft_memcpy.c \
			utils/ft_memset.c \
			utils/ft_memmove.c \
			utils/ft_split.c \
			utils/ft_strjoin.c \
			utils/ft_strdup.c \
			utils/ft_atoi.c \
			utils/ft_putstr.c \
			utils/ft_strlen.c \
			utils/ft_realloc.c \
			utils/ft_convertor.c \
			utils/ft_strchr.c \
			utils/ft_toupper.c \
			utils/ft_str_capitalise.c \
			utils/ft_abs.c \
			utils/ft_sign.c \
			utils/ft_ultoa.c \
			utils/ft_lltoa.c \
			utils/ft_doubletostr.c \
			utils/time_func.c


OBJ_FDF =	$(C_FDF_FILES:%.c=$(BUILD_DIR)/%.o)

all : $(NAME)

${NAME} : $(OBJ_FDF)
	$(CC) $(CFLAGS) $(OBJ_FDF) $(NAME_C) $(LFLAGS) -o $(NAME)

clean :
	rm -rf $(BUILD_DIR)

fclean f: clean
	rm -f $(NAME)

re	: fclean all

$(BUILD_DIR)/%.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY : all clean fclean re bonus
