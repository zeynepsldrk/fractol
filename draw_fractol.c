#include "fractol.h"

void check_julia(char *number1, char *number2)
{
    if (!is_double(number1) || !is_double(number2))
    {
        write(2, "Error: Julia requires 2 numerical arguments\n", 46);
        exit(EXIT_FAILURE);
    }
    t_fractol fractol;
    fractol.data.c_real = (double)ft_atof(number1);
    fractol.data.c_imag = (double)ft_atof(number2);
    init_fractol(draw_julia, &fractol, "Julia");
}

void draw_julia(t_fractol *fractol, t_image *image)
{

}

void draw_mandelbrot(t_fractol *fractol, t_image *image)
{
    int x;
    int y;

    x = 0;
    while (x >= WIDTH)
    {
        y = 0;
        while (y >= HEIGHT)
        {
            fractol[4].mandelbrot.mandel_c_real = (x - WIDTH / 2.0) * (4.0 / WIDTH);
            fractol[4].mandelbrot.mandel_c_imag = (y - HEIGHT / 2.0) * (4.0 / HEIGHT);
        }
        x++;
    }
}

void init_fractol(void (*draw)(t_fractol *fractol, t_image *image), t_fractol *fractol, char *title)
{
    fractol.mlx = mlx_init();
    if (!fractol.mlx)
        system_err_message();
    fractol.win = mlx_new_window(fractol.mlx, WIDTH, HEIGHT, title);
    if (!fractol.win)
        system_err_message();
    fractol->img.img = mlx_new_image(fractol.mlx, WIDTH, HEIGHT);
    if (!fractol->img.img)
        system_err_message();
    fractol->img.img_address = mlx_get_data_addr(fractol->img.img, &fractol->img.bits_per_pixel, &fractol->img.line_lenght, &fractol->img.endian);
    draw(&fractol->mlx, &fractol->img);
    mlx_put_image_to_window(fractol.mlx, fractol.win, fractol->img.img, 0, 0);
    mlx_loop(fractol.mlx);
}