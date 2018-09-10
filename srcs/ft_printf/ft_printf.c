/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:30:34 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/09 17:30:13 by abarnett         ###   ########.fr       */
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

char	*clean(char *s, char *sub, char **fmt, size_t *len)
{
	int		d;

	d = ft_strlend(*fmt, '%');
	if (!s && !sub)
	{
		*len = d;
		return (ft_strncpy(ft_strnew(d), *fmt, d));
	}
	*fmt = to_type(*fmt) + 1;
	d = ft_strlend(*fmt, '%');
	if (s && (*sub) == '\0' && *(*fmt - 1) == 'c')
		*len = *len + 1;
	*len = *len + ft_strlen(sub);
	s = ft_crop(&s, 0, *len + d);
	s = (char *)ft_memcat(s, sub, *len - ft_strlen(sub), ft_strlen(sub));
	*len = *len + d;
	return (ft_memcat(s, *fmt, *len - d, d));
}

int		ft_printf(const char *fmt, ...)
{
	va_list		ap;
	char		*s;
	size_t		len;

	va_start(ap, fmt);
	len = 0;
	s = clean(0, 0, (char **)&fmt, &len);
	while (fmt && *fmt)
	{
		if (!(fmt = ft_strchr((char *)fmt, '%')))
			break ;
		s = clean(s, parse((char *)fmt, ap), (char **)&fmt, &len);
	}
	va_end(ap);
	write(1, s, len);
	ft_strdel(&s);
	return (len);
}
