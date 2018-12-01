/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:21:45 by rreedy            #+#    #+#             */
/*   Updated: 2018/11/29 03:03:20 by rreedy           ###   ########.fr       */
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
	PRECISION = -1;
	WIDTH = 0;

	if (fmt && *fmt == '*' && fmt++)
		WIDTH = va_arg(ap, int);
	else if (fmt && ft_isdigit(*fmt))
	{
		WIDTH = ft_atoi(fmt);
		while (fmt && ft_isdigit(*fmt))
			++fmt;
	}
	if (fmt && *fmt != '.')
		return (fmt);
	++fmt;
	if (fmt && *fmt == '*' && fmt++)
		PRECISION = va_arg(ap, int);
	else if (fmt)
	{
		PRECISION = ft_atoi(fmt);
		while (fmt && ft_isdigit(*fmt))
			++fmt;
	}
	return (fmt);
}

char	*get_type(char *fmt, t_sub *sub)
{
	char	*spec;
	char	*cur;

	TYPE = 0;
	spec = "lLhHjzcCsSdDiIbBoOuUxXpP%,";

	if (*fmt && (cur = ft_strchr(spec, *fmt)) && (cur - spec) <= 6 && ++fmt)
		TYPE = TYPE | (1 << (25 - (cur - spec)));
	if ((TYPE & 0x2800000) && (*fmt == 'l' || *fmt == 'h'))
			TYPE = (*fmt++ == 'l') ? TYPE ^ 0x3000000 : TYPE ^ 0xC00000;
	if (*fmt && (cur = ft_strchr(spec, *fmt)) && (cur - spec) > 6 && ++fmt)
		TYPE = TYPE | (1 << (25 - (cur - spec)));
	if (TYPE & 0xFCC0)
		BASE = (TYPE & 0xC00) ? 2 : 10;
	else if  (TYPE & 0x330)
		BASE = (TYPE & 0x300) ? 8 : 16;
	else if ((TYPE & 0x1) && (BASE = ft_atoi(fmt)) && BASE > 1 && BASE <= 36)
		while (ft_isdigit(*fmt))
				++fmt;
	if ((TYPE & 0x1) && (*fmt == 'b' || *fmt == 'B'))
		TYPE = (*fmt++ == 'b') ? TYPE ^ 0x801 : TYPE ^ 0x401;
	if (!(TYPE & 0xFFFFE))
		TYPE = 0;
	return (fmt);
}

//  - 0+ #
//  lL hHjz cCsS dDiI bBoO uUxX pP%,

int		checks(char **fmt, t_sub *sub)
{
	if (((FLAG & 0x6) && (!(TYPE & 0xF000) || ((FLAG & 0x6) == 0x6))) ||
		((FLAG & 0x1) && (!(TYPE & 0x330))) ||
		((FLAG & 0x8) && (TYPE & 0xF000E)) ||
		((TYPE & 0x3F00000) && (TYPE & 0x5514E)))
		TYPE = 0;
	if (!TYPE)
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
	*fmt = get_pw(*fmt,&sub, ap);
	*fmt = get_type(*fmt, &sub);
	sub.s = (checks(fmt, &sub)) ? parse(sub, ap) : conv_utf8(L"¯\\_(ツ)_/¯");	
	if (!sub.s)
		sub.s = conv_utf8(L"¯\\_(ツ)_/¯");
	return (sub);
}




/*
int		*fill_flags(char *fmt, int flag)
{

	while (fmt)
	{
		if (*fmt == '-')
			flag = flag | 1;
		else if (*fmt == '0')
			flag = flag | 2;
		else if (*fmt == '+')
			flag = flag | 4;
		else if (*fmt == ' ')
			flag = flag | 8;
		else if (*fmt == '#')
			flag = flag | 16;
		else
			return (flag);
		++fmt;
	}
}

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
			**flag = '-';
		if (!ft_strchr(*flag, *fmt))
			*cur++ = *fmt;
		++fmt;
	}
	return (fmt);
}

char 	*fill_type(char *fmt, char *mod, char *type, int *base)
{
	if (fmt && ft_strchr(VALID_MODS, *fmt))
	{
		*mod = *fmt;
		++fmt;
		if (fmt && (*mod == 'l' || *mod == 'h') && (*fmt == 'l' || *fmt == 'h'))
			*mod = ((*fmt++ == 'l') ? 'L' : 'H');
	}
	if (*fmt == ',' && (*base = ft_atoi(fmt + 1)) > 1 && *base <= 36 && fmt++)
		while (fmt && ft_isdigit(*fmt))
			++fmt;
	*type = (fmt && ft_strchr(VALID_TYPE, *fmt)) ? *fmt : 0;
	if ((*type != 'b' || *type != 'B') && *base)
		*type = 0;
	else if ((*type == 'b' || *type == 'B') && !(*base))
		*base = 2;
	else if (*type == 'o' || *type == 'O')
		*base = 8;
	else if (*type == 'x' || *type == 'X')
		*base = 16;
	else if (ft_strchr("dDiIuU", *type))
		*base = 10;
	return (fmt);
}

int		check_flags(char **flag, char *sub, char type, int width)
{
	char	*cur;

	cur = *flag;

	if (!sub)
		return (0);
	if (width < 0)
		*cur++ = '-';
	if ((type == 'c' || type == 'C') && *sub == '\0')
		*cur++ = 'n';
	while (cur && *cur)
	{
		if ((*cur == '+' || *cur == ' ') && (!ft_strchr("dDiI", type) ||
			(ft_strchr(*flag, '+') && ft_strchr(*flag, ' '))))
			return (0);
		if (*cur == '#' && !ft_strchr("oOxX", type))
			return (0);
		if (*cur == '0' && ft_strchr("cCsSpP%", type))
			return (0);
		++cur;
	}
	return (1);
}

/* 
** make flags with bits that will save memory and mallocing and access time
** give each flag a spot to go to 
*/

t_sub	makesub(char **fmt, va_list ap, int init)
{
	t_sub	sub;

	sub.flags = 0;
	sub.p = -1;
	sub.w = 0;
	sub.mod = 0;
	sub.type = 0;
	sub.base = 0;
	sub.s = 0;
	sub.len = 0;
	if (init)
		return (sub);
	*fmt = fill_flags(*fmt, &(sub.flags));
	*fmt = fill_pw(*fmt, ap, &(sub.p), &(sub.w));
	*fmt = fill_type(*fmt, &(sub.mod), &(sub.type), &(sub.base));
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

*/
