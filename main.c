#include "fractol.h"

void usage_message(void)
{
    write(1, USAGE_MSG, sizeof(USAGE_MSG) - 1);
    exit(EXIT_FAILURE);
}

void system_err_message(void)
{
    perror("Could not be started");
    exit(EXIT_FAILURE);
}

int main(int ac, char *av[])
{
    t_fractol fractol;

    if ((ac == 2) && (!ft_strncmp("mandelbrot", av[1], 10)))
        init_fractol(draw_mandelbrot, &fractol, "Mandelbrot");
    else if ((ac == 4) && (!ft_strncmp("julia", av[1], 5)))
        check_julia(av[2], av[3]);
    else
        usage_message();
}