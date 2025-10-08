#include "fractol.h"

void check_julia(char *number1, char *number2)
{
    if (!is_number(number1) || !is_number(number2))
    {
        write(2, "Error: Julia requires 2 integer arguments\n", 43);
        exit(EXIT_FAILURE);
    }
    t_fractol fractol[ARRAY_SIZE];
    fractol[3].julia.julia_real = (double)ft_atoi(number1);
    fractol[3].julia.julia_imag = (double)ft_atoi(number2);
    init_fractol(draw_julia, fractol, "Julia");
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
    fractol[0].mlx = mlx_init();
    if (!fractol[0].mlx)
        system_err_message();
    fractol[1].win = mlx_new_window(fractol[0].mlx, WIDTH, HEIGHT, title);
    if (!fractol[1].win)
        system_err_message();
    fractol[2].img.img = mlx_new_image(fractol[0].mlx, WIDTH, HEIGHT);
    if (!fractol[2].img.img)
        system_err_message();
    fractol[2].img.img_address = mlx_get_data_addr(fractol[2].img.img, &fractol[2].img.bits_per_pixel, &fractol[2].img.line_lenght, &fractol[2].img.endian);
    draw(&fractol[0], &fractol[2].img);
    mlx_put_image_to_window(fractol[0].mlx, fractol[1].win, fractol[2].img.img, 0, 0);
    mlx_loop(fractol[0].mlx);
}