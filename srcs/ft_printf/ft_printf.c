/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:30:34 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/14 17:55:46 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *fmt, ...)
{
	va_list		ap;
	char		*s;
	t_sub		sub;
	size_t		slen;

	va_start(ap, fmt);
	slen = 0;
	s = clean(0, makesub((char *)fmt, ap, 1), (char **)&fmt, &slen);
	while (fmt && *fmt)
	{
		if (!(fmt = ft_strchr((char *)fmt, '%')))
			break ;
		sub = makesub((char *)fmt, ap, 0);
		printf("sub: |%s|\n", sub.s);
		s = clean(s, sub, (char **)&fmt, &slen);
		printf("s: |%s|\n", s);
	}
	va_end(ap);
	write(1, s, slen);
	ft_strdel(&s);
	return (slen);
}
