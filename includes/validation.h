/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:18:49 by donheo            #+#    #+#             */
/*   Updated: 2025/06/22 21:26:21 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

void	is_heredoc_limit_exceeded(const char *input);
int		is_only_whitespaces(const char *input);
int		validate_quotes(const char *cmd);
int		validate_redirections(const char *cmd);
int		validate_operations(const char *input, \
	int expect_command, int in_single_quote, int in_double_quote);
int		check_syntax_error(const char *cmd);

#endif
