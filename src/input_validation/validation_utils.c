/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:55:59 by donheo            #+#    #+#             */
/*   Updated: 2025/07/02 22:00:54 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_whitespace(const char *input)
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
int	has_balanced_quotes(const char *input)
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

void	update_quote_state(const char c, \
int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

void	print_syntax_error(char error_char, t_info *info)
{
	char	error_message[4];

	if (!error_char)
		info->exit_code = error_msg("minishell", \
"syntax error near unexpected token ", "`newline'", 2);
	else
	{
		error_message[0] = '`';
		error_message[1] = error_char;
		error_message[2] = '\'';
		error_message[3] = '\0';
		info->exit_code = error_msg("minishell", \
"syntax error near unexpected token ", error_message, 2);
	}
}
