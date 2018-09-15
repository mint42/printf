/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:55:00 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/14 17:43:25 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*precision(t_sub sub)
{
	if (sub.p < 0 || ft_strchr("cCSp", sub.type))
		return (sub.s);
	if (sub.type == 's')
	{
		if (ft_strlen(sub.s) >= (size_t)sub.p)
			sub.s[sub.p] = '\0';
		return (sub.s);
	}
	if (sub.p == 0 && ft_strequ(sub.s, "0"))
		return (ft_shift(&(sub.s), 0, 0));
	if (sub.s[0] != '-' && (size_t)sub.p <= ft_strlen(sub.s))
		return (sub.s);
	if (sub.s[0] == '-' && (size_t)sub.p < ft_strlen(sub.s))
		return (sub.s);
	if (sub.s[0] != '-')
		sub.s = ft_shift(&(sub.s), sub.p - ft_strlen(sub.s), sub.p);
	else
		sub.s = ft_shift(&(sub.s), sub.p - ft_strlen(sub.s) + 1, sub.p + 1);
	sub.s = addzeros(sub, 1);
	return (sub.s);
}

char	*addzeros(t_sub sub, int p)
{
	int		i;

	i = (ft_strchr(sub.flags, ' ') && !p) ? 1 : 0;
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
	else if ((sub.s[i] == '-' || sub.s[i] == '+') && i > 0)
	{
		sub.s[0] = sub.s[i];
		sub.s[i] = '0';
	}
	return (sub.s);
}

char	*addflags(t_sub sub)
{
	if (!ft_strchr(sub.flags, '#') && !ft_strchr(sub.flags, '+') && \
		!ft_strchr(sub.flags, ' '))
		return (sub.s);
	if (ft_strequ(sub.s, "0") && sub.type == 'o')
		return (sub.s);
	sub.s = ft_shift(&(sub.s), 1, ft_strlen(sub.s) + 1);
	if (ft_strchr(sub.flags, '#') || sub.type == 'p')
	{
		if (sub.type == 'x' || sub.type == 'X' || sub.type == 'p')
		{
			sub.s = ft_shift(&(sub.s), 1, ft_strlen(sub.s) + 1);
			sub.s[1] = (sub.type == 'X') ? 'X' : 'x';
		}
		sub.s[0] = '0';
		return (sub.s);
	}
	if (ft_strchr(sub.flags, '+'))
		sub.s[0] = '+';
	return (sub.s);
}

char	*crop(t_sub sub, size_t *sublen)
{
	sub.s = precision(sub);
	sub.s = addflags(sub);
	if (ft_strchr(sub.flags, '-') && (size_t)sub.w > ft_strlen(sub.s))
		sub.s = ft_shift(&(sub.s), 0, sub.w);
	else if ((size_t)sub.w > ft_strlen(sub.s))
		sub.s = ft_shift(&(sub.s), sub.w - ft_strlen(sub.s), sub.w);
	*sublen = (!*(sub.s) && ft_strchr("cC", sub.type)) ? 1 : ft_strlen(sub.s);
	if (ft_strchr(sub.flags, 'n') && sub.w)
		sub.s[(ft_strchr(sub.flags, '-')) ? 0 : sub.w - 1] = '\0';
	if (ft_strchr(sub.flags, '0') && sub.p == -1)
		sub.s = addzeros(sub, 0);
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
	if ((!ft_strequ(sub.s, "%") || *(*fmt + 1) != '%') && sub.type)
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
