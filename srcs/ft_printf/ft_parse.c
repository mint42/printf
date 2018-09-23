/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:27:43 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/23 08:37:03 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_base(t_sub sub, char *fmt)
{
	fmt = ft_strchr(fmt, sub.type);
	if (ft_strchr("oO", *fmt))
		return (8);
	if (ft_strchr("xX", *fmt))
		return (!ft_isupper(*fmt) ? 16 : 36);
	if (ft_strchr("idDuU", *fmt))
		return (10);
	return (0);
}

char	*parse_cCsS(t_sub sub, char *s, va_list ap)
{
	if (sub.type == 'c')
		s = ft_ctoa(va_arg(ap, int));
	else if (sub.type == 'C')
		s = conv_utf8_c(va_arg(ap, wchar_t));
	else if (sub.type == 's')
		s = vatostr(va_arg(ap, char *));
	else if (sub.type == 'S')
		s = conv_utf8(va_arg(ap, wchar_t *));
	return (s);
}

char	*parse_di(t_sub sub, char *s, va_list ap, int base)
{
	if (!sub.mod)
		s = ft_itoabase(va_arg(ap, int), base);
	else if (sub.mod == 'H')
		s = ft_itoabase((char)va_arg(ap, int), base);
	else if (sub.mod == 'h')
		s = ft_itoabase((short)va_arg(ap, int), base);
	else if (sub.mod == 'L')
		s = ft_itoabase(va_arg(ap, long long int), base);
	else if (sub.mod == 'l')
		s = ft_itoabase(va_arg(ap, long int), base);
	else if (sub.mod == 'j')
		s = ft_itoabase(va_arg(ap, intmax_t), base);
	else if (sub.mod == 'z')
		s = ft_itoabase(va_arg(ap, size_t), base);
	return (s);
}

char	*parse_ouxX(t_sub sub, char *s, va_list ap, int base)
{
	if (!sub.mod)
		s = ft_uitoabase((t_ull)va_arg(ap, unsigned int), base);
	else if (sub.mod == 'H')
		s = ft_itoa((uint8_t)va_arg(ap, int));
	else if (sub.mod == 'h')
		s = ft_uitoabase((t_ull)va_arg(ap, int), base);
	else if (sub.mod == 'L')
		s = ft_uitoabase(va_arg(ap, unsigned long long int), base);
	else if (sub.mod == 'l')
		s = ft_uitoabase((t_ull)va_arg(ap, unsigned long int), base);
	else if (sub.mod == 'j')
		s = ft_uitoabase((t_ull)va_arg(ap, uintmax_t), base);
	else if (sub.mod == 'z')
		s = ft_uitoabase((t_ull)va_arg(ap, size_t), base);
	return (s);
}

char	*parse_DOU(t_sub sub, char *s, va_list ap, int base)
{
	if (!sub.mod && sub.type == 'D')
		s = ft_itoabase(va_arg(ap, long int), 10);
	else if (!sub.mod)
		s = ft_uitoabase((t_ull)va_arg(ap, unsigned long int), base);
	else if (sub.mod == 'h' && sub.type == 'U')
		s = ft_uitoabase((t_ull)va_arg(ap, unsigned long int), base);	
	else if (sub.mod == 'j')
		s = ft_uitoabase((t_ull)va_arg(ap, unsigned int), base);
	else if (sub.mod == 'z')
		s = ft_uitoabase((t_ull)va_arg(ap, ssize_t), base);
	return (s);
}

char	*parse(t_sub sub, char *fmt, va_list ap)
{
	char	*s;
	int		base;

	s = 0;
	base = get_base(sub, fmt);
	if (sub.type == '%')
		s = vatostr("%");
	else if (sub.type == 'p')
		s = ft_ptoa(va_arg(ap, uintptr_t));
	else if (ft_strchr("cCsS", sub.type))
		s = parse_cCsS(sub, s, ap);
	else if (ft_strchr("di", sub.type))
		s = parse_di(sub, s, ap, base);
	else if (ft_strchr("ouxX", sub.type))
		s = parse_ouxX(sub, s, ap, base);
	else if (ft_strchr("DOU", sub.type))
		s = parse_DOU(sub, s, ap, base);
	else if (!s)
		s = vatostr(0);
	return (s);
}
