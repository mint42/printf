/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:55:00 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/19 14:28:42 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*precision(char *s, char type, int i)
{
//	printf("Precision value: %i\n", i);
	if (type == 's')
	{
		s[i] = '\0';
		return (s);
	}
	if ((size_t)i <= ft_strlen(s))
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
	if ((s[i] == '-' || s[i] == '+'))
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

//	printf("index: %d\n", in);
	str = ft_strinit(' ', size);
	cur = *s;
//	printf("cur: \"%s\"\n", cur);
//	printf("str: \"%s\"\n", str);
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

char	*width(char *s, char *flags, int width)
{
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

char	*flag(char *s, char *flags, char type)
{
	int		i;

	i = 0;	
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
		if ((type == 'x' || type == 'X') && s[1] != ' ' && s[1] != '0')
			s = ft_shift(&s, 1, ft_strlen(s) + 1);
		while (s[i] == ' ')
			++i;
		s[--i] = (type == 'x' || type == 'X') ? type : 0;
		if (s[i] == type)
			--i;
		s[i] = '0';
		return (s);
	}
	else if (ft_strchr(flags, '+'))
		s[i] = '+';
	return (s);
}

char	*fill_flags(char *fmt)
{
	char	*flags;
	int		i;

	flags = ft_strnew(5);
	i = 0;
	while (++fmt && (!ft_isalnum(*fmt) || *fmt == '0') && *fmt != '%')
	{
		if (ft_strchr("-0# +", *fmt))
		{
			flags[i] = *fmt;
			++i;
		}
	}
	return (flags);
}

char	*crop(char *s, char *fmt)
{
	char	*flags;
	char	type;
	int		p;
	int		w;


	flags = fill_flags(fmt);
	type = *to_type(fmt);
//	printf("type: \"%c\"\n", type);
	while (fmt && (!ft_isalnum(*fmt) || *fmt == '0') && *fmt != '.')
		++fmt;
	w = (ft_isdigit(*fmt)) ? ft_atoi(fmt) : 0;
	while (fmt && !ft_isalpha(*fmt) && *fmt != '.')
		++fmt;
	++fmt;
	p = (ft_isdigit(*fmt)) ? ft_atoi(fmt) : ft_strlen(s);
//	printf("Before Crop: \"%s\"\n", s);
	s = precision(s, type, p);
//	printf("Precision: \"%s\"\n", s);
	s = width(s, flags, w);
//	printf("Width: \"%s\"\n", s);
	if (!flags || ft_strchr("sScCp", type))
		return (s);
	if (ft_strchr(flags, '#') || ft_strchr(flags, '+') || ft_strchr(flags, ' '))
		s = flag(s, flags, type);
//	printf("Flags: \"%s\"\n", s);
	if (ft_strchr(flags, '0'))
		s = addzeros(s);
//	printf("Zeros: \"%s\"\n", s);
	return (s);
}
