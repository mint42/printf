/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:35:14 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/12 14:41:20 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


char	*getstr(const char *s1)
{
	char	*cpy;

	if (s1 == NULL)
		return (ft_strdup("(null)"));
	cpy = ft_strnew(ft_strlen(s1));
	return (cpy ? ft_strcpy(cpy, s1) : 0);
}

char	*ft_uitoabase(t_ull n, int base)
{
	unsigned int	i;
	t_ull			pow;
	char			*str;
	int				toupper;

	i = 1;
	pow = n;
	toupper = (base > 20 && (base -= 20)) ? 1 : 0;
	if (n == 0)
		return (ft_strdup("0"));
	while (pow >= (t_ull)base && ++i)
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

char	*ft_ptoa(uintptr_t p)
{
	int		i;
	char	*s;
	char	*cur;

	if (!p)
		return (ft_strdup("0x0"));
	i = (sizeof(p) << 3) - 4;
	while (((p >> i) & 0xF) == 0)
		i -= 4;
	s = ft_strnew((i / 4) + 3);
	cur = s;
	if (cur)
	{
		*cur++ = '0';
		*cur++ = 'x';
		while (i >= 0)
		{
			if (((p >> i) & 0xF) >= 10)
				*cur++ = (((p >> i) & 0xF) + 'a' - 10);
			else
				*cur++ = (((p >> i) & 0xF) + '0');
			i -= 4;
		}
	}
	return (s);
}
