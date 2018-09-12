/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:27:43 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/12 16:27:10 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		base(char *fmt)
{
	fmt = to_type(fmt);
	if (*fmt == 'o' || *fmt == 'O')
		return (8);
	if (*fmt == 'u' || *fmt == 'U')
		return (10);
	if (*fmt == 'x' || *fmt == 'X')
		return (!ft_isupper(*fmt) ? 16 : 36);
	if (*fmt == 'D')
		return (10);
	return (0);
}

int		cmp(char *fmt, char *type)
{
	++fmt;
	while (fmt && !ft_isalpha(*fmt) && *fmt != '%')
		++fmt;
	if (*fmt == '%' && *type == '%')
		return (1);
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
	if (cmp(fmt, ",ouxX"))
		s = ft_uitoabase((t_ull)va_arg(ap, unsigned int), base(fmt));
	else if (cmp(fmt, "hh,ouxX"))
		s = ft_itoa((uint8_t)va_arg(ap, int));
	else if (cmp(fmt, "h,ouxX"))
		s = ft_uitoabase((t_ull)va_arg(ap, int), base(fmt));
	else if (cmp(fmt, "l,ouxX") || cmp(fmt, ",OU") || cmp(fmt, "h,U"))
		s = ft_uitoabase((t_ull)va_arg(ap, unsigned long int), base(fmt));
	else if (cmp(fmt, "ll,ouxX"))
		s = ft_uitoabase(va_arg(ap, unsigned long long int), base(fmt));
	else if (cmp(fmt, "j,ouxX"))
		s = ft_uitoabase((t_ull)va_arg(ap, uintmax_t), base(fmt));
	else if (cmp(fmt, "z,ouxX"))
		s = ft_uitoabase((t_ull)va_arg(ap, size_t), base(fmt));
	else if (cmp(fmt, "j,DOU"))
		s = ft_uitoabase((t_ull)va_arg(ap, unsigned int), base(fmt));
	else if (cmp(fmt, "z,DOU"))
		s = ft_uitoabase((t_ull)va_arg(ap, ssize_t), base(fmt));
	else if (cmp(fmt, ",cC"))
		s = ft_ctoa(va_arg(ap, int));
	else if (cmp(fmt, ",s"))
		s = getstr(va_arg(ap, char *));
	else
		s = getstr(0);
	return (s);
}

static void	stars(char *fmt, va_list ap)
{
	while (fmt && !ft_isalpha(*fmt) && *fmt != '%')
	{
		if (*fmt == '*')
			(void)va_arg(ap, int);
		++fmt;
	}
}

char	*parse(char *fmt, va_list ap)
{
	char	*s;

	s = 0;
	stars(fmt, ap);
	if (cmp(fmt, "%"))
		s = getstr("%");
	else if (cmp(fmt, ",di"))
		s = ft_itoabase(va_arg(ap, int), 10);
	else if (cmp(fmt, "hh,di"))
		s = ft_itoabase((char)va_arg(ap, int), 10);
	else if (cmp(fmt, "h,di"))
		s = ft_itoabase((short)va_arg(ap, int), 10);
	else if (cmp(fmt, "l,di") || cmp(fmt, ",D"))
		s = ft_itoabase(va_arg(ap, long int), 10);
	else if (cmp(fmt, "ll,di"))
		s = ft_itoabase(va_arg(ap, long long int), 10);
	else if (cmp(fmt, "j,di"))
		s = ft_itoabase(va_arg(ap, intmax_t), 10);
	else if (cmp(fmt, "z,di"))
		s = ft_itoabase(va_arg(ap, size_t), 10);
	else if (cmp(fmt, ",p"))
		s = ft_ptoa(va_arg(ap, uintptr_t));
	if (!s)
		s = parse2(fmt, s, ap);
	return (s);
}
