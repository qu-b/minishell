/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:06:51 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/08 21:07:12 by kpawlows         ###   ########.fr       */
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

// Frees the arguments
void	free_prompt(char *hostname, char *wd, char *user)
{
	if (hostname != NULL)
		free(hostname);
	if (wd != NULL)
		free(wd);
	(void) user;
	// if (user != NULL) why does this fail?
	// 	free(user);
}

// Glues arguments in a visually appealing fashion and returns the result
char	*glue_prompt(char *hostname, char *wd, char *user)
{
	char	*ps1;

	(void) hostname;
	// ps1 = ft_strjoin(hostname, ":");
	ps1 = ft_strdup("placeholder:");
	ps1 = ft_strjoin_gnl(ps1, wd);
	ps1 = ft_strjoin_gnl(ps1, " ");
	ps1 = ft_strjoin_gnl(ps1, user);
	ps1 = ft_strjoin_gnl(ps1, "$ ");
	free_prompt(hostname, wd, user);
	if (ps1 == NULL)
		return (NULL);
	return (ps1);
}

// Returns 1 if any of the arguments is NULL
int	check_prompt(char *hostname, char *wd, char *user)
{
	(void) hostname;
	int	err;

	err = 0;
	if (hostname == NULL)
	{
		perror("no hostname");
		// err++;
	}
	if (wd == NULL)
	{
		perror("no wd");
		err++;
	}
	if (user == NULL)
	{
		perror("no user");
		err++;
	}
	if (err)
		return (1);
	return (0);
}

// "$HOSTNAME:$WD $USER$ "
char	*prompt(void)
{
	char	*wd;
	char	*user;
	char	*hostname;

	wd = get_wd();
	user = ft_getenv(g_data->env, "USER");
	hostname = ft_getenv(g_data->env, "HOSTNAME");
	if (check_prompt(hostname, wd, user) == 1)
	{
		free_prompt(hostname, wd, user);
		return (NULL);
	}
	// printf("user = %s\n", user);
	return (glue_prompt(hostname, wd, user));
}