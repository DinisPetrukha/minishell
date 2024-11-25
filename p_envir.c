/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_envir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:08:18 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/04 11:08:19 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	**set_pather(char **mat)
{
	int		i;
	char	**envir;

	i = 0;
	envir = NULL;
	while (mat[i])
	{
		if (ft_strncmp(mat[i], "PATH=", 5) == 0)
		{
			envir = ft_split(&(mat[i][6]), ':');
			break ;
		}
		i++;
	}
	return (envir);
}

//if no cmd RETURN NULL
char	*check_env(char **cmd)
{
	if (!(*cmd) || !(**cmd))
		return (NULL);
	if (!ft_strncmp(*cmd, "cd", 3))
		return (*cmd);
	if (!ft_strncmp(*cmd, "echo", 4))
		return (*cmd);
	if (!ft_strncmp(*cmd, "export", 7))
		return (*cmd);
	if (!ft_strncmp(*cmd, "unset", 6))
		return (*cmd);
	if (!ft_strncmp(*cmd, "env", 4))
		return (*cmd);
	if (!ft_strncmp(*cmd, "exit", 5))
		return (*cmd);
	if (access(*cmd, F_OK | R_OK | X_OK) != -1)
	{
		if (!check_dir(*cmd))
			return (NULL);
		return (*cmd);
	}
	return (NULL);
}

char	*check_dir(char *cmd)
{
	struct stat	st;

	if (!cmd)
		return (NULL);
	if (stat(cmd, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (NULL);
	}
	return (cmd);
}

char	*return_path(char *cmd, char **pather, char *path, int force)
{
	if (force == 1)
	{
		free(cmd);
		free_mat(pather);
		if (!check_dir(path))
		{
			if (*path)
				free(path);
			return (NULL);
		}
	}
	else if (force == 0)
	{
		if (pather)
			free_mat(pather);
	}
	else if (force == 2)
	{
		if ((*cmd) && !pather)
			free(cmd);
		else if (!(*cmd) && pather)
			free_mat(pather);
		return (NULL);
	}
	return (path);
}

char	*cmd_path(char *cmd, char **pather, int i)
{
	char	*path;

	path = check_env(&cmd);
	if (path)
		return (return_path(cmd, pather, path, 0));
	if (!(*cmd) || !pather)
		return (return_path(cmd, pather, path, 2));
	while (pather[i])
	{
		path = (ft_neostrjoin(pather[i], "/", 0));
		if (!path)
			return (ret_free(&cmd, pather));
		path = (ft_neostrjoin(path, cmd, 1));
		if (!path)
			return (ret_free(&cmd, pather));
		if (access(path, F_OK | R_OK | X_OK) != -1)
			return (return_path(cmd, pather, path, 1));
		else
			free(path);
		i++;
	}
	return (ret_free(&cmd, pather));
}
