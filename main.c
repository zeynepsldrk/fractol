#include "fractol.h"

void	usage_message(void)
{
	write(1, USAGE_MSG, sizeof(USAGE_MSG) - 1);
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
	fractol.julia_param.c_real = ft_atof(number1);
	fractol.julia_param.c_imag = ft_atof(number2);
	init_fractol(draw_julia, &fractol, "Julia");
}

int	main(int ac, char *av[])
{
	t_fractol	fractol;

	if (ac == 2 && !ft_strncmp("mandelbrot", av[1], 11))
	{
		fractol.julia_param.c_real = 0;
		fractol.julia_param.c_imag = 0;
		init_fractol(draw_mandelbrot, &fractol, "Mandelbrot");
	}
	else if (ac == 4 && !ft_strncmp("julia", av[1], 6))
		check_julia(av[2], av[3]);
	else
		usage_message();
	return (0);
}