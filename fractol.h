#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "mlx.h"
# include "mlx_int.h"

#define ARRAY_SIZE  5

#define USAGE_MSG "Usage: ./fractol <type> [options]\n" \
                  "Available types:\n" \
                  "  mandelbrot\n" \
                  "  julia <real> <imag>\n" \
                  "Examples:\n" \
                  "  ./fractol mandelbrot\n" \
                  "  ./fractol julia -0.7 0.27015\n"

# define WIDTH		600
# define HEIGHT		800



typedef struct s_image
{
    void *img;
    char *img_address;
    int bits_per_pixel;
    int line_lenght;
    int endian;
} t_image;

typedef struct julia
{
    double julia_c_real;
    double julia_c_imag;
    double julia_z_real;
    double julia_z_imag;
} t_julia;

typedef struct mandelbrot
{
    double mandel_c_real;
    double mandel_c_imag;
    double mandel_z_real;
    double mandel_z_imag;
} t_mandelbrot;

typedef struct s_fractol
{
    void *mlx;
    void *win;
    t_image img;
    t_julia julia;
    t_mandelbrot mandelbrot;
} t_fractol;

int	ft_strncmp(const char *s1, const char *s2, size_t n);
int is_number(char *str);
int	ft_atoi(const char *str);
void check_julia(char *number1, char *number2);
void system_err_message(void);
void usage_message(void);
void init_fractol(void (*draw)(t_fractol *, t_image *), t_fractol *fractol, char *title);
void draw_mandelbrot(t_fractol *fractol, t_image *image);
void draw_julia(t_fractol *fractol, t_image *image);

#endif