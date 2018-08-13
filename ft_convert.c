/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:35:14 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/12 16:26:21 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_uitoabase(t_ull n, int base)
{
	unsigned int	i;
	t_ull			pow;
	char			*str;
	int				toupper;

	i = 0;
	pow = 1;
	toupper = (base > 20 && (base -= 20)) ? 1 : 0;
	while (pow - 1 < n && ++i)
		pow = pow * base;
	str = ft_strnew(i);
	while (i-- > 0)
	{
		str[i] = (n % base) + ((base > 10) && (n % base > 9) ? 'A' - 10 : '0');
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

	i = 0;
	pow = 1;
	s = (base == 10 && n < 0) ? 1 : 0;
	if (s)
		++i;
	n = (n < 0) ? n * -1 : n;
	while (pow - 1 < n && ++i)
		pow = pow * base;
	str = ft_strnew(i + s);
	while (i-- > 0)
	{
		str[i] = (n % base) + ((base > 10) && (n % base > 9) ? 'A' - 10 : '0');
		n = n / base;
	}
	if (s)
		str[0] = '-';
	return (str);
}