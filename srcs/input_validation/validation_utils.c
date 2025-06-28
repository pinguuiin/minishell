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

// check if all quotes are properly closed
int	validate_quotes(const char *input)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (input[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (!in_single && !in_double);
}

