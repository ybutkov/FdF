NAME = fdf
NAME_C = fdf.c

SRC = src
BUILD_DIR =	build

MINILIBX_DIR = MinilibX
MINILIBX = $(MINILIBX_DIR)/libmlx.a
MINILIB_GIT = https://github.com/42paris/minilibx-linux.git

LIBFT_DIR = libft
LIBFT_NAME = ft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -Iincludes
INCLUDES += -I$(MINILIBX_DIR)
INCLUDES += -I$(LIBFT_DIR)/includes

CC = cc
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined $(LIB_INCLUDE)
# CFLAGS = -Wall -Wextra -Werror -g -O3 $(LIB_INCLUDE) -I$(MinilibX)
CFLAGS = -Wall -Wextra -Werror -g -O0 $(INCLUDES)


LFLAGS = -L$(LIBFT_DIR) -l$(LIBFT_NAME) 
LFLAGS += -L$(MINILIBX_DIR) -lmlx -L$(MINILIBX_DIR)/lib -lXext -lX11 -lm

C_FDF_FILES = parcer/parcer.c \
			draw_func/put_pixel.c \
			draw_func/draw_line.c \
			draw_func/draw_rectangle.c \
			map_op/map_core.c \
			map_op/map_transform.c \
			map_op/map_basic.c \
			app_op/app_core.c \
			app_op/app_basic.c \
			events/hooks.c \
			events/mouse_hooks.c \
			events/key_actions.c \
			events/actions_wrapper_1.c \
			events/actions_wrapper_2.c \
			events/actions_wrapper_3.c \
			events/actions_wrapper_4.c 


C_FIlES = $(addprefix $(SRC)/, $(C_FDF_FILES))
C_OBJ_FIlES =	$(C_FIlES:%.c=$(BUILD_DIR)/%.o)

BUILD_DIRS := $(sort $(dir $(C_OBJ_FIlES)))

all : $(NAME)

${NAME} : $(MINILIBX) $(LIBFT) $(BUILD_DIRS) $(C_OBJ_FIlES)
	$(CC) $(CFLAGS) $(C_OBJ_FIlES) $(NAME_C) $(LFLAGS) -o $(NAME)

clean :
	rm -rf $(BUILD_DIR)
	make -C $(LIBFT_DIR) clean

fclean f: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re	: fclean all

$(BUILD_DIRS):
	mkdir -p $@

$(BUILD_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR) all

$(MINILIBX):
	if [ ! -d $(MINILIBX_DIR) ]; then \
		git clone $(MINILIB_GIT) $(MINILIBX_DIR); \
	fi
	if [ ! -f $(MINILIBX) ]; then \
		make -C $(MINILIBX_DIR) all; \
	fi

.PHONY : all clean fclean re bonus
