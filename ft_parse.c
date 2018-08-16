/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:27:43 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/16 09:18:06 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		base(char *fmt)
{
	fmt = to_type(fmt);
	if (*fmt == 'o' || *fmt == 'O')
		return (!ft_isupper(*fmt) ? 6 : 26);
	if (*fmt == 'x' || *fmt == 'X')
		return (!ft_isupper(*fmt) ? 8 : 28);
	if (*fmt == 'u' || *fmt == 'U')
		return (!ft_isupper(*fmt) ? 10 : 30);
	return (0);
}

int		cmp(char *fmt, char *type)
{
	++fmt;
	if (*fmt == '%' && *type == '%')
		return (1);
	while (fmt && !ft_isalpha(*fmt))
		++fmt;
	while (type && *type != ',' && *type == *fmt)
	{
		++type;
		++fmt;
	}
	if (*type != ',')
		return (0);
	while (*type++)
		if (*fmt == *type)
			return (1);
	return (0);
}

char	*parse2(char *fmt, char *s, va_list ap)
{
	if (cmp(fmt, ",ouUxX"))
		s = ft_uitoabase((t_ull)va_arg(ap, unsigned int), base(fmt));
//	else if (cmp(fmt, "hh,ouUxX"))
//		s = ft_uctoa(va_arg(ap, unsigned char), base(fmt));
	else if (cmp(fmt, "h,ouUxX"))
		s = ft_uitoabase((t_ull)va_arg(ap, int), base(fmt));
	else if (cmp(fmt, "l,ouUxX"))
		s = ft_uitoabase((t_ull)va_arg(ap, unsigned long int), base(fmt));
	else if (cmp(fmt, "ll,ouUxX"))
		s = ft_uitoabase(va_arg(ap, unsigned long long int), base(fmt));
	else if (cmp(fmt, "j,ouUxX"))
		s = ft_uitoabase((t_ull)va_arg(ap, uintmax_t), base(fmt));
	else if (cmp(fmt, "z,ouUxX"))
		s = ft_itoabase((long long int)va_arg(ap, size_t), base(fmt));
	else if (cmp(fmt, ",c"))
		s = ft_ctoa(va_arg(ap, int));
//	else if (cmp(fmt, "l,c") || cmp(fmt, ",C"))
//		s = va_arg(ap, wint_t);
	else if (cmp(fmt, ",s"))
		s = ft_strdup(va_arg(ap, char *));
//	else if (cmp(fmt, "l,s") || cmp(fmt, "S"))
//		s = va_arg(ap, wint_t *);
	else if (cmp(fmt, ",p"))
		s = ft_strdup((char *)va_arg(ap, void *));
	return (s);
}

char	*parse(char *fmt, va_list ap)
{
	char	*s;

	s = 0;
	if (cmp(fmt, "%"))
		s = ft_strdup("%");
	else if (cmp(fmt, ",di"))
		s = ft_itoabase((long long int)va_arg(ap, int), 10);
	else if (cmp(fmt, "hh,di"))
		s = ft_ctoa(va_arg(ap, int));
	else if (cmp(fmt, "h,di"))
		s = ft_itoabase((long long int)va_arg(ap, int), 10);
	else if (cmp(fmt, "l,di"))
		s = ft_itoabase((long long int)va_arg(ap, long int), 10);
	else if (cmp(fmt, "ll,di"))
		s = ft_itoabase((long long int)va_arg(ap, long long int), 10);
	else if (cmp(fmt, "j,di"))
		s = ft_itoabase((long long int)va_arg(ap, intmax_t), 10);
	else if (cmp(fmt, "z,di"))
		s = ft_itoabase((long long int)va_arg(ap, size_t), 10);
	if (!s)
		s = parse2(fmt, s, ap);
//	s = addsign(s, fmt);
//	s = cutandpad(s, fmt);
	return (s);
}
