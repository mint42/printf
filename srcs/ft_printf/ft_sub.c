/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:21:45 by rreedy            #+#    #+#             */
/*   Updated: 2018/10/23 16:19:20 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
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
*/

void	fill_type(char *fmt, char *mod, char *type)
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
			*flag[0] = '-';
		else if (!ft_strchr(*flag, *fmt))
			*cur++ = *fmt;
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
/*
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
*/

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
//	else if (fmt && ft_isdigit(*fmt))
//		*precision = ft_atoi(fmt);
	else if (fmt && *(fmt - 1) == '.')
		*precision = ft_atoi(fmt);
	while (fmt && (*fmt == '*' || ft_isdigit(*fmt)))
		++fmt;
	return (fmt);
}

/*
**	void	delsub(char **s, char **flags)
**	{
**		(void)s;
**		ft_strdel(s);
**		ft_strdel(flags);
**	}
*/

int		check_flags(char **flag, char *sub, char type, int width)
{
	char	*cur;

	cur = *flag;
	if (width < 0)
		*cur++ = '-';
	if ((type == 'c' || type == 'C') && *sub == '\0')
		*cur++ = 'n';
//	printf("flags: |%s|\n", *flag);
//	printf("type: |%c|\n", type);
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

t_sub	makesub(char *fmt, va_list ap, int init)
{
	t_sub	sub;

	sub.s = 0;
	sub.flags = 0;
	if (init)
		return (sub);
	fmt = fill_flags(fmt, &(sub.flags));
	fmt = fill_pw(fmt, ap, &(sub.p), &(sub.w));
	fill_type(fmt, &(sub.mod), &(sub.type));
	sub.s = (sub.type) ? parse(sub, ap) : ft_strnew(0);
	if (!fmt || !sub.type || !check_flags(&(sub.flags), sub.s, sub.type, sub.w))
	{
		sub.type = 0;
		sub.s = conv_utf8(L"¯\\_(ツ)_/¯");
	}
	if (sub.w < 0)
		sub.w = sub.w * -1;
	sub.len = 0;
	return (sub);
}

/*
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
*/
