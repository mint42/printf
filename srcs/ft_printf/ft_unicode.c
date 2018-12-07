/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 17:52:10 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/06 23:09:51 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** This function returns the amount of bytes that will be needed to hold a wide
** a wide character string when converted to utf_8
*/


int			get_bytes(wchar_t c)
{
	int		bytes;
	int		i;

	11011111 10111111

	1111 1111  1111 1111  1111 1111  1111 1111
	0000 0000  0000 0000  0000 1111  1111 1111

	2;

	11 bits

	11 / 6 = 1 R 5

	13 / 6 = 2 R 1


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

bits / 6 + 1 = 


	 7 / 6 = 1 R 1

	bytes = 1;
	
	10111111 1011000

	
	
	
	i = 32;
	while (i > 0 && (*str ^ (1 << (i - 1))))
		--i;
	bytes = (i > 7) ? (i / 6) : 1;
	if (i > 7)
		bytes = bytes + ((bytes + (i % 6) > 7) ? 2 : 1);
	return (bytes);
}



int			get_utf8_bytes(wchar_t *str)
{
	int	i;
	int	bytes;
	int	leftover;
	int	total;

	total = 0;
	while (str && *str)
	{
		i = 32;
		while (i > 0)
		{
			if (*str & (1 << (i - 1)))
				break ;
			--i;
		}
		bytes = ((i > 7) ? (i / 6) : 1);
		leftover = (i > 7) ? (i % 6) : 0;
		if (leftover)
			++bytes;
		if (leftover + (bytes + 1) > 8)
			++bytes;
		total += bytes;
		++str;
	}
	return (total);
}

/*
** This function returns a character with i bytes turned on at the start
*/

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

/*
** This function increments a utf_8 string by one (or more) bytes to the next
** aligned character
*/

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

char		*conv_utf8(wchar_t *s)
{
	char	*str;
	int		i;

	str = (s) ? ft_strnew(get_utf8_bytes(s)) : 0;
	if (!s || !str)
		return ((!s) ? ft_strdup("(null)") : 0);
	while (s && *s)
	{
		i = 32;
		while (i > 0 && (*str ^ (1 << i - 1)))	
			--i;
		ft_strcat(str, ((i > 7) ? conv_utf8_char(*s) : s));
		++s;
	}
	return (str);
}
