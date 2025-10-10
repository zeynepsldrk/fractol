#include "fractol.h"

void	draw_julia(t_fractol *fractol, t_image *image)
{
	int		x;
	int		y;
	t_data	data;
	int		iterations;
	int		color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			map_pixel_to_data(x, y, fractol->screen, &data);
			data.c_real = fractol->julia_param.c_real;
			data.c_imag = fractol->julia_param.c_imag;
			iterations = calculate_julia(&data, MAX_ITERATION);
			color = get_color(iterations, MAX_ITERATION);
			put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_mandelbrot(t_fractol *fractol, t_image *image)
{
	int		x;
	int		y;
	t_data	data;
	int		iterations;
	int		color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			map_pixel_to_data(x, y, fractol->screen, &data);
			data.z_real = 0.0;
			data.z_imag = 0.0;
			iterations = calculate_mandelbrot(&data, MAX_ITERATION);
			color = get_color(iterations, MAX_ITERATION);
			put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}

void	init_screen(t_screen *screen)
{
	screen->re_max = RE_MAX;
	screen->re_min = RE_MIN;
	screen->im_max = IM_MAX;
	screen->im_min = IM_MIN;
}

void	init_fractol(void (*draw)(t_fractol *fractol, t_image *image),
		t_fractol *fractol, char *title)
{
	fractol->mlx = mlx_init();
	if (!fractol->mlx)
		system_err_message();
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, title);
	if (!fractol->win)
		system_err_message();
	fractol->img.img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (!fractol->img.img)
		system_err_message();
	fractol->img.img_address = mlx_get_data_addr(fractol->img.img,
			&fractol->img.bits_per_pixel,
			&fractol->img.line_length,
			&fractol->img.endian);
	init_screen(&fractol->screen);
	mlx_hook(fractol->win, 17, 0, close_all, fractol);
	mlx_key_hook(fractol->win, press_esc, fractol);
	mlx_mouse_hook(fractol->win, move_mouse, fractol);
	draw(fractol, &fractol->img);
	mlx_put_image_to_window(fractol->mlx, fractol->win,
		fractol->img.img, 0, 0);
	mlx_loop(fractol->mlx);
}