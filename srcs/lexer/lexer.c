/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:47:38 by donheo            #+#    #+#             */
/*   Updated: 2025/06/22 16:38:18 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_elements(const char *input)
{
	int	i;
	t_info	*info;

	info = get_info();
	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (input[i] == '<')
			i = tokenize_input(input, i, info);
		else if (input[i] == '>')
			i = tokenize_output(input, i, info);
		else if (input[i] == '|')
			i = tokenize_pipe(i, info);
		else
		{
			if (input[i] != '\0')
				i = tokenize_cmd(input, i, info);
		}
	}
}
