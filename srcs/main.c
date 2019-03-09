/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:29:10 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/08 18:49:18 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_prompt()
{
	//dont forget to fix directory for root folders
	time_t	tim;

	tim = time(NULL);
	ft_printf("\e[1;31m\342\224\214");
	ft_printf("(\e[0;31m%s\e[1;31m)\342\224\200", "rreedy");
	ft_printf("(\e[0;32m~%s\e[1;31m)\342\224\200", getcwd(NULL, 0) + 18);
	ft_printf("(\e[0;33m%.5s\e[1;31m)\n\342\224\224", ctime(&tim) + 11);
	ft_printf("(\e[0;35mπ\e[1;31m)\e[m ");
}

int			main()
{
	char	*input;

	while (42)
	{
		print_prompt();
		if ((get_next_char(2, ';', &input)) == 1)
		{
			handle_command(input);
			ft_memdel(&input);
		}
	}
	return (0);
}
