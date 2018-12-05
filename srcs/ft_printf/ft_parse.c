/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:27:43 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/03 18:55:49 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*parse_cs(t_sub sub, char *s, va_list ap)
{
	if ((sub.type & 0x40000) || (sub.type == 0x2080000))
		s = conv_utf8_c(va_arg(ap, wchar_t));
	else if ((sub.type & 0x10000) || (sub.type == 0x2020000))
		s = conv_utf8(va_arg(ap, wchar_t *));
	else if ((sub.type & 0x3F80000) == 0x0080000)
		s = ft_ctoa(va_arg(ap, int));
	else if ((sub.type & 0x3F20000) == 0x0020000)
	{
		s = va_arg(ap, char *);
		if (!s)
			s = ft_strdup("(null)");
		else
			s = ft_strdup(s);
	}
	return (s);
}

char	*parse_di(t_sub sub, char *s, va_list ap, int base)
{
	if (sub.type & 0x800000)
		s = ft_itoabase((short)va_arg(ap, int), base);
	else if (sub.type & 0x400000)
		s = ft_itoabase((char)va_arg(ap, int), base);
	else if (sub.type & 0x2005000)
		s = ft_itoabase(va_arg(ap, long int), base);
	else if (sub.type & 0x1000000)
		s = ft_itoabase(va_arg(ap, long long int), base);
	else if (sub.type & 0x200000)
		s = ft_itoabase(va_arg(ap, intmax_t), base);
	else if (sub.type & 0x100000)
		s = ft_itoabase(va_arg(ap, size_t), base);
	else if (!(sub.type & 0x3F00000))
		s = ft_itoabase(va_arg(ap, int), base);
	return (s);
}

char	*parse_boux(t_sub sub, char *s, va_list ap, int base)
{
	if (sub.type & 0x800000)
		s = ft_uitoabase((unsigned short)va_arg(ap, int), base);
	else if (sub.type & 0x400000)
		s = ft_uitoabase((uint8_t)va_arg(ap, int), base);
	else if (sub.type & 0x2000140)
		s = ft_uitoabase(va_arg(ap, unsigned long int), base);
	else if (sub.type & 0x1000000)
		s = ft_uitoabase(va_arg(ap, unsigned long long int), base);
	else if (sub.type & 0x200000)
		s = ft_uitoabase(va_arg(ap, uintmax_t), base);
	else if (sub.type & 0x100000)
		s = ft_uitoabase(va_arg(ap, size_t), base);
	else if (!(sub.type & 0x3F00000))
		s = ft_uitoabase(va_arg(ap, unsigned int), base);
	return (s);
}

char	*parse(t_sub sub, va_list ap)
{
	char	*s;

	s = 0;
	if (sub.type & 0x2)
		s = ft_strdup("%");
	else if (sub.type & 0xC)
		s = ft_uitoabase(va_arg(ap, uintptr_t), 16);
	else if (sub.type & 0xF0000)
		s = parse_cs(sub, s, ap);
	else if (sub.type & 0xF000)
		s = parse_di(sub, s, ap, sub.base);
	else if (sub.type & 0xFF0)
		s = parse_boux(sub, s, ap, sub.base);
	return (s);
}
