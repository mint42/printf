/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:55:00 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/30 15:42:27 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*precision(char *s, char type, int precision)
{
	if (type == 's')
	{
		if (ft_strlen(s) >= (size_t)precision)
			s[precision] = '\0';
		return (s);
	}
	if (precision == 0 && ft_strequ(s, "0"))
		return (ft_shift(&s, 0, 0));
	if (s[0] != '-' && (size_t)precision <= ft_strlen(s))
		return (s);
	if (s[0] == '-' && (size_t)precision < ft_strlen(s))
		return (s);
	if (s[0] != '-')
		s = ft_shift(&s, precision - ft_strlen(s), precision);
	else
		s = ft_shift(&s, precision - ft_strlen(s) + 1, precision + 1);
	s = addzeros(s);
	return (s);
}

char	*addzeros(char *s)
{
	int		i;

	i = 0;
	while (s && s[i] == ' ')
	{
		s[i] = '0';
		++i;
	}
	if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X') && i > 0)
	{
		++i;
		s[1] = s[i];
		s[i] = '0';
	}
	else if ((s[i] == '-' || s[i] == '+') && i > 0)
	{
		s[0] = s[i];
		s[i] = '0';
	}
	return (s);
}

char	*flag(char *s, char *flags, char type)
{
	s = ft_shift(&s, 1, ft_strlen(s) + 1);
	if (ft_strchr(flags, '#'))
	{
		if (type == 'x' || type == 'X')
		{
			s = ft_shift(&s, 1, ft_strlen(s) + 1);
			s[1] = type;
		}
		s[0] = '0';
		return (s);
	}
	if (ft_strchr(flags, '+'))
		s[0] = '+';
	return (s);
}

char	*fill_flags(char *s, char *fmt, char type)
{
	char	*flags;
	int		i;

	flags = ft_strnew(5);
	i = 0;
	while (++fmt && (!ft_isalnum(*fmt) || *fmt == '0') && *fmt != '%')
		if ((*fmt == '-') || (*fmt == '0' && !ft_strchr("sScCp", type)) ||
			((*fmt == '+' || *fmt == ' ') && ft_strchr("dDi", type)) ||
			(*fmt == '#' && ft_strchr("oOxX", type)))
			if (!ft_strchr(flags, *fmt))
				flags[i++] = *fmt;
	i = 0;
	while (flags[i] != '\0')
	{
		if ((flags[i] == '+' || flags[i] == '#') && s[0] == '-')
			flags[i] = '.';
		if (flags[i] == ' ' && (ft_strchr(flags, '+') || s[0] == '-'))
			flags[i] = '.';
		if (flags[i] == '0' && ft_strchr(flags, '-'))
			flags[i] = '.';
		if (flags[i] == '#' && ft_strequ(s, "0") && ft_strchr("xX", type))
			flags[i] = '.';
		++i;
	}
	return (flags);
}

char	*crop(char *s, char *fmt)
{
	char	*flags;
	char	type;
	int		p;
	int		w;

	type = *to_type(fmt);
	flags = fill_flags(s, fmt, type);
	while (fmt && (!ft_isalnum(*fmt) || *fmt == '0') && *fmt != '.')
		++fmt;
	w = (ft_isdigit(*fmt)) ? ft_atoi(fmt) : 0;
	while (fmt && !ft_isalpha(*fmt) && *fmt != '.')
		++fmt;
	p = (*fmt++ == '.') ? ft_atoi(fmt) : -1;
	if (p >= 0 && !ft_strchr("cCSp", type))
		s = precision(s, type, p);
	if (ft_strchr(flags, '#') || ft_strchr(flags, '+') || ft_strchr(flags, ' '))
		s = flag(s, flags, type);
	if (ft_strchr(flags, '-') && (size_t)w >= ft_strlen(s))
		s = ft_shift(&s, 0, w);
	else if ((size_t)w >= ft_strlen(s))
		s = ft_shift(&s, w - ft_strlen(s), w);
	if (ft_strchr(flags, '0') && p == -1)
		s = addzeros(s);
	return (s);
}
