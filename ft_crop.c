/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_crop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 15:55:00 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/16 18:20:42 by rreedy           ###   ########.fr       */
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

char	*signs(char *s, char *fmt, char type)
{
	char	*signs;

	while (fmt && !ft_isalpha(*fmt))
	{
		if (*fmt == ' ' || *fmt == '+' || *fmt == '#')
			break;
		++fmt;
	}
	if (!ft_strchr("+ #", *fmt))
		return (s);
	if ((*fmt == ' ' || *fmt == '+') && ft_strchr(s, '-'))
		return (s);
	if (*fmt == '#' && (type == 'x' || type == 'X'))
		signs = (type == 'x') ? ft_strdup("0x") : ft_strdup("0X");
	else if (*fmt == '#')
		signs = ft_strdup('0');
	signs = (*fmt == ' ') ? ft_strdup(' ') : ft_strdup('+');
	s = ft_shift(s, ft_strlen(signs) + ft_strlen(s));
	s = ft_strcpy(s, signs);
	return (s);
}

char	*justify(char *s, char *fmt)
{
	int		width;
	int		left;
	char	flag;

	left = 0;
	while (fmt && (!ft_isdigit(*fmt) || *fmt == '0'))
	{
		if (*fmt == '-')
			left = 1;
		++fmt;
	}
	width = ft_atoi(fmt);
	if (width <= ft_strlen(s))
		return (s);
	s = (left) ? ft_stresize(s, 0, width) : ft_shift(s, width);
	if (left && *flag == ' ')
		return (ft_strcat(s, memset(*flag, width - ft_strlen(s))));
	s = ft_strncpy (s, *flag);
}

char	*ft_crop(char *s, char *fmt)
{
	char	*cur;

	cur = to_type(fmt);
	if (*cur == 's')
		s = precision(s, fmt);
	if (ft_strchr("dDioOuUxX", *cur)
		s = signs(s, fmt, *cur); // add #, ' ', or +
	s = justify(s, fmt); // justify with 0 or ' '

}
