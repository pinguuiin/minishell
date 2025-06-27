/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:20:17 by donheo            #+#    #+#             */
/*   Updated: 2025/06/27 02:05:49 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// check if a valid token follows a redirection or pipe operator
static int	validate_after_operator(const char *input)
{
	const char	*first_operator;

	first_operator = input;
	input++;
	if (*first_operator == *input)
		input++;
	while (*input == ' ' || *input == '\t')
		input++;
	if (*input == '|' || *input == '<' || *input == '>' || *input == '\0')
		return (0);
	return (1);
}

// validates redirection operators and their syntax outside of quotes
int	validate_redirections(const char *input)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (*input)
	{
		if (*input == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*input == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote \
				&& (*input == '>' || *input == '<'))
			if (!validate_after_operator(input))
				return (0);
		input++;
	}
	return (1);
}

// validate correct use and placement of pipe operators outside of quotes
int	validate_operations(const char *input, \
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
	if (is_only_spaces(input))
		return (1);
	if (!validate_quotes(input))
	{
		ft_putstr_fd("unclosed quote\n", STDERR_FILENO);
		return (0);
	}
	if (!validate_redirections(input))
	{
		ft_putstr_fd("invalid redirection\n", STDERR_FILENO);
		return (0);
	}
	if (!validate_operations(input, 1, 0, 0))
	{
		ft_putstr_fd("invalid operator\n", STDERR_FILENO);
		return (0);
	}
	is_heredoc_limit_exceeded(input);
	return (1);
}
