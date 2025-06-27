/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:55:59 by donheo            #+#    #+#             */
/*   Updated: 2025/06/27 02:14:24 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_spaces(const char *input)
{
	while (*input)
	{
		if (*input != ' ' && *input != '\t')
			return (0);
		input++;
	}
	return (1);
}

void	is_heredoc_limit_exceeded(const char *input)
{
	int	count;

	count = 0;
	while (*input)
	{
		if (*input == '<' && *(input + 1) == '<')
		{
			count++;
			if (count > 16)
			{
				ft_putendl_fd("maximum here-document count exceeded", STDERR_FILENO);
				arena_free_all(get_info()->arena);
				exit(1);
			}
			input++;
		}
		input++;
	}
}
