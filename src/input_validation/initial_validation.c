/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:20:17 by donheo            #+#    #+#             */
/*   Updated: 2025/07/10 07:45:56 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_heredoc_limit_exceeded(const char *input)
{
	int		count;

	count = 0;
	while (*input)
	{
		if (*input == '<' && *(input + 1) == '<')
		{
			count++;
			if (count > 16)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putendl_fd("maximum here-document count exceeded", \
STDERR_FILENO);
				arena_free_all();
				exit(2);
			}
			input++;
		}
		input++;
	}
}

// check if a valid token follows a redirection or pipe operator
static char	*has_valid_token_after_io(char *input)
{
	if ((input[0] == '<' && input[1] == '<') || \
(input[0] == '>' && input[1] == '>'))
		input += 2;
	else
		input += 1;
	while (*input == ' ' || *input == '\t')
		input++;
	if (*input == '|' || *input == '<' || *input == '>' || *input == '\0')
		return (input);
	return (NULL);
}

static char	*has_valid_token_after_pipe(char *input)
{
	input++;
	while (*input == ' ' || *input == '\t')
		input++;
	if (*input == '|' || *input == '\0')
		return (input);
	return (NULL);
}

// validates redirection operators and their syntax outside of quotes
static char	*validate_operators(char *input, int in_single_quote, \
int in_double_quote)
{
	char	*error_char;

	while (*input == ' ' || *input == '\t')
		input++;
	if (*input == '|')
		return (input);
	error_char = NULL;
	while (*input)
	{
		update_quote_state(*input, &in_single_quote, &in_double_quote);
		if (!in_single_quote && !in_double_quote \
&& (*input == '>' || *input == '<'))
			error_char = has_valid_token_after_io(input);
		else if (!in_single_quote && !in_double_quote && (*input == '|'))
			error_char = has_valid_token_after_pipe(input);
		if (error_char)
			return (error_char);
		input++;
	}
	return (NULL);
}

// runs all syntax validation checks
int	has_syntax_error(char *input, t_info *info)
{
	char	*error_char;

	if (!has_balanced_quotes(input))
	{
		info->exit_code = error_msg("minishell", \
"syntax error", "unclosed quote", 2);
		return (1);
	}
	error_char = validate_operators(input, 0, 0);
	if (error_char)
	{
		print_syntax_error(*error_char, info);
		return (1);
	}
	is_heredoc_limit_exceeded(input);
	return (0);
}
