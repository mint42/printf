/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:52:10 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/07 22:16:03 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** This function returns the amount of bytes that will be needed to hold a wide
** a wide character string when converted to utf_8
*/


/*
	11011111 10111111

	1111 1111  1111 1111  1111 1111  1111 1111
	0000 0000  0000 0000  0000 1111  1111 1111

	2;

	11 bits

	11 / 6 = 1 R 5

	13 / 6 = 2 R 1


bits / 5 = 

	00000011 11000000
	11001111 10000000

08	11011111 10111000
09	11011111 10111100
10	11011111 10111110
11	11011111 10111111

12  11101111 10111111 10110000
13	11101111 10111111 10111000
14	11101111 10111111 10111100
15	11101111 10111111 10111110
16	11101111 10111111 10111111

17	11110111 10111111 10111111 10110000
18	11110111 10111111 10111111 10111000
19	11110111 10111111 10111111 10111100
20	11110111 10111111 10111111 10111110
21	11110111 10111111 10111111 10111111

22	11111011 10111111 10111111 10111111 10110000
23
24
25
26	11111011 10111111 10111111 10111111 10111111

27	11111101 10111111 10111111 10111111 10111111 10110000
28
29
30
31	11111101 10111111 10111111 10111111 10111111 10111111

32	11111110 10111111 10111111 10111111 10111111 10111111 10110000


(bits + 3) / 5
*/

/*
** This function returns a character with i bytes turned on at the start
*/


/*
static char	utf8_dummy(int i)
{
	char	c;

	c = 0;
	while (i > 0)
	{
		c |= (0x80 >> (i - 1));
		--i;
	}
	return (c);
}
*/

/*
** THIS IS A HELPER FUNCITON FOR conv_utf8
** IT ASSUMES THE FOLLOWING:
**		cur has enough space for the converted wide char c
**		i is the index of the highest bit in the wide char c
** IT THEN DOES:
**		c gets converted to utf8, and placed inside cur
**		cur does not get moved
**		you should call utf8_inc(&cur) outside the function
**			to move to the next character
*/

/*
static void	conv_utf8_char(char **cur, wchar_t c, int i)
{
	int	x;
	int	bytes;
	int	leftover;

	bytes = ((i > 7) ? (i / 6) : 1);
	leftover = ((i > 7) ? i % 6 : 0);
	if (leftover)
		++bytes;
	if (leftover + (bytes + 1) > 8)
		++bytes;
	x = 0;
	**cur = utf8_dummy(bytes);
	*(*cur + (bytes - 1)) = utf8_dummy(1);
	while (x < i)
	{
		*(*cur + (bytes - 1)) |= (c & (1 << x)) >> (6 * (x / 6));
		++x;
		if (!(x % 6))
		{
			--bytes;
			if (bytes > 1)
				*(*cur + (bytes - 1)) = utf8_dummy(1);
		}
	}
}
*/

/*
** This function increments a utf_8 string by one (or more) bytes to the next
** aligned character
*/

/*
void		utf8_inc(char **str)
{
	if (str)
	{
		if (**str & 0x80)
			while (**str & 0x80)
				++(*str);
		else
			++(*str);
	}
}

char	*conv_utf8_c(wchar_t c)
{
	char	*nstr;
	int		i;

	nstr = ft_strnew(get_utf8_bytes(&c));
	i = 32;
	while (i > 0)
	{
		if (c & (1 << (i - 1)))
			break ;
		--i;
	}
	if (i > 7)
		conv_utf8_char(&nstr, c, i);
	else
		*nstr = c;
	return (nstr);
}
*/

int		get_bytes(wchar_t wc)
{
	int		i;

	i = 32;
	while (i > 0 && (1 ^ (wc >> (i - 1)))) 
		--i;
	return ((i > 7) ? ((i + 3) / 5) : 1);
}

char		*conv_utf8_char(wchar_t wc, char *s)
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

char		*conv_utf8_str(wchar_t *ws, char *s)
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
