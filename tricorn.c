/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tricorn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zedurak <zedurak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:30:24 by zedurak           #+#    #+#             */
/*   Updated: 2025/10/15 20:32:48 by zedurak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	draw_tricorn(t_fractol *fractol, t_image *image)
{
	int	x;
	int	y;
	int	iteration;
	int	color;

	iteration = 0;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mandel_pixel_to_data(x, y, fractol->screen, &fractol->data);
			fractol->data.z_imag = 0.0;
			fractol->data.z_real = 0.0;
			iteration = calculate_tricorn(&fractol->data, MAX_ITERATION);
			color = get_color(iteration, MAX_ITERATION);
			put_pixel(image, x, y, color);
			y++;
		}
		x++;
	}
}

int	calculate_tricorn(t_data *data, int max_iter)
{
	int		iter;
	double	temp;

	iter = 0;
	while (iter < max_iter)
	{
		temp = ((data->z_real * data->z_real) - (data->z_imag * data->z_imag)) + data->c_real;
		data->z_imag = (-2 * data->z_real * data->z_imag) + data->c_imag;
		data->z_real = temp;
		if ((->z_real * data->z_real) + (data->z_imag * data->z_imag) >= 4.0)
			return (iter);
		iter++;
	}
	return (iter);
}
