/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 11:54:22 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/19 12:36:26 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strinit(int c, size_t size)
{
/*	char	*str;
	char	*cur;

	str = (char *)ft_memsec(malloc(size), c, size);
	cur = str;
	while (cur && *cur)
		cur++;
	*cur = '\0';
	printf("str in init: \"%s\"\n", str);	
	printf("strlen: %zi\n", ft_strlen(str));	
	return (str);
*/
	char	*b;
	char	*ptr;

	b = (char *)malloc(size + 1);
	ptr = b;
	while (size-- && ptr)
		*ptr++ = (unsigned char)c;
	*ptr = '\0';
	return (b);
}
