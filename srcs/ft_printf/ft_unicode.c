/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:52:10 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/07 22:37:40 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	08	11011111 10111000
**	09	11011111 10111100
**	10	11011111 10111110
**	11	11011111 10111111
**
**	12  11101111 10111111 10110000
**	13	11101111 10111111 10111000
**	14	11101111 10111111 10111100
**	15	11101111 10111111 10111110
**	16	11101111 10111111 10111111
**
**	17	11110111 10111111 10111111 10110000
**	18	11110111 10111111 10111111 10111000
**	19	11110111 10111111 10111111 10111100
**	20	11110111 10111111 10111111 10111110
**	21	11110111 10111111 10111111 10111111
**
**	bytes = (bits + 3) / 5
*/

int		get_bytes(wchar_t wc)
{
	int		i;

	i = 32;
	while (i > 0 && (1 ^ (wc >> (i - 1))))
		--i;
	return ((i > 7) ? ((i + 3) / 5) : 1);
}

char	*conv_utf8_char(wchar_t wc, char *s)
{
	char	*cur;
	int		bytes;

	bytes = get_bytes(wc);
	if (!s && wc)
		s = ft_strnew(bytes);
	if (!wc || !s)
		return (s = ((!wc) ? ft_ctoa(0) : 0));
	cur = s + bytes - 1;
	if (bytes > 1)
		while (cur >= s)
		{
			*cur = *cur | (!(cur - s) ? (0xFF << (8 - bytes)) : 0x80);
			*cur = *cur | (wc & 0x3F);
			wc = wc >> 6;
			cur = (cur - s) ? (cur - 1) : 0;
		}
	else
		*cur = (char)wc;
	return (s);
}

char	*conv_utf8_str(wchar_t *ws, char *s)
{
	int		bytes;
	int		totalbytes;

	totalbytes = 0;
	if (!ws)
		return (ft_strdup("(null)"));
	while (ws && *ws)
		totalbytes = totalbytes + get_bytes(*ws++);
	s = ft_strnew(totalbytes);
	s = s + totalbytes;
	while (totalbytes)
	{
		--ws;
		bytes = get_bytes(*ws);
		totalbytes = totalbytes - bytes;
		s = s - bytes;
		s = conv_utf8_char(*ws, s);
	}
	return (s);
}
