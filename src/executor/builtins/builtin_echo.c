/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:53:34 by piyu              #+#    #+#             */
/*   Updated: 2025/07/06 00:32:18 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_flag(char *s)
{
	int	i;

	i = 1;
	if (!s || s[0] != '-')
		return (false);
	while (s[i] == 'n')
		i++;
	if (i == 1 || s[i])
		return (false);
	return (true);
}

int	echo(char **argv)
{
	int		i;
	bool	newline;

	i = 1;
	newline = 1;
	if (is_n_flag(argv[1]))
		newline = 0;
	while (is_n_flag(argv[i]))
		i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
