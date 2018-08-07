/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoabase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mint </var/spool/mail/mint>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 19:56:51 by mint              #+#    #+#             */
/*   Updated: 2018/08/06 19:59:42 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

char	*ft_itoabase(long long int value, int base)
{
	char	*str;
	int		sign;
	int		i;
	int		pow;

	i = 0;
	pow = 1;
	sign = (base == 10 && value < 0) ? 1 : 0;
	value = (value < 0) ? value * -1 : value;
	while (pow - 1 < value && ++i)
		pow = pow * base;
	str = (char *)malloc((size_t)(i + 1));
	str[i] = '\0';
	while (i-- > 0)
	{
		str[i + sign] = (value % base) + (value % base > 9 ? 'A' - 10 : 'O');
		value = value / base;
	}
	if (sign)
		str[0] = '-';
	return (str);
}

int		main(int argc, char **argv)
{
	(void)argc;
	printf("\n\n%s\n", ft_itoabase(atoi(argv[1]), atoi(argv[2])));
	return (0);
}
