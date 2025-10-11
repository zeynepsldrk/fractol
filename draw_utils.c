/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zedurak <zedurak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:21:23 by zedurak           #+#    #+#             */
/*   Updated: 2025/10/11 18:58:31 by zedurak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	calculate_mandel_julia(t_data *data, int max_iter)
{
	int iter;
	double temp;

	iter = 0;
	while (iter < max_iter)
	{
		temp = (pow(data->z_real, 2) - pow(data->z_imag, 2)) + data->c_real;
		data->z_imag = (2 * data->z_real * data->z_imag) + data->c_imag;
		data->z_real = temp;
		if ((pow(data->z_real, 2)) + (pow(data->z_imag, 2)) >= 4.0)
			return (iter);
		iter++;
	}
	return (iter);
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	pixel = img->img_address + offset;
	*(int *)pixel = color;
}

int	get_color(int j, int max_iter)
{
	if (j == max_iter)
		return (0x000000);
	if (j % 2 == 1)
		return (0x555555);
	else
		return (0xcccccc);
}

void	pixel_to_data(int x, int y, t_screen screen, t_data *c)
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