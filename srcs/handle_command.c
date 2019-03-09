/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 18:34:29 by rreedy            #+#    #+#             */
/*   Updated: 2019/03/08 18:47:31 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		execute_command(int i, char *command)
{
	static void		(*commands_table[TOTAL_COMMANDS + 1])() = {
		cd,
		echo,
		env,
		exit,
		ls,
		pwd,
		setenv,
		unsetenv,
		bad_command,
	};

	commands_table[i](command);
}

void			handle_command(char *input)
{
	int				i;
	static char		*command[TOTAL_COMMANDS + 1] = {
		"cd",
		"echo",
		"env",
		"exit",
		"ls",
		"pwd",
		"setenv",
		"unsetenv",
		0,
	};

	i = 0;
	while (command[i])
	{
		if (ft_strncmp(input, command[i], ft_strlen(command[i])))
			break ;
		++i;
	}
	execute_command(i, input);
}
