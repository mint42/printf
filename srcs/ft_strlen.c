/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 19:45:51 by rreedy            #+#    #+#             */
/*   Updated: 2018/09/12 16:49:29 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t		ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}
