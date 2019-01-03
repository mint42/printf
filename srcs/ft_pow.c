/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 17:17:04 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/02 19:43:56 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_pow(int n, int exponent)
{
	long	power;

	power = 1;
	while (exponent)
	{
		power = power * n;
		--exponent;
	}
	return (power);
}
