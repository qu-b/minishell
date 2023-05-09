/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:06:51 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/09 17:29:11 by fcullen          ###   ########.fr       */
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

// Glues arguments in a visually appealing fashion and returns the result
char	*glue_prompt(char *wd, char *user)
{
	char	*ps1;

	ps1 = ft_strdup("");
	ps1 = ft_strjoin_gnl(ps1, "\033[1;32m");
	ps1 = ft_strjoin_gnl(ps1, "minishell");
	ps1 = ft_strjoin_gnl(ps1, ":\033[0m");
	ps1 = ft_strjoin_gnl(ps1, wd);
	ps1 = ft_strjoin_gnl(ps1, " ");
	if (wd[0] != 0x00)
	ps1 = ft_strjoin_gnl(ps1, " ");
	ps1 = ft_strjoin_gnl(ps1, user);
	ps1 = ft_strjoin_gnl(ps1, "$ ");
	free(wd);
	if (ps1 == NULL)
		return (NULL);
	return (ps1);
}

// Returns 1 if any of the arguments is NULL
int	check_prompt(char *wd, char *user)
{
	static int	err = 0;

	if (wd == NULL)
	{
		if (err == 0)
			write(2, "Prompt error : invalid wd\n", 26);
		err = 1;
		return (1);
	}
	if (user == NULL)
	{
		if (err == 0)
			write(2, "Prompt error : invalid user\n", 28);
		err = 2;
		return (2);
	}
	err = 0;
	return (0);
}

// Returns the prompt string
// "$WD $USER$ "
char	*prompt(void)
{
	char		*wd;
	char		*user;

	wd = NULL;
	user = NULL;
	wd = get_wd();
	user = ft_getenv(g_data->env, "USER");
	if (check_prompt(wd, user) == 1)
		return (NULL);
	if (check_prompt(wd, user) == 2)
		return (glue_prompt(wd, "> "));
	return (glue_prompt(wd, user));
}
