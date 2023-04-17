/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:29:03 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/17 09:27:52 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_heredoc(t_cmd *cmd, pid_t pid_i)
{
	int tmpfd;

	tmpfd = open("/tmp/mini_heredoc", O_RDONLY, 0644);
	exec_bin(cmd, g_data->env, pid_i, tmpfd);
	close(tmpfd);
	return (1);
}

char	**read_until_del(char **words, char *del, char *tmp_in, char *tmp_wrd)
{
	char	**out;
	char	**new_words;
	int		argnb;

	argnb = ft_argcount(words);
	if (words && is_delimiter(words[argnb - 1], del) == 1)
	{
		free(words[argnb - 1]);
		words[argnb - 1] = NULL;
		return (words);
	}
	while (1)
	{
		tmp_in = readline("> ");
		if (is_delimiter(tmp_in, del) == 1)
		{
			free(tmp_in);
			break ;
		}
		tmp_in = ft_strjoin_gnl(tmp_in, "\n");
		tmp_wrd = ft_strjoin_gnl(tmp_wrd, tmp_in);
		free(tmp_in);
	}
	new_words = ft_split_inc(tmp_wrd, '\n');
	if (!words)
		return (new_words);
	out = ft_ptrjoin(words, new_words);
	free(tmp_wrd);
	return (out);
}

int	heredoc_create_file(char **words)
{
	int		tmpfd;
	int		i;

	tmpfd = open("/tmp/mini_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmpfd < 0)
		return (-1);
	i = 0;
	while (words[i])
	{
		write(tmpfd, words[i], ft_strlen(words[i]));
		i++;
	}
	close(tmpfd);
	return (0);
}

char	**get_new_args(t_token **tokens, char *s)
{
	char	**new_args;
	t_token	*head;
	int		i;

	i = 0;
	head = *tokens;
	while (head && head->type == WORD)
	{
		i++;
		head = head->next;
	}
	new_args = malloc(sizeof(char *) * (i + 3));
	new_args[0] = ft_strdup(s);
	i = 1;
	while ((*tokens) && (*tokens)->type == WORD)
	{
		if (!(*tokens)->value)
			break ;
		new_args[i] = ft_strtrim((*tokens)->value, " ");
		(*tokens) = (*tokens)->next;
		i++;
	}
	new_args[i] = NULL;
	return (new_args);
}

int	heredoc(t_token **tokens, t_cmd *cmd, pid_t pid_i)
{
	char	*del;
	char	**words;
	int		nldel;

	if ((*tokens) && (*tokens)->type == IO && \
	ft_strncmp((*tokens)->value, "<<", 2) == 0)
	{
		nldel = 0;
		del_token(tokens);
		if ((*tokens) && (*tokens)->type == WORD)
		{
			words = NULL;
			del = define_delimiter(tokens, &nldel);
			if (!del)
				return (-1);
			cmd->heredoc = 1;
			if (nldel)
				words = get_words(tokens, &del);
			if (!nldel)
				cmd->args = get_new_args(tokens, cmd->args[0]);
			words = read_until_del(words, del, ft_strdup(""), ft_strdup(""));
			heredoc_create_file(words);
			exec_heredoc(cmd, pid_i);
			(void) pid_i;
			return (0);
		}
		else
			write(2, "heredoc error\n", 14);
	}
	return (0);
}

/*

cat << EOF
hello asd
yesthis is
a line

EOF
hihi from the other side

ls | cat -e | cat -e | cat -e | cat -e

			// ft_printf("del: [%s]\nwords: [%s]\n", del, words);
			// ft_printf("remaining tokens:\n");
			// print_tokens(*tokens);
			// ft_printf("______\n");
*/