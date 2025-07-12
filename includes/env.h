/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piyu <piyu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:21:58 by donheo            #+#    #+#             */
/*   Updated: 2025/07/12 03:57:08 by piyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

struct					s_info;
typedef struct s_info	t_info;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		count_envp(char **envp);
char	**copy_envp_entries(char **envp, char **env_arr, \
int envp_count, t_info *info);
char	**copy_envp(char **envp, t_info *info);
t_env	*envp_to_list(char	**envp, t_arena **arena);

#endif
