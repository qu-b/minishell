#include "minishell.h"

char	*define_delimiter(t_token **tokens)
{
	t_token	*head;
	char	*del;
	int		nl;

	head = *tokens;
	nl = ft_strchr_idx(head->value, '\n');
	if (nl <= 0)
	{
		write(2, "heredoc error\n", 14);
		return (NULL);
	}
	del = ft_substr(head->value, 0, nl);
	head->value += nl;
	return (del);
}

int	find_delimiter(char *s, char *del)
{
	int	i;
	int	dlen;
	int	slen;

	if (!del)
		return (-1);
	dlen = ft_strlen(del);
	slen = ft_strlen(s);
	i = -1;
	while (s[++i] && i < slen - dlen + 1)
	{
		if (ft_strncmp(&s[i], del, dlen) == 0)
			return (i);
	}
	return (-1);
}

char	*read_to_buf(int fd, char *del, int *delpos)
{
	char	*buf;
	char	*out;
	int		eof;

	eof = 1;
	out = ft_strdup("");
	buf = malloc(sizeof(char) * (ft_strlen(del) + 1));
	if (!buf)
		return (NULL);
	while (eof > 0)
	{
		eof = read(fd, buf, ft_strlen(del));
		if (eof < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[eof] = '\0';
		out = ft_strjoin_gnl(out, buf);
		*delpos = find_delimiter(out, del);
		if (*delpos >= 0)
			break ;
	}
	free(buf);
	return (out);
}

char	*get_del(int fd, char *del, char *s)
{
	// char	*s;
	char	*out;
	int		delpos;

	if(fd < 0 || !del)
		return (NULL);
	delpos = 0;
	// out = read_to_buf(fd, del, &delpos);
	// if (delpos == -1)
	// {
	// 	free(out);
	// 	return (NULL);
	// }
	delpos = find_delimiter(s, del);
	if (delpos == -1)
		return (NULL);
	out = ft_substr(s, delpos, ft_strlen(s) - delpos);
	// out[delpos] = 0x00;
	return (out);
}
