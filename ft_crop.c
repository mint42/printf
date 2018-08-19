/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:55:00 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/18 18:03:54 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*precision(char *s, char *fmt)
{
	size_t	i;

	while (fmt && !ft_isalpha(*fmt) && *fmt != '.')
		++fmt;
	if (!fmt || *fmt != '.')
		return (s);
	++fmt;
	i = ft_atoi(fmt);
//	printf("Precision value: %zi\n", i);
	if (*to_type(fmt) == 's')
	{
		s[i] = '\0';
		return (s);
	}
	if (i <= ft_strlen(s))
		return (s);
//	printf("Before Prec Shift: \"%s\"\n", s);
	if (s[0] != '-')
		s = ft_shift(&s, i - ft_strlen(s), i);
	else
		s = ft_shift(&s, i + 1 - ft_strlen(s), i + 1);	
//	printf("After Prec shift: \"%s\"\n", s);
	s = addzeros(s);
//	printf("After Zeros shift: \"%s\"\n", s);
	return (s);
}

char	*addzeros(char *s)
{
	int		i;

	i = 0;
	while (ft_strchr("+-", s[i]))
		++i;
	while (s && s[i] == ' ')
		s[i++] = '0';
	if ((s[i] == '-' || s[i] == '+') && i > 0)
	{
		s[0] = (s[i] == '-') ? '-' : '+';
		s[i] = '0';
	}
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
//		printf("str in shift: \"%s\"\n", str);
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
	
	
//	if (!ft_strchr(flags, '+') && ft_strchr(flags, ' ') && s[0] == '0')
//		return (s);

	
	while (s[i] == ' ')
		++i;
	if (s[i] == '-' || type == 'u' || type == '%')
		return (s);	
	if (i == 0)
		s = ft_shift(&s, 1, ft_strlen(s) + 1);
	else
		--i;
	
	if (ft_strchr(flags, '#'))
	{
		if ((type == 'x' || type == 'X') && (s[1] != ' ' && s[1] != '0'))
			s = ft_shift(&s, 1, ft_strlen(s) + 1);
		while (s[i + 2] == ' ')
			++i;
		if (type == 'x' || type == 'X')
			s[i-- + 1] = type;
		s[i] = '0';
		return (s);
	}
	
	
	else if (ft_strchr(flags, '+'))
		s[i] = '+';
	
	
	return (s);
}

char	*width(char *s, char *fmt, char *flags)
{
	int		i;
	int		width;

	i = 0;
	while (fmt && (!ft_isalnum(*fmt) || *fmt == '0') && *fmt != '.')
		++fmt;
	if (!ft_isdigit(*fmt))
		return (s);
	width = ft_atoi(fmt);
	if ((size_t)width <= ft_strlen(s))
		return (s);
	if (ft_strchr(flags, '-'))
		return (ft_shift(&s, 0, width));
	
	if (!ft_strchr(flags, '0'))	
		s = ft_shift(&s, width - ft_strlen(s), width);	
	else
		s = ft_shift(&s, width - ft_strlen(s), width);
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
	while (++cur && (!ft_isalnum(*cur) || *cur == '0') && *cur != '%')
	{
		if (ft_strchr("-0# +", *cur))
		{
			flags[i] = *cur;
			++i;
		}
	}
	cur = to_type(fmt);
//	printf("Before Crop: \"%s\"\n", s);
	s = precision(s, fmt);
//	printf("Precision: \"%s\"\n", s);
	s = width(s, fmt, flags);
//	printf("Width: \"%s\"\n", s);
	if (!flags || ft_strchr("sScCp", *to_type(fmt)))
		return (s);
	if (ft_strchr(flags, '#') || ft_strchr(flags, '+') || ft_strchr(flags, ' '))
		s = flag(s, flags, *(to_type(fmt)));
//	printf("Flags: \"%s\"\n", s);
	if (ft_strchr(flags, '0'))
		s = addzeros(s);
//	printf("Zeros: \"%s\"\n", s);
	return (s);
}
