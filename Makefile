NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux
SRC = main.c draw_fractol.c utils.c draw_utils.c hooks.c press_keys.c
OBJ = $(SRC:.c=.o)

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LIB) -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f $(OBJ)
	@$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) clean -C $(MLX_DIR)

re: fclean all