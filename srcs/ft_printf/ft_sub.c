/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:21:45 by rreedy            #+#    #+#             */
/*   Updated: 2018/11/13 15:36:12 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*fill_flags(char *fmt, char **flag)
{
	char	*cur;

	++fmt;
	*flag = ft_strnew(6);
	cur = *flag;
	*cur++ = '*';
	while (fmt && ft_strchr("-+ 0#", *fmt))
	{
		if (*fmt == '-')
			*flag[0] = '-';
		else if (!ft_strchr(*flag, *fmt))
			*cur++ = *fmt;
		++fmt;
	}
	return (fmt);
}

char	*fill_pw(char *fmt, va_list ap, int *precision, int *width)
{
	*width = 0;
	*precision = -1;
	if (fmt && *fmt == '*')
	{
		*width = va_arg(ap, int);
		++fmt;
	}
	else if (fmt && ft_isdigit(*fmt))
	{
		*width = ft_atoi(fmt);
		while (ft_isdigit(*fmt))
			++fmt;
	}
	if (fmt && *fmt == '.')
		++fmt;
	if (fmt && *fmt == '*')
		*precision = va_arg(ap, int);
	else if (fmt && *(fmt - 1) == '.')
		*precision = ft_atoi(fmt);
	while (fmt && (*fmt == '*' || ft_isdigit(*fmt)))
		++fmt;
	return (fmt);
}

char 	*fill_type(char *fmt, char *mod, char *type)
{
	*type = 0;
	*mod = 0;
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
	while (!(*type) && fmt && *fmt && (!ft_isalpha(*fmt) && *fmt != '%'))
		++fmt;
	return (fmt);
}

int		check_flags(char **flag, char *sub, char type, int width)
{
	char	*cur;

	cur = *flag;
	if (width < 0)
		*cur++ = '-';
	if ((type == 'c' || type == 'C') && *sub == '\0')
		*cur++ = 'n';
	while (cur && *cur)
	{
		if ((*cur == '+' && !ft_strchr("dDiu", type)) ||
			(*cur == ' ' && !ft_strchr("dDicu%", type)) ||
			(*cur == '#' && !ft_strchr("oOxX", type)))
			return (0);
		if ((*cur == '+' && (sub[0] == '-' || type == 'u' || type == '%')) ||
			(*cur == ' ' && (sub[0] == '-' || ft_strchr(*flag, '+'))) ||
			(*cur == ' ' && (ft_strchr("cu%", type))) ||
			(*cur == '0' && ft_strchr(*flag, '-')) ||
			(*cur == '#' && sub[0] == '-') ||
			(*cur == '#' && ft_strequ(sub, "0") && ft_strchr("xX", type)))
			*cur = ',';
		++cur;
	}
	return (1);
}

t_sub	makesub(char **fmt, va_list ap, int init)
{
	t_sub	sub;

	sub.s = 0;
	sub.flags = 0;
	sub.len = 0;
	if (init)
		return (sub);
	*fmt = fill_flags(*fmt, &(sub.flags));
	*fmt = fill_pw(*fmt, ap, &(sub.p), &(sub.w));
	*fmt = fill_type(*fmt, &(sub.mod), &(sub.type));
	sub.s = (sub.type) ? parse(sub, ap) : 0;
	if (!sub.type || !check_flags(&(sub.flags), sub.s, sub.type, sub.w))
	{
		sub.type = 0;
		sub.s = conv_utf8(L"¯\\_(ツ)_/¯");
	}
	if (sub.w < 0)
		sub.w = sub.w * -1;
	return (sub);
}
