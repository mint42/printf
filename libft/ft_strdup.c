/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 13:16:10 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/22 20:43:52 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;

	if (s1 == NULL)
		return (ft_strdup("(null)"));
	cpy = ft_strnew(ft_strlen(s1));
	return (cpy ? ft_strcpy(cpy, s1) : 0);
}
