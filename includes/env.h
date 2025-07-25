/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:21:58 by donheo            #+#    #+#             */
/*   Updated: 2025/07/15 01:01:21 by donheo           ###   ########.fr       */
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
int envp_count, t_arena *arena);
char	**copy_envp(char **envp, t_arena *arena);
t_env	*envp_to_list(char	**envp, t_arena **arena);

#endif
