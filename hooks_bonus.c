/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zedurak <zedurak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:43:13 by zedurak           #+#    #+#             */
/*   Updated: 2025/10/14 12:55:48 by zedurak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	redraw_fractal(t_fractol *fractol)
{
	if (fractol->fractal_type == JULIA)
		draw_julia(fractol, &fractol->img);
	else if (fractol->fractal_type == TRICORN)
		draw_tricorn(fractol, &fractol->img);
	else
		draw_mandelbrot(fractol, &fractol->img);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img.img, 0, 0);
}

int	move_mouse(int way, int x, int y, t_fractol *fractol)
{
	double	zoom_factor;

	zoom_factor = 1.0;
	if (way == Button5)
		zoom_factor = 0.8;
	else if (way == Button4)
		zoom_factor = 1.2;
	else
		return (0);
	zoom(fractol, x, y, zoom_factor);
	return (0);
}

static void	calculate_mouse_pos(t_fractol *fractol, int a[],
	double *mouse_re, double *mouse_im)
{
	double	range_re;
	double	range_im;

	range_re = fractol->screen.re_max - fractol->screen.re_min;
	range_im = fractol->screen.im_max - fractol->screen.im_min;
	*mouse_re = fractol->screen.re_min + ((double)a[0] / WIDTH) * range_re;
	*mouse_im = fractol->screen.im_max - ((double)a[1] / HEIGHT) * range_im;
}

static	void	apply_zoom(t_fractol *fractol, double mouse_re,
	double mouse_im, double interpolation)
{
	fractol->screen.re_min = mouse_re + (fractol->screen.re_min - mouse_re)
		* interpolation;
	fractol->screen.re_max = mouse_re + (fractol->screen.re_max - mouse_re)
		* interpolation;
	fractol->screen.im_min = mouse_im + (fractol->screen.im_min - mouse_im)
		* interpolation;
	fractol->screen.im_max = mouse_im + (fractol->screen.im_max - mouse_im)
		* interpolation;
}

void	zoom(t_fractol *fractol, int x, int y, double zoom_factor)
{
	int		a[2];
	double	mouse_re;
	double	mouse_im;
	double	interpolation;

	a[0] = x;
	a[1] = y;
	calculate_mouse_pos(fractol, a, &mouse_re, &mouse_im);
	interpolation = 1.0 / zoom_factor;
	apply_zoom(fractol, mouse_re, mouse_im, interpolation);
	redraw_fractal(fractol);
}
