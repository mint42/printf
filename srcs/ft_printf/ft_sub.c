/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:21:45 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/07 22:41:25 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_flags(char *fmt, t_sub *sub)
{
	char	*spec;
	char	*cur;

	FLAG = 0;
	spec = "-0+ #";
	while (*fmt && (cur = ft_strchr(spec, *fmt)) && ++fmt)
		FLAG = FLAG | (1 << (4 - (cur - spec)));
	return (fmt);
}

char	*get_pw(char *fmt, t_sub *sub, va_list ap)
{
	int		*num;

	PRECISION = -1;
	WIDTH = 0;
	JUSTIFICATION = 0;
	num = (*fmt == '.' && ++fmt) ? &PRECISION : &WIDTH;
	if (!ft_isdigit(*fmt) && *fmt != '.' && *fmt != '*')
		return (fmt);
	while (num)
	{
		if (fmt && *fmt == '*' && fmt++)
			*num = va_arg(ap, int);
		else
		{
			*num = ft_atoi(fmt);
			while (fmt && ft_isdigit(*fmt))
				++fmt;
		}
		if (num == &WIDTH && *fmt == ':' && ++fmt)
			num = &JUSTIFICATION;
		else
			num = (*fmt == '.' && num != &PRECISION && ++fmt) ? &PRECISION : 0;
	}
	return (fmt);
}

char	*get_type(char *fmt, t_sub *sub)
{
	char	*spec;
	char	*cur;

	TYPE = 0;
	spec = "lLhHjzcCsSdDiIbBoOuUxXpP%(";
	if (*fmt && (cur = ft_strchr(spec, *fmt)) && (cur - spec) < 6 && ++fmt)
		TYPE = TYPE | (1 << (25 - (cur - spec)));
	if ((TYPE & 0x2800000) && (*fmt == 'l' || *fmt == 'h'))
		TYPE = (*fmt++ == 'l') ? TYPE ^ 0x3000000 : TYPE ^ 0xC00000;
	if (*fmt && (cur = ft_strchr(spec, *fmt)) && (cur - spec) >= 6 && ++fmt)
		TYPE = TYPE | (1 << (25 - (cur - spec)));
	if (TYPE & 0xFCC0)
		BASE = (TYPE & 0xC00) ? 2 : 10;
	else if (TYPE & 0x330)
		BASE = (TYPE & 0x300) ? 8 : 16;
	else if ((TYPE & 0x1) && (BASE = ft_atoi(fmt)) && BASE > 1 && BASE <= 36)
		while (ft_isdigit(*fmt))
			++fmt;
	if ((TYPE & 0x1) && *fmt == ')' && ++fmt && (*fmt == 'b' || *fmt == 'B'))
		TYPE = (*fmt++ == 'b') ? TYPE ^ 0x801 : TYPE ^ 0x401;
	if (!(TYPE & 0xFFFFE))
		TYPE = 0;
	return (fmt);
}

/*
** - 0+ #
** lL hHjz cCsS dDiI bBoO uUxX pP%(
*/

int		checks(char **fmt, t_sub *sub)
{
	if (((FLAG & 0x6) && (!(TYPE & 0xF000) || ((FLAG & 0x6) == 0x6))) ||
		((FLAG & 0x1) && (BASE != 8 && BASE != 16 && BASE != 2)) ||
		((FLAG & 0x8) && (TYPE & 0xF000E)) ||
		((TYPE & 0x3F00000) && (TYPE & 0x5514E)))
		TYPE = 0;
	if (!TYPE || !S)
	{
		while (*fmt && **fmt && ft_strchr(VALID_FMTS, **fmt))
			++(*fmt);
		return (0);
	}
	if (WIDTH < 0)
	{
		FLAG = FLAG | 0x10;
		WIDTH = WIDTH * -1;
	}
	if ((FLAG & 0x8) && ((FLAG & 0x10) || PRECISION > -1))
		FLAG = FLAG ^ 0x8;
	if ((PRECISION > -1) && (TYPE & 0xD000E))
		PRECISION = -1;
	if (S[0] == '-' && (FLAG & 0x7))
		FLAG = FLAG & 0x18;
	if (ft_strequ(S, "0") && (FLAG & 0x5))
		FLAG = (FLAG & 0x4) ? (FLAG ^ 0x6) : (FLAG & 0x18);
	return (1);
}

t_sub	makesub(char **fmt, va_list ap, int init)
{
	t_sub	sub;

	sub.s = 0;
	sub.len = 0;
	if (init)
		return (sub);
	++(*fmt);
	*fmt = get_flags(*fmt, &sub);
	*fmt = get_pw(*fmt, &sub, ap);
	*fmt = get_type(*fmt, &sub);
	sub.s = (sub.type) ? parse(sub, ap) : 0;
	if (!checks(fmt, &sub))
		sub.s = conv_utf8_str(L"¯\\_(ツ)_/¯", sub.s);
	return (sub);
}
