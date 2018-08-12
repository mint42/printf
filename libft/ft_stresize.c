/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stresize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mint </var/spool/mail/mint>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 16:02:32 by mint              #+#    #+#             */
/*   Updated: 2018/08/10 18:06:03 by mint             ###   ########.fr       */
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
