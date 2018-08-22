/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:55:00 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/21 17:52:10 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char	*precision(char *s, char type, int precision)
{
//	printf("Precision value: %i\n", precision);
	if (type == 's' && ft_strlen(s) >= (size_t)precision)
	{
		s[precision] = '\0';
		return (s);
	}
	if (precision == 0 && ft_strequ(s, "0"))
		return (ft_shift(&s, 0, 0));
	if (s[0] != '-' && (size_t)precision <= ft_strlen(s))
		return (s);
	if (s[0] == '-' && (size_t)precision < ft_strlen(s))
		return (s);
//	printf("Before Prec Shift: \"%s\"\n", s);
	s = ft_shift(&s, precision - ft_strlen(s), precision);
//	printf("After Prec shift: \"%s\"\n", s);
	s = addzeros(s);
//	printf("After Zeros shift: \"%s\"\n", s);
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

char	*ft_shift(char **s, int in, size_t size)
{
	char	*str;
	char	*cur;

//	printf("index: %d\n", in);
//	printf("size: %zu\n", size);
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
//		printf("size in shift: %zu\n", size);
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
	return(ft_shift(&s, width - ft_strlen(s), width));
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

char	*fill_flags(char *fmt, char *s, char type)
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
	int		prec;
	int		w;


	type = *to_type(fmt);
	flags = fill_flags(fmt, s, type);
//	printf("type: \"%c\"\n", type);
//	printf("flags: \"%s\"\n", flags);

	while (fmt && (!ft_isalnum(*fmt) || *fmt == '0') && *fmt != '.')
		++fmt;
	w = (ft_isdigit(*fmt)) ? ft_atoi(fmt) : 0;
	while (fmt && !ft_isalpha(*fmt) && *fmt != '.')
		++fmt;
	prec = (*fmt++ == '.') ? 1 : 0;
	p = (prec) ? ft_atoi(fmt) : ft_strlen(s);

//	printf("Width Value: \"%d\"\n", w);
//	printf("Precision Value: \"%d\"\n", p);

//	printf("Before Crop: \"%s\"\n", s);
	
	s = precision(s, type, p);
//	printf("Precision: \"%s\"\n", s);
	
	if (ft_strchr(flags, '#') || ft_strchr(flags, '+') || ft_strchr(flags, ' '))
		s = flag(s, flags, type);
//	printf("Flags: \"%s\"\n", s);
	
	s = width(s, flags, w);
//	printf("Width: \"%s\"\n", s);

	if (ft_strchr(flags, '0') && !prec)
		s = addzeros(s);
//	printf("Zeros: \"%s\"\n", s);

	return (s);
}
