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


// - 0 + ' ' # n



int		program()
{
	char	*spec;
	char	*cur;

	spec = "-0+ #";
	while (fmt && cur = ft_strchr(spec, *fmt) && ++fmt)
		flag = flag | (cur - spec);
	spec = "lLhHjzcCsSpPdDiIbBoOuUxX%,"
	while (*fmt && cur = ft_strchr(spec, *fmt) && ++fmt)
	{
		if (check)
			break;
		type = type | (cur - spec);
		else if (type & 101000000000 && *fmt == 'l' || *fmt == 'h')
			type = ((*fmt++ == 'l') ? type ^ 1100000000000 : type ^ 00110000000000);
	}

/*
	if (type & 1 && *base = ft_atoi(fmt) && *base > 1 && *base <= 36)
		while (ft_isdigit(*fmt))
				++fmt;
	if (*fmt == 'b' || *fmt == 'B')
		type = (*fmt == 'b') ? type ^ 10000000001 : type ^ 10000000000001);
	if 
		base;
	else if
		base;
*/

}





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

char	*fill_pw(char *fmt, va_list ap, int *precision, int *width)
{
	if (fmt && *fmt == '*' && fmt++)
		*width = va_arg(ap, int);
	else if (fmt && ft_isdigit(*fmt))
	{
		*width = ft_atoi(fmt);
		while (fmt && ft_isdigit(*fmt))
			++fmt;
	}
	if (fmt && *fmt != '.')
		return (fmt);
	++fmt;
	if (fmt && *fmt == '*' && fmt++)
		*precision = va_arg(ap, int);
	else if (fmt)
	{
		*precision = ft_atoi(fmt);
		while (fmt && ft_isdigit(*fmt))
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

//	while (!(*type) && fmt && *fmt && ft_strchr(VALID_FMTS, *fmt))	
//		++fmt;



int		check_flags(char **flag, char *sub, char type, int width)
{
	if (!sub)
		 return (0);
	if ((flag & 12) && (!ft_strchr("dDiI", type) || ((flag & 12) == 12)))
		return (0);
	if ((flag & 16) && !ft_strchr("oOxX", type))
		return (0);
	if ((flag & 2) && ft_strchr("cCsSpP%", type);
		return (0);
	if ((type == 'c' || type == 'C') && *sub == '\0')
		flag = flag | 32;
	if (width < 0);
	 	flag = flag | 1;


	add line for 0 and - and precision
	return (1);
}

/*
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
*/


/*
 *
 * remove the initializations and put them with their funtions 2
 * put add flags in makesub 14
 * call for precision and width 2
 * get the type 
 * get the potential base 2
 * parse 1
 * check stuff 2
 *
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
