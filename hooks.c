/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zedurak <zedurak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:21:40 by zedurak           #+#    #+#             */
/*   Updated: 2025/10/11 15:21:42 by zedurak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_all(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img.img);
	mlx_destroy_window(fractol->mlx, fractol->win);
	mlx_destroy_display(fractol->mlx);
	free(fractol->mlx);
	exit(0);
	return (0);
}

int	press_esc(int keycode, t_fractol *fractol)
{
	if (keycode == 65307)
		close_all(fractol);
	return (0);
}

int	move_mouse(int way, int x, int y, t_fractol *fractol)
{
	double	zoom_factor;

	zoom_factor = 1.0;
	if (way == 4)
		zoom_factor = 0.8;
	else if (way == 5)
		zoom_factor = 1.2;
	else
		return (0);
	zoom(fractol, x, y, zoom_factor);
	return (0);
}

void	zoom(t_fractol *fractol, int x, int y, double zoom_factor)
{
	double		mouse_re;
	double		mouse_im;
	double		re_factor;
	double		im_factor;
	t_screen	*screen;

	screen = &fractol->screen;
	re_factor = (screen->re_max - screen->re_min) / (WIDTH - 1);
	im_factor = (screen->im_max - screen->im_min) / (HEIGHT - 1);
	mouse_re = screen->re_min + (x * re_factor);
	mouse_im = screen->im_max - (y * im_factor);
	screen->re_min = mouse_re + (screen->re_min - mouse_re) * zoom_factor;
	screen->re_max = mouse_re + (screen->re_max - mouse_re) * zoom_factor;
	screen->im_min = mouse_im + (screen->im_min - mouse_im) * zoom_factor;
	screen->im_max = mouse_im + (screen->im_max - mouse_im) * zoom_factor;
	if (fractol->fractal_type == JULIA)
		draw_julia(fractol, &fractol->img);
	else
		draw_mandelbrot(fractol, &fractol->img);
	mlx_put_image_to_window(fractol->mlx, fractol->win,
		fractol->img.img, 0, 0);
}