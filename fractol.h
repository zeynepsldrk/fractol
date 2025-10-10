#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

#define USAGE_MSG "Usage: ./fractol <type> [options]\n" \
                  "Available types:\n" \
                  "  mandelbrot\n" \
                  "  julia <real> <imag>\n" \
                  "Examples:\n" \
                  "  ./fractol mandelbrot\n" \
                  "  ./fractol julia -0.7 0.27015\n"

# define WIDTH			600
# define HEIGHT			800
# define MAX_ITERATION	70

# define RE_MIN			-2.0
# define RE_MAX			2.0
# define IM_MIN			-2.0
# define IM_MAX			2.0

typedef struct s_image
{
	void	*img;
	char	*img_address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_data
{
	double	c_real;
	double	c_imag;
	double	z_real;
	double	z_imag;
}	t_data;

typedef struct s_screen
{
	double	re_min;
	double	re_max;
	double	im_min;
	double	im_max;
}	t_screen;

typedef struct s_fractol
{
	void		*mlx;
	void		*win;
	t_image		img;
	t_data		julia_param;
	t_screen	screen;
}	t_fractol;


int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		is_double(char *str);
double	ft_atof(const char *s);
void	usage_message(void);
void	system_err_message(void);
void	check_julia(char *number1, char *number2);
void	init_fractol(void (*draw)(t_fractol *fractol, t_image *image),
			t_fractol *fractol, char *title);
void	init_screen(t_screen *screen);
void	draw_mandelbrot(t_fractol *fractol, t_image *image);
void	draw_julia(t_fractol *fractol, t_image *image);
void	put_pixel(t_image *img, int x, int y, int color);
int		get_color(int iteration, int max_iter);
void	map_pixel_to_data(int x, int y, t_screen screen, t_data *c);
int		close_all(t_fractol *fractol);
int		press_esc(int keycode, t_fractol *fractol);
int		move_mouse(int way, int x, int y, t_fractol *fractol);
void	zoom(t_fractol *fractol, int x, int y, double zoom_factor);
int		calculate_mandelbrot(t_data *data, int max_iter);
int		calculate_julia(t_data *data, int max_iter);

#endif