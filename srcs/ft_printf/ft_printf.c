/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:30:34 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/10 18:32:41 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int		ft_printf(const char *fmt, ...)
{
	va_list		ap;
	char		*s;
	t_sub		sub;
	size_t		slen;

	va_start(ap, fmt);
	slen = 0;
	s = clean(0, makesub((char **)&fmt, ap, 1), (char **)&fmt, &slen);
	while (fmt && *fmt)
	{
		if (!(fmt = ft_strchr((char *)fmt, '%')))
			break ;
		sub = makesub((char **)&fmt, ap, 0);
		s = clean(s, sub, (char **)&fmt, &slen);
	}
	va_end(ap);
	write(1, s, slen);
	ft_strdel(&s);
	return (slen);
}

int		ft_sprintf(char **s, const char *fmt, ...)
{
	va_list		ap;
	t_sub		sub;
	size_t		slen;

	va_start(ap, fmt);
	slen = 0;
	*s = clean(0, makesub((char **)&fmt, ap, 1), (char **)&fmt, &slen);
	while (fmt && *fmt)
	{
		if (!(fmt = ft_strchr((char *)fmt, '%')))
			break ;
		sub = makesub((char **)&fmt, ap, 0);
		*s = clean(*s, sub, (char **)&fmt, &slen);
	}
	va_end(ap);
	return (slen);
}

int		ft_printfd(int fd, const char *fmt, ...)
{
	va_list		ap;
	char		*s;
	t_sub		sub;
	size_t		slen;

	va_start(ap, fmt);
	slen = 0;
	s = clean(0, makesub((char **)&fmt, ap, 1), (char **)&fmt, &slen);
	while (fmt && *fmt)
	{
		if (!(fmt = ft_strchr((char *)fmt, '%')))
			break ;
		sub = makesub((char **)&fmt, ap, 0);
		s = clean(s, sub, (char **)&fmt, &slen);
	}
	va_end(ap);
	write(fd, s, slen);
	ft_strdel(&s);
	return (slen);
}
