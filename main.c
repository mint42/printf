/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 14:31:48 by rreedy            #+#    #+#             */
/*   Updated: 2018/08/12 15:57:56 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		main()
{
	unsigned long int longboi= 3688522574;

	ft_printf("FT_PRINTF:\nunsigned long int: %lu\n\n", longboi);
	printf("PRINTF:\nunsigned long int: %lu\n\n", longboi);
	return (0);
}

/******************************************************************************
//
//		di             ouUxX                   c           s             p
//
//	no	int            unsigned int            int         char*         void*
//  hh	char           unsigned char
//  h	short int      unsigned short int
//  l	long int       unsigned long int       wint_t      wint_t*
//  ll	long long int  unsigned long long int
//  j	intmax_t       uintmax_t
//  z	size_t         size_t
//
****************************************************************************/


