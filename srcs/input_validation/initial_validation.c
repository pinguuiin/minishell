/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 08:20:17 by donheo            #+#    #+#             */
/*   Updated: 2025/06/20 10:54:37 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_quotes(const char *cmd)
{
	int	in_single;
	int	in_double;
	int	i;

	in_single = 0;
	in_double = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (cmd[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (!in_single && !in_double);
}

static int	validate_after_operator(const char *cmd)
{
	const char	*first_operator;

	first_operator = cmd;
	cmd++;
	if (*first_operator == *cmd)
		cmd++;
	while (*cmd == ' ' || *cmd == '\t')
		cmd++;
	if (*cmd == '|' || *cmd == '<' || *cmd == '>' || *cmd == '\0')
		return (0);
	return (1);
}

int	validate_redirections(const char *cmd)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (*cmd)
	{
		if (*cmd == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if ((*cmd) == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote \
				&& (*cmd == '>' || *cmd == '<'))
			if (!validate_after_operator(cmd))
				return (0);
		cmd++;
	}
	return (1);
}

int	validate_operations(const char *cmd, int expect_command)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	expect_command = 1;
	while (*cmd)
	{
		if (*cmd == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if ((*cmd) == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*cmd == '|' && !in_single_quote && !in_double_quote)
		{
			if (expect_command)
				return (0);
			expect_command = 1;
		}
		else if (*cmd == ' ' || *cmd == '\t')
			expect_command = 0;
		cmd++;
	}
	if (expect_command)
		return (0);
	return (1);
}

int	check_syntax_error(const char *cmd)
{
	if (is_empty_input(cmd))
		return (1);
	if (!validate_quotes(cmd))
	{
		ft_putstr_fd("unclosed quote\n", STDERR_FILENO);
		return (0);
	}
	if (!validate_redirections(cmd))
	{
		ft_putstr_fd("invalid redirection\n", STDERR_FILENO);
		return (0);
	}
	if (!validate_operations(cmd, 1))
	{
		ft_putstr_fd("invalid operator\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}
