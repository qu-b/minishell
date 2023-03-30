/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:14:07 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/30 16:03:32 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parser(t_data **data, char *input)
{
	t_token	*head;

	if (!lexer(&head, input))
		process_tokens(head);
	else
	{
		write(2, "Command Error\n", 14);
		return (1);
	}
	print_tokens(head);
	(*data)->tokens = head;
	return (0);
}
