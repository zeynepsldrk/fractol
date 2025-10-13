NAME = fractol
BONUS = fractol_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux

SRC = main.c draw_fractol.c utils.c draw_utils.c hooks.c press_keys.c
OBJ = $(SRC:.c=.o)

BNSRC = main_bonus.c draw_fractol_bonus.c utils_bonus.c draw_utils_bonus.c hooks_bonus.c press_keys_bonus.c tricorn.c
BNOBJ = $(BNSRC:.c=.o)

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

bonus: $(MLX_LIB) $(BONUS)

$(BONUS): $(BNOBJ)
	$(CC) $(CFLAGS) $(BNOBJ) $(MLX_LIB) -L/usr/lib -lXext -lX11 -lm -lz -o $(BONUS)

clean:
	rm -f $(OBJ) $(BNOBJ)
	@$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS)
	@$(MAKE) clean -C $(MLX_DIR)

re: fclean all bonus

.PHONY: all bonus clean fclean re