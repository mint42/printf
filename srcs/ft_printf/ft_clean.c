/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:55:00 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/14 11:24:12 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*precision(char *sub, char *flg, char type, int precision)
{
	if (precision < 0 || ft_strchr("cCSp", type))
		return (sub);
	if (type == 's')
	{
		if (ft_strlen(sub) >= (size_t)precision)
			sub[precision] = '\0';
		return (sub);
	}
	if (precision == 0 && ft_strequ(sub, "0"))
		return (ft_shift(&sub, 0, 0));
	if (sub[0] != '-' && (size_t)precision <= ft_strlen(sub))
		return (sub);
	if (sub[0] == '-' && (size_t)precision < ft_strlen(sub))
		return (sub);
	if (sub[0] != '-')
		sub = ft_shift(&sub, precision - ft_strlen(sub), precision);
	else
		sub = ft_shift(&sub, precision - ft_strlen(sub) + 1, precision + 1);
	sub = addzeros(sub, flg, 1);
	return (sub);
}

char	*addzeros(char *sub, char *flg, int p)
{
	int		i;

	i = (ft_strchr(flg, ' ') && !p) ? 1 : 0;
	while (sub && sub[i] == ' ')
	{
		sub[i] = '0';
		++i;
	}
	if (sub[i] == '0' && (sub[i + 1] == 'x' || sub[i + 1] == 'X') && i > 0)
	{
		++i;
		sub[1] = sub[i];
		sub[i] = '0';
	}
	else if ((sub[i] == '-' || sub[i] == '+') && i > 0)
	{
		sub[0] = sub[i];
		sub[i] = '0';
	}
	return (sub);
}

char	*addflags(char *sub, char *flg, char type)
{
	if (!ft_strchr(flg, '#') && !ft_strchr(flg, '+') && !ft_strchr(flg, ' '))
		return (sub);
	if (ft_strequ(sub, "0") && type == 'o')
		return (sub);
	sub = ft_shift(&sub, 1, ft_strlen(sub) + 1);
	if (ft_strchr(flg, '#') || type == 'p')
	{
		if (type == 'x' || type == 'X' || type == 'p')
		{
			sub = ft_shift(&sub, 1, ft_strlen(sub) + 1);
			sub[1] = (type == 'X') ? 'X' : 'x';
		}
		sub[0] = '0';
		return (sub);
	}
	if (ft_strchr(flg, '+'))
		sub[0] = '+';
	return (sub);
}

char	*crop(t_sub sub, size_t *sublen)
{
	sub.s = precision(sub.s, sub.flags, sub.type, sub.p);
	sub.s = addflags(sub.s, sub.flags, sub.type);
	if (ft_strchr(sub.flags, '-') && (size_t)sub.w > ft_strlen(sub.s))
		sub.s = ft_shift(&(sub.s), 0, sub.w);
	else if ((size_t)sub.w > ft_strlen(sub.s))
		sub.s = ft_shift(&(sub.s), sub.w - ft_strlen(sub.s), sub.w);
	*sublen = (*(sub.s) == '\0' && sub.type == 'c') ? 1 : ft_strlen(sub.s);
	if (ft_strchr(sub.flags, 'n') && sub.w)
		sub.s[(ft_strchr(sub.flags, '-')) ? 0 : sub.w - 1] = '\0';
	if (ft_strchr(sub.flags, '0') && sub.p == -1)
		sub.s = addzeros(sub.s, sub.flags, 0);
	return (sub.s);
}

char	*clean(char *s, t_sub sub, char **fmt, size_t *slen)
{
	size_t	d;

	sub.len = (ft_strequ(sub.s, "%")) ? 1 : 0;
	d = ft_strlend(*fmt, '%');
	if (!s)
	{
		*slen = d;
		return (ft_strncpy(ft_strnew(d), *fmt, d));
	}
	if (!ft_strequ(sub.s, "%") || *(*fmt + 1) != '%')
		sub.s = crop(sub, &(sub.len));
	*fmt = to_type(*fmt) + 1;
	d = ft_strlend(*fmt, '%');
	s = ft_crop(&s, 0, *slen + sub.len + d);
	s = (char *)ft_memcat(s, sub.s, *slen, sub.len);
	*slen = *slen + sub.len;
	s = ft_memcat(s, *fmt, *slen, d);
	*slen = *slen + d;
	delsub(&sub.s, &sub.flags);
	return (s);
}
