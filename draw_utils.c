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
	int		bytes_per_pixel;

	bytes_per_pixel = img->bits_per_pixel / 8;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * img->line_length) + (x * bytes_per_pixel);
	pixel = img->img_address + offset;
	*(unsigned int *)pixel = color;
}

int	get_color(int iterastion, int max_iter)
{
	double norm;
	
    double norm = (double)iteration / MAX_ITER;
    if (iteration >= MAX_ITER)
        return 0x000000;  
    int colors[8] = {
        0xFF0000,
        0xFF7F00,  
        0xFFFF00,  
        0x00FF00,  
        0x0000FF,  
        0x4B0082,  
        0x9400D3,  
        0xFF1493   
    };
    
    int color_index = iteration % 8;
    return (int)(colors[color_index] * norm);
}

void	julia_pixel_to_data(int x, int y, t_screen screen, t_data *c)
{
	double	re_factor;
	double	im_factor;

	re_factor = (screen.re_max - screen.re_min) / (WIDTH - 1);
	im_factor = (screen.im_max - screen.im_min) / (HEIGHT - 1);
	c->z_real = screen.re_min + (x * re_factor);
	c->z_imag = screen.im_max - (y * im_factor);
}

void mandel_pixel_to_data(int x, int y, t_screen screen, t_data *c)
{
	double	re_factor;
	double	im_factor;

	re_factor = (screen.re_max - screen.re_min) / (WIDTH - 1);
	im_factor = (screen.im_max - screen.im_min) / (HEIGHT - 1);
	c->c_real = screen.re_min + (x * re_factor);
	c->c_imag = screen.im_max - (y * im_factor);
}