/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:24:23 by donheo            #+#    #+#             */
/*   Updated: 2025/06/22 14:30:51 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_input(const char *input, int i, t_info *info)
{
	t_token	*token;

	token = aalloc(&(info->arena), sizeof(t_token));
	token->value = NULL;
	if (!token)
		clean_and_exit("fails memory allocation for input token");
	if (input[i + 1] == '<')
	{
		token->type = HEREDOC;
		connect_tokens(&(info->tokens), token);
		return (i + 2);
	}
	else
	{
		token->type = IN;
		connect_tokens(&(info->tokens), token);
		return (i + 1);
	}
}

int	tokenize_output(const char *input, int i, t_info *info)
{
	t_token	*token;

	token = aalloc(&(info->arena), sizeof(t_token));
	token->value = NULL;
	if (!token)
		clean_and_exit("fails memory allocation for output token");
	if (input[i + 1] == '>')
	{
		token->type = APPEND;
		connect_tokens(&(info->tokens), token);
		return (i + 2);
	}
	else
	{
		token->type = OUT;
		connect_tokens(&(info->tokens), token);
		return (i + 1);
	}
}

int	tokenize_pipe(const char *input, int i, t_info *info)
{
	t_token	*token;

	token = aalloc(&(info->arena), sizeof(t_token));
	token->value = NULL;
	if (!token)
		clean_and_exit("fails memory allocation for pipe token");
	token->type = PIPE;
	connect_tokens(&(info->tokens), token);
	return (i + 1);
}

void	check_token_type(const char *input, int i, t_token *token)
{
	if (input[i] == '$')
	{
		while ()
	}
}

int	tokenize_cmd(const char *input, int i, t_info *info, int in_single_quote, int in_double_quote)
{
	t_cmd_type	cmd_type;
	t_token		*token;

	cmd_type.start_i = i;
	token = aalloc(&(info->arena), sizeof(t_token));
	if (!token)
		clean_and_exit("fails memory allocation for pipe token");
	check_token_type(input, i, token);
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if ((input[i] == ' ' || input[i] == '\t') && !in_single_quote &&
		!in_double_quote)
			break;
		i++;
	}
	ft_strlcpy();

}

void	tokenize_elements(const char *input, t_info *info)
{
	int	i;

	i = 0;
	while (input[i])
	{
		i = skip_spaces(input, i, info);
		if (input[i] == '<')
			i = tokenize_input(input, i, info);
		else if (input[i] == '>')
			i = tokenkize_output(input, i, info);
		else if (input[i] == '|')
			i = tokenize_pipe(input, i, info);
		else
			i = tokenize_cmd(input, i, info, 0, 0);
	}
}
