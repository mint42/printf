/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:30:34 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/16 11:01:20 by rreedy           ###   ########.fr       */
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

char	*clean(char *s, char *sub, char **fmt)
{
	int		d;

	d = ft_strlend(*fmt, '%');
	if (!s && !sub)
		return (ft_strncpy(ft_strnew(d), *fmt, d));
	if (s && sub)
		s = ft_stresize(&s, 0, ft_strlen(s) + ft_strlen(sub));
	else if (!s && sub)
		s = ft_strnew(ft_strlen(sub));
	s = ft_strcat(s, sub);
	*fmt = to_type(*fmt) + 1;
	s = ft_stresize(&s, 0, ft_strlen(s) + ft_strlend(*fmt, '%'));
	return (ft_strncat(s, *fmt, ft_strlend(*fmt, '%')));
}

int		ft_printf(const char *fmt, ...)
{
	va_list		ap;
	char		*cur;
	char		*s;

	cur = (char *)fmt;
	va_start(ap, fmt);
	s = clean(0, 0, (char **)&fmt);
	while (cur && *cur)
	{
		if (!(cur = ft_strchr(cur, '%')))
			return (ft_nutstr(s));
		s = clean(s, parse(cur, ap), &cur);
	}
	va_end(ap);
	return (ft_nutstr(s));
}
