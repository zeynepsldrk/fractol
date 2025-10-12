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

int	press_keys(int keycode, t_fractol *fractol)
{
	double	move_amount;
	
	move_amount = 0.1;
	if (keycode == 65307)
		close_all(fractol);
	else if (keycode == 65361)
		fractol->center_x -= move_amount / fractol->zoom;
	else if (keycode == 65363)
		fractol->center_x += move_amount / fractol->zoom;
	else if (keycode == 65362)
		fractol->center_y -= move_amount / fractol->zoom;
	else if (keycode == 65364)
		fractol->center_y += move_amount / fractol->zoom;
	else
		return (0);
	if (fractol->fractal_type == JULIA)
		draw_julia(fractol, &fractol->img);
	else
		draw_mandelbrot(fractol, &fractol->img);
	mlx_put_image_to_window(fractol->mlx, fractol->win,
		fractol->img.img, 0, 0);
	return (0);
}

int	move_mouse(int way, int x, int y, t_fractol *fractol)
{
	fractol->screen. = 1.0;
	if (way == 4)
		fractol->screen. = 0.8;
	else if (way == 5)
		fractol->screen. = 1.2;
	else
		return (0);
	zoom(fractol, x, y, fractol->screen.);
	return (0);
}

void	zoom(t_fractol *fractol, int x, int y, double zoom_factor)
{
	double	mouse_re;
	double	mouse_im;
	
	mouse_re = fractol->center_x + (x - WIDTH / 2.0) / (WIDTH / 4.0) / fractol->zoom;
	mouse_im = fractol->center_y + (y - HEIGHT / 2.0) / (HEIGHT / 4.0) / fractol->zoom;
	fractol->zoom *= zoom_factor;
	fractol->center_x = mouse_re - (x - WIDTH / 2.0) / (WIDTH / 4.0) / fractol->zoom;
	fractol->center_y = mouse_im - (y - HEIGHT / 2.0) / (HEIGHT / 4.0) / fractol->zoom;
	if (fractol->fractal_type == JULIA)
		draw_julia(fractol, &fractol->img);
	else
		draw_mandelbrot(fractol, &fractol->img);
	mlx_put_image_to_window(fractol->mlx, fractol->win,
		fractol->img.img, 0, 0);
}