NAME = so_long
CFLAGS    = -Wall -Wextra -Werror -g -fsanitize=address
INCLUDE = -I $(LIBFT_DIR)/include -I $(MLX_DIR)
LIB = -L $(MLX_DIR) -l $(MLX) -L $(LIBFT_DIR) -l $(LIBFT) \
	-L/usr/X11R6/lib -lX11 -lXext
SRC_DIR = ./
MANDATORY_FILES = so_long.c affordance.c texture_into_grid.c put_texture.c \
initialize_map.c event.c check_map.c
MANDATORY_OBJS = $(addprefix $(SRC_DIR)/, $(MANDATORY_FILES:.c=.o))
BONUS_FILES = so_long_bonus.c
BONUS_OBJS = $(addprefix $(SRC_DIR)/, $(BONUS_FILES:.c=.o))

LIBFT = ft
LIBFT_DIR = ./lib/libft
MLX_DIR = ./lib/minilibx-linux
MLX = mlx_Darwin

ifdef IS_BONUS_FILES
	OBJS = $(BONUS_OBJS)
else
	OBJS = $(MANDATORY_OBJS)
endif

all: $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT_DIR) bonus
	make -C $(MLX_DIR)
	gcc $(CFLAGS) $(OBJS) $(INCLUDE) $(LIB) -framework OpenGL -framework AppKit -o $(NAME)

bonus:
	make IS_BONUS=1

.c.o: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	$(RM) $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re