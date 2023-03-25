/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:32:10 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/25 05:16:33 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
DESCRIPTION

    The internal format of directories is unspecified.

    The <dirent.h> header defines the following data type through typedef:

    DIR
        A type representing a directory stream. 

    It also defines the structure dirent which includes the following members:


    ino_t  d_ino       file serial number
    char   d_name[]    name of entry

    The type ino_t is defined as described in <sys/types.h>.

    The character array d_name is of unspecified size, but the number of bytes preceding the terminating null byte will not exceed {NAME_MAX}.

    The following are declared as functions and may also be defined as macros. Function prototypes must be provided for use with an ISO C compiler.


    int            closedir(DIR *);
    DIR           *opendir(const char *);
    struct dirent *readdir(DIR *);
    int            readdir_r(DIR *, struct dirent *, struct dirent **);
    void           rewinddir(DIR *);
    void           seekdir(DIR *, long int);
    long int       telldir(DIR *);

	https://www.thegeekstuff.com/2012/01/linux-inodes/ :

	An Inode number points to an Inode. An Inode is a data structure that stores the following information about a file :

    Size of file
    Device ID
    User ID of the file
    Group ID of the file
    The file mode information and access privileges for owner, group and others
    File protection flags
    The timestamps for file creation, modification etc
    link counter to determine the number of hard links
    Pointers to the blocks storing file’s contents

https://opensource.apple.com/source/Libc/Libc-320/include/dirent.h.auto.html

./minishell cd /Users/krys/dev/42/09-minishell/dirtest
/Users/krys/dev/42/09-minishell/minishell_qubd/minishell
*/

// change dir if valid, returns full dir path
char	*ft_cd_change(char *path)
{
	char	*full_path;

	full_path = NULL;
	if (access(path, R_OK) < 0)
	{
		write(2, "Error : invalid path\n", 22);
		return (NULL);
	}
	// change dir here
	chdir(path);
	full_path = getcwd(full_path, 0);
	return (full_path);
}

// updates PWD and OLDPWD in env
int	ft_cd_update_env(t_export *cd, char **env, char **args)
{
	char	*cwd;
	char	*full_path;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	full_path = ft_cd_change(args[1]);
	if (full_path == NULL)
		return (-1);
	cd->new_env = ft_export_string(env, "PWD=", full_path);
	cd->new_env = ft_export_string(cd->new_env, "OLDPWD=", cwd);
	free(full_path);
	free(cwd);
	return (0);
}

char	**ft_cd(char **env, char **args)
{
	DIR 			*dir;
	struct dirent	*current;
	t_export		*cd;
	char			**new_env;

	if (!args || !*args || !env || !*env)
		return (env);
	cd = malloc(sizeof(cd));
	if (ft_cd_update_env(cd, env, args) < 0)
		return (env);
	new_env = ft_ptrdup_free(cd->new_env, ft_argcount(cd->new_env));
	if (new_env == NULL)
		return (env);
	(void) dir;
	(void) current;
	// dir = opendir(args[1]);
	// if (!dir)
	// 	return ;
	// current = readdir(dir);
	// while(current != NULL)
	// {
	// 	printf("dir name = %s\n", current->d_name);
	// 	printf("dir inode number =%llu\n", current->d_ino);
	// 	current = readdir(dir);
	// }
	// closedir(dir);
	return (new_env);
}
