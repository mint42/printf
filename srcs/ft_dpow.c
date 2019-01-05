/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dpow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 17:17:04 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/03 19:53:38 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
