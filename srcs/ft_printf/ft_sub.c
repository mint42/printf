/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:21:45 by rreedy            #+#    #+#             */
/*   Updated: 2018/10/17 17:34:24 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_type(char *fmt, char *mod, char *type)
{
	*type = 0;
	*mod = 0;
	if (*fmt == '%' && *(fmt + 1))
		++fmt;
	while (fmt && !ft_isalpha(*fmt) && *fmt != '%')
		++fmt;
	if (fmt && (*fmt == 'l' || *fmt == 'h' || *fmt == 'j' || *fmt == 'z'))
	{
		*mod = *fmt;
		++fmt;
		if (fmt && (*fmt == 'l' || *fmt == 'h'))
		{
			*mod = ((*fmt == 'l') ? 'L' : 'H');
			++fmt;
		}
	}
	*type = (fmt && ft_strchr("sSpdDioOuUxXcC%", *fmt)) ? *fmt : 0;
}

char	*fill_flags(char *fmt, char **flg, t_sub sub)
{
	int		i;

	++fmt;
	*flg = ft_strnew(7);
	i = 0;
	flg[i++] = '*';
	if ((type == 'c' || type == 'C') && (*sub) == '\0')
		*flg[i++] = 'n';
	while (fmt && ft_strchr("-+ 0#", *fmt))
	{
		if (!ft_strchr(flg, *fmt))
			*flg[i++] = *fmt;
		++fmt;
	}
	return (fmt);
}

/*
	i = 0;
	while (flg[i] != '\0')
	{
		if ((flg[i] == '+' && (sub[0] == '-' || !ft_strchr("dDi", type))) ||
			(flg[i] == ' ' && (sub[0] == '-' || ft_strchr(flg, '+') ||
			!ft_strchr("dDi", type))) ||
			(flg[i] == '0' && ft_strchr(flg, '-')) ||
			(flg[i] == '#' && (!ft_strchr("oOxX", type) || sub[0] == '-')) ||
			(flg[i] == '#' && ft_strequ(sub, "0") && ft_strchr("xX", type)))
			flg[i] = '.';
		++i;
	}
*/

void	fill_pw(char *fmt, va_list ap, int *precision, int *width)
{
	*width = 0;
	*precision = -1;
//	if (*fmt == '%' && *(fmt + 1) == '%')
//		return ;
	while (fmt && (!ft_isalnum(*fmt) || *fmt == '0') && !ft_strchr(".*", *fmt))
		++fmt;
	if (*fmt == '*')
		*width = va_arg(ap, int);
	else
		*width = (ft_isdigit(*fmt)) ? ft_atoi(fmt) : 0;
	while (fmt && !ft_isalpha(*fmt) && *fmt != '.')
		++fmt;
	if (*fmt == '.' && *(fmt + 1) == '*')
		*precision = va_arg(ap, int);
	else
		*precision = (*fmt == '.') ? ft_atoi(++fmt) : -1;
}

/*
**	void	delsub(char **s, char **flags)
**	{
**		(void)s;
**		ft_strdel(s);
**		ft_strdel(flags);
**	}
*/

char	undefined(char *fmt, t_sub sub)
{
	int		i;

	i = 0;
	while (flg[i] != '\0')
	{
		if ((flg[i] == '+' && (sub[0] == '-' || !ft_strchr("dDi", type))) ||
			(flg[i] == ' ' && (sub[0] == '-' || ft_strchr(flg, '+') ||
			!ft_strchr("dDi", type))) ||
			(flg[i] == '0' && ft_strchr(flg, '-')) ||
			(flg[i] == '#' && (!ft_strchr("oOxX", type) || sub[0] == '-')) ||
			(flg[i] == '#' && ft_strequ(sub, "0") && ft_strchr("xX", type)))
			flg[i] = '.';
		++i;
	}
	while (fmt)
	{
		++fmt;
		if (ft_strchr("+ -0#", *fmt))
			continue ;
		else if (ft_isnum(*fmt) || *fmt == '*')
			continue ;
		else if (*fmt == '.' && (*(++fmt) == '*' || ft_isnum(*(++fmt))))
			continue ;
		else if (sub.mod == *fmt || (tolower(sub.mod) == *fmt && tolower(sub.mod) == *(++fmt)))
			continue ;
		else if (sub.type == *fmt)
			continue ;
		else
			break ;
	}
}

t_sub	makesub(char *fmt, va_list ap, int init)
{
	t_sub	sub;

	if (init)
	{
		sub.s = 0;
		sub.flags = 0;
		return (sub);
	}
	sub.flags = fill_flags(fmt, sub);
	fill_pw(fmt, ap, &(sub.p), &(sub.w));
	fill_type(fmt, &(sub.mod), &(sub.type));
	sub.s = (sub.type) ? parse(sub, fmt, ap) : ft_strnew(0);
	if (!sub.type || ft_strchr(sub.flags, '.'))
		sub.s = conv_utf8(L"¯\\_(ツ)_/¯");
	if (sub.w < 0)
		sub.w = sub.w * -1;
	sub.len = 0;
	return (sub);
}

t_sub	makesub(char *fmt, va_list ap, int init)
{
	t_sub	sub;

	if (init)
	{
		sub.s = 0;
		sub.flags = 0;
		return (sub);
	}
	fill_pw(fmt, ap, &(sub.p), &(sub.w));
	fill_type(fmt, &(sub.mod), &(sub.type));
	sub.s = (sub.type) ? parse(sub, fmt, ap) : ft_strnew(0);
	sub.flags = fill_flags(sub.s, fmt, sub.type, sub.w);
	if (!sub.type || ft_strchr(sub.flags, '.'))
		sub.s = conv_utf8(L"¯\\_(ツ)_/¯");
	if (sub.w < 0)
		sub.w = sub.w * -1;
	sub.len = 0;
	return (sub);
}
