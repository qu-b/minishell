/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:06:51 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/10 11:34:16 by kpawlows         ###   ########.fr       */
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
	if (last_dir[0] == 0x00)
	{
		free(last_dir);
		return (ft_strdup("/"));
	}
	return (last_dir);
}

// Glues arguments in a visually appealing fashion and returns the result
char	*glue_prompt(char *wd, char *user, char *add)
{
	char	*ps1;

	(void) add;
	ps1 = ft_strdup("");
	ps1 = ft_strjoin_gnl(ps1, "\033[1;32mminishell:\033[0m");
	ps1 = ft_strjoin_gnl(ps1, wd);
	ps1 = ft_strjoin_gnl(ps1, " ");
	if (user != NULL)
	{
		ps1 = ft_strjoin_gnl(ps1, user);
		ps1 = ft_strjoin_gnl(ps1, "$ ");
	}
	if (add != NULL)
		ps1 = ft_strjoin_gnl(ps1, add);
	free(wd);
	free(user);
	if (ps1 == NULL)
		return (NULL);
	return (ps1);
}

// Checks wd and user
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
		return (glue_prompt(wd, NULL, "> "));
	return (glue_prompt(wd, user, NULL));
}
