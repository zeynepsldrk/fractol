/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zedurak <zedurak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:21:40 by zedurak           #+#    #+#             */
/*   Updated: 2025/10/11 15:21:42 by zedurak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int        close_all(t_fractol *fractol)
{
        mlx_destroy_image(fractol->mlx, fractol->img.img);
        mlx_destroy_window(fractol->mlx, fractol->win);
        mlx_destroy_display(fractol->mlx);
        free(fractol->mlx);
        exit(0);
        return (0);
}

static void        move_left_right(int keycode, t_fractol *fractol, double move)
{
        double        range_re;

        range_re = fractol->screen.re_max - fractol->screen.re_min;
        if (keycode == 65361)
        {
                fractol->screen.re_min -= range_re * move;
                fractol->screen.re_max -= range_re * move;
        }
        else if (keycode == 65363)
        {
                fractol->screen.re_min += range_re * move;
                fractol->screen.re_max += range_re * move;
        }
}

static void        move_up_down(int keycode, t_fractol *fractol, double move)
{
        double        range_im;

        range_im = fractol->screen.im_max - fractol->screen.im_min;
        if (keycode == 65362)
        {
                fractol->screen.im_min -= range_im * move;
                fractol->screen.im_max -= range_im * move;
        }
        else if (keycode == 65364)
        {
                fractol->screen.im_min += range_im * move;
                fractol->screen.im_max += range_im * move;
        }
}

static void        redraw_fractal(t_fractol *fractol)
{
        if (fractol->fractal_type == JULIA)
                draw_julia(fractol, &fractol->img);
        else
                draw_mandelbrot(fractol, &fractol->img);
        mlx_put_image_to_window(fractol->mlx, fractol->win,
                fractol->img.img, 0, 0);
}

int        press_keys(int keycode, t_fractol *fractol)
{
        double        move_amount;

        move_amount = 0.1;
        if (keycode == 65307)
                close_all(fractol);
        else if (keycode == 65361 || keycode == 65363)
                move_left_right(keycode, fractol, move_amount);
        else if (keycode == 65362 || keycode == 65364)
                move_up_down(keycode, fractol, move_amount);
        else
                return (0);
        redraw_fractal(fractol);
        return (0);
}

int        move_mouse(int way, int x, int y, t_fractol *fractol)
{
        double        zoom_factor;

        zoom_factor = 1.0;
        if (way == 4)
                zoom_factor = 0.8;
        else if (way == 5)
                zoom_factor = 1.2;
        else
                return (0);
        zoom(fractol, x, y, zoom_factor);
        return (0);
}

static void        calculate_mouse_pos(t_fractol *fractol, int x, int y,
                        double *mouse_re, double *mouse_im)
{
        double        range_re;
        double        range_im;

        range_re = fractol->screen.re_max - fractol->screen.re_min;
        range_im = fractol->screen.im_max - fractol->screen.im_min;
        *mouse_re = fractol->screen.re_min + ((double)x / WIDTH) * range_re;
        *mouse_im = fractol->screen.im_max - ((double)y / HEIGHT) * range_im;
}

static void        apply_zoom(t_fractol *fractol, double mouse_re,
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

void        zoom(t_fractol *fractol, int x, int y, double zoom_factor)
{
        double        mouse_re;
        double        mouse_im;
        double        interpolation;

        calculate_mouse_pos(fractol, x, y, &mouse_re, &mouse_im);
        interpolation = 1.0 / zoom_factor;
        apply_zoom(fractol, mouse_re, mouse_im, interpolation);
        redraw_fractal(fractol);
}