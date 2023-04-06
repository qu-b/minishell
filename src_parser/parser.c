/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:14:07 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/06 06:57:32 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parser(char *input)
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
	// (*data)->tokens = head;
	g_data->tokens = head;
	return (0);
}
