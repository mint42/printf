/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mint </var/spool/mail/mint>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 15:53:37 by mint              #+#    #+#             */
/*   Updated: 2018/08/10 15:56:26 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char 	*ft_strlower(char *s)
{
	char	*cur;

	cur = s;
	while (cur && *cur)
	{
		if (ft_isupper(*cur))
			*cur = ft_tolower(*cur);
		++cur; 
	}
	return (s);
}
