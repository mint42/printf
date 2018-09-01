/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:14:59 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/16 09:15:19 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupper(char *s)
{
	char	*cur;

	cur = s;
	while (cur && *cur)
	{
		if (ft_islower(*cur))
			*cur = ft_toupper(*cur);
		++cur;
	}
	return (s);
}
