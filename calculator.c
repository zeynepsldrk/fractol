#include "fractol.h"

int	calculate_mandelbrot(t_data *data, int max_iter)
{
	double	temp_real;
	double	z_real_sq;
	double	z_imag_sq;
	int		i;

	i = 0;
	while (i < max_iter)
	{
		z_real_sq = data->z_real * data->z_real;
		z_imag_sq = data->z_imag * data->z_imag;
		if (z_real_sq + z_imag_sq > 4.0)
			return (i);
		temp_real = z_real_sq - z_imag_sq + data->c_real;
		data->z_imag = 2.0 * data->z_real * data->z_imag + data->c_imag;
		data->z_real = temp_real;
		i++;
	}
	return (max_iter);
}

int	calculate_julia(t_data *data, int max_iter)
{
	double	temp_real;
	double	z_real_sq;
	double	z_imag_sq;
	int		i;

	i = 0;
	while (i < max_iter)
	{
		z_real_sq = data->z_real * data->z_real;
		z_imag_sq = data->z_imag * data->z_imag;
		if (z_real_sq + z_imag_sq > 4.0)
			return (i);
		temp_real = z_real_sq - z_imag_sq + data->c_real;
		data->z_imag = 2.0 * data->z_real * data->z_imag + data->c_imag;
		data->z_real = temp_real;
		i++;
	}
	return (max_iter);
}