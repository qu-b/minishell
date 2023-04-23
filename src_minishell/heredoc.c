/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:29:03 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/21 22:54:01 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	read_loop(char **tmp_in, char **tmp_wrd, char *del)
{
	while (1)
	{
		*tmp_in = readline("> ");
		if (is_delimiter(*tmp_in, del) == 1)
			break ;
		*tmp_in = ft_strjoin_gnl(*tmp_in, "\n");
		*tmp_wrd = ft_strjoin_gnl(*tmp_wrd, *tmp_in);
		free(*tmp_in);
	}
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
		free(tmp_in);
		free(tmp_wrd);
		return (words);
	}
	read_loop(&tmp_in, &tmp_wrd, del);
	free(tmp_in);
	new_words = ft_split_inc(tmp_wrd, '\n');
	free(tmp_wrd);
	if (!words)
		return (new_words);
	out = ft_ptrjoin(words, new_words);
	free(tmp_wrd);
	return (out);
}

// creates /tmp/mini_heredoc file, writes **words to it
// prepares cmd->tmpfd for exec_main
int	heredoc_create(t_cmd *cmd, char **words)
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
	cmd->tmpfd = open("/tmp/mini_heredoc", O_RDONLY, 0644);
	return (0);
}

int	heredoc_main(t_token **tokens, t_cmd *cmd)
{
	char	*del;
	char	**words;
	int		nldel;

	nldel = 0;
	words = NULL;
	del = define_delimiter(tokens, &nldel);
	if (!del)
		return (-1);
	cmd->heredoc = 1;
	if (nldel)
		words = get_words(tokens, &del);
	if (!nldel)
		cmd->args = get_new_args(tokens, cmd);
	words = read_until_del(words, del, ft_strdup(""), ft_strdup(""));
	heredoc_create(cmd, words);
	ft_printf("remaining tokens:\n");
	print_tokens(*tokens);
	ft_printf("______\n");
	return (0);
}

int	heredoc(t_token **tokens, t_cmd *cmd)
{
	int	heredoc_pos;

	heredoc_pos = 0;
	heredoc_pos = heredoc_find(tokens, cmd);
	if (heredoc_pos)
	{	
		while (heredoc_pos-- > -1)
			(*tokens) = (*tokens)->next;
		if ((*tokens) && (*tokens)->type == WORD)
			return (heredoc_main(tokens, cmd));
		else
		{
			write(2, "heredoc error\n", 14);
			return (-1);
		}
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