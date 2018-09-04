/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:30:34 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/03 21:24:16 by rreedy           ###   ########.fr       */
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
	if (s && !(*sub) && *(*fmt - 1) == 'c')
		*len = *len + 1;
	*len = *len + ft_strlen(sub);
	s = ft_crop(&s, 0, *len);
	s = (char *)ft_memcat(s, sub, *len - ft_strlen(sub), ft_strlen(sub));
	*len = *len + d;
	return (ft_memcat(s, *fmt, *len - d, d));
}

int		ft_printf(const char *fmt, ...)
{
	va_list		ap;
	char		*cur;
	char		*s;
	size_t		len;

	cur = (char *)fmt;
	va_start(ap, fmt);
	len = 0;
	s = clean(0, 0, (char **)&fmt, &len);
	while (cur && *cur)
	{
		if (!(cur = ft_strchr(cur, '%')))
			return (write(1, s, len));
		s = clean(s, parse(cur, ap), &cur, &len);
	}
	va_end(ap);
	return (write(1, s, len));
}
