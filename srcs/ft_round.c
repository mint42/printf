/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 23:15:40 by rreedy            #+#    #+#             */
/*   Updated: 2018/12/28 00:12:01 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_round(double n)
{
	long	rn;

	if (n >= 0)
	{
		if ((n - (long)n) * 10 > 5)
			rn = (long)n + 1;
		else
			rn = (long)n;
	}
	else
	{
		if ((n - (long)n) * -10 > 5)
			rn = (long)n - 1;
		else
			rn = (long)n;
	}
	return (rn);
}
