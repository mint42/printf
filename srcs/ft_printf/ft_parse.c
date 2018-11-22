/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:27:43 by rreedy            #+#    #+#             */
/*   Updated: 2018/11/21 23:45:19 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// c C s S

char	*parse_cs(t_sub sub, char *s, va_list ap)
{
	if (sub.type == 'C' || (sub.mod == 'l' && sub.type == 'c'))
		s = conv_utf8_c(va_arg(ap, wchar_t));
	else if (sub.type == 'S' || (sub.mod == 'l' && sub.type == 's'))
		s = conv_utf8(va_arg(ap, wchar_t *));
	else if (sub.type == 'c' && !sub.mod)
		s = ft_ctoa(va_arg(ap, int));
	else if (sub.type == 's' && !sub.mod)
	{
		s = va_arg(ap, char *);
		if (!s)
			s = ft_strdup("(null)");
		else
			s = ft_strdup(s);
	}
	return (s);
}

// d D i I

char	*parse_di(t_sub sub, char *s, va_list ap, int base)
{
	if (sub.mod == 'h')
		s = ft_itoabase((short)va_arg(ap, int), base);
	else if (sub.mod == 'H')
		s = ft_itoabase((char)va_arg(ap, int), base);
	else if (sub.mod == 'l')
		s = ft_itoabase(va_arg(ap, long int), base);
	else if (sub.mod == 'L' || sub.type == 'D' || sub.type == 'I')
		s = ft_itoabase(va_arg(ap, long long int), base);
	else if (sub.mod == 'j')
		s = ft_itoabase(va_arg(ap, intmax_t), base);
	else if (sub.mod == 'z')
		s = ft_itoabase(va_arg(ap, size_t), base);
	else if (!sub.mod)
		s = ft_itoabase(va_arg(ap, int), base);
	return (s);
}

// b B o O u U x X

char	*parse_boux(t_sub sub, char *s, va_list ap, int base)
{
	if (sub.mod == 'h')
		s = ft_uitoabase((unsigned short)va_arg(ap, int), base);
	else if (sub.mod == 'H')
		s = ft_uitoabase((uint8_t)va_arg(ap, int), base);
	else if (sub.mod == 'l' || sub.type == 'O' || sub.type == 'U')
		s = ft_uitoabase(va_arg(ap, unsigned long int), base);
	else if (sub.mod == 'L')
		s = ft_uitoabase(va_arg(ap, unsigned long long int), base);
	else if (sub.mod == 'j')
		s = ft_uitoabase(va_arg(ap, uintmax_t), base);
	else if (sub.mod == 'z')
		s = ft_uitoabase(va_arg(ap, size_t), base);
	else if (!sub.mod)
		s = ft_uitoabase(va_arg(ap, unsigned int), base);
	return (s);
}

/*
char	*parse_ldlolu(t_sub sub, char *s, va_list ap, int base)
{
	if (!sub.mod && sub.type == 'D')
		s = ft_itoabase(va_arg(ap, long int), 10);
	else if (!sub.mod || sub.mod == 'H' || (sub.mod == 'h' && sub.type == 'U'))
		s = ft_uitoabase(va_arg(ap, unsigned long int), base);
	else if (sub.mod == 'l')
		s = ft_uitoabase(va_arg(ap, unsigned long int), base);
	else if (sub.mod == 'h')
		s = ft_uitoabase((unsigned short)va_arg(ap, unsigned long int), base);
	else if (sub.mod == 'L')
		s = ft_uitoabase(va_arg(ap, unsigned long long int), base);
	else if (sub.mod == 'j')
		s = ft_uitoabase(va_arg(ap, unsigned int), base);
	else if (sub.mod == 'z')
		s = ft_uitoabase(va_arg(ap, ssize_t), base);
	return (s);
}
*/

char	*parse(t_sub sub, va_list ap)
{
	char	*s;

	s = 0;
	if (ft_strchr("pPCSDIOU%", sub.type) && sub.mod)
		return (s);
	else if (sub.type == '%')
		s = ft_strdup("%");
	else if (sub.type == 'p' || sub.type == 'P')
		s = ft_uitoabase(va_arg(ap, uintptr_t), 16);
	else if (ft_strchr("cCsS", sub.type))
		s = parse_cs(sub, s, ap);
	else if (ft_strchr("dDiI", sub.type))
		s = parse_di(sub, s, ap, sub.base);
	else if (ft_strchr("bBoOuUxX", sub.type))
		s = parse_boux(sub, s, ap, sub.base);
	if (ft_strchr("PBX", sub.type))
		s = ft_strupper(s);
//	else if (ft_strchr("DOU", sub.type))
//		s = parse_ldlolu(sub, s, ap, sub.base);
//	else if (!s)
//		s = vatostr(0);
	return (s);
}
