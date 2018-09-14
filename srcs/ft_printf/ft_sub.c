/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 12:16:05 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/14 11:23:33 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*to_type(char *fmt)
{
	++fmt;
	while (!ft_isalpha(*fmt) && *fmt != '%')
		++fmt;
	if (*fmt == 'l' || *fmt == 'h' || *fmt == 'j' || *fmt == 'z')
		++fmt;
	if (*fmt == 'l' || *fmt == 'h')
		++fmt;
	return (fmt);
}

char	*fill_flags(char *sub, char *fmt, char type)
{
	char	*flg;
	int		i;

	flg = ft_strnew(6);
	i = 0;
	if ((type == 'c' || type == 'C') && (*sub) == '\0')
		flg[i++] = 'n';
	while (++fmt && (!ft_isalnum(*fmt) || *fmt == '0') && *fmt != '%')
		if (ft_strchr("-+ 0#", *fmt) && !ft_strchr(flg, *fmt))
			flg[i++] = *fmt;
	i = 0;
	while (flg[i] != '\0')
	{
		if ((flg[i] == '+' && (sub[0] == '-' || !ft_strchr("dDi", type))) ||
			(flg[i] == ' ' && (sub[0] == '-' || ft_strchr(flg, '+') ||
			!ft_strchr("dDi", type))) || (flg[i] == '0' && (ft_strchr(flg, '-')
			|| ft_strchr("sScCp", type))) || (flg[i] == '#' &&
			(!ft_strchr("oOxX", type) || sub[0] == '-')) ||
			(flg[i] == '#' && ft_strequ(sub, "0") && ft_strchr("xX", type)))
			flg[i] = '.';
		++i;
	}
	return (flg);
}

void	fill_pw(char *fmt, va_list ap, int *precision, int *width)
{
	
	*width = 0;
	*precision = -1;

	if (*fmt == '%' && *(fmt + 1) == '%')
		return ;
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
		*precision = (*fmt++ == '.') ? ft_atoi(fmt) : -1;

//	*width = 0;
//	*precision = -1;
//	while (fmt && (!ft_isalnum(*fmt) || *fmt == '0') && !ft_strchr(".*", *fmt))
//		++fmt;
//	if (*fmt == '*')
//		*width = va_arg(ap, int);
//	else
//		*width = (ft_isdigit(*fmt)) ? ft_atoi(fmt) : 0;
//	while (fmt && !ft_isalpha(*fmt) && !ft_strchr(".*", *fmt))
//		++fmt;
//	if (*fmt == '*')
//		*precision = va_arg(ap, int);
//	else
//		*precision = (*fmt++ == '.') ? ft_atoi(fmt) : -1;
}

void	delsub(char **s, char **flags)
{
	(void)s;
	ft_strdel(s);
	ft_strdel(flags);
}

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
	sub.type = *to_type(fmt);
	sub.s = parse(fmt, ap);
	sub.flags = fill_flags(sub.s, fmt, sub.type);
	sub.len = 0;
	return (sub);
}
