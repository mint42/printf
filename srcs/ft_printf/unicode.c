#include "ft_printf.h"

/*
** This function returns the amount of bytes that will be needed to hold a wide
** a wide character string when converted to utf_8
*/
int		get_utf8_bytes(wchar_t *str)
{
	int	i;
	int	bytes;
	int	leftover;
	int	total;

	total = 0;
	while (*str)
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
void	utf8_inc(char **str)
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

char	*conv_utf8(wchar_t *str)
{
	char	*nstr;
	char	*cur;
	int		i;

	nstr = ft_strnew(get_utf8_bytes(str));
	cur = nstr;
	if (nstr)
		while (*str)
		{
			i = 32;
			while (i > 0)
			{
				if (*str & (1 << (i - 1)))
					break ;
				--i;
			}
			if (i > 7)
				conv_utf8_char(&cur, *str, i);
			else
				*cur = (char)*str;
			utf8_inc(&cur);
			++str;
		}
	return (nstr);
}

/*
str = conv_utf8(L"t\u2135esti\U0001f47ding o\vne tw\u03c0o\n");
*/
