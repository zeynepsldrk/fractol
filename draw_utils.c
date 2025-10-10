#include "fractol.h"

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	pixel = img->img_address + offset;
	*(unsigned int *)pixel = color;
}

int	get_color(int iteration, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iteration == max_iter)
		return (0x000000);
	t = (double)iteration / (double)max_iter;
	if (t < 0.16)
	{
		r = (int)(9 * (1 - t) * t * t * t * 255);
		g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	else if (t < 0.42)
	{
		r = (int)(8.5 * (1 - t) * t * t * t * 255);
		g = (int)(8.5 * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(9 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	else
	{
		r = (int)(9 * (1 - t) * (1 - t) * t * t * 255);
		g = (int)(15 * (1 - t) * t * t * t * 255);
		b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	return ((r << 16) | (g << 8) | b);
}

void	map_pixel_to_data(int x, int y, t_screen screen, t_data *c)
{
	double	re_factor;
	double	im_factor;

	re_factor = (screen.re_max - screen.re_min) / (WIDTH - 1);
	im_factor = (screen.im_max - screen.im_min) / (HEIGHT - 1);
	c->c_real = screen.re_min + (x * re_factor);
	c->c_imag = screen.im_max - (y * im_factor);
	c->z_real = c->c_real;
	c->z_imag = c->c_imag;
}