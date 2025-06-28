/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:47:38 by donheo            #+#    #+#             */
/*   Updated: 2025/06/28 21:20:16 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenize_input(const char *input, int i, t_info *info)
{
	t_token	*token;

	token = aalloc(&(info->arena), sizeof(t_token));
	token->value = NULL;
	if (!token)
		clean_and_exit("input token");
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

static int	tokenize_output(const char *input, int i, t_info *info)
{
	t_token	*token;

	token = aalloc(&(info->arena), sizeof(t_token));
	token->value = NULL;
	if (!token)
		clean_and_exit("output token");
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

static int	tokenize_pipe(int i, t_info *info)
{
	t_token	*token;

	token = aalloc(&(info->arena), sizeof(t_token));
	token->value = NULL;
	if (!token)
		clean_and_exit("pipe token");
	token->type = PIPE;
	connect_tokens(&(info->tokens), token);
	return (i + 1);
}

static int	tokenize_cmd(const char *input, int i, t_info *info, int in_single_quote, int in_double_quote)
{
	t_token	*token;
	int		start_i;

	start_i = i;
	token = aalloc(&(info->arena), sizeof(t_token));
	if (!token)
		clean_and_exit("cmd token");
	token->type = CMD;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = in_double_quote;
		else if (!is_token_boundary(input[i], in_single_quote, in_double_quote))
			break ;
		i++;
	}
	token->value = aalloc(&info->arena, i - start_i + 1);
	if (!token->value)
		clean_and_exit("cmd token value");
	ft_strlcpy(token->value, &input[start_i], i - start_i + 1);
	connect_tokens(&(info->tokens), token);
	return (i);
}

void	tokenize_elements(const char *input)
{
	int		i;
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
				i = tokenize_cmd(input, i, info, 0, 0);
		}
	}
}
