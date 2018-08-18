/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:55:00 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/18 13:55:22 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*precision(char *s, char *fmt)
{
	int		i;

	while (fmt && !ft_isalpha(*fmt) && *fmt != '.')
		++fmt;
	if (!fmt || *fmt != '.')
		return (s);
	++fmt;
	i = ft_atoi(fmt);
	s[i] = '\0';
	return (s);
}

char	*ft_shift(char **s, int in, size_t size)
{
	char	*str;
	char	*cur;

	str = ft_strinit(' ', size);
	cur = *s;
	if (!str)
		return (0);
	while (cur && *cur && size)
	{
		str[in] = *cur;
		++cur;
		++in;
		--size;
	}
	ft_strdel(s);
	return (str);
}

char	*flag(char *s, char *flags, char type)
{
	int		i;

	i = 0;
	if (!ft_strchr(flags, '+') && ft_strchr(flags, ' ') && s[0] == '0')
		return (s);
	if (s[0] == '-')
		return (s);
	if (s[0] != ' ' || s[0] != '0')
		s = ft_shift(&s, 1, ft_strlen(s) + 1);
	if (ft_strchr(flags, '#'))
	{
		if ((type == 'x' || type == 'X') && (s[1] != ' ' || s[1] != '0'))
			s = ft_shift(&s, 1, ft_strlen(s) + 1);
		while (s[i + 2] == ' ')
			++i;
		if (type == 'x' || type == 'X')
			s[i-- + 1] = type;
		s[i] = '0';
		return (s);
	}
	else if (ft_strchr(flags, '+'))
	{
		while (s[i + 1] == ' ')
			++i;
		s[i] = '+';
	}
	return (s);
}

char	*width(char *s, char *fmt, char *flags)
{
	int		i;
	int		width;

	i = 0;
	while (fmt && !ft_isdigit(*fmt) && !ft_isalpha(*fmt) && *fmt != '.')
		++fmt;
	if (!ft_isdigit(*fmt))
		return (s);
	width = ft_atoi(fmt);
	if ((size_t)width <= ft_strlen(s))
		return (s);
	if (ft_strchr(flags, '-'))
		return (ft_shift(&s, 0, width));
	s = ft_shift(&s, width - ft_strlen(s), width);	
	if (!ft_strchr(flags, '0'))
		return (s);
	while (s && s[i] == ' ')
		s[i++] = '0';
	if (s[i] == '-')
	{
		s[0] = '-';
		s[i] = '0';
	}
	return (s);
}

char	*crop(char *s, char *fmt)
{
	char	*cur;
	char	*flags;
	int		i;

	flags = ft_strnew(5);
	cur = fmt;
	i = 0;
	while (++cur && !ft_isalpha(*cur) && *cur != '%')
	{
		if (ft_strchr("-0# +", *cur))
		{
			flags[i] = *cur;
			++i;
		}
	}
	cur = to_type(fmt);
	if (*cur == 's')
		s = precision(s, fmt);
	s = width(s, fmt, flags);
	if (!flags || ft_strchr("sScCp", *to_type(fmt)))
		return (s);
	if (ft_strchr(flags, '#') || ft_strchr(flags, '+') || ft_strchr(flags, ' '))
		s = flag(s, flags, *(to_type(fmt)));
	return (s);
}
