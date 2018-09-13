/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:55:00 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/12 17:42:37 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*precision(char *sub, char *flg, char type, int precision)
{
	if (precision < 0 || ft_strchr("cCSp", type))
		return (sub);
	if (type == 's')
	{
		if (ft_strlen(sub) >= (size_t)precision)
			sub[precision] = '\0';
		return (sub);
	}
	if (precision == 0 && ft_strequ(sub, "0"))
		return (ft_shift(&sub, 0, 0));
	if (sub[0] != '-' && (size_t)precision <= ft_strlen(sub))
		return (sub);
	if (sub[0] == '-' && (size_t)precision < ft_strlen(sub))
		return (sub);
	if (sub[0] != '-')
		sub = ft_shift(&sub, precision - ft_strlen(sub), precision);
	else
		sub = ft_shift(&sub, precision - ft_strlen(sub) + 1, precision + 1);
	sub = addzeros(sub, flg, 1);
	return (sub);
}

char	*addzeros(char *sub, char *flg, int p)
{
	int		i;

	i = (ft_strchr(flg, ' ') && !p) ? 1 : 0;
	while (sub && sub[i] == ' ')
	{
		sub[i] = '0';
		++i;
	}
	if (sub[i] == '0' && (sub[i + 1] == 'x' || sub[i + 1] == 'X') && i > 0)
	{
		++i;
		sub[1] = sub[i];
		sub[i] = '0';
	}
	else if ((sub[i] == '-' || sub[i] == '+') && i > 0)
	{
		sub[0] = sub[i];
		sub[i] = '0';
	}
	return (sub);
}

char	*addflags(char *sub, char *flg, char type)
{
	if (!ft_strchr(flg, '#') && !ft_strchr(flg, '+') && !ft_strchr(flg, ' '))
		return (sub);
	if (ft_strequ(sub, "0") && type == 'o')
		return (sub);
	sub = ft_shift(&sub, 1, ft_strlen(sub) + 1);
	if (ft_strchr(flg, '#') || type == 'p')
	{
		if (type == 'x' || type == 'X' || type == 'p')
		{
			sub = ft_shift(&sub, 1, ft_strlen(sub) + 1);
			sub[1] = (type == 'X') ? 'X' : 'x';
		}
		sub[0] = '0';
		return (sub);
	}
	if (ft_strchr(flg, '+'))
		sub[0] = '+';
	return (sub);
}

char	*fill_flags(char *sub, char *fmt, char type)
{
	char	*flg;
	int		i;

	flg = ft_strnew(6);
	i = 0;
	if (type == 'c' && (*sub) == '\0')
		flg[i++] = 'n';
	while (++fmt && (!ft_isalnum(*fmt) || *fmt == '0') && *fmt != '%')
		if (ft_strchr("-+ 0#", *fmt) && !ft_strchr(flg, *fmt))
			flg[i++] = *fmt;
	i = 0;
	while (flg[i] != '\0')
	{
		if ((flg[i] == '+' && (sub[0] == '-' || !ft_strchr("dDi", type))) ||
			(flg[i] == ' ' && (sub[0] == '-' || ft_strchr(flg, '+') ||
			!ft_strchr("dDi", type))) || (flg[i] == '0' && (ft_strchr(flg, '-')
			|| ft_strchr("sScCp", type))) || (flg[i] == '#' &&
			(!ft_strchr("oOxX", type) || sub[0] == '-')) ||
			(flg[i] == '#' && ft_strequ(sub, "0") && ft_strchr("xX", type)))
			flg[i] = '.';
		++i;
	}
	return (flg);
}

char	*crop(char *sub, char *fmt, size_t *sublen)
{
	char	*flg;
	char	type;
	int		p;
	int		w;

	type = *to_type(fmt);
	flg = fill_flags(sub, fmt, type);
	w = fill_pow(fmt, 0, 'w');
	p = fill_pow(fmt, 0, 'p');
//	while (fmt && (!ft_isalnum(*fmt) || *fmt == '0') && *fmt != '.')
//		++fmt;
//	w = (ft_isdigit(*fmt)) ? ft_atoi(fmt) : 0;
//	while (fmt && !ft_isalpha(*fmt) && *fmt != '.')
//		++fmt;
//	p = (*fmt++ == '.') ? ft_atoi(fmt) : -1;
	sub = precision(sub, flg, type, p);
	sub = addflags(sub, flg, type);
	if (ft_strchr(flg, '-') && (size_t)w > ft_strlen(sub))
		sub = ft_shift(&sub, 0, w);
	else if ((size_t)w > ft_strlen(sub))
		sub = ft_shift(&sub, w - ft_strlen(sub), w);
	*sublen = ((*sub) == '\0' && type == 'c') ? 1 : ft_strlen(sub);
	if (ft_strchr(flg, 'n') && w)
		sub[(ft_strchr(flg, '-')) ? 0 : w - 1] = '\0';
	sub = (ft_strchr(flg, '0') && p == -1) ? addzeros(sub, flg, 0) : sub;
	ft_strdel(&flg);
	return (sub);
}
