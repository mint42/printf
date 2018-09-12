/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:30:34 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/12 15:17:23 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*to_type(char *fmt)
{
	++fmt;
	while (!ft_isalpha(*fmt) && *fmt != '%')
		++fmt;
	if (*fmt == 'l' || *fmt == 'h' || *fmt == 'j' || *fmt == 'z')
		++fmt;
	if (*fmt == 'l' || *fmt == 'h')
		++fmt;
	return (fmt);
}

char	*clean(char *s, char *sub, char **fmt, size_t *slen)
{
	size_t	d;
	size_t	sublen;

	sublen = (ft_strequ(sub, "%")) ? 1 : 0;
	d = ft_strlend(*fmt, '%');
	if (!s && !sub)
	{
		*slen = d;
		return (ft_strncpy(ft_strnew(d), *fmt, d));
	}
	if (!ft_strequ(sub, "%") || *(*fmt + 1) != '%')
		sub = crop(sub, *fmt, &sublen);
	*fmt = to_type(*fmt) + 1;
	d = ft_strlend(*fmt, '%');
	s = ft_crop(&s, 0, *slen + sublen + d);
	s = (char *)ft_memcat(s, sub, *slen, sublen);
	*slen = *slen + sublen;
	s = ft_memcat(s, *fmt, *slen, d);
	*slen = *slen + d;
	ft_strdel(&sub);
	return (s);
}

int		ft_printf(const char *fmt, ...)
{
	va_list		ap;
	char		*s;
	char		*sub;
	size_t		slen;

	va_start(ap, fmt);
	slen = 0;
	s = clean(0, 0, (char **)&fmt, &slen);
	while (fmt && *fmt)
	{
		if (!(fmt = ft_strchr((char *)fmt, '%')))
			break ;
		sub = parse((char *)fmt, ap);
		s = clean(s, sub, (char **)&fmt, &slen);
	}
	va_end(ap);
	write(1, s, slen);
	ft_strdel(&s);
	return (slen);
}
