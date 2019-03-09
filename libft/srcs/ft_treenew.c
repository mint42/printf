/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 12:51:42 by rreedy            #+#    #+#             */
/*   Updated: 2019/01/29 12:51:49 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_binarytree	*ft_treenew(void *content)
{
	t_binarytree	*node;

	node = (t_binarytree *)malloc(sizeof(t_binarytree));
	node->content = content;
	node->left = 0;
	node->right = 0;
	return (node);
}
