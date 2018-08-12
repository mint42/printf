/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mint </var/spool/mail/mint>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 15:44:42 by mint              #+#    #+#             */
/*   Updated: 2018/08/10 15:55:13 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char 	*ft_strupper(char *s)
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
