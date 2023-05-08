/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/13 16:49:09 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Get working directory's name
char	*get_wd(void)
{
	char	*wd;
	char	*last_slash;
	char	*last_dir;

	wd = getcwd(NULL, 0);
	if (wd == NULL)
		return (NULL);
	last_slash = ft_strrchr(wd, '/');
	if (last_slash == NULL)
		last_dir = ft_strdup(wd);
	else
		last_dir = ft_strdup(last_slash + 1);
	if (last_dir == NULL)
	{
		free(wd);
		return (NULL);
	}
	free(wd);
	return (last_dir);
}

// "$HOSTNAME:$WD $USER$ "
char	*prompt(void)
{
	char	*wd;
	char	*ps1;

	wd = get_wd();
	if (wd == NULL)
	{
		perror("get_wd");
		return (NULL);
	}
	ps1 = ft_strjoin_gnl(wd, "$ ");
	if (ps1 == NULL)
	{
		perror("ft_strdup");
		free(wd);
		return (NULL);
	}
	return (ps1);
}

int	minishell(void)
{
	char	*ps1;

	sig_acccept();
	while (g_data->input != NULL)
	{
		ps1 = prompt();
		g_data->input = readline(ps1);
		free(ps1);
		if (!g_data->input)
			break ;
		add_history(g_data->input);
		if (parser(g_data->input))
			write(2, "Command Error\n", 14);
		else if (executor())
		{
			free_tokens(&g_data->tokens);
			free(g_data->input);
			return (1);
		}
		free_tokens(&g_data->tokens);
		free(g_data->input);
	}
	return (0);
}
