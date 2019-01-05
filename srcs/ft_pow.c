/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 17:17:04 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/03 19:53:38 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_pow(int n, int exponent)
{
	long	power;

	power = 1;
	while (exponent > 0)
	{
		power = power * n;
		--exponent;
	}
	return (power);
}

double	ft_dpow(int n, int exponent)
{
	double	power;

	power = 1;
	while (exponent > 0)
	{
		power = power * n;
		--exponent;
	}
	return (power);
}
