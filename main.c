/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zedurak <zedurak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:21:46 by zedurak           #+#    #+#             */
/*   Updated: 2025/10/15 19:47:41 by zedurak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	void	print_error(void)
{
	write(1, "Usage: ./fractol <type> [options]\n", 34);
	write(1, "Available types:\n", 17);
	write(1, "  mandelbrot\n", 12);
	write(1, "  julia <real> <imag>\n", 22);
	write(1, "Examples:\n", 10);
	write(1, "  ./fractol mandelbrot\n", 23);
	write(1, "  ./fractol julia -0.7 0.27015\n", 30);
}

void	usage_message(void)
{
	print_error();
	exit(EXIT_FAILURE);
}

void	system_err_message(void)
{
	perror("Could not be started");
	exit(EXIT_FAILURE);
}

void	check_julia(char *number1, char *number2)
{
	t_fractol	fractol;

	if (!is_double(number1) || !is_double(number2))
	{
		write(2, "Error: Julia requires 2 numerical arguments\n", 45);
		exit(EXIT_FAILURE);
	}
	fractol.fractal_type = JULIA;
	fractol.data.c_real = ft_atof(number1);
	fractol.data.c_imag = ft_atof(number2);
	init_fractol(draw_julia, &fractol, "Julia");
}

int	main(int ac, char *av[])
{
	t_fractol	fractol;

	if (ac == 2 && !ft_strncmp("mandelbrot", av[1], 11))
	{
		fractol.fractal_type = MANDELBROT;
		init_fractol(draw_mandelbrot, &fractol, "Mandelbrot");
	}
	else if (ac == 2 && !ft_strncmp("julia", av[1], 6))
	{
		fractol.fractal_type = JULIA;
		fractol.data.c_real = -0.7;
		fractol.data.c_imag = 0.27;
		init_fractol(draw_julia, &fractol, "Julia");
	}
	else if (ac == 4 && !ft_strncmp("julia", av[1], 6))
		check_julia(av[2], av[3]);
	else
		usage_message();
	return (0);
}
