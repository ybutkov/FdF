NAME = fdf
NAME_C = fdf.c

SRC = src
BUILD_DIR =	build

UNAME_SYSTEM = $(shell uname -s)

MINILIBX_DIR = MinilibX

# Linux
MINILIB_GIT = https://github.com/42paris/minilibx-linux.git

# MacOS
MINILIB_MAC_OS_URL = https://cdn.intra.42.fr/document/document/39773/minilibx_macos_metal.tgz
MINILIB_ZIP_FILE = $(notdir $(MINILIB_MAC_OS_URL))

# Set MINILIBX based on OS
ifeq ($(UNAME_SYSTEM), Linux)
	MINILIBX = $(MINILIBX_DIR)/libmlx.a
	LFLAGS_OS = -L$(MINILIBX_DIR) -lXext -lX11 -lm
else ifeq ($(UNAME_SYSTEM), Darwin)
	MINILIBX = $(MINILIBX_DIR)/libmlx.dylib
	LFLAGS_OS = -framework OpenGL -framework AppKit -Wl,-rpath,@executable_path/MinilibX
endif

LIBFT_DIR = libft
LIBFT_NAME = ft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -Iincludes
INCLUDES += -I$(MINILIBX_DIR)
INCLUDES += -I$(LIBFT_DIR)/includes

CC = cc
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined $(LIB_INCLUDE)
CFLAGS = -Wall -Wextra -Werror -O3 $(INCLUDES)

LFLAGS = -L$(LIBFT_DIR) -l$(LIBFT_NAME) 
LFLAGS += -L$(MINILIBX_DIR) -lmlx
LFLAGS += $(LFLAGS_OS)

C_FDF_FILES = parcer/parcer.c \
			draw_func/put_pixel.c \
			draw_func/draw_line.c \
			draw_func/draw_rectangle.c \
			map_op/map_core.c \
			map_op/map_core_2.c \
			map_op/map_transform.c \
			map_op/map_basic.c \
			app_op/app_core.c \
			app_op/app_core_2.c \
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
ifeq ($(UNAME_SYSTEM), Darwin)
	install_name_tool -change libmlx.dylib @executable_path/MinilibX/libmlx.dylib $(NAME)
endif

clean :
	rm -rf $(BUILD_DIR)
	make -C $(LIBFT_DIR) clean

fclean f: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	rm -f $(MINILIB_ZIP_FILE)
	[ -d $(MINILIBX_DIR) ] && rm -rf $(MINILIBX_DIR)

re	: fclean all

$(BUILD_DIRS):
	mkdir -p $@

$(BUILD_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR) all

$(MINILIBX):
	if [ ! -d $(MINILIBX_DIR) ]; then \
		if [ "$(UNAME_SYSTEM)" = "Linux" ]; then \
			git clone $(MINILIB_GIT) $(MINILIBX_DIR); \
		elif [ "$(UNAME_SYSTEM)" = "Darwin" ]; then \
			mkdir -p $(MINILIBX_DIR); \
			curl -LO $(MINILIB_MAC_OS_URL); \
			tar -xzf $(MINILIB_ZIP_FILE) --strip-components=1 -C $(MINILIBX_DIR); \
		else \
			echo "Unsupported OS"; \
			exit 1; \
		fi; \
	fi
	if [ ! -f $(MINILIBX) ]; then \
		make -C $(MINILIBX_DIR) all; \
	fi

.PHONY : all clean fclean re bonus
