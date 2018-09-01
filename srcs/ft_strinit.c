/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 11:54:22 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/21 16:47:31 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strinit(int c, size_t size)
{
	char	*b;
	char	*ptr;

	b = (char *)malloc(size + 1);
	ptr = b;
	while (size-- && ptr)
		*ptr++ = (unsigned char)c;
	*ptr = '\0';
	return (b);
}
