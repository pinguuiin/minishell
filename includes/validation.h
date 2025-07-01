/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donheo <donheo@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 22:18:49 by donheo            #+#    #+#             */
/*   Updated: 2025/07/01 05:57:45 by donheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

int		is_all_whitespace(const char *input);
int		has_balanced_quotes(const char *cmd);
void	update_quote_state(const char c, \
	int *in_single_quote, int *in_double_quote);
int		has_syntax_error(const char *cmd);

#endif
