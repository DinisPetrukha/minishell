/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpetrukh <dpetrukh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 09:35:16 by dpetrukh          #+#    #+#             */
/*   Updated: 2024/10/06 15:25:55 by dpetrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	cd_too_many(char **mat, int tofree)
{
	if (mat[1] && mat[2])
	{
		if (tofree)
			free_mat(mat);
		ft_putstr_fd("cd: too many arguments\n", 2);
		s_sts(1);
		return (1);
	}
	return (0);
}

int	b_cd(char **mat, int tofree, t_lexer *lexer)
{
	char	*path;

	if (cd_too_many(mat, tofree))
		return (1);
	if (mat[1] == NULL || !strncmp(mat[1], "~", 2) || !strncmp(mat[1], "~/", 3))
	{
		path = ft_getenv(lexer->env, "HOME");
		if (path)
			chdir(path);
		else
			ft_putstr_fd("cd: HOME not set\n", 2);
		free(path);
	}
	else if (chdir(mat[1]) == -1)
	{
		if (tofree)
			free_mat(mat);
		ft_putstr_fd("cd: No such file or directory\n", 2);
		s_sts(1);
		return (1);
	}
	if (tofree)
		free_mat(mat);
	return (0);
}
