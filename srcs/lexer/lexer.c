/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 18:47:38 by donheo            #+#    #+#             */
/*   Updated: 2025/07/01 17:35:45 by donheo           ###   ########.fr       */
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

static int	tokenize_word(const char *input, int i, t_info *info)
{
	t_token	*token;
	int		start_i;
	int		in_single_quote;
	int		in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	token = create_new_token(WORD, info);
	start_i = i;
	while (input[i])
	{
		update_quote_state(input[i], &in_single_quote, &in_double_quote);
		if (!is_token_breaker(input[i], in_single_quote, in_double_quote))
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

void	tokenize_elements(t_info *info)
{
	int		i;

	i = 0;
	while ((info->input)[i])
	{
		i = skip_spaces(info->input, i);
		if ((info->input)[i] == '<')
			i = tokenize_input(info->input, i, info);
		else if ((info->input)[i] == '>')
			i = tokenize_output(info->input, i, info);
		else if ((info->input)[i] == '|')
			i = tokenize_pipe(i, info);
		else
		{
			if ((info->input)[i] != '\0')
				i = tokenize_word(info->input, i, info);
		}
	}
}
