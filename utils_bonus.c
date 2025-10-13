/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zedurak <zedurak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:25:12 by zedurak           #+#    #+#             */
/*   Updated: 2025/10/13 15:25:28 by zedurak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n) && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
}

int	is_double(char *str)
{
	int	i;
	int	dot;

	if (!str || !*str)
		return (0);
	i = 0;
	dot = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (++dot > 1)
				return (0);
		}
		else if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static double	ft_frac(const char *s, int *i)
{
	double	f;
	double	res;

	f = 0.1;
	res = 0.0;
	(*i)++;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		res += (s[*i] - '0') * f;
		f *= 0.1;
		(*i)++;
	}
	return (res);
}

double	ft_atof(const char *s)
{
	int		i;
	int		sign;
	double	res;

	i = 0;
	res = 0.0;
	sign = 1;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			sign = -1;
	while (s[i] >= '0' && s[i] <= '9')
		res = res * 10 + (s[i++] - '0');
	if (s[i] == '.')
		res += ft_frac(s, &i);
	return (res * sign);
}
