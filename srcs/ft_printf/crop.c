/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:22:01 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/11 16:48:50 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*precision(t_sub sub)
{
	int		i;

	i = 0;
	if (sub.type & 0x30000)
	{
		while(sub.s[i] != '\0' && sub.p)
		{
			++i;
			while (sub.s[i] && (sub.s[i] & 0xC0) == 0x80)
				++i;
			--sub.p;
		}
		sub.s[i] = '\0';
		return (sub.s);
	}
	if (sub.s[0] != '-' && (size_t)sub.p > ft_strlen(sub.s))
		sub.s = ft_shift(&(sub.s), sub.p - ft_strlen(sub.s), sub.p);
	else if (sub.s[0] == '-' && (size_t)sub.p >= ft_strlen(sub.s))
		sub.s = ft_shift(&(sub.s), sub.p - ft_strlen(sub.s) + 1, sub.p + 1);
	sub.s = zeros(sub, 1);
	return (sub.s);
}

char	*flags(t_sub sub)
{
	if (sub.base == 2 || sub.base == 16 || (sub.type & 0xC))
		sub.s = ft_shift(&(sub.s), 2, ft_strlen(sub.s) + 2);
	else
		sub.s = ft_shift(&(sub.s), 1, ft_strlen(sub.s) + 1);
	if ((sub.flags & 0x1) || (sub.type & 0xC))
	{
		if (sub.base == 2 || sub.base == 16 || (sub.type & 0xC))
			sub.s[1] = (sub.base == 2) ? 'b' : 'x';
		sub.s[0] = '0';
		return (sub.s);
	}
	if (sub.flags & 0x4)
		sub.s[0] = '+';
	return (sub.s);
}

char	*width(t_sub sub, size_t *sublen)
{
	int		i;

	i = 0;
	if (sub.type & 0x50000)
		while (sub.s[i] && ++i)
			while (sub.s[i] && (sub.s[i] & 0xC0) == 0x80 && ++i)
				++sub.w;
	if ((size_t)sub.j > (size_t)sub.w - *sublen)
		sub.j = sub.w - *sublen;
	if (!(sub.flags & 0x30))
		sub.j = sub.w - sub.j - *sublen;
	else if ((sub.flags & 0x30) == 0x30)
		sub.j = (sub.w - *sublen) / 2;
	else if (sub.flags & 0x20)
		sub.j = ((sub.w - *sublen) / 2) + (((sub.w - *sublen) % 2) ? 1 : 0);
	if ((sub.type & 0xC0000) && *(sub.s) == '\0')
	{
		sub.s = ft_shift((&sub.s), sub.j, sub.w);
		sub.s[sub.j] = '\0';
	}
	else
		sub.s = ft_shift(&(sub.s), sub.j, sub.w);
	*sublen = sub.w;
	return (sub.s);
}

char	*zeros(t_sub sub, int p)
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

char	*crop(t_sub sub, size_t *sublen)
{
	if (sub.p >= 0)
		sub.s = precision(sub);
	if ((sub.flags & 0x7) || (sub.type & 0xC))
		sub.s = flags(sub);
	*sublen = ((sub.type & 0xC0000) && *(sub.s) == '\0') ? 1 : ft_strlen(sub.s);
	if ((size_t)sub.w > *sublen)
		sub.s = width(sub, sublen);
	if (sub.flags & 0x8)
		sub.s = zeros(sub, 0);
	if (sub.type & 0x414)
		ft_strupper(sub.s);
	return (sub.s);
}
