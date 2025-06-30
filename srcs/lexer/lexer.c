/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:47:38 by donheo            #+#    #+#             */
/*   Updated: 2025/06/30 08:46:45 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenize_input(const char *input, int i, t_info *info)
{
	t_token	*token;

	if (input[i + 1] == '<')
	{
		token = create_new_token(HEREDOC, info);
		append_token(&(info->tokens), token);
		return (i + 2);
	}
	else
	{
		token = create_new_token(IN, info);
		append_token(&(info->tokens), token);
		return (i + 1);
	}
}

static int	tokenize_output(const char *input, int i, t_info *info)
{
	t_token	*token;

	if (input[i + 1] == '>')
	{
		token = create_new_token(APPEND, info);
		append_token(&(info->tokens), token);
		return (i + 2);
	}
	else
	{
		token = create_new_token(OUT, info);
		append_token(&(info->tokens), token);
		return (i + 1);
	}
}

static int	tokenize_pipe(int i, t_info *info)
{
	t_token	*token;

	token = create_new_token(PIPE, info);
	append_token(&(info->tokens), token);
	return (i + 1);
}

static int	tokenize_word(const char *input, int i, t_info *info, int in_single_quote, int in_double_quote)
{
	t_token	*token;
	int		start_i;

	token = create_new_token(WORD, info);
	start_i = i;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!is_token_breaker(input[i], in_single_quote, in_double_quote))
			break ;
		i++;
	}
	token->value = aalloc(&info->arena, i - start_i + 1);
	if (!token->value)
		clean_and_exit("word token value");
	ft_strlcpy(token->value, &input[start_i], i - start_i + 1);
	append_token(&(info->tokens), token);
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
				i = tokenize_word(input, i, info, 0, 0);
		}
	}
}
