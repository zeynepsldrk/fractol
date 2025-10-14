/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_keys_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zedurak <zedurak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:49:35 by zedurak           #+#    #+#             */
/*   Updated: 2025/10/14 16:21:34 by zedurak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	close_all(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img.img);
	mlx_destroy_window(fractol->mlx, fractol->win);
	mlx_destroy_display(fractol->mlx);
	free(fractol->mlx);
	exit(0);
	return (0);
}

static	void	move_left_right(int keycode, t_fractol *fractol, double move)
{
	double	range_re;

	range_re = fractol->screen.re_max - fractol->screen.re_min;
	if (keycode == 65361 || keycode == 97)
	{
		fractol->screen.re_min += range_re * move;
		fractol->screen.re_max += range_re * move;
	}
	else if (keycode == 65363 || keycode == 100)
	{
		fractol->screen.re_min -= range_re * move;
		fractol->screen.re_max -= range_re * move;
	}
}

static	void	move_up_down(int keycode, t_fractol *fractol, double move)
{
	double	range_im;

	range_im = fractol->screen.im_max - fractol->screen.im_min;
	if (keycode == 65364 || keycode == 115)
	{
		fractol->screen.im_min += range_im * move;
		fractol->screen.im_max += range_im * move;
	}
	else if (keycode == 65362 || keycode == 119)
	{
		fractol->screen.im_min -= range_im * move;
		fractol->screen.im_max -= range_im * move;
	}
}

int	press_keys(int keycode, t_fractol *fractol)
{
	double	move_amount;

	move_amount = 0.1;
	if (keycode == 65307)
		close_all(fractol);
	else if (keycode == 65361 || keycode == 65363)
		move_left_right(keycode, fractol, move_amount);
	else if (keycode == 100 || keycode == 97)
		move_left_right(keycode, fractol, move_amount);
	else if (keycode == 65362 || keycode == 65364)
		move_up_down(keycode, fractol, move_amount);
	else if (keycode == 115 || keycode == 119)
		move_up_down(keycode, fractol, move_amount);
	else
		return (0);
	redraw_fractal(fractol);
	return (0);
}
