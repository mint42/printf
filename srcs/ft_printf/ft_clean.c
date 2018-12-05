/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:22:01 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/03 21:01:09 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*precision(t_sub sub)
{
	if (sub.type & 0x20000)
	{
		if (ft_strlen(sub.s) >= (size_t)sub.p)
			sub.s[sub.p] = '\0';
		return (sub.s);
	}
	if (sub.s[0] != '-' && (size_t)sub.p > ft_strlen(sub.s))
		sub.s = ft_shift(&(sub.s), sub.p - ft_strlen(sub.s), sub.p);
	else if (sub.s[0] == '-' && (size_t)sub.p >= ft_strlen(sub.s))
		sub.s = ft_shift(&(sub.s), sub.p - ft_strlen(sub.s) + 1, sub.p + 1);
	sub.s = addzeros(sub, 1);
	return (sub.s);
}

char	*addzeros(t_sub sub, int p)
{
	int		i;

	i = ((sub.flags & 0x2) && !p) ? 1 : 0;
	while (sub.s && sub.s[i] == ' ')
	{
		sub.s[i] = '0';
		++i;
	}
	if (sub.s[i] == '0' && (sub.s[i + 1] == 'x' || sub.s[i + 1] == 'X') && i)
	{
		++i;
		sub.s[1] = sub.s[i];
		sub.s[i] = '0';
	}
	else if ((sub.s[i] == '-' || sub.s[i] == '+') && i)
	{
		sub.s[0] = sub.s[i];
		sub.s[i] = '0';
	}
	return (sub.s);
}

char	*addflags(t_sub sub)
{
	sub.s = ft_shift(&(sub.s), 1, ft_strlen(sub.s) + 1);
	if ((sub.flags & 0x1) || (sub.type & 0xC))
	{
		if (sub.base == 2 || sub.base == 16 || (sub.type & 0xC))
		{
			sub.s = ft_shift(&(sub.s), 1, ft_strlen(sub.s) + 1);
			sub.s[1] = (sub.base == 2) ? 'b' : 'x';
		}
		sub.s[0] = '0';
		return (sub.s);
	}
	if (sub.flags & 0x4)
		sub.s[0] = '+';
	return (sub.s);
}

char	*crop(t_sub sub, size_t *sublen)
{
	if (sub.p >= 0)
		sub.s = precision(sub);
	if ((sub.flags & 0x7) || (sub.type & 0xC))
		sub.s = addflags(sub);
	*sublen = ((sub.type & 0xC0000) && *(sub.s) == '\0') ? 1 : ft_strlen(sub.s);
	if ((size_t)sub.w > *sublen)
	{
		if ((size_t)sub.j > (size_t)sub.w - *sublen)
			sub.j = sub.w - *sublen;
		if (!(sub.flags & 0x10))
			sub.j = sub.w - sub.j - *sublen;
		if ((sub.type & 0xC0000) && *(sub.s) == '\0')
		{
			sub.s = ft_shift((&sub.s), sub.j, sub.w);
			sub.s[sub.j] = '\0';
		}
		else
			sub.s = ft_shift(&(sub.s), sub.j, sub.w);
		*sublen = sub.w;
	}
	if (sub.flags & 0x8)
		sub.s = addzeros(sub, 0);
	if (sub.type & 0x414)
		ft_strupper(sub.s);
	return (sub.s);
}

char	*clean(char *s, t_sub sub, char **fmt, size_t *slen)
{
	size_t	d;

	if (!s)
	{
		d = ft_strlend(*fmt, '%');
		*slen = d;
		return (ft_strncpy(ft_strnew(d), *fmt, d));
	}
	if (sub.type)
		sub.s = crop(sub, &(sub.len));
	else
		sub.len = 13;
	d = ft_strlend(*fmt, '%');
	s = ft_crop(&s, 0, *slen + sub.len + d);
	s = (char *)ft_memcat(s, sub.s, *slen, sub.len);
	*slen = *slen + sub.len;
	s = ft_memcat(s, *fmt, *slen, d);
	*slen = *slen + d;
	ft_strdel(&(sub.s));
	return (s);
}
