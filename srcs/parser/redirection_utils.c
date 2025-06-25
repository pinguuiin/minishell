/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 03:33:45 by donheo            #+#    #+#             */
/*   Updated: 2025/06/25 18:39:44 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*allocate_and_connect_redir(t_info *info,t_cmd *cmd)
{
	t_redir	*new_redir;
	t_redir	*temp;
	if (!cmd->redirection)
	{
		cmd->redirection = alloc(&(info->arena), sizeof(t_redir));
		if(!cmd->redirection)
			clean_and_exit("memory allocation fails for new cmd redir");
		new_redir = cmd->redirection;
	}
	else
	{
		temp = cmd->redirection;
		new_redir = alloc(&(info->arena), sizeof(t_redir));
		if(!new_redir)
			clean_and_exit("memory allocation fails for cmd redir");
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_redir;
	}
	return (new_redir);
}

char	*allocate_and_copy_env_name(const char *value, int i, t_info *info)
{
	int		start_i;
	char	*env_name;

	start_i = i;
	while (ft_isalnum(value[i]) || value[i] == '_')
		i++;
	env_name = aalloc(&(info->arena), i - start_i + 2);
	if (!env_name)
		clean_and_exit("memory allocation fails for env name");
	strlcpy(env_name, &value[start_i], i - start_i + 2);
	return (env_name);
}

int	calculate_total_len_of_char(char *value)
{
	int	i;
	int	total_len;
	int	in_double_quote;
	int	in_single_quote;

	i = 0;
	total_len = 0;
	in_double_quote = 0;
	in_single_quote = 0;
	while(value[i])
	{
		if (value[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (value[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && value[i] == '$' && (ft_isalnum(value[i + 1]) || value[i + 1] == '_'))
		{
			i -= calculate_env_len(value, i + 1, &total_len);
			continue;
		}


		i++;
	}

}

char	*expand_value(char *value, char *file)
{
	int	total_len;

	total_len = calculate_total_len_of_char(value);





	remove_quotes(file);
}
