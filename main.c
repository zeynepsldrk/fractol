#include "fractol.h"

int main(int ac, char *av[])
{
    void *mlx;
    void *win;
    
    if (ac == 2 || ac == 4)
    {
        mlx = mlx_init();
        if (!mlx)
        {
            perror("Could not be started");
            exit(EXIT_FAILURE);
        }
        win = mlx_new_window(mlx, WIDTH, HEIGHT, "Fractol the First");
        if (!win)
        {
            perror("Could not be appeared window");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        write(2, "Error: Invalid arguments\n", 25);
        exit(EXIT_FAILURE);
    }
}
