/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:18:49 by donheo            #+#    #+#             */
/*   Updated: 2025/07/02 11:32:02 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

typedef struct s_info	t_info;

int		is_all_whitespace(const char *input);
int		has_balanced_quotes(const char *cmd);
void	update_quote_state(const char c, \
int *in_single_quote, int *in_double_quote);
void	print_syntax_error(char error_char, t_info *info);
int		has_syntax_error(char *input, t_info *info);

#endif
