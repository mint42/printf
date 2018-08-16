/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stresize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 09:12:59 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/16 09:13:02 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stresize(char **s, int in, int size)
{
	char	*str;

	str = ft_strnew(size);
	if (!str)
		return (0);
	ft_strncpy(str, *s + in, size);
	ft_strdel(s);
	return (str);
}
