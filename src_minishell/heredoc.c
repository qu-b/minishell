/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:29:03 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/16 22:45:58 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_heredoc(t_cmd *cmd, pid_t pid_i, char *doc)
{
	int tmpfd;

	(void) pid_i;
	(void) doc;
	tmpfd = open("/tmp/heredoclol", O_RDONLY, 0644);
	exec_bin(cmd, g_data->env, pid_i, tmpfd);
	close(tmpfd);
	// char buf[100];
	// ft_printf("tmpfd = %d\n", cmd->tmpfd);
	// read(cmd->tmpfd, buf, 10);
	// ft_printf("buf: [%s]\n", buf);
	return (1);
}

void	del_token(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	(*tokens) = (*tokens)->next;
	if (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		// and smth else probably
	}
}

int	heredoc(t_token **tokens, t_cmd *cmd, pid_t pid_i)
{
	char	*del;
	char	*doc;
	char	*words;
	int		tmpfd;

	if ((*tokens) && (*tokens)->type == IO && ft_strncmp((*tokens)->value, "<<", 2) == 0)
	{
		del_token(tokens);
		if ((*tokens) && (*tokens)->type == WORD)
		{
			del = NULL;
			words = get_word_string(tokens, &del);
			// ft_printf("del: [%s]\n", del);
			// ft_printf("(*tokens)->value: [%s]\n", (*tokens)->value);
			doc = delimit(words, del);
			cmd->heredoc = 1;
			if (!words || !del || !doc)
			{
				write(2, "heredoc error\n", 14);
				return (-1);
			}
			// ft_printf("doc: [%s]\n", doc);
			ft_printf("remaining tokens:\n");
			print_tokens(*tokens);
			ft_printf("______\n");
			tmpfd = open("/tmp/heredoclol", O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (tmpfd == -1)
				return (-1);
			write(tmpfd, doc, ft_strlen(doc));
			close(tmpfd);
			exec_heredoc(cmd, pid_i, doc);
			return (0);
		}
		else
			write(2, "heredoc error\n", 14);
	}
	return (0);
}

/*

cat << EOF
helloooooo ooooooooo
yesthis iiiiiiiiiii
a line
EOF
hihi from the other side
ls | cat -e | cat -e | cat -e | cat -e

*/