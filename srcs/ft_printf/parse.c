/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:27:43 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/28 00:37:25 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*parse_unicode(t_sub *sub, va_list ap)
{
	if (TYPE == 0x40000 || TYPE == 0x2080000)
	{
		S = conv_utf8_char(va_arg(ap, wchar_t), S);
		if (*S == '\0')
			FLAGS = FLAGS | 0x40;
	}
	else if (TYPE == 0x10000 || TYPE == 0x2020000)
	{
		S = conv_utf8_str(va_arg(ap, wchar_t *), S);
		if (!S)
		{
			S = ft_strdup("(null)");
			FLAGS = FLAGS | 0x40;
		}
	}
	return ((S) ? crop_unicode(sub) : S);
}

char	*parse_csp(t_sub *sub, va_list ap)
{
	if (TYPE == 0x2)
		S = ft_strdup("%");
	else if (TYPE == 0x80000)
	{
		S = ft_ctoa(va_arg(ap, int));
		if (*S == '\0')
			FLAGS = FLAGS | 0x40;
	}
	else if (TYPE == 0x20000)
	{
		S = va_arg(ap, char *);
		if (S)
			S = ft_strdup(S);
		else
		{
			S = ft_strdup("(null)");
			FLAGS = FLAGS | 0x40;
		}
	}
	return ((S) ? crop_csp(sub) : S);
}

/*
**	char	*parse_fae(t_sub *sub, va_list ap)
**	{
**		if (TYPE & float);
**			S = ft_ftoa((float)va_arg(ap, double));
**		else if (TYPE & double);
**			S = ft_ftoa(va_arg(ap, double));
**		else if (TYPE & long double);
**			S = ft_ftoa((float)va_arg(ap, long double));
**		return ((S) ? crop_fae(sub) : S);
**	}
*/

char	*parse_di(t_sub *sub, va_list ap)
{
	if (TYPE & 0x800000)
		S = ft_itoabase((short)va_arg(ap, int), BASE);
	else if (TYPE & 0x400000)
		S = ft_itoabase((char)va_arg(ap, int), BASE);
	else if (TYPE & 0x2005000)
		S = ft_itoabase(va_arg(ap, long int), BASE);
	else if (TYPE & 0x1000000)
		S = ft_itoabase(va_arg(ap, long long int), BASE);
	else if (TYPE & 0x200000)
		S = ft_itoabase(va_arg(ap, intmax_t), BASE);
	else if (TYPE & 0x100000)
		S = ft_itoabase(va_arg(ap, size_t), BASE);
	else if (!(TYPE & 0x3F00000))
		S = ft_itoabase(va_arg(ap, int), BASE);
	return ((S) ? crop_di(sub) : S);
}

char	*parse_bouxp(t_sub *sub, va_list ap)
{
	if (TYPE & 0x800000)
		S = ft_uitoabase((unsigned short)va_arg(ap, int), BASE);
	else if (TYPE & 0x400000)
		S = ft_uitoabase((uint8_t)va_arg(ap, int), BASE);
	else if (TYPE & 0x2000140)
		S = ft_uitoabase(va_arg(ap, unsigned long int), BASE);
	else if (TYPE & 0x100000C)
		S = ft_uitoabase(va_arg(ap, unsigned long long int), BASE);
	else if (TYPE & 0x200000)
		S = ft_uitoabase(va_arg(ap, uintmax_t), BASE);
	else if (TYPE & 0x100000)
		S = ft_uitoabase(va_arg(ap, size_t), BASE);
	else if (!(TYPE & 0x3F00000))
		S = ft_uitoabase(va_arg(ap, unsigned int), BASE);
	return ((S) ? crop_bouxp(sub) : S);
}
