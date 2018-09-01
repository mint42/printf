/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 18:49:39 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/30 15:32:21 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memcat(void *dst, const void *src, int i, size_t size)
{
	unsigned char	*cur;
	unsigned char	*cur2;

	cur = (unsigned char *)dst + size;
	cur2 = (unsigned char *)src;
	while (i--)
		*cur++ = *cur2++;
	return (dst);
}
