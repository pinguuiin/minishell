/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:20:17 by donheo            #+#    #+#             */
/*   Updated: 2025/06/30 09:51:57 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_heredoc_limit_exceeded(const char *input)
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

// check if a valid token follows a redirection or pipe operator
static int	has_valid_token_after_operator(const char *input)
{
	if ((input[0] == '<' && input[1] == '<') || (input[0] == '>' && input[1] == '>'))
		input += 2;
	else
		input += 1;
	while (*input == ' ' || *input == '\t')
		input++;
	if (*input == '|' || *input == '<' || *input == '>' || *input == '\0')
		return (0);
	return (1);
}

// validates redirection operators and their syntax outside of quotes
static int	validate_redirections(const char *input)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (*input)
	{
		update_quote_state(*input, &in_single_quote, &in_double_quote);
		if (!in_single_quote && !in_double_quote \
				&& (*input == '>' || *input == '<'))
			if (!has_valid_token_after_operator(input))
				return (0);
		input++;
	}
	return (1);
}

// validate correct use and placement of pipe operators outside of quotes
static int	validate_pipe_syntax(const char *input, \
	int expect_command, int in_single_quote, int in_double_quote)
{
	while (*input)
	{
		if (*input == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			expect_command = 0;
		}
		else if (*input == '"' && !in_single_quote)
		{
			expect_command = 0;
			in_double_quote = !in_double_quote;
		}
		else if (*input == '|' && !in_single_quote && !in_double_quote)
		{
			if (expect_command)
				return (0);
			expect_command = 1;
		}
		else if (*input != ' ' && *input != '\t')
			expect_command = 0;
		input++;
	}
	if (expect_command)
		return (0);
	return (1);
}

// runs all syntax validation checks
int	check_syntax_error(const char *input)
{
	if (is_all_whitespace(input))
		return (1);
	if (!has_balanced_quotes(input))
	{
		ft_putstr_fd("unclosed quote\n", STDERR_FILENO);
		return (0);
	}
	if (!validate_redirections(input))
	{
		ft_putstr_fd("invalid redirection\n", STDERR_FILENO);
		return (0);
	}
	if (!validate_pipe_syntax(input, 1, 0, 0))
	{
		ft_putstr_fd("invalid operator\n", STDERR_FILENO);
		return (0);
	}
	is_heredoc_limit_exceeded(input);
	return (1);
}
