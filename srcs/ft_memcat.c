/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 18:49:39 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/03 21:25:51 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcat(void *dst, const void *src, size_t dstlen, size_t srclen)
{
	unsigned char	*cur;
	unsigned char	*cur2;

	cur = (unsigned char *)dst + dstlen;
	cur2 = (unsigned char *)src;
	while (srclen--)
		*cur++ = *cur2++;
	return (dst);
}
