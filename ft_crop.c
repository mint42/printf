/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:55:00 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/17 21:18:18 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*precision(char *s, char *fmt)
{
	int		i;

	while (fmt && !ft_isalpha(*fmt) && *fmt != '.')
		++fmt;
	if (!fmt)
		return (s);
	i = ft_atoi(fmt);
	while (i--)
		++s;
	*s = '\0';
	return (s);
}


char	*shift(char **s, int in, size_t size)
{
	char	*str;

	str = ft_strnew(len);
	if (!str)
		return (0);
	strcpy(str + in, *s, size);
	ft_strdel(s);
	return (str);
}

	char	*signs;

	if (*fmt == '#' && (type == 'x' || type == 'X'))
		signs = (type == 'x') ? ft_strdup("0x") : ft_strdup("0X");
	else if (*fmt == '#')
		signs = ft_strdup('0');




char	*fill_flags(char *fmt)
{
	char	*flags;

	flags = ft_strnew(5);
	while (fmt && !ft_isalpha(*fmt))
	{
		++fmt;
		while (!ft_isalpha(*fmt) && ft_strchr("0# +-", *fmt))
			*flags++ = *fmt++;
	}
	return (flags);
}

char	*crop(char *s, char *fmt)
{
	char	*cur;
	char	*flags;
	int		width;

	cur = to_type(fmt);
	flags = fill_flags(fmt);
	if (*cur == 's')
		s = precision(s, fmt);
	if (ft_strchr(flags, '#'))
		s = hashtag(s, *(to_type(fmt)));

	+ - width ' ' 0 

	if (width <= ft_strlen(s))
		return (s);
	if (!flags)
		return (s);
	s = left ? ft_stresize(s, 0, width) : ft_shift(s, width - ft_strlen(s), width);
	
	if (!ft_strchr(flags, '-') && ft_strchr(flags, '0'))


	if (ft_strchr(flags, '+') || ft_strchr(flags, ' '))
		not be negative number


	if (left && *flag == ' ')
		return (ft_strcat(s, memset(*flag, width - ft_strlen(s))));
	s = ft_strncpy (s, *flag);
}
