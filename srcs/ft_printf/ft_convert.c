/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:35:14 by rreedy            #+#    #+#             */
/*   Updated: 2018/11/21 22:53:16 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
/*
char	*vatostr(const char *s1)
{
	char	*cpy;

	if (s1 == NULL)
		return (ft_strdup("(null)"));
	cpy = ft_strnew(ft_strlen(s1));
	return (cpy ? ft_strcpy(cpy, s1) : 0);
}
*/
/*
int		get_base(char type)
{
	if (type == 'b')
		return (2);
	if (ft_strchr("oO", type))
		return (8);
	if (ft_strchr("xX", type))
		return (16);
	if (ft_strchr("idDuU", type))
		return (10);
	return (0);
}
*/

char	*ft_uitoabase(unsigned long long int n, int base)
{
	unsigned int			i;
	unsigned long long int	pow;
	char					*str;

	i = 1;
	pow = n;
	if (n == 0)
		return (ft_strdup("0"));
	while (pow >= (unsigned long long int)base && ++i)
		pow /= base;
	str = ft_strnew(i);
	while (i-- > 0)
	{
		str[i] = (n % base) + ((base > 10) && (n % base > 9) ? 'a' - 10 : '0');
		n = n / base;
	}
	return (str);
}

char	*ft_itoabase(long long int n, int base)
{
	long long int	pow;
	int				sign;
	int				i;
	char			*str;

	i = 1;
	sign = (base == 10 && n < 0) ? 1 : 0;
	if (n == 0 || n < -9223372036854775807)
		return (n ? ft_strdup("-9223372036854775808") : ft_strdup("0"));
	if (sign)
		++i;
	n = (n < 0) ? n * -1 : n;
	pow = n;
	while (pow >= (long long)base && ++i)
		pow /= base;
	str = ft_strnew(i + sign);
	while (i-- > 0)
	{
		str[i] = (n % base) + ((base > 10) && (n % base > 9) ? 'a' - 10 : '0');
		n = n / base;
	}
	if (sign)
		str[0] = '-';
	return (str);
}

/*
char	*ft_uitoabase(unsigned long long int n, int base)
{
	unsigned int			i;
	unsigned long long int	pow;
	char					*str;
	int						toupper;

	i = 1;
	pow = n;
	toupper = (base > 20 && (base -= 20)) ? 1 : 0;
	if (n == 0)
		return (ft_strdup("0"));
	while (pow >= (unsigned long long int)base && ++i)
		pow /= base;
	str = ft_strnew(i);
	while (i-- > 0)
	{
		str[i] = (n % base) + ((base > 10) && (n % base > 9) ? 'a' - 10 : '0');
		n = n / base;
	}
	return ((toupper) ? ft_strupper(str) : str);
}

char	*ft_itoabase(long long int n, int base)
{
	int				i;
	long long int	pow;
	int				s;
	char			*str;

	i = 1;
	s = (base == 10 && n < 0) ? 1 : 0;
	if (n == 0 || n < -9223372036854775807)
		return (n ? ft_strdup("-9223372036854775808") : ft_strdup("0"));
	if (s)
		++i;
	n = (n < 0) ? n * -1 : n;
	pow = n;
	while (pow >= (long long)base && ++i)
		pow /= base;
	str = ft_strnew(i + s);
	while (i-- > 0)
	{
		str[i] = (n % base) + ((base > 10) && (n % base > 9) ? 'a' - 10 : '0');
		n = n / base;
	}
	if (s)
		str[0] = '-';
	return (str);
}
*/
