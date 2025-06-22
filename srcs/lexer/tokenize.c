/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:24:23 by donheo            #+#    #+#             */
/*   Updated: 2025/06/22 16:34:04 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_input(const char *input, int i, t_info *info)
{
	t_token	*token;

	token = aalloc(&(info->arena), sizeof(t_token));
	token->value = NULL;
	if (!token)
		clean_and_exit("memory allocation failed for input token");
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
		clean_and_exit("memory allocation failed for output token");
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

int	tokenize_pipe(int i, t_info *info)
{
	t_token	*token;

	token = aalloc(&(info->arena), sizeof(t_token));
	token->value = NULL;
	if (!token)
		clean_and_exit("memory allocation failed for pipe token");
	token->type = PIPE;
	connect_tokens(&(info->tokens), token);
	return (i + 1);
}

static void	get_token_type_and_value(const char *input, \
	t_cmd_type *cmd_type, t_token *token, t_info *info)
{
	cmd_type->in_double_quote = 0;
	cmd_type->in_single_quote = 0;
	cmd_type->i = cmd_type->start_i;
	token->value = aalloc(&info->arena, \
		cmd_type->end_i - cmd_type->start_i + 2);
	if (!token->value)
		clean_and_exit("memory allocation failed for cmd token value");
	while (cmd_type->i <= cmd_type->end_i)
	{
		if (input[cmd_type->i] == '\'' && !cmd_type->in_double_quote)
			set_quote_and_word(&(cmd_type->in_single_quote), cmd_type);
		else if (input[cmd_type->i] == '"' && !cmd_type->in_single_quote)
			set_quote_and_word(&(cmd_type->in_double_quote), cmd_type);
		else if (input[cmd_type->i] == '$' && !cmd_type->in_single_quote)
			cmd_type->i = skip_env_name(input, cmd_type);
		else
			cmd_type->has_word = 1;
		(cmd_type->i)++;
	}
	if (cmd_type->has_env && cmd_type->has_word)
		token->type = WORD_WITH_ENV;
	else if (cmd_type->has_env)
		token->type = ENV_VAR;
	else
		token->type = WORD;
}

int	tokenize_cmd(const char *input, int i, t_info *info)
{
	t_cmd_type	cmd_type;
	t_token		*token;

	ft_memset(&cmd_type, 0, sizeof(t_cmd_type));
	cmd_type.start_i = i;
	token = aalloc(&(info->arena), sizeof(t_token));
	if (!token)
		clean_and_exit("memory allocation failed for cmd token");
	while (input[i])
	{
		if (input[i] == '\'' && !cmd_type.in_double_quote)
			cmd_type.in_single_quote = !cmd_type.in_single_quote;
		else if (input[i] == '"' && !cmd_type.in_single_quote)
			cmd_type.in_double_quote = !cmd_type.in_double_quote;
		else if ((input[i] == ' ' || input[i] == '\t') && \
		!cmd_type.in_single_quote && !cmd_type.in_double_quote)
			break ;
		i++;
	}
	cmd_type.end_i = i - 1;
	get_token_type_and_value(input, &cmd_type, token, info);
	ft_strlcpy(token->value, &input[cmd_type.start_i], \
		cmd_type.end_i - cmd_type.start_i + 2);
	connect_tokens(&(info->tokens), token);
	return (i);
}
